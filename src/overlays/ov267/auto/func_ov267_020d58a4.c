struct blk3 { int a, b, c; };
int func_ov267_020d58a4(char *obj, char *src, int *flags) {
    char *ptrA = *(char **)(obj + 0x214);
    char *ptrB = *(char **)(*(char **)ptrA + 0x384);
    if (*(int *)(ptrB + 0x5b0) != 0) return 0;
    unsigned short f = (unsigned short)*flags;
    if ((f & 1) && (f & 0x10)) {
        char *ptrB2;
        *(int *)(ptrB + 0x5b0) = (int)src;
        ptrB2 = *(char **)(*(char **)ptrA + 0x384);
        *(struct blk3 *)(ptrB2 + 0x5c0) = *(struct blk3 *)(src + 0x190);
        return 1;
    }
    return 1;
}
