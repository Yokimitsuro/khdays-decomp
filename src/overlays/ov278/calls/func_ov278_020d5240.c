/* Dismount-leap tick: +0x24 keeps 3x the frame rate, the +0x14 timer and the +0x78 clock
 * accumulate it and the timer maps to t in 0..1. The +8 velocity is the cubic Hermite blend of the
 * +0x58 start, the +0x384 mount's +0xb0 position and the +0x40 / +0x4c tangents relative to the
 * +0x1c anchor; the +0x64 pose slerps by t towards the mount's +0xa0 pose, whose forward
 * (data_02042258) sets the +0x28 / +0x2c headings. At t = 1 bits 1-2 of the actor's +0x60 high
 * byte and bit 0 of +0x1ae clear, the mount's +0x3bc bit 0 is set when exactly one rider counter
 * (+0x3d0 / +0x3d2) is left, the actor's +0x3d4 bit 0 is set and the node moves to 020d54e0. */
typedef unsigned short u16;
typedef struct { int x, y, z; } Vec3;
struct m4 { int w[4]; };
struct Bits3bc { unsigned char b0 : 1; };
struct Bits3d4 { unsigned int b0 : 1; };

static inline int FX_Mul(int a, int b) {
    return (int)(((long long)a * b + 0x800) >> 12);
}

extern int FX_Inv(int num, int den);
extern void func_01ffa724(int scale, const Vec3 *v, Vec3 *out);
extern void VEC_Add(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern void VEC_Subtract(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern void func_0202f55c(void *a, int s, void *b, void *m);
extern void func_0202f384(Vec3 *out, void *rotation, const Vec3 *in);
extern int func_020050b4(int x, int z);
extern void func_0203c634(int *node, int slot, void *cb);
extern const Vec3 data_02042258;
extern void func_ov278_020d5494(void);

void func_ov278_020d5240(int *node) {
    int *state = (int *)node[1];
    Vec3 mountPos;
    Vec3 acc;
    Vec3 tmp;
    struct m4 pose;
    int t;
    int t2;
    int t3;
    int t2x3;

    state[9] = *(int *)(node[0] + 0x2c) * 30 / 10;
    state[5] += *(int *)(node[0] + 0x2c);
    state[0x1e] += *(int *)(node[0] + 0x2c);
    mountPos = *(Vec3 *)(*(int *)(*state + 0x384) + 0xb0);
    t = FX_Inv(state[5], 0x1000);
    t2 = FX_Mul(t, t);
    t3 = FX_Mul(t2, t);
    t2x3 = 3 * t2;
    func_01ffa724(2 * t3 - t2x3 + 0x1000, (Vec3 *)(state + 0x16), &acc);
    func_01ffa724(-(t3 + t3) + t2x3, &mountPos, &tmp);
    VEC_Add(&acc, &tmp, &acc);
    func_01ffa724(t3 - 2 * t2 + t, (Vec3 *)(state + 0x10), &tmp);
    VEC_Add(&acc, &tmp, &acc);
    func_01ffa724(t3 - t2, (Vec3 *)(state + 0x13), &tmp);
    VEC_Add(&acc, &tmp, &acc);
    VEC_Subtract(&acc, (Vec3 *)state[7], (Vec3 *)(state + 2));
    func_0202f55c(&pose, t, state + 0x19, (void *)(*(int *)(*state + 0x384) + 0xa0));
    func_0202f384(&tmp, (void *)(*(int *)(*state + 0x384) + 0xa0), &data_02042258);
    state[0xb] = state[0xa] = func_020050b4(tmp.x, tmp.z);
    if (state[5] < 0x1000) return;
    {
        int actor = *state;
        u16 hw = *(u16 *)(actor + 0x60);
        *(u16 *)(actor + 0x60) = (hw & ~0xff00) |
            (((unsigned int)(unsigned short)((((unsigned int)hw << 0x10) >> 0x18) & ~6) << 0x18) >> 0x10);
    }
    *(u16 *)(*state + 0x100 + 0xae) &= ~1;
    if (!(*(short *)(*state + 0x300 + 0xd0) != 0 && *(short *)(*state + 0x300 + 0xd2) != 0)) {
        if (*(short *)(*state + 0x300 + 0xd0) != 0 || *(short *)(*state + 0x300 + 0xd2) != 0) {
            ((struct Bits3bc *)(*(int *)(*state + 0x384) + 0x3bc))->b0 = 1;
        }
    }
    ((struct Bits3d4 *)(*state + 0x3d4))->b0 = 1;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov278_020d5494);
}
