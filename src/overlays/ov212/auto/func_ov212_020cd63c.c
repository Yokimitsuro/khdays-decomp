int func_ov212_020cd63c(char *obj, int arg) {
    if (arg == 0) {
        if ((unsigned)(*(int *)(obj + 0x6c) - 2) <= 1) {
            return 1;
        }
    }
    return *(int *)(obj + 0x6c) == 1;
}
