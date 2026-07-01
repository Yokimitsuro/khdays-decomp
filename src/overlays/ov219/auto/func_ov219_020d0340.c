int func_ov219_020d0340(int *r0) {
    signed char *r1 = (signed char *)((int *)r0[0x214 / 4])[0];
    if (*(signed char *)((char *)r1 + 0x100 + 0xc6) != 9) {
        *(signed char *)((char *)r1 + 0x1c7) = 9;
        return 1;
    }
    return 0;
}
