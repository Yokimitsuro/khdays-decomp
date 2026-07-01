int func_ov186_020d1df0(char *arg) {
    char *base = *(char **)(arg + 0x214);
    char *s = *(char **)base;
    signed char a = *(signed char *)(s + 0x1c6);
    if (a == 9) {
        *(signed char *)(s + 0x1c7) = 0;
        return 1;
    }
    {
        signed char b = *(signed char *)(s + 0x1c7);
        if (b != 8 && a != 8) {
            if (a == 7 || a == 2 || a == 4 || a == 6) {
                *(signed char *)(s + 0x1c7) = 8;
            }
        }
    }
    return 0;
}
