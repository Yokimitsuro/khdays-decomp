extern int func_020235d0();

void *func_ov014_0207fce8(int this_) {
    int sub = *(int *)(this_ + 8);
    unsigned int r = func_020235d0(*(unsigned short *)(this_ + 0x14),
                                   *(unsigned char *)(this_ + 0x16));
    r = ((r & 0xfffe) << 0xf) >> 0x10;
    if ((r & 1) == 0) return 0;
    return *(void **)(sub + 0x68);
}
