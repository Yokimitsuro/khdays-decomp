/* Per-tick decay of the spin: rebuild the heading vector, then bleed the magnitude down
 * once per 0x88 ticks elapsed.
 *
 * The stored Q12 radian at ctx[9] becomes a sin/cos table index (see func_ov137_020cc9e0
 * for that conversion) and lands as a flat XZ vector at ctx[6..8], which is then scaled by
 * the current magnitude.  ctx[7] carries the vertical component across from ctx[0xd].
 *
 * The decay loop consumes the caller's elapsed time in whole 0x88-tick steps, and for each
 * step multiplies the magnitude by `1.0 - FX_Mul(FX_Inv(min(rest, 0x88), 0x88), 0xe0)` --
 * so a full step costs 0xe0/0x1000, about 5.5%, and a partial remainder costs proportionally
 * less.  The vertical component is then debited by `elapsed * -0x50 / 0x88`, which the ROM
 * emits as a magic multiply by 0x78787879 with asr #6.
 *
 * Matched on the first compile.  Worth recording WHY, because the disassembly looks
 * intimidating: the ROM hoists six constants into callee-saved registers around the loop
 * (0x800 and 0 twice each, plus 0xe0), and those are not something the source has to
 * arrange -- they are the loop-invariant halves of the two inlined 64-bit FX_Mul expansions,
 * and mwcc hoists them by itself from the ordinary static-inline spelling.  A hoisted
 * constant is only a source-level lever when it is hoisted across a CALL, as in the 96-byte
 * Tally family; inside straight-line arithmetic the compiler already does it.
 */
extern int FX_Inv(int num, int den);
extern void func_01ffa724(int t, const int *src, int *dst);
extern const short data_0203d210[];

static inline int FX_Mul(int a, int b) {
    return (int)(((long long)a * b + 0x800) >> 12);
}

void func_ov129_020d5b08(int *self) {
    int *ctx = (int *)self[1];
    int idx;
    int n;
    int t;

    idx = (unsigned short)(((long long)ctx[9] * 0x28be60db9391LL + 0x80000000000LL) >> 44) >> 4;
    ctx[6] = data_0203d210[idx * 2];
    ctx[7] = 0;
    ctx[8] = data_0203d210[idx * 2 + 1];
    func_01ffa724(ctx[0xc], &ctx[6], &ctx[6]);
    ctx[7] = ctx[0xd];

    n = *(int *)(self[0] + 0x2c);
    if (n > 0) {
        do {
            t = FX_Inv(n <= 0x88 ? n : 0x88, 0x88);
            ctx[0xc] = FX_Mul(ctx[0xc], 0x1000 - FX_Mul(t, 0xe0));
            n = n - 0x88;
        } while (n > 0);
    }

    ctx[0xd] = ctx[0xd] + *(int *)(self[0] + 0x2c) * -0x50 / 0x88;
}
