void func_ov253_020d1220(char *obj) {
    char *node = *(char **)(obj + 4);
    char *mgr = *(char **)(node + 4);
    *(int *)(mgr + 0x5c) |= 2;
    *(int *)(*(char **)(*(char **)node + 0x3b0) + 0xc) = 0;
}
