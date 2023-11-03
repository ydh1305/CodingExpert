import os
import time
import sys
import struct
import threading
import heapq
import platform
from sys import argv
from os.path import getsize
from sys import exit

from modules import *

class FlashMate:
    ALL_DL = 90
    REBOOT = 99
    EXIT = 100

    def __init__(self):
        self.file_list = []
        self.menu_list = [self.ALL_DL, self.REBOOT, self.EXIT]
        self.partnum_list = []

        self.filemanager = FileManager(self)
        self.usbcdc = CDC(self)
        self.upgrademanager = UpgradeManager(self)
        self.bbt = BBT(self)
        
        self.filemanager.init_file_info()
        self.total_time = 0

        print("FlashMate Flashing Tool (Build ID {}.{}.{})\n" .format(FM_VERSION_MAJOR, FM_VERSION_MINOR, FM_VERSION_PATCH))

    def print_menu(self):
        print("Download Options")
        print("======================================================")
        print("(No. {:10} {:>14} {:>10} {:>10} )".format("Partition", "File Name", "Address", "Region"))
        for finfo in FM.file_list:
            print("({},".format(finfo.num), "'{:10} {:>14} {:>10} {:>10}')".format(finfo.part, finfo.fname, hex(finfo.addr * SPI_NAND_BLOCK_SIZE), hex(finfo.region * SPI_NAND_BLOCK_SIZE)))
        print("90, All download")
        print("99, Reboot")
        print("100, Exit")
        print("======================================================")

    def press_any_key(self):
        if platform.system() == 'Windows':
            os.system("pause")
        else:
            input("Press any key to continue.")
        exit()

    def get_input(self):
        FM.menu_list.extend(FM.partnum_list)

        while True:
            self.print_menu()
            choice = input("Enter your choice : ")
            if int(choice) in FM.menu_list:
                print()
                return int(choice)
            else:
                print("Please enter a valid number.\n")
    
    def init_flash_time(self):
        self.total_time = 0

    def execute(self):
        if len(sys.argv) >= 2:
            self.handle_command_line()
        else:
            self.handle_interactive()
        self.press_any_key()

    def handle_command_line(self):
        print("Searching for USB port ...")

        if sys.argv[1] is None:
            self.COM = self.usbcdc.init_usb_cdcacm()
        else:
            self.COM = self.usbcdc.setup_serial_comm(sys.argv[1])

        if self.COM is None:
            print("Serial Port was not found.\n")
            self.press_any_key()
        else:
            print("Device attached\n")

        if sys.argv[2]== "all":
            self.event_handler(self.COM, self.ALL_DL)
            print("Finished. Total Time : {:6.3f} sec\n".format(round(self.total_time, 3)))
            if "reboot" in sys.argv:
                self.event_handler(self.COM, self.REBOOT)
        else:
            if self.ALL_DL in sys.argv:
                print("Can't select ALL option in partial download.\n")
                self.press_any_key()

            for arg in sys.argv[2:]:
                if arg.isdigit() and int(arg) not in self.partnum_list:
                    print("Please enter the valid value for partial D/L.")
                    self.press_any_key()

            partial_list = [int(arg) for arg in sys.argv[2:]if arg != "reboot" and int(arg) != self.ALL_DL and int(arg) != self.REBOOT]
            for partial_num in partial_list:
                self.event_handler(self.COM, partial_num)

            if len(partial_list) > 0:
                print("Finished. Total Time : {:6.3f} sec\n".format(round(self.total_time, 3)))
            if "reboot" in sys.argv:
                self.event_handler(self.COM, self.REBOOT)

    def handle_interactive(self):
        print("Searching for USB port ...")

        self.COM = self.usbcdc.init_usb_cdcacm()

        if self.COM is None:
            print("Serial Port was not found.\n")
            self.press_any_key()
        else:
            print("Device attached\n")

        while True:
            self.init_flash_time()
            user_sel = self.get_input()
            self.event_handler(self.COM, user_sel)
            if int(user_sel) in self.partnum_list or user_sel is self.ALL_DL:
                print("Finished. Total Time : {:6.3f} sec\n".format(round(self.total_time, 3)))

    def event_handler(self, COM, user_sel):
        if user_sel == self.ALL_DL:
            print("Erase all of blocks ...\n")
            FM.upgrademanager.erase_blocks(COM, 0, SPI_NAND_TOTAL_BLK)
            FM.bbt.setup_bbt(COM, 0, SPI_NAND_TOTAL_BLK)

            for finfo in FM.file_list:
                run_time = FM.upgrademanager.erase_blocks(COM, finfo.addr, finfo.addr + finfo.region)
                FM.total_time += run_time
                print("Erasing {!r:<10} OKAY [{:7.3f}]".format(finfo.part, run_time))
                pQ = FM.bbt.get_goodblk(finfo.addr, finfo.region)
                if finfo.part in ["SBL", "BOOTA", "BOOTB"]:
                    run_time = FM.upgrademanager.upgrade_ite_image(COM, "./{}".format(finfo.fname), pQ)
                elif finfo.part in ["FSRO", "FSRW", "FSROA", "FSROB", "FSRWA", "FSRWB"]:
                    run_time = FM.upgrademanager.upgrade_sparse_image(COM, "./{}".format(finfo.fname), pQ)
                FM.total_time += run_time
                print("Writing {!r:<10} OKAY [{:7.3f}]\n".format(finfo.part, run_time))
                pQ.clear()
            
            FM.bbt.update_bbt(COM)

        elif user_sel == self.REBOOT:
            FM.usbcdc.send_command(COM, 'Reboot')
            self.press_any_key()
            
        elif user_sel == self.EXIT:
            print("Exiting ...\n") 
            self.press_any_key()
        
        else:
            finfo = FM.filemanager.get_file_info(user_sel, FM.file_list)

            if finfo == None:
                print("Invalid Partition number. Please check and re-enter.")
                self.press_any_key()
            else:
                run_time = FM.upgrademanager.erase_blocks(COM, finfo.addr, finfo.addr + finfo.region)
                FM.total_time += run_time
                print("Erasing {!r:<10} OKAY [{:7.3f}]".format(finfo.part, run_time))
                FM.bbt.setup_bbt(COM, finfo.addr, finfo.region)
                pQ = FM.bbt.get_goodblk(finfo.addr, finfo.region)
                if finfo.part in ["SBL", "BOOTA", "BOOTB"]:
                    run_time = FM.upgrademanager.upgrade_ite_image(COM, "./{}".format(finfo.fname), pQ)
                elif finfo.part in ["FSRO", "FSRW", "FSROA", "FSROB", "FSRWA", "FSRWB"]:
                    run_time = FM.upgrademanager.upgrade_sparse_image(COM, "./{}".format(finfo.fname), pQ)
                FM.total_time += run_time
                print("Writing {!r:<10} OKAY [{:7.3f}]\n".format(finfo.part, run_time))
                pQ.clear()

if __name__ == "__main__":
    FM = FlashMate()
    FM.execute()
