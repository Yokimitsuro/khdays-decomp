/* Chase tick of the ov283 helper (move 1 only): the goal heading (+0x18) points from its +4 point to
 * the owner's +0x38c model's target (+0x390); the +0x14 heading turns toward it at 1.125 per frame and
 * the +8 velocity runs along it at 0.5 (vertical part from the aim), the pose turns about up and the
 * +0xf0 velocity mirrors it. */
typedef struct { int x, y, z; } Vec3;
typedef struct { int x, y, z, w; } Quat;

extern void VEC_Subtract(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern int func_020050b4(int x, int z);
extern int func_01ff8d18(const Vec3 *v, Vec3 *out);
extern int func_0203d040(int a, int b, int c, int d);
extern void func_01ffa724(int scale, const Vec3 *v, Vec3 *out);
extern void func_0202f188(Quat *out, const Vec3 *axis, int angle);
extern void func_0203c9d0(void *srt, const Quat *rot);
extern const short data_0203d210[];
extern const Vec3 data_02042264;

#define ANG2IDX(a) ((unsigned short)(((long long)(a) * 0x28be60db9391LL + 0x80000000000LL) >> 44) >> 4)

static inline void VecSet(Vec3 *v, int x, int y, int z)
{
    v->x = x;
    v->y = y;
    v->z = z;
}

void func_ov283_020cf5f4(int *node)
{
    int *state = (int *)node[1];
    Quat q;
    Vec3 d;
    Vec3 unit;
    int rate;
    int target;

    if (*(signed char *)(*state + 0x1c6) != 1) {
        return;
    }
    rate = *(int *)(node[0] + 0x2c) * 0x5a / 80;
    target = *(int *)(*(int *)(*state + 0x38c) + 0x390);
    VEC_Subtract((Vec3 *)(target + 0x190), (Vec3 *)state[1], &d);
    state[6] = func_020050b4(d.x, d.z);
    func_01ff8d18(&d, &unit);
    state[5] = func_0203d040(state[5], state[6], rate, 0);
    {
        int idx = ANG2IDX(state[5]) * 2;

        VecSet((Vec3 *)(state + 2), data_0203d210[idx], unit.y, data_0203d210[idx + 1]);
    }
    func_01ffa724(0x800, (Vec3 *)(state + 2), (Vec3 *)(state + 2));
    func_0202f188(&q, &data_02042264, state[5]);
    func_0203c9d0((void *)(*state + 0xa0), &q);
    *(Vec3 *)(*state + 0xf0) = *(Vec3 *)(state + 2);
}
