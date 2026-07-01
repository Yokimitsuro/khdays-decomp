int func_ov265_020d0d30(char *obj) {
    char *base = *(char **)(*(char **)(obj + 0x214));
    signed char v = *(signed char *)(base + 0x1c6);
    if (v == 0xd) return 0;
    if (v == 2 || v == 4) {
        *(char *)(base + 0x1c7) = 0xd;
        return 1;
    }
    return 0;
}
