int func_ov275_020d2e7c(int *r0) {
    signed char *p = *(signed char **)((char *)r0[0x214 / 4]);

    if ((p[0x1c6] == 2 || p[0x1c6] == 4) && p[0x1c7] == -1) {
        p[0x1c7] = 12;
        return 1;
    }
    return 0;
}
