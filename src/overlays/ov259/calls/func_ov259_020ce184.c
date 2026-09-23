/* Watch slot of the ov259 actor (every frame): the +0x78 heading turns toward +0x7c by 90 x the
 * frame rate over the +0x94 turn time, the +0xa0 pose becomes that heading composed with the ground
 * normal (+0x124), the +0x8c clock runs while +0x4c is clear, +0xf0 keeps the last +0x14 drift and
 * the drift decays by +0x88, the physics step runs (020ce63c) and a pending +0x90 delay fires sound
 * 0x172 with the +0xa4 variant at the +0x10 point when it runs out; then the base tick (020cd648). */
typedef struct { int x, y, z; } Vec3;
typedef struct { int x, y, z, w; } Quat;

extern int func_02020400(int num, int den);
extern int func_0203d040(int a, int b, int c, int d);
extern void func_0202f188(Quat *out, const Vec3 *axis, int angle);
extern void func_0202ed60(Quat *out, const Vec3 *from, const Vec3 *to);
extern void func_0202ef54(Quat *out, const Quat *a, const Quat *b);
extern void func_0203c9d0(char *srt, Quat *q);
extern void func_01ffa724(int scale, Vec3 *v, Vec3 *d);
extern void func_ov259_020ce63c(int *node);
extern void func_ov259_020cd3c4(int actor, int id, int variant, void *at);
extern void func_ov259_020cd648(int *node);
extern const Vec3 data_02042264;

void func_ov259_020ce184(int *node)
{
    int *state = (int *)node[1];
    Quat turn;
    Quat pose;

    state[0x1e] = func_0203d040(state[0x1e], state[0x1f],
                                func_02020400(*(int *)(node[0] + 0x2c) * 0x5a, state[0x25]), 0);
    func_0202f188(&turn, &data_02042264, state[0x1e]);
    func_0202ed60(&pose, &data_02042264, (Vec3 *)(*state + 0x124));
    func_0202ef54(&pose, &pose, &turn);
    func_0203c9d0((char *)(*state + 0xa0), &pose);
    if (state[0x13] == 0) {
        state[0x23] += *(int *)(node[0] + 0x2c);
    }
    {
        Vec3 *drift = (Vec3 *)(state + 5);
        *(Vec3 *)(*state + 0xf0) = *drift;
        func_01ffa724(state[0x22], drift, drift);
    }
    func_ov259_020ce63c(node);
    if (state[0x24] > 0) {
        state[0x24] -= *(int *)(node[0] + 0x2c);
        if (state[0x24] <= 0) {
            func_ov259_020cd3c4(*state, 0x172, (unsigned short)state[0x29], (void *)state[4]);
        }
    }
    func_ov259_020cd648(node);
}
