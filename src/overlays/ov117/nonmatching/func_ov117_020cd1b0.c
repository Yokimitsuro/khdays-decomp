/* NONMATCHING -- 324/324 B, and the only difference is WHERE ONE LOAD IS SCHEDULED:
 *     ROM : ldr r2,[sp,#8] ; ldr r1,[sp] ; mov r0,#0 ; str ; str ; ... ; str r2
 *     mwcc: ldr r1,[sp] ; mov r0,#0 ; str ; str ; ldr r2,[sp,#8] ; str r2
 * Same instructions, same registers, same STORE order -- only the v[2] load moves.
 * Ruled out: all three orderings of the three assignments, and declaring `v` as a struct
 * with named fields. The scheduler does not follow the source order here.
 *
 * Head of a 5-member family (324 B), so it is worth finishing.
 *
 * SOLVED on the way -- do NOT rediscover:
 *  - func_ov117_020cc5c0 is called with TWO arguments here (r0, r1). Ghidra shows four;
 *    r2/r3 are leftovers the preceding bl clobbered. NOTE the same callee takes THREE in
 *    ov117_020cccb4 and ov117_020ccdf4 -- it is unprototyped, so the arity is per-call-site
 *    and must be read from the disassembly every time.
 *  - the bit test at +0x17a needs a 1-bit BITFIELD (`unsigned char b0 : 1`). The explicit
 *    `((unsigned)x << 31) >> 31` folds to `tst #1` and is 4 B short.
 *  - `n / 30` reproduces the ROM's magic multiply (0x88888889, add, asr #4).
 *  - `obj[0xc] = -0x200;` really does compile to `mov #0x200 ; rsb #0` -- that is the ROM's
 *    form, not a missed `mvn`. */
typedef struct { unsigned char b0 : 1; } Bit0;
extern int  func_ov107_020cab14(int obj, int flag);
extern void func_0203c634(int self, int index, void *cb);
extern void VEC_Subtract();
extern int  func_01ff8d18();
extern void func_ov117_020cc5c0();
extern void func_01ffa724();
extern void func_ov117_020cd2f4(void);

void func_ov117_020cd1b0(int self) {
    int *obj = *(int **)(self + 4);
    int v[3];
    int n;
    int target = func_ov107_020cab14(*obj, 0);

    obj[1] = target;
    if (target == 0) {
        *(signed char *)(*obj + 0x1c7) = 2;
        func_0203c634(self, *(signed char *)(self + 0x20), 0);
        return;
    }
    VEC_Subtract(target + 400, *obj + 0xb0, v);
    n = func_01ff8d18(v, v);
    if (n > 0x8000) {
        n = 0x8000;
    }
    func_ov117_020cc5c0((int)obj, obj + 6);
    obj[0xc] = -0x200;
    if (((Bit0 *)(*obj + 0x17a))->b0) {
        obj[0x19] = v[0];
        obj[0x1a] = 0;
        obj[0x1b] = v[2];
        func_01ff8d18(obj + 0x19, obj + 0x19);
        func_01ffa724(n / 30, obj + 0x19, obj + 0x19);
        obj[0x18] = 0;
        obj[0x1c] = *(int *)(obj[0x11] + 4);
        {
            unsigned short w = *(unsigned short *)(*obj + 0x60);
            *(unsigned short *)(*obj + 0x60) =
                (unsigned short)((w & ~0xff00)
                                 | (((((unsigned int)w << 0x10) >> 0x18 | 2) << 0x18) >> 0x10));
        }
        func_0203c634(self, *(signed char *)(self + 0x20), &func_ov117_020cd2f4);
    }
}
