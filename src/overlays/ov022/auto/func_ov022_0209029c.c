int func_ov022_0209029c(unsigned short *arg0, unsigned int arg1) {
    if (*arg0 == 0) return 0;
    if (arg1 != 0xffffffff && (*(unsigned int *)(arg0 + 4) & (1 << arg1)) == 0) return 0;
    return 1;
}
