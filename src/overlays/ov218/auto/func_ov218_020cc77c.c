void func_ov218_020cc77c(char *obj) {
    char *base = *(char **)(*(char **)(obj + 0x214));
    if (*(signed char *)(base + 0x1c6) != 3) {
        *(char *)(base + 0x1c7) = 3;
    }
}
