void func_ov161_020ccaa0(char *obj) {
    char *p = *(char **)(obj + 4);
    *(int *)(*(char **)(p + 0x4) + 0x5c) |= 2;
    *(int *)(*(char **)(*(char **)(p + 0x0) + 0x3c4) + 0x2c) = 0;
}
