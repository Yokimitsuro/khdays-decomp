int func_ov244_020cd7ac(char *obj, int param2, int *flags) {
    char *base = *(char **)(obj + 0x214);
    unsigned v = (unsigned short)*flags;
    if (v & 1) {
        if (*(int *)(base + 0x14) != 0) return 0;
        *(char *)(*(char **)base + 0x1c7) = 2;
        *(int *)(base + 0x14) = 1;
        *(int *)(base + 0x18) = param2;
        return 1;
    }
    return 0;
}
