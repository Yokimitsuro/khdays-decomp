/*
 * func_ov142_020d1268 -- UNFINISHED. 196/196 bytes, ~30/30 instructions.
 * x5 family (worth 5). Semantically complete; the shape is exact bar ONE reordered pair.
 *
 * WHAT IT DOES: re-acquire the target (020cab14); none -> state 2 and advance. Aim vector from
 * the party member (state[0xf]) to the target (target+0x190), FLATTENED (y = 0), normalised;
 * heading (atan2 of x,z) into state[3]. Then state[4] = (owner_delta * 30) / 5 -- a signed
 * divide-by-5, the owner's per-frame delta scaled to a rate. Advance with a callback.
 *
 * THE DIVISION was the real content and it is SOLVED: `*(int *)(*self + 0x2c) * 0x1e / 5`.
 *  - `/ 10` (the obvious reading of Ghidra's magic-multiply) gives `asr #2` -- division by 20
 *    with this magic; wrong.
 *  - `/ 5` gives `asr #1` = division by 5, matching the ROM's `add r3, r0, r3, asr #1`.
 *  - `* 6` (the algebraic simplification, since x*30/5 == x*6) COLLAPSES to a single mul (176 B),
 *    so the ROM did NOT simplify -- it keeps the mul-by-30 and the signed divide-by-5 separate,
 *    which is what a literal `* 0x1e / 5` reproduces. mwcc will not fold `*30/5` to `*6` for a
 *    signed variable (not valid in general), so the two stay separate exactly as written.
 *
 * THE GAP (all of it): the signed-divide sequence is emitted in the other order.
 *      ROM:   ldr r1,[..] ; mul r3,r1,r0 ; lsr r0,r3,#0x1f ; smull r1,r3,r2,r3 ; add r3,r0,r3,asr#1
 *      mine:  ldr r2,[..] ; mul r3,r2,r0 ; smull r0,r2,r1,r3 ; lsr r0,r3,#0x1f ; add r2,r0,r2,asr#1
 * The ROM computes the sign bit (`lsr #0x1f`) BEFORE the `smull`; mwcc computes it after. That
 * swap propagates the r1/r2 assignment of the loaded value vs the magic constant. Same
 * instructions, one reordered pair.
 *
 * RULED OUT: the division as a separate `int delta` step, as `int t = x*0x1e; t/5`, and `* 30`
 * vs `* 0x1e` -- all byte-identical, diff pinned at 0x89. The order of the three
 * divide-by-constant instructions is fixed by mwcc's code generator, not by the C expression.
 *
 * NEXT STEP: this is the divide-by-constant SCHEDULING tie -- mwcc emits the sign-correction
 * before or after the smull by its own rule, and no source form found moves it. Belongs with the
 * register-CHOICE class in deferred-ties.md (the register swap here is downstream of the schedule
 * swap). Worth 5, so a prime candidate if the divide-sequence order ever proves steerable.
 */
extern int func_ov107_020cab14(int obj, int out);
extern void func_0203c634(int self, int idx, int cb);
extern void VEC_Subtract(void *a, void *b, void *d);
extern int func_01ff8d18(void *a, void *d);
extern int func_020050b4(int x, int z);
extern int func_ov142_020d132c;

void func_ov142_020d1268(int *self) {
    int *state = (int *)self[1];
    int target;
    int aim[3];

    target = func_ov107_020cab14(*state, 0);
    state[1] = target;
    if (target == 0) {
        *(char *)(*state + 0x1c7) = 2;
        func_0203c634((int)self, *(signed char *)((int)self + 0x20), 0);
        return;
    }
    VEC_Subtract((void *)(target + 0x190), (void *)state[0xf], aim);
    aim[1] = 0;
    func_01ff8d18(aim, aim);
    state[3] = func_020050b4(aim[0], aim[2]);
    state[4] = *(int *)(*self + 0x2c) * 0x1e / 5;
    func_0203c634((int)self, *(signed char *)((int)self + 0x20), (int)&func_ov142_020d132c);
}
