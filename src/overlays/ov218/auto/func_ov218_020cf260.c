void func_ov218_020cf260(char *obj) {
    char *node = *(char **)(obj + 4);
    char *mgr = *(char **)(node + 4);
    *(int *)(mgr + 0x5c) |= 2;
    *(int *)(*(char **)node + 0x3a8) = 0;
    *(int *)(*(char **)node + 0x394) = 0;
}
