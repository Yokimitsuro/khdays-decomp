/* Spin tick of the ov245 enemy's body: the +0x10 angle eases towards the +0x14 target (0203d040,
 * three times the frame step), the owner's +0xa0 transform takes that yaw, and the owner's +0x3bc
 * velocity loses 15.6 % per 1/30 s slice of the frame. */
typedef struct { int x, y, z; } Vec3;
typedef struct { int x, y, z, w; } Quat;

extern int func_0203d040(int a, int b, int c, int d);
extern void func_0202f188(Quat *out, const Vec3 *axis, int angle);
extern void func_0203c9d0(void *srt, Quat *q);
extern int FX_Inv(int num, int den);
extern void func_01ffa724(int scale, void *v, void *out);
extern const Vec3 data_02042264;

#define FX_MUL(a, b) ((int)(((long long)(a) * (b) + 0x800) >> 12))

void func_ov245_020d22e0(int *node)
{
    int *state = (int *)node[1];
    Quat q;
    int rem;

    state[4] = func_0203d040(state[4], state[5], *(int *)(node[0] + 0x2c) * 3, 0);
    func_0202f188(&q, &data_02042264, state[4]);
    func_0203c9d0((void *)(*state + 0xa0), &q);
    for (rem = *(int *)(node[0] + 0x2c); rem > 0; rem -= 0x88) {
        int t = FX_Inv(rem <= 0x88 ? rem : 0x88, 0x88);

        func_01ffa724(0x1000 - FX_MUL(t, 0x280), (void *)(*state + 0x3bc), (void *)(*state + 0x3bc));
    }
}
