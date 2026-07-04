extern int func_020235d0();

void *func_ov017_020806d0(int this_) {
    unsigned int r = func_020235d0(*(unsigned short *)(this_ + 0x14),
                                   *(unsigned char *)(this_ + 0x16));
    r = ((r & 0xfffe) << 0xf) >> 0x10;
    if (r & 1) return 0;
    return (void *)(this_ + 0x1c);
}
