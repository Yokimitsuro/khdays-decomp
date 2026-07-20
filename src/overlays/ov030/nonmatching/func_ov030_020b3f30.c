/* NONMATCHING: equivalent C, global callee-saved coloring-direction tie
 * (count=5, 208B). Logic/structure/size byte-exact. Same class as ov127/ov142.
 *
 * BEST FORM (2026-07-20): 32 bytes differ, down from 54. The improvement was
 * hoisting `slot` to function scope and declaring the long-lived locals in the
 * ROM's register order `obj, i, slot, acc7, acc8` -- that pins obj->r4 and
 * slot->r6 correctly (the old form left slot loop-scoped, so it never took part
 * in the function-scope coloring). What still ties:
 *   - {i, acc7, acc8}: ROM colours i->r5, acc7->r7, acc8->r8; mwcc gives
 *     i->r7, acc7->r8, acc8->r5. The three are initialised to 0 and mwcc
 *     coalesces the zero-copies in the opposite direction. Init order
 *     (i-first, acc=i copies, do/while) was tried -- all 35, i.e. worse.
 *   - {p, j} scratch: ROM p->r2, j->r1; mwcc p->r1, j->r2.
 * The ov131 nested-block crack (2026-07-20) does NOT transfer: it reassigns a
 * PAIR of pointers tied for one register slot; this is a 3-way accumulator
 * colour plus a scratch swap, a different flavour.
 *
 * Semantics: for i in 0..3, scan up to 8 slots at this+0x234 (stride 0x170)
 * for the first with byte[+0x12c]==0; init that slot (0x148/0x14c=0, 0x150/
 * 0xb0/0xb4/0xb8=0x1000, 0x138=obj->0x490, 0x154=0xa000, 0x158=0x119a, 0x15c=
 * (s16)obj->0x66, 0x12c=1, 0x130=0, 0x134=i*0x2000, 0x15e=i*0x3fff), call
 * func_ov030_020b4048 mid-init and func_ov030_020b4024 at end. */
extern void func_ov030_020b4048(int slot, int b);
extern void func_ov030_020b4024(int slot);

void func_ov030_020b3f30(int this_) {
    int obj;
    int i;
    int slot;
    int acc7;
    int acc8;

    obj = *(int *)(this_ + 0xdb4);
    acc7 = 0;
    acc8 = 0;

    for (i = 0; i < 4; i++) {
        char *p = (char *)(this_ + 0x234);
        int j;
        for (j = 0; j < 8; j++) {
            slot = (int)p;
            if (*(unsigned char *)(p + 0x12c) == 0) break;
            p += 0x170;
        }
        *(int *)(slot + 0x148) = 0;
        *(int *)(slot + 0x14c) = 0;
        *(int *)(slot + 0x150) = 0x1000;
        func_ov030_020b4048(slot, 0);
        *(int *)(slot + 0xb8) = 0x1000;
        *(int *)(slot + 0xb4) = 0x1000;
        *(int *)(slot + 0xb0) = 0x1000;
        *(int *)(slot + 0x138) = *(int *)(obj + 0x490);
        *(int *)(slot + 0x154) = 0xa000;
        *(int *)(slot + 0x158) = 0x119a;
        *(signed char *)(slot + 0x15c) = *(short *)(obj + 0x66);
        *(unsigned char *)(slot + 0x12c) = 1;
        *(int *)(slot + 0x130) = 0;
        *(int *)(slot + 0x134) = acc7;
        *(unsigned short *)(slot + 0x15e) = acc8;
        func_ov030_020b4024(slot);
        acc7 += 0x2000;
        acc8 += 0x3fff;
    }
}
