extern int data_ov025_020b39e4;

unsigned int func_ov025_0208dfc4(unsigned int arg0) {
    unsigned int i = 0;
    do {
        if (arg0 < *(unsigned short *)((char *)&data_ov025_020b39e4 + i * 8)) return i;
        i = (i + 1) & 0xffff;
    } while (i < 0x38);
    return 0;
}
