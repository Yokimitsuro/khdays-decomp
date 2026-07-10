extern int func_ov022_02095524(int a);

/* Struct-field form keeps the direct `ldr [obj,#0x468]` for the high half. */
struct Flags020ad8e0 { char pad0[0x464]; unsigned long long f464; };

void func_ov022_020ad8e0(int obj, int mode) {
    if (mode != 0) {
        if (*(int *)(obj + 0x4b4) != 0) return;
        if ((*(unsigned long long *)obj & 0x80000LL) != 0) return;
        if ((*(unsigned long long *)obj & 0x1000000LL) != 0) return;
        if ((((struct Flags020ad8e0 *)obj)->f464 & 0x10000LL) != 0) return;
        if ((((struct Flags020ad8e0 *)obj)->f464 & 0x8000000000LL) != 0) return;
        if (func_ov022_02095524(obj + 0x22f8) != 0) return;
        *(unsigned long long *)obj |= 0x2000LL;
        return;
    }
    *(unsigned long long *)obj &= ~0x2000LL;
}
