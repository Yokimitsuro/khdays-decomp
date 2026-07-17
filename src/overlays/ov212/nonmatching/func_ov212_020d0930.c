/*
 * func_ov212_020d0930 -- UNFINISHED. 280/280 bytes, 70/70 instructions.
 * x3 family (ov266/ov267) -> worth 3. ONE instruction is in a different scheduling
 * slot; everything else is byte-identical.
 *
 * WHAT IT DOES: steer toward the anchor. If bit 0 of the hw60 lo byte is set, run
 * 020ce120 first. Take the vector from the anchor (ctx[2]) to the owner's point
 * (owner+0x190), cache its heading as a Q12-radian angle (atan2 = 020050b4(dx, dz))
 * at ctx+0x3c, and measure how far past the owner's reach (+0x80) it is. Convert the
 * heading to a 16-bit table index, write {sin, 0, cos} into ctx+0x10, scale it by the
 * owner's speed (+0x578) in place, and once inside 0x2000 latch slot 2 and advance.
 *
 * SOLVED HERE, keep both (each was worth a real chunk of the diff):
 *  - The Q12-radians -> index -> sin/cos block is the catalogued crack and came out
 *    byte-identical first try:
 *      idx = (unsigned short)(((long long)a * 0x28be60db9391LL + 0x80000000000LL) >> 44) >> 4;
 *      data_0203d210[idx*2] / [idx*2+1] = sin / cos
 *  - `*ctx` must be cached in a LOCAL across the func_01ff8d18 call:
 *      { int node = *ctx; dist = func_01ff8d18(&d, &d) - *(int *)(node + 0x80); }
 *    Spelling it `- *(int *)(*ctx + 0x80)` makes mwcc reload *ctx AFTER the call
 *    instead of hoisting it into r5 before. That alone moved the diff 0x59 -> 0x84.
 *    (Related to the `call() - expr` entry in codegen-cracks.md, but the opposite
 *    direction: here the ROM hoists and the naive form reloads.)
 *
 * THE DIFF: `add r1, r4, #0x10` -- the address of the {sin,0,cos} vector, which is
 * passed to func_01ffa724 as BOTH pointer arguments (`mov r2, r1`). The ROM computes
 * it at +0x084, filling the true-dependency stall between `asr r7, r8, #0x1f` and the
 * `mla sb, r7, r3, sb` that consumes r7. mwcc computes it ~10 instructions later,
 * after `lsl r7, r0, #1`. Both fill a slot; both are legal; the register is the same.
 * Note the three stores go through `[r4, #0x10/0x14/0x18]` directly -- r1 is used
 * ONLY as the call argument, so the pointer is not the stores' base.
 *
 * PRE-PARK CHECKLIST -- all four run:
 *  1. --thumb: ARM gives the exact 280/280.
 *  2. Arity, every callee checked against real (non-asm_stub) call sites in the tree:
 *     020050b4(dx, dz) 2 · 01ff8d18(v, out) 2 · 01ffa724(scale, v, out) 3 ·
 *     0203c634(self, slot, cb) 3 · VEC_Subtract(a, b, out) 3. All agree with the
 *     ROM's own register setup. 020ce120 is undone, but the ROM sets r0/r1/r2 and
 *     r0/r1 are already live (self, *ctx), so 3 is the only reading.
 *  3. No constant is in the wrong register.
 *  4. Diff read back: one instruction, moved, same operands and same destination reg.
 *
 * RULED OUT (6 spellings, all still 280/280 with the diff pinned at 0x84):
 *   the vector's address as a pointer local declared at the top of the function
 *   ... declared immediately before the conversion (so it precedes it in program order)
 *   ... used for the three stores as well (`out->x = ...`) instead of ctx[4..6]
 *   ... used ONLY as the call argument, stores left on ctx[4..6] (the ROM's own shape)
 *   ... with the 0x578 scale hoisted into a local too
 *   `(int *)` instead of `(struct vec3 *)` for the cached node pointer
 *
 * NEXT STEP: the axis is which stall slot in the 64x64 multiply chain mwcc fills. I
 * could not reach it from the source -- the add is ready from the function's first
 * instruction in every spelling, so program order does not appear to be the lever.
 * Do NOT file this as a "scheduler tie" and stop: that label has been wrong ~20 times
 * in this project. It is one unexplained slot on an otherwise perfect function.
 */
struct vec3 { int x, y, z; };
struct hw60 { unsigned short lo : 8, hi : 8; };

extern void func_ov212_020ce120(void *self, int a, int b);
extern int VEC_Subtract(void *a, void *b, void *out);
extern int func_020050b4(int a, int b);
extern int func_01ff8d18(const struct vec3 *v, struct vec3 *out);
extern void func_01ffa724(int s, struct vec3 *v, struct vec3 *out);
extern void func_0203c634(void *self, int idx, void *cb);
extern short data_0203d210[];

void func_ov212_020d0930(void *self) {
    int *ctx = *(int **)((char *)self + 4);
    struct vec3 d;
    int dist;
    unsigned int idx;

    if (((struct hw60 *)(*ctx + 0x60))->lo & 1) {
        func_ov212_020ce120(self, *ctx, ctx[2]);
    }
    VEC_Subtract((void *)(*ctx + 0x190), (void *)ctx[2], &d);
    ctx[0xf] = func_020050b4(d.x, d.z);
    { int node = *ctx;
    dist = func_01ff8d18(&d, &d) - *(int *)(node + 0x80); }
    idx = (unsigned short)(((long long)ctx[0xf] * 0x28be60db9391LL + 0x80000000000LL) >> 44) >> 4;
    ctx[4] = data_0203d210[idx * 2];
    ctx[5] = 0;
    ctx[6] = data_0203d210[idx * 2 + 1];
    func_01ffa724(*(int *)(*ctx + 0x578), (struct vec3 *)(ctx + 4), (struct vec3 *)(ctx + 4));
    if (dist >= 0x2000) {
        return;
    }
    *(char *)(*ctx + 0x1c7) = 2;
    func_0203c634(self, *(signed char *)((char *)self + 0x20), 0);
}
