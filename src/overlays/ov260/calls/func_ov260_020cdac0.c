/* Watch slot of the ov260 actor (every frame): the +0x64 heading turns toward +0x68 by 2.5 x the
 * frame rate, the +0xa0 pose follows it, +0xf0 keeps the last +0x20 velocity which then clears, and
 * in move 4 the +0x60 idle time runs down to 0. */
typedef struct { int x, y, z; } Vec3;
typedef struct { int x, y, z, w; } Quat;

extern int func_0203d040(int a, int b, int c, int d);
extern void func_0202f188(Quat *out, const Vec3 *axis, int angle);
extern void func_0203c9d0(char *srt, Quat *q);
extern const Vec3 data_02042264;
extern const Vec3 data_02041dc8;

#define FX_MUL(a, b) ((int)(((long long)(a) * (b) + 0x800) >> 12))

void func_ov260_020cdac0(int *node)
{
    int *state = (int *)node[1];
    Quat q;

    state[0x19] = func_0203d040(state[0x19], state[0x1a], FX_MUL(*(int *)(node[0] + 0x2c), 0x2800), 0);
    func_0202f188(&q, &data_02042264, state[0x19]);
    func_0203c9d0((char *)(*state + 0xa0), &q);
    {
        Vec3 *vel = (Vec3 *)(state + 8);

        *(Vec3 *)(*state + 0xf0) = *vel;
        *vel = data_02041dc8;
    }
    if (*(signed char *)(*state + 0x1c6) != 4) {
        return;
    }
    if ((state[0x18] -= *(int *)(node[0] + 0x2c)) < 0) {
        state[0x18] = 0;
    }
}
