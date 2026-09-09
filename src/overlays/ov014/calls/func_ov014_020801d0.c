extern void func_ov002_020767ec(void *entry);
extern unsigned int func_020235d0(int bitOffset, int bitCount);
extern void func_020235e8(unsigned int id, unsigned int bitCount,
                          unsigned int value);

void func_ov014_020801d0(int this_) {
    unsigned int r;
    func_ov002_020767ec((void *)this_);
    r = func_020235d0(*(unsigned short *)(this_ + 0x14),
                      *(unsigned char *)(this_ + 0x16));
    {
        unsigned int value = r;
        func_020235e8(*(unsigned short *)(this_ + 0x14),
                      *(unsigned char *)(this_ + 0x16),
                      ((value & 0xffff0001) | 2) & 0xffff);
    }
    *(unsigned short *)(this_ + 0x12) &= ~8;
    *(unsigned char *)(this_ + 0x135) = 1;
    *(unsigned char *)(this_ + 0x134) = 3;
}
