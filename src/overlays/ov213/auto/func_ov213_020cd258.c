int func_ov213_020cd258(char *obj) {
    char *node = *(char **)*(char **)(obj + 0x214);
    signed char state = *(signed char *)(node + 0x1c6);
    if (!(state != 2 && state != 4 && state != 5 && state != 6 && state != 7)) {
        if (*(signed char *)(node + 0x1c7) == -1) {
            *(char *)(node + 0x1c7) = 0xf;
            return 1;
        }
    }
    return 0;
}
