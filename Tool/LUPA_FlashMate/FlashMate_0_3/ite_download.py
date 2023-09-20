import os
import serial.tools.list_ports
import time
import sys
import struct
import threading
from sys import argv
from os.path import getsize

# Ite Download Tool version
IDT_VERSION_MAJOR = 0
IDT_VERSION_MINOR = 2

LDB_VERSION_MAJOR = 0
LDB_VERSION_MINOR = 5

MAX_HEADER_LEN = 8
MAX_PACKET_LEN = 128

ver = 0
curr = 0
percentage = 0

excluded_files = ["genffs", "system_1.nsic", "ite_download.exe", "ldb.py", "ite_download.py", "kproc.sys"]

def LUPA_VERSION(major, minor):
    return (major << 8) | minor

def send_start_packet(tty):
    buf = b'\x01\x02\x4c\x44\x42\x0a\x03\x04'

    while 1:
        if len(tty.read(1024)) == 0:
            break

    tty.write(buf)
    time.sleep(0.1)

def set_version_dependencies(version):
    global ver
    global MAX_PACKET_LEN

    ver = version
    if ver >= LUPA_VERSION(0, 4):
        MAX_PACKET_LEN = 512
    elif ver >= LUPA_VERSION(0, 3):
        MAX_PACKET_LEN = 1024

def send_command(prefix, len):
    command = bytes(prefix, encoding='UTF-8')
    values = (command, len)
    fmt = '>4s I'
    header = struct.Struct(fmt);
    buf = header.pack(*values)
    tty.write(buf)

def send_payload(payload, len):
    buf = bytes(payload, encoding='UTF-8')
    tty.write(buf)

def show_progress(size, total, callback):
    global curr, percentage

    curr += size
    percentage = int(curr / total * 100)
    if callback is None:
        print('\r%d/%d (%d%%)'%(curr, total, percentage), end='', flush=True)
    if curr >= total:
        curr = 0
        percentage = 100
        if callback is None:
            print()
    if callback is not None:
        callback(percentage)

def send_file(filename, size, callback):
    global curr

    curr = 0
    remain = size
    file = open(filename, 'rb')

    while remain:
        if ver == LUPA_VERSION(0, 0):
            offset = size - remain
        else :
            buf = receive_packet(tty, 4)
            if len(buf) != 4:
                break
            offset = int.from_bytes(buf, byteorder='big')
        if offset & (1 << (32-1)):
            offset -= 1 << 32
        if offset == -1 or offset > size:
            if callback is None:
                print()
            break
        file.seek(offset)
        remain = size - offset
        data = file.read(MAX_PACKET_LEN)
        if not data:
            break
        tty.write(data)
        remain -= len(data)
        if curr != offset:
            curr = offset
        show_progress(len(data), size, callback)
    file.close()

def send_shell_command(command, read_echo):
    global tty

    command += '\n'
    for i in range(0, len(command)):
        tty.write(bytes(command[i], encoding='UTF-8'))
        if read_echo == True:
            tty.read(1)

    if command == 'reboot\n':
        print('exit: system reboot by user')
        exit()

def receive_packet(tty, size):
    timeout = 100
    buf = b''
    remain = size
    while remain:
        buf += tty.read(remain)
        if len(buf) > 0:
            # reset timeout
            timeout = 100
        remain = size - len(buf)
        timeout -= 1
        if timeout == 0:
            break
    return buf

def init_tty(port_name):
    if sys.platform.startswith('win'):
        import serial
        try:
            port = serial.Serial(port=port_name, baudrate=115200, timeout=0.1)
        except serial.SerialException:
            print('Can\'t open', port_name)
            exit()
    else:
        import termios
        try:
            port = open(port_name, mode='rb+', buffering=0)
        except FileNotFoundError:
            print('Can\'t open', port_name)
            exit()
        attrs = termios.tcgetattr(port)
        attrs[0] = termios.IGNPAR
        attrs[1] = 0
        attrs[3] = 0
        # input speed
        attrs[4] = termios.B115200
        # output speed
        attrs[5] = termios.B115200
        attrs[6][termios.VMIN] = 0
        attrs[6][termios.VTIME] = 1

        termios.tcflush(port, termios.TCIFLUSH)
        termios.tcsetattr(port,termios.TCSANOW,attrs)

    #send_start_packet(port)
    return port

def receive_response():
    buf = receive_packet(tty, MAX_HEADER_LEN)
    if len(buf) != MAX_HEADER_LEN:
        print('Error :', 'No response from target.' if len(buf) == 0 else 'Invalid packet length.')
        send_command('QUIT', 0)
        tty.close()
        exit()
    header = struct.unpack('>4s I', buf)
    prefix = header[0]
    info = header[1]
    try:
        if prefix.decode('utf-8') == 'OKAY' or prefix.decode('utf-8') == 'DATA':
            return prefix, info
        elif prefix.decode('utf-8') == 'FAIL':
            errno = header[1]
            if errno == 0:
                print('Operation failed : Unknown error')
            else:
                print('Operation failed :', os.strerror(errno))
            send_command('QUIT', 0)
            receive_response()
            tty.close()
            exit()
        elif prefix.decode('utf-8') == 'WAIT':
            return receive_response()
        elif prefix.decode('utf-8') == 'EMSG':
            buf = receive_packet(tty, header[1])
            print('Error :', buf.decode('utf-8'))
            send_command('QUIT', 0)
            receive_response()
            tty.close()
            exit()
    except UnicodeDecodeError:
        print('Error : Invalid packet data')
        send_command('QUIT', 0)
        tty.close()
        exit()
    return prefix, info

def receive_buffer(size):
    buffer = ''
    while size:
        data = receive_packet(tty, MAX_PACKET_LEN if size >= MAX_PACKET_LEN else size)
        buffer += data.decode('utf-8')
        size -= len(data)
    return buffer

def change_baudrate(port_name, baudrate):
    if sys.platform.startswith('win'):
        import serial
        global tty
        time.sleep(0.01)
        tty.baudrate = baudrate
    else:
        import termios
        time.sleep(0.01)
        attrs = termios.tcgetattr(tty)
        if baudrate == 921600:
            # input speed
            attrs[4] = termios.B921600
            # output speed
            attrs[5] = termios.B921600
        elif baudrate == 460800:
            # input speed
            attrs[4] = termios.B460800
            # output speed
            attrs[5] = termios.B460800
        else:
            # input speed
            attrs[4] = termios.B115200
            # output speed
            attrs[5] = termios.B115200
        termios.tcsetattr(tty,termios.TCSANOW,attrs)
    time.sleep(0.01)

def process_shell_command(port_name, command):
    buffer = []
    global tty
    tty = init_tty(port_name)

    #print(command);
    send_command('OPEN', 0)
    prefix, ver = receive_response()
    set_version_dependencies(ver)

    if ver >= LUPA_VERSION(0, 2):
        if command is None:
            size = 0
        else:
            size = len(command)

        send_command('SHEL', size)
        receive_response()

        if command is None:
            lastcmd = ''
            e = threading.Event()
            t = threading.Thread(target=shell_rx_thread, args=(e,))
            t.start()
            time.sleep(0.1)

            try:
                while 1:
                    ch = shell_getch()
                    if ord(ch) == 0x3:
                        raise KeyboardInterrupt
                    tty.write(bytes(ch, encoding='UTF-8'))
                    if ord(ch) == 0xd or ord(ch) == 0xa:
                        if lastcmd == 'exit':
                            raise KeyboardInterrupt
                        if lastcmd.startswith('reboot') == True:
                            e.set()
                            time.sleep(0.1)
                            print('exit: system reboot by user')
                            exit()
                        lastcmd = ''
                    elif ord(ch) == 0x8 or ord(ch) == 0x7f:
                        lastcmd = lastcmd[:-1]
                    else:
                        lastcmd = lastcmd + ch

            except KeyboardInterrupt:
                e.set()
                time.sleep(0.1)
                if lastcmd != 'exit':
                    send_shell_command('exit', False)

        else:
            send_shell_command(command, True)
            while 1:
                if command == 'prof':
                    time.sleep(1)
                elif len(command) > 4 and command[0:4] == 'prof':
                    cmd_d_s = command.split()
                    if cmd_d_s[1] == '-s':
                        time.sleep(int(cmd_d_s[2])/1000)
                    elif cmd_d_s[3] == '-s':
                        time.sleep(int(cmd_d_s[4])/1000)

                time.sleep(0.5)
                #read command output
                text = tty.read(1024)
                #debug log
                #print(text)

                if command is None:
                    print(text.decode('utf-8'), end='', flush=True)

                if len(text) == 0:
                    break
                buffer.append(text.decode('utf-8', errors='ignore'))

                if command == "fs mount /dev/mtd2 /data ltffs":
                    time.sleep(4)

                #if command == "fs umount /system" or command == "fs umount /font":
                    #flag = text.startswith(b'umount failed', 0, 10)
                    #if flag is True:
                        #umount_flag = 1
                    
                #time.sleep(4)
                
            if command is not None:
                buffer = ''.join(buffer)

        send_command('QUIT', 0)
        receive_response()

    elif ver == LUPA_VERSION(0, 1):
        if command is None:
            size = 0
        else:
            size = len(command)

        send_command('SHEL', size)
        receive_response()

        try:
            while 1:
                if command is None:
                    print('lupa> ', end='', flush=True)
                    text = sys.stdin.readline(80)
                    if text == '\n':
                        continue
                else:
                    text = command + '\n'

                for i in range(0, len(text)):
                    tty.write(bytes(text[i], encoding='UTF-8'))
                    #read echo and ignore.
                    tty.read(1)

                if text == 'exit\n':
                    break

                while 1:
                    #read command output
                    text = tty.read(1024)
                    if command is None:
                        print(text.decode('utf-8'), end='', flush=True)

                    if len(text) == 0:
                        break
                    buffer.append(text.decode('utf-8'))

                if command is not None:
                    buffer = ''.join(buffer)
                    break

        except KeyboardInterrupt:
            text = 'exit\n'
            for i in range(0, len(text)):
                tty.write(bytes(text[i], encoding='UTF-8'))
                #read echo
                tty.read(1)
            print('', flush=True)

        send_command('QUIT', 0)
        receive_response()

    else:
        if command is None:
            print('Invalid parameter.')
            exit()

        size = len(command)
        send_command('SHEL', size)
        send_payload(command, size)
        receive_response()

        prefix, size = receive_response()
        buffer = receive_buffer(size)

        send_command('QUIT', 0)
        receive_response()
        print('Done.')

    tty.close()
    return buffer

def process_push_command(port_name, local, remote, callback):
    global tty
    tty = init_tty(port_name)

    send_command('OPEN', 0)
    prefix, ver = receive_response()
    set_version_dependencies(ver)

    '''
    if ver >= LUPA_VERSION(0, 3):
        baudrate = '921600'
        send_command('BAUD', len(baudrate))
        send_payload(baudrate, len(baudrate))
        change_baudrate(port_name, int(baudrate))
        receive_response()
    '''

    send_command('PUSH', len(remote))
    send_payload(remote, len(remote))
    receive_response()

    size = getsize(local)
    send_command('DATA', size)
    send_file(local, size, callback)
    receive_response()

    send_command('QUIT', 0)
    receive_response()

    tty.close()
    print('Done.') 


def list_files(directory):
    files = []
    for dirpath, dirnames, filenames in os.walk(directory):
        for filename in filenames:
            if filename not in excluded_files:
                files.append(os.path.join(dirpath, filename))
    return files

def find_serial_port(vid, pid):
    timeout = time.time() + 120

    while True:
        ports = list(serial.tools.list_ports.comports())
        for portn in ports:
            if portn.vid == vid and portn.pid == pid:
                return portn.name
        if time.time() > timeout:
            break
        time.sleep(1)
    return None

menu = """
==================
Download Options
1. Boot download
2. ALL download 
9. EXIT
==================
"""

def get_input():
    while True:
        print(menu)
        choice = input("Enter your choice (1, 2, or 9): ")
        if choice in ['1', '2', '9']:
            return int(choice)
        else:
            print("Invalid value. Please select 1, 2, or 9.\n")

def handle_user_selection(user_sel, serial_port):
    if user_sel == 1:
        print("Boot download selected.")
        print("\nBoot image download ...")
        process_push_command(serial_port, "kproc.sys", "/cache/kproc.sys", None)
        print("Erase & Flash ...")
        process_shell_command(serial_port, "fs erase boot_a")
        process_shell_command(serial_port, "fs flash_image /cache/kproc.sys boot_a")
        process_shell_command(serial_port, "fs erase boot_b")
        process_shell_command(serial_port, "fs flash_image /cache/kproc.sys boot_b")
        process_shell_command(serial_port, "fs rm /cache/kproc.sys")
        print('Done.')
        
    elif user_sel == 2:
        print("ALL download selected.")
        print("\nUmounts all of partitions ...")
        process_shell_command(serial_port, "fs umount /config")
        process_shell_command(serial_port, "fs umount /data")
        process_shell_command(serial_port, "fs umount /cache")
        process_shell_command(serial_port, "settings format")
        process_shell_command(serial_port, "fs umount /settings")
        process_shell_command(serial_port, "fs umount /system")
        process_shell_command(serial_port, "fs umount /system")
        process_shell_command(serial_port, "fs umount /font")
        process_shell_command(serial_port, "fs umount /font")
        print('Done.')

        print("\nInitialize BBT & Filesystem ...")
        process_shell_command(serial_port, "fs erase reserved")
        print('Done.')

        print("\nMount all of partitions ...")
        process_shell_command(serial_port, "fs mount /dev/mtd2 /data ltffs")
        process_shell_command(serial_port, "fs mount /dev/mtd0 /cache ltffs")
        process_shell_command(serial_port, "fs mount /dev/mtd4 /settings ltffs")
        process_shell_command(serial_port, "fs mount /dev/mtd1 /config ltffs")
        process_shell_command(serial_port, "fs mount /dev/mtd5 /system ltffs")
        process_shell_command(serial_port, "fs mount /dev/mtd3 /font ltffs")
        print('Done.')

        print("\nBoot image download ...")
        process_push_command(serial_port, "kproc.sys", "/cache/kproc.sys", None)
        print("Erase & Flash ...")
        process_shell_command(serial_port, "fs erase boot_a")
        process_shell_command(serial_port, "fs flash_image /cache/kproc.sys boot_a")
        process_shell_command(serial_port, "fs erase boot_b")
        process_shell_command(serial_port, "fs flash_image /cache/kproc.sys boot_b")
        process_shell_command(serial_port, "fs rm /cache/kproc.sys")
        print('Done.')

        print("\nROM image download ...")
        files = list_files(".")
        for file in files:
            newfile = file.replace("\\", "/")
            newfile = newfile[1:]
            print(newfile)
            process_push_command(serial_port, file, newfile, None)

    elif user_sel == 9:
        print("Exiting...") 
        process_shell_command(serial_port, "log info")
        os.system("pause")
        sys.exit()

if __name__ == "__main__":
    print("ITE Download Tool ver {}.{}" .format(IDT_VERSION_MAJOR, IDT_VERSION_MINOR))
    print("\nFind USB Serial Port ...")
    serial_port = find_serial_port(0x2FE3, 0x0100)

    if serial_port is None:
        print("Serial Port was not found.")
        print("Press any key to close the command window.")
        os.system("pause")
        sys.exit()
    else:
        print("Device attached\n")

    user_sel = get_input()
    #process_shell_command(serial_port, "log off")
    handle_user_selection(user_sel, serial_port)
    #process_shell_command(serial_port, "log info")

    print("\nPress any key to close the command window.")
    os.system("pause")
    sys.exit()
