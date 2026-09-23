/* Watch slot of an ov256 claw (every frame). While docked (+0x3a0 and +0x39c clear) it follows the
 * owner's hand bone (+0x418 left / +0x424 right, +0x394) and +0x80 rests on the vertical axis; when
 * fully idle (+0x398 too) the +0x50 heading follows the owner's +0x3ac part (+0x458). The heading
 * quaternion is tilted onto the ground normal (+0x124) while landed and idle. The +0xa0 pose takes the
 * hand bone's rotation while docked, at the end of a 9-orbit launch (0x550 into it) or early in the
 * first orbit (before 0x908); otherwise the heading. +0xf0 keeps the last +0x10 velocity, which then
 * clears. */
typedef unsigned char u8;
typedef struct { int x, y, z; } Vec3;
typedef struct { int x, y, z, w; } Quat;
struct Flag17a { u8 b0 : 1; };

extern void func_ov107_020c5c54(int actor, Vec3 *at);
extern void func_0202f188(Quat *out, const Vec3 *axis, int angle);
extern void func_0202ed60(Quat *out, const Vec3 *from, const Vec3 *to);
extern void func_0202ef54(Quat *out, const Quat *a, const Quat *b);
extern void func_0203c9d0(char *srt, void *q);
extern const Vec3 data_02042264;
extern const Vec3 data_02041dc8;

#define HAND_BONE(s) (*(u8 *)((s) + 0x394) == 0 ? *(int *)(*(int *)((s) + 0x3ac) + 0x418) \
                                                 : *(int *)(*(int *)((s) + 0x3ac) + 0x424))

void func_ov256_020d1714(int *node)
{
    int *state = (int *)node[1];
    Vec3 hand;
    Quat q;
    Quat tilt;

    if (*(int *)(*state + 0x3a0) == 0 && *(int *)(*state + 0x39c) == 0) {
        hand = *(Vec3 *)(HAND_BONE(*state) + 0x14);
        func_ov107_020c5c54(*state, &hand);
        *(Vec3 *)(state + 0x20) = data_02042264;
    }
    if (*(int *)(*state + 0x39c) == 0 && *(int *)(*state + 0x3a0) == 0 && *(int *)(*state + 0x398) == 0) {
        state[0x14] = *(int *)(*(int *)(*state + 0x3ac) + 0x458);
    }
    func_0202f188(&q, &data_02042264, state[0x14]);
    if (((struct Flag17a *)(*state + 0x17a))->b0 && *(int *)(*state + 0x3a0) == 0 &&
        *(int *)(*state + 0x39c) == 0 && *(int *)(*state + 0x398) == 0) {
        func_0202ed60(&tilt, &data_02042264, (Vec3 *)(*state + 0x124));
        func_0202ef54(&q, &tilt, &q);
    }
    if (*(int *)(*state + 0x3a0) == 0 && *(int *)(*state + 0x39c) == 0) {
        if (*(u8 *)(*state + 0x394) == 0) {
            func_0203c9d0((char *)(*state + 0xa0), (void *)(*(int *)(*(int *)(*state + 0x3ac) + 0x418) + 4));
        } else {
            func_0203c9d0((char *)(*state + 0xa0), (void *)(*(int *)(*(int *)(*state + 0x3ac) + 0x424) + 4));
        }
    } else if ((*(int *)(*state + 0x3a0) != 0 && state[0x18] >= 0x550 && state[0x19] == 9) ||
               (state[0x18] < 0x908 && state[0x19] == 0 && *(int *)(*state + 0x3a0) != 0)) {
        if (*(u8 *)(*state + 0x394) == 0) {
            func_0203c9d0((char *)(*state + 0xa0), (void *)(*(int *)(*(int *)(*state + 0x3ac) + 0x418) + 4));
        } else {
            func_0203c9d0((char *)(*state + 0xa0), (void *)(*(int *)(*(int *)(*state + 0x3ac) + 0x424) + 4));
        }
    } else {
        func_0203c9d0((char *)(*state + 0xa0), &q);
    }
    {
        Vec3 *vel = (Vec3 *)(state + 4);

        *(Vec3 *)(*state + 0xf0) = *vel;
        *vel = data_02041dc8;
    }
}
