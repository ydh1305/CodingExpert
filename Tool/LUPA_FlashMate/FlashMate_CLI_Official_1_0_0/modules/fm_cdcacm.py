import asyncio
import sys
import os
import time
import struct
import platform

from modules import fm_prd
from sys import exit

class CDC:
    # IT9867 EVB target USB Info
    USB_VID = 0xC1CA
    USB_PID = 0xBDBB

    res_code = b"ReadOkay";

    MAX_PACKET_LEN = 8

    def __init__(self, parent):
        self.parent = parent

    def init_usb_cdcacm(self):
        serial_port = self.find_serial_port(CDC.USB_VID, CDC.USB_PID)
        if serial_port is None:
            return None

        com = self.setup_serial_comm(serial_port)
        return com

    def find_serial_port(self, vid, pid): 
        if platform.system() == 'Windows':
            import serial.tools.list_ports
            ports = list(serial.tools.list_ports.comports())
            for portn in ports:
                if portn.vid == vid and portn.pid == pid:
                    return portn.name
            return None
        else:
            import os
            import pyudev

            vid_string = hex(vid)[2:].lower()
            pid_string = hex(pid)[2:].lower()

            context = pyudev.Context()
            devices = context.list_devices(subsystem='tty')
            for device in devices:
                try:
                    if device['ID_VENDOR_ID'] == vid_string and device['ID_MODEL_ID'] == pid_string:
                        return os.path.join('/dev', device.device_node.split('/')[-1])
                except KeyError:
                    pass
                return None

    def setup_serial_comm(self, port_name):
        if platform.system() == 'Windows':
            import serial
            try:
                port = serial.Serial(port=port_name, baudrate=115200, timeout=2)
            except serial.SerialException:
                print("Please enter a valid COM port. (current:{})".format(port_name))
                exit()
        else:
            import termios
            try:
                port = open(port_name, mode='rb+', buffering=0)
            except FileNotFoundError:
                print("Please enter a valid USB port. (current:{})".format(port_name))
                exit()
            attrs = termios.tcgetattr(port)
            attrs[0] = termios.IGNPAR
            attrs[1] = 0
            attrs[3] = 0
            attrs[4] = termios.B115200
            attrs[5] = termios.B115200
            attrs[6][termios.VMIN] = 0
            attrs[6][termios.VTIME] = 2

            termios.tcflush(port, termios.TCIFLUSH)
            termios.tcsetattr(port,termios.TCSANOW,attrs)

        return port

    def usbcdc_write(self, COM, data):
        COM.write(data)

    def usbcdc_read(self, COM, size):
        buf = COM.read(size)
        return buf

    def send_command(self, COM, command):
        buf = bytes(command, encoding='UTF-8')
        COM.write(buf)

    def send_finish(self, COM):
        FMHeader = fm_prd.FlashMateHeader(3000, 3000, 0)
        frame = struct.pack("=HHI", FMHeader.block, FMHeader.page, FMHeader.size)
        COM.write(frame)
    
    def receive_packet(self, COM, size):
        timeout = 100
        buf = b''
        while size > 0 and timeout > 0:
            data = COM.read(size)
            if data:
                buf += data
                size -= len(data)
                timeout = 100
            else:
                timeout -= 1
        return buf

    def receive_response(self, COM):
        buf = self.receive_packet(COM, CDC.MAX_PACKET_LEN)
        if buf != CDC.res_code:
            print("Invalid packet data")
