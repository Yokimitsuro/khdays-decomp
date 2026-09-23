/* Physics tick of the ov283 actor: the +0x38 heading snaps to the +0x40 goal while +0x70 is set, else
 * turns toward it at 9x the frame rate, and orients the pose about up; the +0x4c and +0x50 timers run
 * down (to 0), the +0x3c tilt eases back toward 0 by 0.066, the +0xf0 velocity mirrors +0x10, which
 * is scaled by +0x5c; both +0x394/+0x39c limb pairs update (020ced80) and a pending +0x60 timer runs
 * down. */
typedef struct { int x, y, z; } Vec3;
typedef struct { int x, y, z, w; } Quat;
struct Ov283Limbs { char pad[0x394]; int bones[2]; int parts[2]; };

extern int func_0203d040(int a, int b, int c, int d);
extern void func_0202f188(Quat *out, const Vec3 *axis, int angle);
extern void func_0203c9d0(void *srt, const Quat *rot);
extern void func_01ffa724(int scale, const Vec3 *v, Vec3 *out);
extern int func_ov283_020ced80(int part, int bone);
extern const Vec3 data_02042264;

void func_ov283_020ccfb8(int *node)
{
    int *state = (int *)node[1];
    Quat q;
    int rate = *(int *)(node[0] + 0x2c) * 0x5a / 10;
    int i;

    if (state[0x1c] != 0) {
        state[0xe] = state[0x10];
    } else {
        state[0xe] = func_0203d040(state[0xe], state[0x10], rate, 0);
    }
    func_0202f188(&q, &data_02042264, state[0xe]);
    func_0203c9d0((void *)(*state + 0xa0), &q);
    state[0x13] -= *(int *)(node[0] + 0x2c);
    if (state[0x13] <= 0) {
        state[0x13] = 0;
    }
    state[0x14] -= *(int *)(node[0] + 0x2c);
    if (state[0x14] <= 0) {
        state[0x14] = 0;
    }
    if (state[0xf] >= 0x110) {
        state[0xf] -= 0x110;
    } else if (state[0xf] <= -0x110) {
        state[0xf] += 0x110;
    }
    {
        Vec3 *vel = (Vec3 *)(state + 4);

        *(Vec3 *)(*state + 0xf0) = *vel;
        func_01ffa724(state[0x17], vel, vel);
    }
    for (i = 0; i < 2; i++) {
        func_ov283_020ced80(((struct Ov283Limbs *)*state)->parts[i], ((struct Ov283Limbs *)*state)->bones[i]);
    }
    if (state[0x18] <= 0) {
        return;
    }
    state[0x18] -= *(int *)(node[0] + 0x2c);
}
