/* Flight orientation tick of the ov219 enemy: the +0xc yaw eases towards the +0x10 target yaw
 * (four frame-times per step), the actor's +0xa0 rotation becomes the up-vector-to-+0x124 tilt
 * combined with that yaw spin, and the +0x24 velocity is written to the actor's +0xf0. Then, in
 * 0x88-frame-time slices, the velocity decays by 0x180/0x88 of the slice and the +0x20 speed by
 * 0x200/0x88 of it. */
struct Vecx32 { int x, y, z; };
struct Quat { int a, b, c, d; };

extern int func_0203d040(int cur, int target, int step, int flags);
extern void func_0202f188(struct Quat *q, const struct Vecx32 *axis, int angle);
extern void func_0202ed60(struct Quat *q, const struct Vecx32 *from, const struct Vecx32 *to);
extern void func_0202ef54(struct Quat *dst, const struct Quat *a, const struct Quat *b);
extern void func_0203c9d0(int transform, const struct Quat *q);
extern int FX_Inv(int a, int b);
extern void func_01ffa724(int scale, void *v, void *d);
extern const struct Vecx32 data_02042264;

static inline int FX_Mul(int a, int b)
{
    return (int)(((long long)a * b + 0x800) >> 12);
}

void func_ov219_020d092c(int *node)
{
    int *state = (int *)node[1];
    struct Quat spin;
    struct Quat q;
    int dt;
    int t;

    state[3] = func_0203d040(state[3], state[4], *(int *)(*node + 0x2c) << 2, 0);
    func_0202f188(&spin, &data_02042264, state[3]);
    func_0202ed60(&q, &data_02042264, (const struct Vecx32 *)(*state + 0x124));
    func_0202ef54(&q, &q, &spin);
    func_0203c9d0(*state + 0xa0, &q);
    *(struct Vecx32 *)(*state + 0xf0) = *(struct Vecx32 *)(state + 9);
    dt = *(int *)(*node + 0x2c);
    if (dt <= 0) {
        return;
    }
    do {
        t = FX_Inv(dt <= 0x88 ? dt : 0x88, 0x88);
        func_01ffa724(0x1000 - FX_Mul(t, 0x180), state + 9, state + 9);
        t = FX_Inv(dt <= 0x88 ? dt : 0x88, 0x88);
        state[8] = FX_Mul(state[8], 0x1000 - FX_Mul(t, 0x200));
        dt -= 0x88;
    } while (dt > 0);
}
