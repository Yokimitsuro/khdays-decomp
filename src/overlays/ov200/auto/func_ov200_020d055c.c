int func_ov200_020d055c(char *obj) {
    int x = *(int *)(obj + 0x38);
    x = (x << 28) >> 28;
    return x == 0;
}
