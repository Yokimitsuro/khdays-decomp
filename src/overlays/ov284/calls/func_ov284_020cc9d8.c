/* Turn tick of the ov284 enemy: the +0x18 rate is 30 x dt / 15, the +0x20 timer counts the
 * frame-time down while positive, the +0x10 yaw steps towards the +0x14 target yaw by the rate
 * and the actor's +0xa0 orientation is rebuilt from the yaw about world Y. */
typedef struct { int x, y, z; } Vec3;
extern int func_0203d040(int cur, int want, int step, int *state);
extern void func_0203c9b4(void *quat, const Vec3 *axis, int angle);
extern const Vec3 data_02042264;

void func_ov284_020cc9d8(int *self) {
    int *ctx = (int *)self[1];
    ctx[6] = *(int *)(self[0] + 0x2c) * 30 / 15;
    if (ctx[8] > 0) {
        ctx[8] = ctx[8] - *(int *)(self[0] + 0x2c);
    }
    ctx[4] = func_0203d040(ctx[4], ctx[5], ctx[6], 0);
    func_0203c9b4((void *)(ctx[0] + 0xa0), &data_02042264, ctx[4]);
}
