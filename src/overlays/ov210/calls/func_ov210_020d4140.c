/* Scatter setup of the ov210 enemy (x3 with ov211/ov282): clears bit 7 of the owner's +0x60 high
 * byte, then rolls three horizontal directions within +-0x3244 of forward: the +8 and +0x14 ones
 * are scaled to a random reach between 20.0 and 40.0, the +0x30 one stays a unit vector. +0x3c
 * becomes 2.0 or 12.0 at random, bit 0 of the +0x60 high byte is raised, +0x48 takes another
 * random angle, +0x40 clears and the tick hands over to func_ov210_020d4368. */
typedef unsigned short u16;
typedef struct { int x, y, z; } Vec3;

struct hw60 { unsigned short lo : 8, hi : 8; };

extern long long func_02023eb4(int bound);
extern void func_01ffa724(int scale, const Vec3 *v, Vec3 *out);
extern void func_0203c634(int *node, int slot, void *cb);
extern const short data_0203d210[];
extern void func_ov210_020d4368(int *node);

static inline int RandRange(int lo, int hi) { return (int)func_02023eb4(hi - lo + 1) + lo; }
#define ANG2IDX(a) ((unsigned short)(((long long)(a) * 0x28be60db9391LL + 0x80000000000LL) >> 44) >> 4)

void func_ov210_020d4140(int *node)
{
    int *state = (int *)node[1];
    unsigned int idx;
    unsigned int idx2;
    u16 v;

    ((struct hw60 *)(*state + 0x60))->hi &= ~0x80;
    idx = ANG2IDX(RandRange(-0x3244, 0x3244));
    state[2] = data_0203d210[idx * 2];
    state[3] = 0;
    state[4] = data_0203d210[idx * 2 + 1];
    func_01ffa724(RandRange(0x14000, 0x28000), (Vec3 *)(state + 2), (Vec3 *)(state + 2));
    idx2 = ANG2IDX(RandRange(-0x3244, 0x3244));
    state[5] = data_0203d210[idx2 * 2];
    state[6] = 0;
    state[7] = data_0203d210[idx2 * 2 + 1];
    func_01ffa724(RandRange(0x14000, 0x28000), (Vec3 *)(state + 5), (Vec3 *)(state + 5));
    idx = ANG2IDX(RandRange(-0x3244, 0x3244));
    state[0xc] = data_0203d210[idx * 2];
    state[0xd] = 0;
    state[0xe] = data_0203d210[idx * 2 + 1];
    state[0xf] = RandRange(0, 1) == 0 ? 0x2000 : 0xc000;
    v = *(u16 *)(*state + 0x60);
    *(u16 *)(*state + 0x60) = (u16)((v & ~0xff00) | (((((unsigned int)v << 0x10) >> 0x18 | 1) << 0x18) >> 0x10));
    state[0x12] = RandRange(-0x3244, 0x3244);
    state[0x10] = 0;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), (void *)func_ov210_020d4368);
}
