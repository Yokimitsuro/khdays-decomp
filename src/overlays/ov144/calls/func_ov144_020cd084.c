/* Turn tick of the ov144 enemy (and its byte-identical twin): the +0x30 yaw turns toward the
 * +0x34 target yaw by the frame-time (doubled in sub-states 5-7, frozen in sub-state 8), the
 * actor's +0xa0 transform takes the yaw as a quaternion about the up axis, the +0x24 velocity
 * moves to the actor's +0xf0 and is zeroed; in sub-states 2/3 with a non-negative +0x3c0 table
 * entry the +0x3c timer counts the frame-time down and, once spent, the sub-state is remembered
 * in +0x50 and sub-state 8 is requested. */
typedef struct Vec3 { int x, y, z; } Vec3;

extern int func_0203d040(int cur, int target, int step, int *out);
extern void func_0202f188(int *quat, const Vec3 *axis, int angle);
extern void func_0203c9d0(void *srt, int *quat);
extern const Vec3 data_02041dc8;
extern const Vec3 data_02042264;

#define FX_MUL(a, b) ((int)(((long long)(a) * (b) + 0x800) >> 12))

void func_ov144_020cd084(int *node)
{
    int *state = (int *)node[1];
    int quat[4];
    Vec3 *vel;

    switch (*(signed char *)(*state + 0x1c6)) {
    case 5:
    case 6:
    case 7:
        state[0xc] = func_0203d040(state[0xc], state[0xd], FX_MUL(*(int *)(*node + 0x2c), 0x2000), 0);
        break;
    case 8:
        break;
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
    default:
        state[0xc] = func_0203d040(state[0xc], state[0xd], FX_MUL(*(int *)(*node + 0x2c), 0x1000), 0);
        break;
    }
    func_0202f188(quat, &data_02042264, state[0xc]);
    func_0203c9d0((char *)*state + 0xa0, quat);
    vel = (Vec3 *)(state + 9);
    *(Vec3 *)(*state + 0xf0) = *vel;
    *vel = data_02041dc8;
    if (*(signed char *)(*state + 0x1c6) != 2 && *(signed char *)(*state + 0x1c6) != 3) {
        return;
    }
    if (*(int *)(*state + state[0x12] * 4 + 0x3c0) < 0) {
        return;
    }
    state[0xf] -= *(int *)(*node + 0x2c);
    if (state[0xf] > 0) {
        return;
    }
    *(unsigned char *)(state + 0x14) = *(signed char *)(*state + 0x1c6);
    *(unsigned char *)(*state + 0x1c7) = 8;
}
