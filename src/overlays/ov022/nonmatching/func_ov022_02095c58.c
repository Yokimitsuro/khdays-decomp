/* NONMATCHING: register-permutation tie, size-exact. Two near-misses that cannot be
 * combined:
 *   - with the 64-bit value inline (`(*(unsigned long long *)obj & 0x400000LL)`) the
 *     TAIL colors correctly but the head swaps the low-word load and the AND temp
 *     (orig `ldr r2,[r4]; and r1,r2,#0x400000`; mwcc emits them the other way round);
 *   - binding it to a local `f` fixes the head and instead permutes the tail's three
 *     registers (a/hp/prod land in r1/r3/r2 instead of r2/r1/r3).
 * Six forms tried: inline vs local, struct-field access, an extra `lo` local, and
 * three tail declaration orders. Semantics below are exact. */
extern void func_ov002_0206cd60(int a, int b);
extern int func_020358f4(int kind, int b);
extern void func_ov022_020acc94(int obj, int v);
extern int data_0204c240;

void func_ov022_02095c58(int obj) {
    int p = *(int *)(obj + 0xd80);
    unsigned long long f;
    int prod, hp;
    if (p != 0 && *(unsigned char *)(*(int *)(p + 0x14) + 2) == 2) return;
    f = *(unsigned long long *)obj;
    if ((f & 0x400000LL) != 0) return;
    if ((*(unsigned char *)&data_0204c240 & 4) == 0) {
        if (((unsigned int)f & 0x10000) == 0 && *(unsigned char *)(obj + 9) == 0)
            func_ov002_0206cd60(1, 2);
    }
    if (func_020358f4(*(unsigned char *)(obj + 9), 0x34) == 0) return;
    prod = *(unsigned short *)(obj + 0x16) * 0xcd;
    hp = *(unsigned short *)(obj + 0x12);
    if (hp > (prod >> 12)) func_ov022_020acc94(obj, hp - (prod >> 12));
    else func_ov022_020acc94(obj, 1);
}
