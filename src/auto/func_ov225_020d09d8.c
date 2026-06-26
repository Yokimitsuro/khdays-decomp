int func_ov225_020d09d8(char *arg0) {
    signed char *p = **(signed char ***)(arg0 + 0x214);
    if (p[0x1c7] == -1) {
        p[0x1c7] = 0xf;
        return 1;
    }
    return 0;
}
