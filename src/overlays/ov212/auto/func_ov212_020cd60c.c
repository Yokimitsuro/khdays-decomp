int func_ov212_020cd60c(char *obj, int arg) {
    if (arg == 0) {
        if ((unsigned)(*(int *)(obj + 0x6c) - 4) <= 1) {
            return 1;
        }
    }
    return *(int *)(obj + 0x6c) == 0;
}
