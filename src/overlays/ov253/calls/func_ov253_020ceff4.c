/* func_ov253_020ceff4 -- ease the object toward its target: burn the owner's frame delta off the
 * remaining time at ctx[0xb] (never below zero), step the interpolator (func_0203d040) and apply
 * the result to the transform at +0xa0. */
extern int func_0203d040(int a, int b, int c, int d);
extern void func_0203c9b4(int dst, void *src, int v);
extern int data_02042264;

void func_ov253_020ceff4(int *self) {
    int *ctx = (int *)self[1];
    if (ctx[0xb] > 0) {
        ctx[0xb] = ctx[0xb] - *(int *)(self[0] + 0x2c);
    }
    ctx[4] = func_0203d040(ctx[4], ctx[5], ctx[6], 0);
    func_0203c9b4(ctx[0] + 0xa0, &data_02042264, ctx[4]);
}
