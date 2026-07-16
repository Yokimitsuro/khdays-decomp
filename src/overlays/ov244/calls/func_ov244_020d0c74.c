extern void func_ov107_020c5c54();

void func_ov244_020d0c74(int this_) {
    unsigned short *p = (unsigned short *)(this_ + 0x60);
    unsigned int h;
    func_ov107_020c5c54(this_);
    h = *p;
    *p = h & ~0xff00 | (((((unsigned int)h << 0x10) >> 0x18 | 1) << 0x18) >> 0x10);
}
