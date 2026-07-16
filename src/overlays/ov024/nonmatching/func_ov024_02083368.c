/* func_ov024_02083368 -- MobiClip: resolve up to three stream descriptors, then start them.
 * `desc` is three 8-byte entries; an entry whose s16 tag is 2 is resolved through
 * func_02021948 into a handle, and entries with any other tag stay 0 (absent).
 * The three handles are then handed to func_ov024_02082c98 together.
 * THUMB; the tail is a blx because 02082c98 is ARM.
 *
 * NONMATCHING: register permutation only -- 80/80 bytes, every instruction in the right place,
 * identical prologue, first diff at 0x18. Only three low registers are free (r5=desc, r6=owner),
 * so one of the three handles must spill to [sp]. The ROM assigns them in first-use order and
 * spills the last (h0->r7, h1->r4, h2->[sp]); mwcc rotates it (h0->r4, h1->[sp], h2->r7) and
 * spills the middle one instead. The permutation carries through to the final call's arg setup.
 * Tried and rejected: decl order h1/h2/h0, decl order h0/h1/h2, and both init orders --
 * the mapping never moves, so it is not decl-order driven here (it follows first use).
 *
 * The THUMB `movs r0,#N; ldrsh r0,[r5,r0]` pairs are not a quirk to steer around: THUMB ldrsh
 * has no immediate-offset form, only register-offset. */
extern int func_02021948(int owner, short *entry);
extern void func_ov024_02082c98(int a, int b, int c);

int func_ov024_02083368(int owner, short *desc) {
    int h0;
    int h1;
    int h2;

    h0 = 0;
    h1 = 0;
    h2 = 0;
    if (desc[0] == 2) {
        h0 = func_02021948(owner, desc);
    }
    if (desc[4] == 2) {
        h1 = func_02021948(owner, desc + 4);
    }
    if (desc[8] == 2) {
        h2 = func_02021948(owner, desc + 8);
    }
    func_ov024_02082c98(h0, h1, h2);
    return 1;
}
