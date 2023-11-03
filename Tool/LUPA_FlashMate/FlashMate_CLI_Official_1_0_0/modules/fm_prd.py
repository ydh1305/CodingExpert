# FlashMate Tool version
FM_VERSION_MAJOR       = 1
FM_VERSION_MINOR       = 0
FM_VERSION_PATCH       = 0

class FlashMateHeader:
    def __init__(self, block, page, size):
        self.block = block
        self.page = page
        self.size = size

class MetaInfo:
    def __init__(self, fid, la, size):
        self.fid = fid
        self.la = la
        self.size = size

class BbmHeader:
    def __init__(self, erase_count):
        self.erase_count = erase_count

class BlkHeader:
    def __init__(self, fid, la, status, size):
        self.fid = fid
        self.la = la
        self.status = status
        self.size = size

class BlkInfo:
    def __init__(self, header, signature):
        self.header = header
        self.signature = signature