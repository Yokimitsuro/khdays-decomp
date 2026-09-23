/* Body tick of the ov235 enemy (slot 2): the steering step runs (func_ov235_020ccee8 with the
 * rate), the +0x1c orientation eases towards +0x2c by the +0x40 rate and orients the owner's +0xa0
 * pose, the +0x50 clock runs and a non-negative +0x4c cooldown counts down. Within 5.0 of the
 * origin the +0x10 step is pushed outwards by the missing distance; the step then becomes the
 * owner's +0xf0 velocity and resets. */
typedef struct { int x, y, z; } Vec3;
typedef struct { int w[4]; } Quat;

extern void func_ov235_020ccee8(int *state, int rate);
extern void func_0202f55c(Quat *dst, int t, const Quat *from, const Quat *to);
extern void func_0203c9d0(void *srt, const Quat *q);
extern void VEC_Subtract(const void *a, const void *b, Vec3 *out);
extern int func_01ff8d18(const Vec3 *v, Vec3 *out);
extern void func_01ffa724(int scale, const Vec3 *v, Vec3 *out);
extern void VEC_Add(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern const Vec3 data_02041dc8;

void func_ov235_020cd3f8(int *node)
{
    int *state = (int *)node[1];
    Vec3 d;
    int len;

    func_ov235_020ccee8(state, *(int *)(node[0] + 0x2c));
    func_0202f55c((Quat *)(state + 7), state[0x10], (Quat *)(state + 7), (Quat *)(state + 0xb));
    func_0203c9d0((void *)(*state + 0xa0), (Quat *)(state + 7));
    state[0x14] += *(int *)(node[0] + 0x2c);
    if (state[0x13] >= 0) {
        state[0x13] -= *(int *)(node[0] + 0x2c);
    }
    VEC_Subtract((void *)state[1], &data_02041dc8, &d);
    len = func_01ff8d18(&d, &d);
    if (len < 0x5000) {
        func_01ffa724(0x5000 - len, &d, &d);
        VEC_Add((Vec3 *)(state + 4), &d, (Vec3 *)(state + 4));
    }
    {
        Vec3 *step = (Vec3 *)(state + 4);

        *(Vec3 *)(*state + 0xf0) = *step;
        *step = data_02041dc8;
    }
}
