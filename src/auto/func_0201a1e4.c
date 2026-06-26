void func_0201a1e4(short *volatile *p, short a, short b) {
    if (*p) {
        (*p)[0x34 / 2] = 2;
        (*p)[0x38 / 2] = a;
        (*p)[0x3a / 2] = b;
    }
}
