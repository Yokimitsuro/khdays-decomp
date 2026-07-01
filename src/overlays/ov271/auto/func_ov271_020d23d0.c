int func_ov271_020d23d0(char *obj) {
    int x = *(int *)(obj + 0x38);
    x = (x << 28) >> 28;
    return x == 0;
}
