/* func_ov206_020cd72c -- x4 (ov206/...). Advance the tracked motion, tick down four timers, nudge on
 * the active side, and publish to the owner. flag = (current scene 0206b84c() == 0x12e). Step the
 * value at +0x40 via 0203d040, turn it into a delta against data_02042264 (0202f188) and write to the
 * owner at +0xa0 (0203c9d0). Decrement each of the four bytes at +0x53..+0x56 that are still non-zero.
 * If flag: when *(ctx[1]+8) > 0x1a000 subtract 0x200 from ctx[7]; when < -0x1a000 add 0x200. Publish
 * the cached offset at +0x14 to the owner at +0xf0 and reset it to the neutral constant.
 * (Same shape as func_ov208_020d14c4; different field offsets.)
 */
typedef struct { int v[4]; } Xform;
typedef struct { int x, y, z; } Vec3;

extern int func_ov002_0206b84c(void);
extern int func_0203d040(int a, int b, int c, int *state);
extern void func_0202f188(Xform *out, const Xform *src, int v);
extern void func_0203c9d0(int dst, const Xform *x);
extern Xform data_02042264;
extern Vec3 data_02041dc8;

void func_ov206_020cd72c(int self, int p2, int p3, int p4) {
    int *ctx = *(int **)(self + 4);
    unsigned char *cb = (unsigned char *)ctx;
    int flag = (func_ov002_0206b84c() == 0x12e);
    Xform a;
    int i;
    int owner;

    ctx[0x10] = func_0203d040(ctx[0x10], ctx[0x11], ctx[0xf], 0);
    func_0202f188(&a, &data_02042264, ctx[0x10]);
    func_0203c9d0(ctx[0] + 0xa0, &a);

    for (i = 0; i < 4; i++) {
        unsigned char c = cb[i + 0x53];
        if (c != 0) {
            cb[i + 0x53] = c - 1;
        }
    }

    if (flag != 0) {
        int t = *(int *)(ctx[1] + 8);
        if (t > 0x1a000) {
            ctx[7] = ctx[7] - 0x200;
        } else if (t < -0x1a000) {
            ctx[7] = ctx[7] + 0x200;
        }
    }

    owner = *ctx;
    ctx = (int *)((char *)ctx + 0x14);
    *(Vec3 *)(owner + 0xf0) = *(Vec3 *)ctx;
    *(Vec3 *)ctx = data_02041dc8;
}
