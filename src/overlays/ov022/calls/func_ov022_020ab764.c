extern int func_02030788(void);
extern int func_ov022_020a35f4(int obj, int mode);

int func_ov022_020ab764(int obj) {
    int r = 0;
    if (func_02030788() == 0)
        *(unsigned long long *)(obj + 0x464) |= 0x8000LL;
    if ((*(unsigned long long *)obj & 0x2000LL) == 0) {
        if ((*(unsigned int *)(obj + 0x24) & 4) != 0) r = func_ov022_020a35f4(obj, 0);
        else r = func_ov022_020a35f4(obj, 2);
    }
    if (r != 0)
        *(unsigned long long *)obj &= ~0x2000LL;
    return r;
}
