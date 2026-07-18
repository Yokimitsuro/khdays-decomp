/* func_ov268_020d14cc -- x3 (ov208/...). Advance the tracked motion, tick down four timers, nudge on
 * the active side, and publish to the owner. flag = (current scene 0206b84c() == 0x12e). Step the
 * value at +0x30 via 0203d040, turn it into a delta against data_02042264 (0202f188) and write to the
 * owner at +0xa0 (0203c9d0). Decrement each of the four bytes at +0x4a..+0x4d that are still non-zero.
 * If flag: when *(ctx[2]+8) > 0x1a000 subtract 0x200 from ctx[7]; when < -0x1a000 add 0x200. Publish
 * the cached offset at +0x14 to the owner at +0xf0 and reset it to the neutral constant.
 */
typedef struct { int v[4]; } Xform;
typedef struct { int x, y, z; } Vec3;

extern int func_ov002_0206b84c(void);
extern int func_0203d040(int a, int b, int c, int *state);
extern void func_0202f188(Xform *out, const Xform *src, int v);
extern void func_0203c9d0(int dst, const Xform *x);
extern Xform data_02042264;
extern Vec3 data_02041dc8;

void func_ov268_020d14cc(int self, int p2, int p3, int p4) {
    int *ctx = *(int **)(self + 4);
    unsigned char *cb = (unsigned char *)ctx;
    int flag = (func_ov002_0206b84c() == 0x12e);
    Xform a;
    int i;
    int owner;

    ctx[0xc] = func_0203d040(ctx[0xc], ctx[0xd], ctx[0x18], 0);
    func_0202f188(&a, &data_02042264, ctx[0xc]);
    func_0203c9d0(ctx[0] + 0xa0, &a);

    for (i = 0; i < 4; i++) {
        unsigned char c = cb[i + 0x4a];
        if (c != 0) {
            cb[i + 0x4a] = c - 1;
        }
    }

    if (flag != 0) {
        int t = *(int *)(ctx[2] + 8);
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
