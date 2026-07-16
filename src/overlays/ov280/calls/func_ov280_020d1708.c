/* func_ov280_020d1708 -- decide which way to sidestep, then hand off to func_ov280_020d18f0.
 *
 * A 2-way roll parked at +0x4a picks the method (the byte is stored and read BACK, which is why
 * the ROM masks it with `ands #0xff` -- and why the `== 2` arm exists at all even though the roll
 * itself only yields 0 or 1; the byte is the source of truth, not the roll):
 *
 *   0 -> probe both sides. Take the canned offset data_ov280_020d36a4, run it through
 *        func_ov280_020d06bc and ask func_ov280_020d0750 whether that way is blocked; then repeat
 *        with a straight +0x5000 X offset. Each block bumps a counter and sets the turn sign at
 *        +0x4f (-1 for the first, +1 for the second). BOTH blocked (count >= 2) means boxed in:
 *        play move 2 and re-enter with no callback. NEITHER blocked (count == 0) means it does
 *        not matter, so flip a coin.
 *
 *   2 -> use the geometry instead: project via func_0202f384 and take the sign of the 2D cross
 *        product (cur.x * proj.z - cur.z * proj.x). Negative turns one way, non-negative the
 *        other.
 *
 * Either way the chosen sign scales the 0x1922 turn step out of the heading at +0x1c.
 *
 * VEC_DotProduct's result is genuinely unused here -- the call is left in because the ROM makes
 * it; do not "clean it up".
 *
 * FX_Mul is inlined by the ROM (no FX_ reloc), hence the static inline; -inline on,noauto only
 * inlines what is marked. */

typedef struct {
    int x;
    int y;
    int z;
} VecFx32;

extern void func_ov280_020d0628(int self);
extern int func_02023eb4(int n);
extern void func_ov280_020d06bc(VecFx32 *out, int self, const VecFx32 *ref);
extern int func_ov280_020d0750(int self, const VecFx32 *v, int a);
extern void func_0203c634(int self, int action, void *cb);
extern void func_0202f384(VecFx32 *out, int a, const VecFx32 *b);
extern int VEC_DotProduct(const VecFx32 *a, const VecFx32 *b);
extern void func_ov280_020d0cf4(int self, int a, int b, int c, void (*cb)(void));
extern void func_ov280_020d18f0(void);
extern VecFx32 data_ov280_020d36a4;
extern VecFx32 data_02042258;

static inline int FX_Mul(int a, int b) {
    return (int)(((long long)a * b + 0x800) >> 12);
}

void func_ov280_020d1708(int self) {
    int *ctx;
    /* Reverse of their stack order: out at sp+4, v at sp+0x10 (sp+0 is the outgoing arg slot). */
    VecFx32 v;
    VecFx32 out;
    unsigned char count;

    ctx = *(int **)(self + 4);
    func_ov280_020d0628(self);
    *(unsigned char *)((char *)ctx + 0x4a) = func_02023eb4(2);

    if (*(unsigned char *)((char *)ctx + 0x4a) == 0) {
        count = 0;

        v = data_ov280_020d36a4;
        func_ov280_020d06bc(&v, self, &v);
        if (func_ov280_020d0750(self, &v, 0) != 0) {
            *(signed char *)((char *)ctx + 0x4f) = -1;
            count++;
        }

        v.x = 0x5000;
        v.y = 0;
        v.z = 0;
        func_ov280_020d06bc(&v, self, &v);
        if (func_ov280_020d0750(self, &v, 0) != 0) {
            *(signed char *)((char *)ctx + 0x4f) = 1;
            count++;
        }

        if (count >= 2) {
            *(signed char *)(ctx[0] + 0x1c7) = 2;
            func_0203c634(self, *(signed char *)(self + 0x20), 0);
            return;
        }

        if (count == 0) {
            /* Tested `== 0` so the -1 arm is emitted first (mvneq then movne), matching the ROM;
             * the `!= 0 ? 1 : -1` form emits them the other way round. */
            *(signed char *)((char *)ctx + 0x4f) = func_02023eb4(2) == 0 ? -1 : 1;
        }
        ctx[7] -= *(signed char *)((char *)ctx + 0x4f) * 0x1922;

    } else if (*(unsigned char *)((char *)ctx + 0x4a) == 2) {
        func_0202f384(&out, ctx[0] + 0xa0, &data_02042258);
        VEC_DotProduct((const VecFx32 *)((char *)ctx + 0x3c), &out);

        *(signed char *)((char *)ctx + 0x4f) =
            FX_Mul(ctx[0xf], out.z) - FX_Mul(ctx[0x11], out.x) < 0 ? 1 : -1;
        ctx[7] -= *(signed char *)((char *)ctx + 0x4f) * 0x1922;
    }

    func_ov280_020d0cf4(self, 2, 2, 0, func_ov280_020d18f0);
}
