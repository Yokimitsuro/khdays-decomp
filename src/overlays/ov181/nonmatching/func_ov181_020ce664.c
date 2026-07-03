/* func_ov181_020ce664 (x6 family: ov182/183/184/250/251) — NON-MATCHING.
 * Semantically byte-exact except ONE scheduling tie: the hw60 hi-byte clear
 * (`->hi &= ~0x40`) emits `bic lr,lr,#0xff00` 4 instructions too early. The
 * original delays clearing the destination high byte until after the source
 * byte is masked (it hoists the state[0x6c]=0 zero + SetIndexedSlot arg loads
 * into that window instead); mwcc schedules the bic greedily-first. Every
 * value-computation spelling tried (struct bitfield, explicit-shift with the
 * (u&~0xff00) operand first/last, (unsigned short)-cast to force the 16-bit
 * mask) reproduces the exact bytes but not the bic position — the known hw60
 * bic-position tie (cf. ov269_020d382c). asm stub stays byte-exact via dsd. */
struct b1 { unsigned char b:1; };
struct hw { unsigned short lo:8, hi:8; };
struct v3 { int x, y, z; };

extern void func_ov107_020c9264(int a, int b, int c);
extern void func_ov107_020c9ee8(int a, int b, int c);
extern void func_0203c634(int node, int slot, void *cb);
extern void func_ov181_020ce748(void);

void func_ov181_020ce664(int node) {
    int state = *(int *)(node + 4);
    *(struct v3 *)(state + 0x54) = *(struct v3 *)(state + 0x78);
    *(int *)(state + 0x7c) -=
        (int)((0x800 + ((long long)(*(int *)(*(int *)node + 0x2c) * 30) << 7)) >> 12);
    if (!((struct b1 *)(*(int *)state + 0x17a))->b) return;
    func_ov107_020c9264(*(int *)state, 0x12, 0);
    func_ov107_020c9ee8(*(int *)(*(int *)state + 0x390), 0, 0);
    ((struct hw *)(*(int *)state + 0x60))->hi &= ~0x40;
    *(int *)(state + 0x6c) = 0;
    *(unsigned char *)(state + 0x51) &= ~2;
    func_0203c634(node, *(signed char *)(node + 0x20), &func_ov181_020ce748);
}
