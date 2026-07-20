/* Per-frame step of the wind-up: rebuild the heading, bleed the speed, and hand over to
 * the next state once the charge is full.
 *
 * The stored Q12 radian at ctx[5] becomes a sin/cos table index and lands as a flat XZ
 * vector at ctx[0x15..0x17], scaled by the current speed.  The speed then loses
 * `FX_Mul(elapsed * 30, 0x10)` per frame, and the charge at ctx[7] accumulates the raw
 * elapsed time; crossing 0x1000 fires the one-shot at ctx+0x50 exactly once.
 *
 * The exit is gated on the byte the pointer at ctx[3] refers to.  When it clears, roll the
 * next delay uniformly in [+0x224, +0x228] with the range forced positive, request state 2
 * on the owner and end the state with no successor.
 *
 * Matched first try.  The `* 0x10` in the speed decay is spelled as an FX_Mul like every
 * other fixed-point product here even though the constant is a power of two -- mwcc turns
 * it into the shift-and-carry sequence itself, and writing the shifts by hand is not what
 * the ROM did.
 */
extern void func_01ffa724(int t, const int *src, int *dst);
extern void func_ov184_020d2164(int *ctx);
extern int func_02023eb4();
extern void func_0203c634(int *self, int action, void *cb);
extern const short data_0203d210[];

static inline int FX_Mul(int a, int b) {
    return (int)(((long long)a * b + 0x800) >> 12);
}

void func_ov184_020d3a64(int *self) {
    int *ctx = (int *)self[1];
    int idx;
    int lo;

    idx = (unsigned short)(((long long)ctx[5] * 0x28be60db9391LL + 0x80000000000LL) >> 44) >> 4;
    ctx[0x15] = data_0203d210[idx * 2];
    ctx[0x16] = 0;
    ctx[0x17] = data_0203d210[idx * 2 + 1];
    func_01ffa724(ctx[0x1c], &ctx[0x15], &ctx[0x15]);

    ctx[0x1c] = ctx[0x1c] - FX_Mul(*(int *)(self[0] + 0x2c) * 0x1e, 0x10);

    ctx[7] = ctx[7] + *(int *)(self[0] + 0x2c);
    if (ctx[7] >= 0x1000 && *(unsigned char *)((char *)ctx + 0x50) == 0) {
        *(unsigned char *)((char *)ctx + 0x50) = 1;
        func_ov184_020d2164(ctx);
    }

    if (*(unsigned char *)ctx[3] != 0) {
        return;
    }

    lo = *(int *)(ctx[0] + 0x224);
    ctx[0x1d] = lo + func_02023eb4((*(int *)(ctx[0] + 0x228) - lo < 0
                                    ? -(*(int *)(ctx[0] + 0x228) - lo)
                                    : *(int *)(ctx[0] + 0x228) - lo) + 1);
    *(signed char *)(ctx[0] + 0x1c7) = 2;
    func_0203c634(self, *(signed char *)((char *)self + 0x20), 0);
}
