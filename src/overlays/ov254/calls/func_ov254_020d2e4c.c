/* Hit filter of an ov254 helper (+0x1d0): ignored while guarding (+0x1ac bit 0) or for flag-8
 * hits. The source is kept in +4; the +0x1c push is the flattened direction from the actor to its
 * +0x394 owner when it points within ~50 degrees of the hit's own direction, else the hit
 * direction. A sourced hit resets the +0x40 / +0x44 timers, sets +0x4c and clears the +0x34 hit
 * mask; an unsourced one adds bit (short)hit[4] to that 64-bit mask. Returns 1. */
typedef unsigned short u16;
typedef struct { int x, y, z; } Vec3;
struct HitWord { unsigned int lo : 16, hi : 16; };

extern int func_01ff8d18(Vec3 *v, Vec3 *d);
extern void VEC_Subtract(const void *a, const void *b, Vec3 *out);
extern int VEC_DotProduct(const Vec3 *a, const Vec3 *b);
extern void func_01ffa724(int scale, Vec3 *v, Vec3 *d);

int func_ov254_020d2e4c(char *self, int src, unsigned int *hit)
{
    int *state = *(int **)(self + 0x214);
    Vec3 dir;
    Vec3 toOwner;

    if ((*(u16 *)(self + 0x100 + 0xac) & 1) != 0) {
        return 0;
    }
    if ((((struct HitWord *)hit)->lo & 8) != 0) {
        return 0;
    }
    state[1] = src;
    dir = *(Vec3 *)(hit + 1);
    dir.y = 0;
    func_01ff8d18(&dir, &dir);
    VEC_Subtract((void *)(*(int *)(*state + 0x394) + 0x74), (void *)(*state + 0x74), &toOwner);
    toOwner.y = 0;
    func_01ff8d18(&toOwner, &toOwner);
    if (VEC_DotProduct(&toOwner, &dir) >= 0xa49) {
        func_01ffa724(0x1000, &toOwner, (Vec3 *)(state + 7));
    } else {
        func_01ffa724(0x1000, &dir, (Vec3 *)(state + 7));
    }
    if (state[1] != 0) {
        state[0x11] = 0;
        state[0x10] = 0;
        state[0x13] = 1;
        state[0xd] = 0;
        state[0xe] = 0;
    } else {
        *(unsigned long long *)(state + 0xd) |= 1ULL << (short)hit[4];
    }
    return 1;
}
