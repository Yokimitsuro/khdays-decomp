extern int func_ov022_02095450(int a);
extern int func_ov022_02095524(int a);

/* The struct-field form keeps the direct `ldr [obj,#0x468]` for the high half. */
struct Flags02095d10 { char pad0[0x464]; unsigned long long flags; };

int func_ov022_02095d10(int obj) {
    unsigned long long f = ((struct Flags02095d10 *)obj)->flags;
    int ok = ((f & 8LL) != 0);
    if (ok && (*(unsigned long long *)obj & 0x210002010LL) != 0) ok = 0;
    if (ok && (f & 0x10100LL) != 0) ok = 0;
    if (ok && func_ov022_02095450(obj + 0x22f8) != 0 &&
        func_ov022_02095524(obj + 0x22f8) == 0) ok = 0;
    return ok;
}
