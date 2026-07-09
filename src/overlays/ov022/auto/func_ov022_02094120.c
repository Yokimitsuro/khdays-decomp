int func_ov022_02094120(unsigned char *arg0, int arg1) {
    if ((*arg0 & 4) == 0 || arg1 > 0x6000) {
        *arg0 &= ~0x10;
        return 0;
    }
    *arg0 |= 0x10;
    *(int *)(arg0 + 0x10c) = 0;
    return 1;
}
