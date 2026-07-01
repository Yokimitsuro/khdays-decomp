void func_ov092_020bc108(char *p) {
    char *q = p + 0x2c80;
    *(int *)(q + 4) = 0;
    {
        char *r = *(char **)(p + 0xd80);
        if (r != 0) {
            int v = *(int *)(*(char **)(r + 0x14) + 8);
            if (v > 0) *(int *)(q + 4) = v;
        }
    }
    *(int *)(q + 8) = 0;
}
