extern int func_ov022_0209029c(int obj, unsigned int idx);
extern int func_020357f4(int kind, unsigned int idx);

int func_ov022_0209038c(int obj, unsigned int idx) {
    int *flags = *(int **)(obj + 0x58);
    int r = 1;
    if (idx == 0xffffffff) return 0;
    if (func_ov022_0209029c(obj, idx) == 0) return 0;
    if (func_020357f4(*(unsigned char *)(*(int *)(obj + 0x58) + 9), idx) <= 0) return 0;
    switch (*(unsigned char *)(obj + 2)) {
    case 1:
    case 2:
    case 3:
    case 4:
    case 9:
        r = 0;
        goto end;
    case 5:
    case 6:
    case 7:
    case 8:
        r = 0;
        break;
    case 0:
    default:
        break;
    }
end:
    if ((*(unsigned long long *)flags & 0x10LL) != 0 ||
        (*(unsigned long long *)flags & 0x2000LL) != 0)
        r = 0;
    return r;
}
