extern int func_0202aee0(int a, int b);
extern int func_ov022_0209fc78(int obj, int a);
extern int func_ov022_02083f90(void);
extern void func_ov022_020b0d28(int a, int b, int c, int d);

/* Bit 52 of the 64-bit flag word at obj+0x464. The struct-field form keeps the
 * direct `ldr [obj,#0x468]` for the high half; a plain cast splits the base. */
struct Flags0209c7dc { char pad0[0x464]; unsigned long long flags; };

void func_ov022_0209c7dc(int obj) {
    int v = *(int *)(obj + 0x6bc);
    int base = func_0202aee0(*(int *)(obj + 0x20) + 4, 0);
    short cur;
    if (func_ov022_0209fc78(obj, -1) == 0) return;
    if (*(int *)(obj + 0x6bc) < 0x1e) return;
    if (*(int *)(obj + 0x6bc) >= 0x2e) return;
    cur = *(short *)(obj + 0x2aba);
    if (cur == func_ov022_02083f90()) {
        if ((((struct Flags0209c7dc *)obj)->flags & 0x10000000000000LL) == 0)
            base -= cur;
    }
    func_ov022_020b0d28(obj + 0x910, v - 0x1e, base, obj + 0x588);
}
