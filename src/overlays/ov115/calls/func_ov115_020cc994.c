void func_ov115_020cc994(char *obj) {
    char *p = *(char **)(obj + 4);
    *(int *)(*(char **)(p + 0x0) + 0x5c) |= 2;
    *(int *)(*(char **)(*(char **)(p + 0x4) + 0x39c) + 0x4) = 0;
}
