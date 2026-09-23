/* Common update of the ov255 states (slot 0): the attack cues advance (func_ov255_020cce6c), the
 * +0x1c orientation turns towards +0x2c by the +0x40 rate and is applied to the owner's +0xa0
 * pose, the +0x58 timer accumulates the frame rate and the +0x54 cooldown counts down while not
 * negative; the +0x10 step is handed to the owner's +0xf0 velocity and cleared. */
typedef struct { int x, y, z; } Vec3;
typedef struct { int w[4]; } Quat;

extern void func_ov255_020cce6c(int *state, int rate);
extern void func_0202f55c(Quat *dst, int t, const Quat *from, const Quat *to);
extern void func_0203c9d0(void *srt, const Quat *q);
extern const Vec3 data_02041dc8;

void func_ov255_020cd328(int *node)
{
    int *state = (int *)node[1];

    func_ov255_020cce6c(state, *(int *)(node[0] + 0x2c));
    func_0202f55c((Quat *)(state + 7), state[0x10], (Quat *)(state + 7), (Quat *)(state + 0xb));
    func_0203c9d0((void *)(*state + 0xa0), (Quat *)(state + 7));
    state[0x16] += *(int *)(node[0] + 0x2c);
    if (state[0x15] >= 0) {
        state[0x15] -= *(int *)(node[0] + 0x2c);
    }
    {
        Vec3 *step = (Vec3 *)(state + 4);

        *(Vec3 *)(*state + 0xf0) = *step;
        *step = data_02041dc8;
    }
}
