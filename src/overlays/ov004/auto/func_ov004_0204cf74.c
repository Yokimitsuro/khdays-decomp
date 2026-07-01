int func_ov004_0204cf74(unsigned char *p) {
    if (p[0x23] != 4) {
        return 0;
    }
    return *(unsigned short *)(p + 2) == 0xa;
}
