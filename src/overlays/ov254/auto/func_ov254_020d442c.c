void func_ov254_020d442c(char *obj) {
    char *base = *(char **)obj;
    signed char v = *(signed char *)(base + 0x1c6);
    if (v == 1) {
        *(char *)(base + 0x1c7) = 2;
    }
}
