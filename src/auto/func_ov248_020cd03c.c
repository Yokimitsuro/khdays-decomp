int func_ov248_020cd03c(int *r0) {
    char *p = *(char **)(r0[0x214 / 4]);
    if (*(signed char *)(p + 0x1c6) != 0xc) {
        p[0x1c7] = 0xc;
        return 1;
    }
    return 0;
}
