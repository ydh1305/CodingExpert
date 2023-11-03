import sys
import os
import time

from modules.fm_ugmanager import SPI_NAND_BLOCK_SIZE

class FileInfo:
    def __init__(self, num, part, fname, addr, region):
        self.num = num
        self.part = part
        self.fname = fname
        self.addr = int(addr, 16) // SPI_NAND_BLOCK_SIZE
        self.region = int(region, 16) // SPI_NAND_BLOCK_SIZE

class FileManager:
    def __init__(self, parent):
        self.parent = parent
    
    def init_file_info(self):
        with open('file_list.txt', 'r') as file:
            lines = file.readlines()
        num = 1
        for line in lines[1:]:
            data = line.split()
            if len(data) == 4:
                part, fname, addr, region = data
                self.parent.file_list.append(FileInfo(num, part, fname, addr, region))
                self.parent.partnum_list.append(num)
                num += 1

    def get_file_info(self, part_num, file_list):
        for file in file_list:
            if file.num == part_num:
                return file
        return None