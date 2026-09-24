/* Carry tick of the ov146 enemy: the +0x28 heading eases towards +0x2c at three times the frame rate
 * (0203d040) and gives the owner's yaw quaternion. While +0x58 is set the carried +8 actor copies the
 * owner's +0xa0 transform, is flagged held (+0x1ae bit 4, +0x60 high bits 1/2/6) and, unless the owner
 * is idle or in sub-state 9, the +0x14 climb eases towards 1.5 above the owner's +0x13c height.
 * Otherwise the climb sinks by 0x90, the yaw is combined with the owner's +0x124 facing and, when the
 * actor is flagged (+0x60 bit 2), it is placed both radii ahead along the heading from the +0xc anchor
 * (020c5c54); the held flags are cleared. The owner then takes the rotation, the +0x10 velocity moves
 * to its +0xf0 and is cleared, and the +0x40 / +0x44 timers run down to zero. */
typedef unsigned short u16;
typedef struct { int x, y, z; } Vec3;
typedef struct { int w[4]; } Quat;
typedef struct { int w[11]; } Xform;
struct XformHost { char pad[0xa0]; Xform xf; };
struct VelHost { char pad[0xf0]; Vec3 vel; };
struct Hw60 { u16 lo : 8, hi : 8; };

extern int func_0203d040(int a, int b, int c, int d);
extern void func_0202f188(Quat *q, const Vec3 *axis, int angle);
extern void func_0202ed60(Quat *out, const Vec3 *forward, const Vec3 *direction);
extern void func_0202ef54(Quat *out, const Quat *a, const Quat *b);
extern void func_01ffa724(int scale, Vec3 *v, Vec3 *d);
extern void VEC_Add(void *a, void *b, Vec3 *d);
extern void func_ov107_020c5c54(int actor, Vec3 *at);
extern void func_0203c9d0(void *pose, const Quat *q);
extern const Vec3 data_02042264;
extern const short data_0203d210[];
extern const Vec3 data_02041dc8;

#define ANG2IDX(a) ((unsigned short)(((long long)(a) * 0x28be60db9391LL + 0x80000000000LL) >> 44) >> 4)

void func_ov146_020ccae4(int *node)
{
    int *state = (int *)node[1];
    Quat q;
    Quat face;
    Vec3 v;

    state[10] = func_0203d040(state[10], state[11], *(int *)(node[0] + 0x2c) * 3, 0);
    func_0202f188(&q, &data_02042264, state[10]);
    if (state[0x16] != 0) {
        int owner = *state;
        signed char sub = *(signed char *)(owner + 0x1c6);

        if (sub != 0 && sub != 9) {
            state[5] += (0x1800 - *(int *)(owner + 0x13c)) / 30;
        }
        ((struct XformHost *)state[2])->xf = ((struct XformHost *)*state)->xf;
        *(u16 *)(state[2] + 0x100 + 0xae) |= 0x10;
        {
            u16 hw = *(u16 *)(state[2] + 0x60);
            *(u16 *)(state[2] + 0x60) = (hw & ~0xff00) |
                ((((((unsigned int)hw << 0x10) >> 0x18) | 0x46) << 0x18) >> 0x10);
        }
    } else {
        int actor;

        state[5] -= 0x90;
        func_0202ed60(&face, &data_02042264, (Vec3 *)(*state + 0x124));
        func_0202ef54(&q, &face, &q);
        actor = state[2];
        if ((((struct Hw60 *)(actor + 0x60))->lo & 4) != 0) {
            unsigned int idx = ANG2IDX(state[10]);
            int reach = *(int *)(actor + 0x80) + *(int *)(*state + 0x80);

            v.x = data_0203d210[idx * 2];
            v.y = 0;
            v.z = data_0203d210[idx * 2 + 1];
            func_01ffa724(reach, &v, &v);
            VEC_Add(&v, (void *)state[3], &v);
            func_ov107_020c5c54(state[2], &v);
        }
        *(u16 *)(state[2] + 0x100 + 0xae) &= ~0x10;
        {
            u16 hw60 = *(u16 *)(state[2] + 0x60);
            *(u16 *)(state[2] + 0x60) =
                (hw60 & ~0xff00) |
                (((unsigned int)(u16)((((unsigned int)hw60 << 0x10) >> 0x18) & ~0x46) << 0x18) >> 0x10);
        }
    }
    func_0203c9d0((void *)(*state + 0xa0), &q);
    ((struct VelHost *)*state)->vel = *(Vec3 *)(state + 4);
    *(Vec3 *)(state + 4) = data_02041dc8;
    if ((state[0x10] -= *(int *)(node[0] + 0x2c)) < 0) {
        state[0x10] = 0;
    }
    if ((state[0x11] -= *(int *)(node[0] + 0x2c)) <= 0) {
        state[0x11] = 0;
    }
}
