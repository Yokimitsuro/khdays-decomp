void func_ov206_020cccc0(char *obj) {
    char *node = *(char **)(obj + 4);
    char *mgr = *(char **)(node + 4);
    *(int *)(mgr + 0x5c) |= 2;
    *(int *)(*(char **)(*(char **)node + 0x3e0) + 4) = 0;
}
