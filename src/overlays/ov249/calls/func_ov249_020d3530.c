/* func_ov249_020d3530 -- the slam tick: the impulse at ctx+0x1c is copied out to
 * ctx+0x10 and then grown, walking the elapsed time in steps of 0x88 and scaling it by
 * `0x1000 + FX_Mul(FX_Inv(min(step, 0x88), 0x88), 0xab)` each step (see func_ov228_020d159c for
 * the decaying twin). The owner's +0x494 contact sphere, moved by the copied impulse, is swept
 * with kind 2 (func_ov249_020d0c28). Once the owner lands (+0x17a bit 0) the owner's +0x180 point
 * is kept at ctx+0x34 with its height lowered to the owner's +0x80 floor less 0x200, effect 6
 * spawns there, animation 0x19 plays, reaction 0x145 mode 0xc fires at it, the timer at +0x4c
 * restarts and the tick hands over to func_ov249_020d36b8. */

typedef struct {
    int x;
    int y;
    int z;
} VecFx32;

typedef struct {
    VecFx32 pos;
    int radius;
} Sphere;

struct Bits17a { unsigned char b0 : 1; };

extern int FX_Inv(int a, int b);
extern void func_01ffa724(int scale, VecFx32 *v, VecFx32 *out);
extern void VEC_Add(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void func_ov249_020d0c28(int *ctx, int kind, Sphere *sphere, void *box);
extern void func_ov107_020c0b90(int actor, int a, VecFx32 v, int b);
extern void func_ov107_020c9264(int owner, int mode, int arg);
extern void func_ov107_020c5af8(int owner, int id, int mode, void *at);
extern void func_0203c634(int self, int action, void *cb);
extern void func_ov249_020d36b8(void);

void func_ov249_020d3530(int self) {
    int *ctx;
    Sphere sphere;
    int step;

    ctx = *(int **)(self + 4);
    *(VecFx32 *)((char *)ctx + 0x10) = *(VecFx32 *)((char *)ctx + 0x1c);

    step = *(int *)(*(int *)self + 0x2c);
    while (step > 0) {
        func_01ffa724((int)(((long long)FX_Inv(step <= 0x88 ? step : 0x88, 0x88) * 0xabLL
                             + 0x800LL)
                            >> 12)
                          + 0x1000,
                      (VecFx32 *)((char *)ctx + 0x1c), (VecFx32 *)((char *)ctx + 0x1c));
        step -= 0x88;
    }

    sphere = *(Sphere *)(ctx[0] + 0x494);
    VEC_Add(&sphere.pos, (VecFx32 *)((char *)ctx + 0x10), &sphere.pos);
    func_ov249_020d0c28(ctx, 2, &sphere, 0);
    if (((struct Bits17a *)(ctx[0] + 0x17a))->b0 == 0) {
        return;
    }
    *(VecFx32 *)((char *)ctx + 0x34) = *(VecFx32 *)(ctx[0] + 0x180);
    ctx[0xe] -= *(int *)(ctx[0] + 0x80) - 0x200;
    func_ov107_020c0b90(ctx[0], 6, *(VecFx32 *)((char *)ctx + 0x34), 0);
    func_ov107_020c9264(ctx[0], 0x19, 0);
    func_ov107_020c5af8(ctx[0], 0x145, 0xc, (char *)ctx + 0x34);
    ctx[0x13] = 0;
    func_0203c634(self, *(signed char *)(self + 0x20), func_ov249_020d36b8);
}
