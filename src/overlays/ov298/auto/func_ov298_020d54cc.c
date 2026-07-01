void func_ov298_020d54cc(char *p) {
    char *q = *(char **)(*(char **)(p + 4)) + 0x100;
    *(unsigned short *)(q + 0xae) |= 3;
}
