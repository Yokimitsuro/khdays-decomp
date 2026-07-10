extern int func_02030788(void);
extern int func_ov022_020a35f4(int obj, int mode);

int func_ov022_020ab810(int obj) {
    int r = 0;
    if (func_02030788() == 0)
        *(unsigned long long *)(obj + 0x464) |= 0x200000000LL;
    if (func_02030788() == 0)
        *(unsigned long long *)(obj + 0x464) |= 0x4000000000LL;
    *(int *)(obj + 0x4b4) = 0x3000;
    if ((*(unsigned long long *)obj & 0x800LL) == 0) r = func_ov022_020a35f4(obj, 0);
    if (r != 0)
        *(unsigned long long *)obj &= ~0x800LL;
    return r;
}
