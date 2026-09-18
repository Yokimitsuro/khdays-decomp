/* Wind-up tick of the ov114 enemy: the +0x50 heading is the flat (sin, 0, cos) of the +0x14
 * yaw scaled by the +0x68 speed, which bleeds FX_Mul(elapsed x 30, 0x10) per frame; the +0x44
 * charge accumulates the elapsed time and, crossing 0x1000, fires cc6f4 exactly once (+0x49),
 * zeroing the speed when it lands. Once the byte the +0xc pointer refers to clears, the next
 * +0x4c delay is rolled in [+0x224, +0x228] of the actor, sub-state 2 is requested and the
 * state ends with no successor. */
extern void func_01ffa724(int t, const int *src, int *dst);
extern int func_ov277_020d1d00(int *ctx);
extern int func_02023eb4(int range);
extern void func_0203c634(int *self, int action, void *cb);
extern const short data_0203d210[];

static inline int FX_Mul(int a, int b) {
    return (int)(((long long)a * b + 0x800) >> 12);
}

void func_ov277_020d3254(int *self)
{
    int *ctx = (int *)self[1];
    int idx;
    int lo;

    idx = (unsigned short)(((long long)ctx[5] * 0x28be60db9391LL + 0x80000000000LL) >> 44) >> 4;
    ctx[0x14] = data_0203d210[idx * 2];
    ctx[0x15] = 0;
    ctx[0x16] = data_0203d210[idx * 2 + 1];
    func_01ffa724(ctx[0x1a], &ctx[0x14], &ctx[0x14]);
    ctx[0x1a] = ctx[0x1a] - FX_Mul(*(int *)(self[0] + 0x2c) * 0x1e, 0x10);
    ctx[0x11] = ctx[0x11] + *(int *)(self[0] + 0x2c);
    if (*(unsigned char *)((char *)ctx + 0x49) == 0 && ctx[0x11] >= 0x1000) {
        *(unsigned char *)((char *)ctx + 0x49) = 1;
        if (func_ov277_020d1d00(ctx) != 0) {
            ctx[0x1a] = 0;
        }
    }
    if (*(unsigned char *)ctx[3] != 0) {
        return;
    }
    lo = *(int *)(ctx[0] + 0x224);
    ctx[0x13] = lo + func_02023eb4((*(int *)(ctx[0] + 0x228) - lo < 0
                                    ? -(*(int *)(ctx[0] + 0x228) - lo)
                                    : *(int *)(ctx[0] + 0x228) - lo) + 1);
    *(signed char *)(ctx[0] + 0x1c7) = 2;
    func_0203c634(self, *(signed char *)((char *)self + 0x20), 0);
}
