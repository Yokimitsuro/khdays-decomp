void func_ov219_020d0320(char *obj) {
    char *base = *(char **)(*(char **)(obj + 0x214));
    if (*(signed char *)(base + 0x1c6) != 3) {
        *(char *)(base + 0x1c7) = 3;
    }
}
