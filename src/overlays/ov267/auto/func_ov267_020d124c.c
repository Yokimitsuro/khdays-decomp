int func_ov267_020d124c(char *obj, int arg) {
    if (arg == 0) {
        if ((unsigned)(*(int *)(obj + 0x6c) - 2) <= 1) {
            return 1;
        }
    }
    return *(int *)(obj + 0x6c) == 1;
}
