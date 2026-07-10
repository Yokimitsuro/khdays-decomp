extern int func_02030788(void);

struct Flags020ad358 { char pad0[0x464]; unsigned long long f464; };

void func_ov022_020ad358(int obj, int param_2) {
    struct Flags020ad358 *fp = (struct Flags020ad358 *)obj;
    int ok = 1;
    if (func_02030788() != 0) return;
    if ((fp->f464 & 0x100LL) != 0 || (fp->f464 & 0x8000LL) != 0 ||
        (fp->f464 & 0x10000000LL) != 0)
        ok = 0;
    if ((*(unsigned long long *)obj & 0x2000LL) != 0) ok = 0;
    if ((*(unsigned long long *)obj & 0x200000000LL) == 0) ok = 0;
    if (ok) {
        *(unsigned long long *)obj &= ~0x200000000LL;
        *(unsigned long long *)obj |= 0x10000000LL;
        *(int *)(obj + 0x690) = param_2;
        return;
    }
    *(unsigned long long *)obj &= ~0x200000000LL;
}
