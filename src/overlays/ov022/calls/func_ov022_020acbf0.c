extern int func_ov022_0208868c(void);

void func_ov022_020acbf0(int obj) {
    unsigned long long f;
    int state;
    if (func_ov022_0208868c() != 0) return;
    f = *(unsigned long long *)obj;
    if ((f & 0x1000000LL) != 0) return;
    if ((f & 0x100LL) != 0) return;
    if ((f & 0x20000LL) != 0) return;
    if ((f & 0x800000LL) != 0) return;
    if ((f & 0x2000LL) != 0) return;
    state = *(signed char *)(obj + 0x2770);
    if (state == 3 || state == 0xb || state == 2) return;
    *(unsigned long long *)obj = f | 0x800000LL;
}
