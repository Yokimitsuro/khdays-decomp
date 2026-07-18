/* func_ov138_020d0a30 -- x3 (ov137/...). Advance the tracked motion and publish it to the owner.
 * The stored value at +0xc is stepped by func_0203d040 (which also updates the state block at +0x40),
 * the step is turned into a delta against data_02042264, composed with the owner's own rig value
 * (+0x124), and the result written to the owner at +0xa0. A non-negative countdown at +0x44 is debited
 * by the caller's per-tick amount (+0x2c of self[0]). Finally the cached offset at +0x18 is published
 * to the owner at +0xf0 and reset to the neutral constant. (Twin of func_ov158_020ccdf0; differs only
 * in the countdown test: >= 0 here vs > 0 there.) */

typedef struct {
    int v[4];
} Xform;

typedef struct {
    int x;
    int y;
    int z;
} Vec3;

extern int func_0203d040(int a, int b, int c, int *state);
extern void func_0202f188(Xform *out, const Xform *src, int v);
extern void func_0202ed60(Xform *out, const Xform *src, int rig);
extern void func_0202ef54(Xform *out, const Xform *a, const Xform *b);
extern void func_0203c9d0(int dst, const Xform *x);
extern Xform data_02042264;
extern Vec3 data_02041dc8;

void func_ov138_020d0a30(int self) {
    int *ctx;
    Xform b;
    Xform a;
    int owner;

    ctx = *(int **)(self + 4);
    ctx[3] = func_0203d040(ctx[3], ctx[4], ctx[5], &ctx[0x10]);
    func_0202f188(&a, &data_02042264, ctx[3]);
    func_0202ed60(&b, &data_02042264, ctx[0] + 0x124);
    func_0202ef54(&b, &b, &a);
    func_0203c9d0(ctx[0] + 0xa0, &b);

    if (ctx[0x11] >= 0) {
        ctx[0x11] = ctx[0x11] - *(int *)(*(int *)self + 0x2c);
    }

    /* ctx is walked forward here on purpose: reading the owner and stepping to +0x18 in one go is
     * what gives the ROM's post-indexed `ldr r0,[r4],#0x18`. It is ctx's last use. */
    owner = *ctx;
    ctx = (int *)((char *)ctx + 0x18);
    *(Vec3 *)(owner + 0xf0) = *(Vec3 *)ctx;
    *(Vec3 *)ctx = data_02041dc8;
}
