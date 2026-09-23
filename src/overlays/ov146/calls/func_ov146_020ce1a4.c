/* Approach tick: the +0x2c heading turns towards the actor's +0x190 point from the +0xc anchor,
 * the +0x10 velocity is the +0x28 yaw's direction at speed 0.125, and once the anchor is within 2.0
 * (beyond the actor's +0x80 radius) the next move is 2. */
typedef struct { int x, y, z; } Vec3;

extern void VEC_Subtract(const void *a, const void *b, Vec3 *out);
extern int func_020050b4(int x, int z);
extern int func_01ff8d18(Vec3 *v, Vec3 *d);
extern void func_01ffa724(int scale, Vec3 *v, Vec3 *d);
extern void func_0203c634(int *node, int slot, void *cb);
extern const short data_0203d210[];

#define ANG2IDX(a) ((unsigned short)(((long long)(a) * 0x28be60db9391LL + 0x80000000000LL) >> 44) >> 4)

void func_ov146_020ce1a4(int *node)
{
    int *state = (int *)node[1];
    Vec3 d;
    int dist;
    int owner;
    unsigned int idx;

    VEC_Subtract((void *)(*state + 0x190), (void *)state[3], &d);
    state[0xb] = func_020050b4(d.x, d.z);
    owner = *state;
    dist = func_01ff8d18(&d, &d) - *(int *)(owner + 0x80);
    idx = ANG2IDX(state[0xa]);
    state[4] = data_0203d210[idx * 2];
    state[5] = 0;
    state[6] = data_0203d210[idx * 2 + 1];
    func_01ffa724(0x200, (Vec3 *)(state + 4), (Vec3 *)(state + 4));
    if (dist < 0x2000) {
        *(signed char *)(*state + 0x1c7) = 2;
        func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
    }
}
