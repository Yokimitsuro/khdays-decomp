/* func_ov249_020d3318 -- the recoil tick: bleed the stored impulse away over 0x1800 of timer,
 * then re-aim at the target; past 0x1800 the move ends.
 *
 * The impulse vector at ctx+0x1c is copied out to ctx+0x10 each tick and then decayed: the
 * elapsed time is walked in steps of 0x88, and each step scales the vector by
 * `0x1000 - FX_Mul(FX_Inv(min(step, 0x88), 0x88), 0xa4)` through func_01ffa724. Stepping rather
 * than one multiply is what the ROM does -- it keeps the decay frame-rate independent.
 *
 * Note the 64-bit constant: the multiply is a full signed 64x64 (two mla's, with the constant's
 * high word held at 0 in its own register), so 0xa4 and the 0x800 rounding are `long long`
 * literals, not ints. An int constant emits the shorter 64x32 form.
 *
 * Only past 0x800 does the re-aim run: take the vector to the target, FLATTEN it (y = 0), and use
 * its length -- capped at 0x1000 -- as the strength, its atan2 as the heading (cached at +0x44).
 * The heading becomes a {sin, 0, cos} direction via data_0203d210 (see codegen-cracks.md), which
 * func_01ffa724 scales by the strength; x and z land at ctx+0x10 / +0x18.
 *
 * The ending clears the impulse (+0x1c = 0, +0x20 = -0x1800, +0x24 = 0), drops bit 0x40 of the
 * hw60 hi-byte (it HAS the trunc pair, so bitfield form) and hands off to func_ov249_020d3530. */

typedef struct {
    int x;
    int y;
    int z;
} VecFx32;

typedef struct {
    unsigned short lo : 8;
    unsigned short hi : 8;
} Hw60;

extern int FX_Inv(int a, int b);
extern void func_01ffa724(int scale, VecFx32 *v, VecFx32 *out);
extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern int func_01ff8d18(const VecFx32 *a, const VecFx32 *b);
extern int func_020050b4(int dx, int dz);
extern void func_ov107_020c9264(int owner, int mode, int arg);
extern void func_0203c634(int self, int action, void *cb);
extern void func_ov249_020d3530(void);
extern short data_0203d210[];

void func_ov249_020d3318(int self) {
    int *ctx;
    /* Reverse of their stack order: dir at sp+0, d at sp+0xc. */
    VecFx32 d;
    VecFx32 dir;
    int step;
    int strength;
    int idx;

    ctx = *(int **)(self + 4);
    ctx[0x13] += *(int *)(*(int *)self + 0x2c);

    /* Guarded the `< 0x1800` way round so the ending falls out of line at the end of the
     * function, which is where the ROM's `bge` sends it. */
    if (ctx[0x13] < 0x1800) {
        *(VecFx32 *)((char *)ctx + 0x10) = *(VecFx32 *)((char *)ctx + 0x1c);

        step = *(int *)(*(int *)self + 0x2c);
        while (step > 0) {
            func_01ffa724(0x1000
                              - (int)(((long long)FX_Inv(step <= 0x88 ? step : 0x88, 0x88) * 0xa4LL
                                       + 0x800LL)
                                      >> 12),
                          (VecFx32 *)((char *)ctx + 0x1c), (VecFx32 *)((char *)ctx + 0x1c));
            step -= 0x88;
        }

        if (ctx[0x13] < 0x800) {
            return;
        }

        VEC_Subtract((const VecFx32 *)(*(int *)(ctx[0] + 0x3bc) + 0x190), (const VecFx32 *)ctx[3],
                     &d);
        d.y = 0;
        strength = func_01ff8d18(&d, &d);
        ctx[0x11] = func_020050b4(d.x, d.z);
        if (strength >= 0x1000) {
            strength = 0x1000;
        }

        idx = (unsigned short)(((long long)ctx[0x11] * 0x28be60db9391LL + 0x80000000000LL) >> 44)
              >> 4;
        dir.x = data_0203d210[idx * 2];
        dir.y = 0;
        dir.z = data_0203d210[idx * 2 + 1];
        func_01ffa724(strength, &dir, &dir);
        ctx[4] = dir.x;
        ctx[6] = dir.z;
        return;
    }

    if (*(unsigned char *)(ctx[1] + 0xad) != 0) {
        return;
    }
    func_ov107_020c9264(ctx[0], 0x18, 0);
    ctx[7] = 0;
    ctx[8] = -0x1800;
    ctx[9] = 0;
    ((Hw60 *)(ctx[0] + 0x60))->hi &= ~0x40;
    *(unsigned char *)((char *)ctx + 0x61) = 0;
    func_0203c634(self, *(signed char *)(self + 0x20), func_ov249_020d3530);
}
