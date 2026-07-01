int func_ov271_020d23b4(char *obj) {
    int x = *(int *)(obj + 0x38);
    x = (x << 28) >> 28;
    return x == 1;
}
