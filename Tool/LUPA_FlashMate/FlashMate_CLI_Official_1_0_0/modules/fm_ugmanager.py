import sys
import os
import time
import struct

from modules import fm_prd
from modules import fm_cdcacm

# IT986X SoC series SPI NAND Info
SPI_NAND_PAGE_SIZE     = 2048
SPI_NAND_PAGE_PER_BLK  = 64
SPI_NAND_BLOCK_SIZE    = (SPI_NAND_PAGE_PER_BLK * SPI_NAND_PAGE_SIZE)
SPI_NAND_TOTAL_BLK     = 1024

class UpgradeManager:
    # SIC Sparse Image Info
    SIC_SPARSE_HEADER_SIZE = 20
    sic_sparse_sig = b"LG-SIC-Sparse-Format"

    # IT986X SoC series Image Info
    GOOD_BLK_MARK_SIZE     = 4
    good_blk_mark = b"FINE"

    def __init__(self, parent):
        self.parent = parent
        self.usbcdc = fm_cdcacm.CDC(self)

    def file_reader_meta_info(self, fd):
        buf = fd.read(struct.calcsize("=HHI"))
        if buf is None:
            raise Exception("Failed to read meta info.")

        meta_info = fm_prd.MetaInfo(*struct.unpack("=HHI", buf))
        return meta_info

    def file_reader_data(self, fd, size):
        buf = fd.read(size)
        if buf is None:
            raise Exception("Failed to read data.") 

        return buf
    
    def update_block(self, COM):
        FMHeader = fm_prd.FlashMateHeader(2500, 2500, 0)
        frame = struct.pack("=HHI", FMHeader.block, FMHeader.page, FMHeader.size)
        self.usbcdc.usbcdc_write(COM, frame)
        buf = self.usbcdc.usbcdc_read(COM, 4)
        blk = struct.unpack("=I", buf)[0]
        return blk

    def erase_blocks(self, COM, pos_s, pos_e):
        start_time = time.perf_counter()
        self.usbcdc.send_command(COM, 'Erase {} {}'.format(pos_s, pos_e))
        self.usbcdc.receive_response(COM)
        end_time = time.perf_counter()
        return round(end_time - start_time, 3)

    def upgrade_sparse_image(self, COM, fname, queue):
        start_time = time.perf_counter()
        fd = open(fname, "rb")
        fsize = os.path.getsize(fname)
        blk_idx = queue.pop()
        FMHeader = fm_prd.FlashMateHeader(blk_idx, 1, 0)

        data = fd.read(UpgradeManager.SIC_SPARSE_HEADER_SIZE + 8)
        fsize -= (UpgradeManager.SIC_SPARSE_HEADER_SIZE + 8);
        
        if UpgradeManager.sic_sparse_sig != data[:UpgradeManager.SIC_SPARSE_HEADER_SIZE]:
            print("SIC signature mismatch.")
            fd.close()
            return None    

        self.usbcdc.send_command(COM, 'Flash')
        self.usbcdc.receive_response(COM)
        cur_fid = -1
        updata_needed = False

        while fsize > 0:
            if fsize > 4:
                meta_info = self.file_reader_meta_info(fd)
                fsize -= struct.calcsize("=HHI")

                if cur_fid == -1:
                    cur_fid = meta_info.fid

                frame = self.file_reader_data(fd, meta_info.size)
                fsize -= meta_info.size
            else:
                updata_needed = True

            if cur_fid != meta_info.fid or updata_needed == True:
                blk = self.update_block(COM)
                if updata_needed == True:
                    data = fd.read(4)
                    fsize -= len(data)
                    if data == b'\xff\xff\xff\xff':
                        break
                if FMHeader.block == blk:
                    FMHeader.block = queue.pop()
                else:
                    newblk = None
                    while queue:
                        newblk = queue.pop()
                        if newblk > blk:
                            break
                    FMHeader.block = newblk
            
                cur_fid = meta_info.fid
                FMHeader.page = 1
                        
            FMHeader.size = meta_info.size
            header = struct.pack("=HHI", FMHeader.block, FMHeader.page, FMHeader.size)

            self.usbcdc.usbcdc_write(COM, header)
            self.usbcdc.usbcdc_write(COM, frame)

            FMHeader.page += 1 

        fd.close()

        self.usbcdc.send_finish(COM)
        self.usbcdc.receive_response(COM)
        end_time = time.perf_counter()
        return round(end_time - start_time, 3)
    
    def upgrade_ite_image(self, COM, fname, queue):
        start_time = time.perf_counter()
        fd = open(fname, "rb")
        fsize = os.path.getsize(fname)
        blk_idx = queue.pop()
        FMHeader = fm_prd.FlashMateHeader(blk_idx, 0, 0)

        self.usbcdc.send_command(COM, 'Flash')
        self.usbcdc.receive_response(COM)

        while fsize > 0:
            if FMHeader.page == 0 and FMHeader.block != 0:
                data = fd.read(SPI_NAND_PAGE_SIZE - UpgradeManager.GOOD_BLK_MARK_SIZE)
                frame = UpgradeManager.good_blk_mark + data
            else:
                data = fd.read(SPI_NAND_PAGE_SIZE)
                frame = data

            FMHeader.size = len(frame)
            header = struct.pack("=HHI", FMHeader.block, FMHeader.page, FMHeader.size)

            self.usbcdc.usbcdc_write(COM, header)
            self.usbcdc.usbcdc_write(COM, frame)

            FMHeader.page = (FMHeader.page + 1) % SPI_NAND_PAGE_PER_BLK
            fsize -= len(data)
            if FMHeader.page == 0 or fsize == 0:
                blk = self.update_block(COM)
                if fsize == 0:
                    break
                if FMHeader.block == blk:
                    FMHeader.block = queue.pop()
                else:
                    newblk = None
                    while queue:
                        newblk = queue.pop()
                        if newblk > blk:
                            break
                    FMHeader.block = newblk

        fd.close()

        self.usbcdc.send_finish(COM)
        self.usbcdc.receive_response(COM)
        end_time = time.perf_counter()
        return round(end_time - start_time, 3)