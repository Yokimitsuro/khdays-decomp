/* Start a hop run of the ov245 enemy towards `target`: plans the hops (020d2bc4, 0.75 per hop),
 * keeps `speed` at +0x48, faces the +0x18 direction along the `angle` heading (height kept) and
 * requests move 1. */
typedef struct { int x, y, z; } Vec3;
extern void func_ov245_020d2bc4(int *state, int a, int b);
extern const short data_0203d210[];

#define ANG2IDX(a) ((unsigned short)(((long long)(a) * 0x28be60db9391LL + 0x80000000000LL) >> 44) >> 4)

static inline void VecSet(Vec3 *v, int x, int y, int z)
{
    v->x = x;
    v->y = y;
    v->z = z;
}

void func_ov245_020d2c78(int *state, int target, int angle, int speed)
{
    unsigned int idx;

    func_ov245_020d2bc4(state, target, 0x300);
    state[0x12] = speed;
    idx = ANG2IDX(angle);
    VecSet((Vec3 *)(state + 6), data_0203d210[idx * 2], state[7], data_0203d210[idx * 2 + 1]);
    *(unsigned char *)(*state + 0x1c7) = 1;
}
