extern void func_ov259_020d1c44(int param_1);

void func_ov259_020d17fc(int this_) {
    if (*(int *)(this_ + 0x50) == 1) {
        unsigned short *p = (unsigned short *)(this_ + 0x60);
        unsigned int h = *p;
        *p = h & ~0xff00 | (((((unsigned int)h << 0x10) >> 0x18 | 2) << 0x18) >> 0x10);
        func_ov259_020d1c44(*(int *)(this_ + 0x214));
    }
}
