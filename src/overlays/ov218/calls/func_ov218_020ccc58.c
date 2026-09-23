/* Spin tick of the ov218 actor: the +0xc heading turns toward the +0x10 goal at four times the frame
 * rate (0203d040); the actor's pose becomes the rotation from up to its +0x124 normal combined with the
 * heading about up, its +0xf0 velocity mirrors +0x28, and for the frame (in 0x88-sized slices) the
 * velocity damps by 0.12 and the +0x1c spin by 0.125 per slice. */
typedef struct { int x, y, z; } Vec3;
typedef struct { int x, y, z, w; } Quat;

extern int func_0203d040(int a, int b, int c, int d);
extern void func_0202f188(Quat *out, const Vec3 *axis, int angle);
extern void func_0202ed60(Quat *out, const Vec3 *from, const Vec3 *to);
extern void func_0202ef54(Quat *out, const Quat *a, const Quat *b);
extern void func_0203c9d0(void *srt, const Quat *rot);
extern int FX_Inv(int num, int den);
extern void func_01ffa724(int scale, const Vec3 *v, Vec3 *out);
extern const Vec3 data_02042264;

#define FX_MUL(a, b) ((int)(((long long)(a) * (b) + 0x800) >> 12))

void func_ov218_020ccc58(int *node)
{
    int *state = (int *)node[1];
    Quat spin;
    Quat tilt;
    int remaining;

    state[3] = func_0203d040(state[3], state[4], *(int *)(node[0] + 0x2c) * 4, 0);
    func_0202f188(&spin, &data_02042264, state[3]);
    func_0202ed60(&tilt, &data_02042264, (Vec3 *)(*state + 0x124));
    func_0202ef54(&tilt, &tilt, &spin);
    func_0203c9d0((void *)(*state + 0xa0), &tilt);
    *(Vec3 *)(*state + 0xf0) = *(Vec3 *)(state + 0xa);
    for (remaining = *(int *)(node[0] + 0x2c); remaining > 0; remaining -= 0x88) {
        func_01ffa724(0x1000 - FX_MUL(FX_Inv(remaining <= 0x88 ? remaining : 0x88, 0x88), 0x1f0),
                      (Vec3 *)(state + 0xa), (Vec3 *)(state + 0xa));
        state[7] = FX_MUL(state[7], 0x1000 - FX_MUL(FX_Inv(remaining <= 0x88 ? remaining : 0x88, 0x88), 0x200));
    }
}
