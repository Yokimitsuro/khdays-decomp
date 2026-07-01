void func_ov162_020ce8c0(char *obj) {
    char *p = *(char **)(obj + 4);
    *(int *)(*(char **)(p + 0x4) + 0x5c) |= 2;
    *(int *)(*(char **)(*(char **)(p + 0x0) + 0x3c4) + 0x2c) = 0;
}
