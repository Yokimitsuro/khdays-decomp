/* Mount step: once both riders (+0x3b4 / +0x3b8) raise bit 1 of their +0x1ac flags the actor's
 * +0x3bd latch is set; the +0xc yaw steps towards the +0x10 target by the +0x14 rate and the
 * +0xa0 orientation is rebuilt about world Y; the +0x54 timer counts the frame step down while positive; the
 * velocity is handed to the actor's +0xf0 motion slot and cleared. */
typedef struct { int x, y, z; } Vec3;
extern int func_0203d040(int cur, int want, int step, int *state);
extern void func_0203c9b4(void *quat, const Vec3 *axis, int angle);
extern const Vec3 data_02042264;
extern const Vec3 data_02041dc8;

void func_ov278_020cf984(int *self) {
    int *ctx = (int *)self[1];
    {
        int actor = ctx[0];
        int b = *(unsigned short *)(*(int *)(actor + 0x3b8) + 0x100 + 0xac) & 2;
        int a = *(unsigned short *)(*(int *)(actor + 0x3b4) + 0x100 + 0xac) & 2;
        if (a != 0 && b != 0) {
            *(unsigned char *)(actor + 0x3bd) = 1;
        }
    }
    ctx[3] = func_0203d040(ctx[3], ctx[4], ctx[5], 0);
    func_0203c9b4((void *)(ctx[0] + 0xa0), &data_02042264, ctx[3]);
    if (ctx[0x15] > 0) {
        ctx[0x15] -= *(int *)(self[0] + 0x2c);
    }
    {
        Vec3 *p18 = (Vec3 *)(ctx + 6);
        *(Vec3 *)(ctx[0] + 0xf0) = *p18;
        *p18 = data_02041dc8;
    }
}
