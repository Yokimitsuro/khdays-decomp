int func_ov267_020d16d0(char *obj) {
    char *base = *(char **)(*(char **)(obj + 0x214));
    if (*(signed char *)(base + 0x1c7) == -1) {
        *(char *)(base + 0x1c7) = 0xe;
        return 1;
    }
    return 0;
}
