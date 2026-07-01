int func_ov082_020b84dc(unsigned char *p) {
    unsigned char v = p[0x918];
    switch (v) {
        case 0x1a: return 0x6b;
        case 0x1b: return 0x56;
        case 0: return 0x55;
        case 1: return 0x55;
        default: return v + 0x55;
    }
}
