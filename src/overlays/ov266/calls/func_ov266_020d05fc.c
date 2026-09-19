/* Shared frame step of the ov266 enemy: with the +0x60 low bit set the grab phase machine
 * runs; the +0x34 heading turns towards +0x3c by twice the owner's rate and is written into the
 * +0xa0 pose (quaternion about data_02042264). Outside mode 8 the zero vector (data_02041dc8) turned by the pose is added to the +0x74 position and the
 * +0x10 velocity to give the next point; if a thin ray from it straight down by 2.0 plus the
 * actor radius finds no floor, the velocity is zeroed. The velocity is then published to +0xf0 and reset to zero
 * (data_02041dc8); if the 020cf3fc check passes the +0x44 timer resets, otherwise it counts
 * the rate up to 0xf000, and the rate is recorded at +0x580. */
typedef struct { int x, y, z; } Vec3;
typedef struct { int q[4]; } Quat;
typedef struct { unsigned short lo : 8, hi : 8; } Hw60;

extern void func_ov266_020cf45c(int *state);
extern int func_0203d040(int cur, int target, int step, int done);
extern void func_0202f188(Quat *out, const Vec3 *axis, int angle);
extern void func_0203c9d0(void *srt, Quat *q);
extern void func_0202f384(Vec3 *out, void *pose, const Vec3 *in);
extern void VEC_Add(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern int *func_01fff920(void *world, Vec3 *origin, Vec3 *dir);
extern int func_ov266_020cf3fc(int *state, int a);
extern const Vec3 data_02042264;
extern const Vec3 data_02041dc8;

void func_ov266_020d05fc(int *node)
{
    int *state = (int *)node[1];
    Vec3 down;
    Quat q;
    Vec3 next;
    Vec3 up;
    char *owner = *(char **)(*state + 4);

    if ((((Hw60 *)(*state + 0x60))->lo & 1) != 0) {
        func_ov266_020cf45c(state);
    }
    state[0xd] = func_0203d040(state[0xd], state[0xf], *(int *)(node[0] + 0x2c) * 2, 0);
    func_0202f188(&q, &data_02042264, state[0xd]);
    func_0203c9d0((void *)(*state + 0xa0), &q);
    if (*(signed char *)(*state + 0x1c6) != 8) {
        up = data_02041dc8;
        next = data_02041dc8;
        func_0202f384(&next, (void *)(state + 0x28), &next);
        VEC_Add(&next, (Vec3 *)(*state + 0x74), &next);
        VEC_Add(&next, (Vec3 *)(state + 4), &next);
        down.y = -(*(int *)(*state + 0x80) + 0x2000);
        down.x = 0;
        down.z = 0;
        if (func_01fff920(*(void **)(owner + 0x7c), &next, &down) == 0) {
            *(Vec3 *)(state + 4) = up;
        }
    }
    {
        Vec3 *pVel = (Vec3 *)(state + 4);
        *(Vec3 *)(*state + 0xf0) = *pVel;
        *pVel = data_02041dc8;
    }
    if (func_ov266_020cf3fc(state, 1) != 0) {
        state[0x11] = 0;
    } else if (state[0x11] < 0xf000) {
        state[0x11] += *(int *)(node[0] + 0x2c);
    }
    *(int *)(*state + 0x580) = *(int *)(node[0] + 0x2c);
}
