/* Approach tick: the +0x10 heading turns towards the actor's +0x190 point from the +8 anchor, the
 * +0x28 velocity is the +0xc yaw's direction at speed 0.375, and once the anchor is within 2.0
 * (beyond the actor's +0x80 radius) the next move is 2. */
typedef struct { int x, y, z; } Vec3;

extern void VEC_Subtract(const void *a, const void *b, Vec3 *out);
extern int func_020050b4(int x, int z);
extern int func_01ff8d18(Vec3 *v, Vec3 *d);
extern void func_01ffa724(int scale, Vec3 *v, Vec3 *d);
extern void func_0203c634(int *node, int slot, void *cb);
extern const short data_0203d210[];

#define ANG2IDX(a) ((unsigned short)(((long long)(a) * 0x28be60db9391LL + 0x80000000000LL) >> 44) >> 4)

void func_ov218_020cdf04(int *node)
{
    int *state = (int *)node[1];
    Vec3 d;
    int dist;
    int owner;
    unsigned int idx;

    VEC_Subtract((void *)(*state + 0x190), (void *)state[2], &d);
    state[4] = func_020050b4(d.x, d.z);
    owner = *state;
    dist = func_01ff8d18(&d, &d) - *(int *)(owner + 0x80);
    idx = ANG2IDX(state[3]);
    state[0xa] = data_0203d210[idx * 2];
    state[0xb] = 0;
    state[0xc] = data_0203d210[idx * 2 + 1];
    func_01ffa724(0x600, (Vec3 *)(state + 0xa), (Vec3 *)(state + 0xa));
    if (dist < 0x2000) {
        *(signed char *)(*state + 0x1c7) = 2;
        func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
    }
}
