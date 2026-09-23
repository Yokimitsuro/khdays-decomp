/* Roll tick of the ov218 actor (move 1 only): it faces along its ground-plane +0x28 motion (the
 * rotation from data_02042258 to it, 0202ed60), its +0xf0 velocity mirrors +0x10, the horizontal
 * velocity damps to 0.906 on the ground (0.969 in the air) and gravity pulls 0.94 per frame. On the
 * ground a slow roll (under 0.0625) stops; otherwise the +0x38 bounce speed damps by 0.094 per 0x88
 * slice and becomes the vertical velocity. */
typedef unsigned char u8;
typedef struct { int x, y, z; } Vec3;
typedef struct { int x, y, z, w; } Quat;
typedef struct { u8 b0 : 1; } Bit0;

extern int func_01ff8d18(const Vec3 *v, Vec3 *out);
extern void func_0202ed60(Quat *out, const Vec3 *from, const Vec3 *to);
extern void func_0203c9d0(void *srt, const Quat *rot);
extern int FX_Inv(int num, int den);
extern const Vec3 data_02042258;
extern const Vec3 data_02041dc8;

#define FX_MUL(a, b) ((int)(((long long)(a) * (b) + 0x800) >> 12))

void func_ov218_020ce5ac(int *node)
{
    int *state = (int *)node[1];
    Quat q;
    Vec3 dir;
    int grounded;
    int damp;
    int remaining;

    if (*(signed char *)(*state + 0x1c6) != 1) {
        return;
    }
    grounded = ((Bit0 *)(*state + 0x17a))->b0;
    damp = grounded ? 0xe80 : 0xf80;
    dir = *(Vec3 *)(state + 0xa);
    dir.y = 0;
    if (func_01ff8d18(&dir, &dir) == 0) {
        dir = data_02042258;
    }
    func_0202ed60(&q, &data_02042258, &dir);
    func_0203c9d0((void *)(*state + 0xa0), &q);
    *(Vec3 *)(*state + 0xf0) = *(Vec3 *)(state + 4);
    state[4] = FX_MUL(state[4], damp);
    state[6] = FX_MUL(state[6], damp);
    state[5] += -(*(int *)(node[0] + 0x2c) << 7) / 0x88;
    if (!grounded) {
        return;
    }
    if (func_01ff8d18((Vec3 *)(state + 4), &dir) < 0x100) {
        *(Vec3 *)(state + 4) = data_02041dc8;
        return;
    }
    for (remaining = *(int *)(node[0] + 0x2c); remaining > 0; remaining -= 0x88) {
        state[0xe] = FX_MUL(state[0xe], 0x1000 - FX_MUL(FX_Inv(remaining <= 0x88 ? remaining : 0x88, 0x88), 0x180));
    }
    state[5] = state[0xe];
}
