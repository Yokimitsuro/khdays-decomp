int func_ov263_020d2f0c(char *obj, int unused, int *flags) {
    char *base = *(char **)(obj + 0x214);
    unsigned v = (unsigned short)*flags;
    if ((v & 1) && (v & 0x10)) {
        *(int *)(base + 0x1c) = 0x16000;
        return 0;
    }
    return 1;
}
