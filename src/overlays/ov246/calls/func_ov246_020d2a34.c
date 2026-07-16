/* func_ov246_020d2a34 -- the fall tick: drop the object, orient it to the surface it is over, and
 * hand off once the landing timer expires.
 *
 * Losing the target (func_ov107_020cab14 returning 0) ends the state through func_0203c640.
 *
 * The probe is a straight -0x32000 Y ray (func_ov246_020d2764); when it finds something, the hit
 * is turned into an orientation (func_0202ed60 against the constant axis data_02042264) and
 * pushed into the sub-object at ctx[2]+4, whose height at +0x20 also creeps up by 0x100 a tick.
 *
 * The position at ctx+0x10 is rebuilt every tick from *(ctx[0]+0x398): x and z are copied
 * straight over (+0x14 / +0x1c of that block) and y advances by FX_Mul(delta * 30, 0x800) --
 * half of it, kept unfolded because that is the multiply-then-shift the ROM emits.
 *
 * The timer at +0x28 runs to 0x1000, then resets and hands off to func_ov246_020d2b8c.
 *
 * Stack (0x28): q at sp+0, v at sp+0x10, hit at sp+0x1c -- declared back-to-front, and `v` uses an
 * aggregate initialiser so its address is materialised into a register (see codegen-cracks.md);
 * ctx and delta take declaration-initialisers so they are read before the zeroing, as the ROM
 * does. */

typedef struct {
    int x;
    int y;
    int z;
} VecFx32;

typedef struct {
    int x;
    int y;
    int z;
    int w;
} Quaternion;

extern int func_ov107_020cab14(int owner, int a);
extern void func_0203c640(int self);
extern int func_ov246_020d2764(int *ctx, const VecFx32 *ray, VecFx32 *hit);
extern void func_0202ed60(Quaternion *out, const VecFx32 *axis, const VecFx32 *hit);
extern void func_0203c9d0(int obj, const Quaternion *q);
extern void func_0203ca30(int obj, const VecFx32 *v);
extern void func_0203c634(int self, int action, void *cb);
extern void func_ov246_020d2b8c(void);
extern VecFx32 data_02042264;

static inline int FX_Mul(int a, int b) {
    return (int)(((long long)a * b + 0x800) >> 12);
}

void func_ov246_020d2a34(int self) {
    int *ctx = *(int **)(self + 4);
    int delta = *(int *)(*(int *)self + 0x2c) * 30;
    VecFx32 hit;
    VecFx32 v = {0, 0, 0};
    Quaternion q;

    ctx[0xb] = func_ov107_020cab14(ctx[0], 0);
    if (ctx[0xb] == 0) {
        func_0203c640(self);
        return;
    }

    v.y = -0x32000;
    if (func_ov246_020d2764(ctx, &v, &hit) != 0) {
        func_0202ed60(&q, &data_02042264, &hit);
        func_0203c9d0(ctx[2] + 4, &q);
        ctx[8] += 0x100;
        func_0203ca30(ctx[2] + 4, (const VecFx32 *)((char *)ctx + 0x1c));
    }

    ctx[4] = *(int *)(*(int *)(ctx[0] + 0x398) + 0x14);
    ctx[5] += FX_Mul(delta, 0x800);
    ctx[6] = *(int *)(*(int *)(ctx[0] + 0x398) + 0x1c);
    func_0203ca30(ctx[1] + 4, (const VecFx32 *)((char *)ctx + 0x10));

    ctx[0xa] += *(int *)(*(int *)self + 0x2c);
    if (ctx[0xa] <= 0x1000) {
        return;
    }

    ctx[0xa] = 0;
    func_0203c634(self, *(signed char *)(self + 0x20), func_ov246_020d2b8c);
}
