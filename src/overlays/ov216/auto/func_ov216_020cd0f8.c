int func_ov216_020cd0f8(char *p) {
    char *ptr = *(char **)(p + 4);
    int diff = *(int *)(ptr + 0x50) - *(int *)(*(char **)p + 0x2c);
    *(int *)(ptr + 0x50) = diff;
    if (diff <= 0) {
        *(int *)(ptr + 0x50) = 0;
        if (*(int *)(ptr + 8) != 0) {
            ((char *)*(char **)ptr)[0x1c7] = 6;
            return 1;
        }
    }
    return 0;
}
