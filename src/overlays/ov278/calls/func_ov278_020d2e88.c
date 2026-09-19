/* Buck tick: runs the +0x14 timer and maps it to t in 0..1. The +8 velocity is the cubic
 * Hermite blend of the +0x58 start, the +0x394 mount's +0xb0 position, the +0x40 launch and
 * +0x4c landing tangents (h00 = 2t^3-3t^2+1, h01 = -2t^3+3t^2, h10 = t^3-2t^2+t, h11 = t^3-t^2)
 * relative to the +0x1c anchor; the +0x64 pose slerps by t towards the mount's +0xa0 pose,
 * whose forward (data_02042258) sets the +0x2c / +0x30 headings. At t = 1 bit 1 of the actor's
 * +0x60 high byte and bit 0 of +0x1ae clear, the mount is told to land (020c5c54), the mount's
 * +0x3bc bit 0 is set when exactly one rider counter is left, the actor's +0x3c0 bit 0 is set
 * and the node moves to 020d30f4. */
typedef unsigned short u16;
typedef struct { int x, y, z; } Vec3;
struct m4 { int w[4]; };
struct Bits3bc { unsigned char b0 : 1; };
struct Bits3c0 { unsigned int b0 : 1; };

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
extern void func_ov107_020c5c54(int obj, Vec3 *v);
extern void func_0203c634(int *node, int slot, void *cb);
extern const Vec3 data_02042258;
extern void func_ov278_020d30a8(void);

void func_ov278_020d2e88(int *node) {
    int *state = (int *)node[1];
    Vec3 mountPos;
    Vec3 acc;
    Vec3 tmp;
    struct m4 pose;
    int t;
    int t2;
    int t3;
    int t2x3;

    state[5] += *(int *)(node[0] + 0x2c);
    mountPos = *(Vec3 *)(*(int *)(*state + 0x394) + 0xb0);
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
    func_0202f55c(&pose, t, state + 0x19, (void *)(*(int *)(*state + 0x394) + 0xa0));
    func_0202f384(&tmp, (void *)(*(int *)(*state + 0x394) + 0xa0), &data_02042258);
    state[0xc] = state[0xb] = func_020050b4(tmp.x, tmp.z);
    if (state[5] < 0x1000) return;
    {
        int actor = *state;
        u16 hw = *(u16 *)(actor + 0x60);
        *(u16 *)(actor + 0x60) = (hw & ~0xff00) |
            (((unsigned int)(unsigned short)((((unsigned int)hw << 0x10) >> 0x18) & ~2) << 0x18) >> 0x10);
    }
    *(u16 *)(*state + 0x100 + 0xae) &= ~1;
    func_ov107_020c5c54(*state, &mountPos);
    if (!(*(short *)(*state + 0x300 + 0xbc) != 0 && *(short *)(*state + 0x300 + 0xbe) != 0)) {
        if (*(short *)(*state + 0x300 + 0xbc) != 0 || *(short *)(*state + 0x300 + 0xbe) != 0) {
            ((struct Bits3bc *)(*(int *)(*state + 0x394) + 0x3bc))->b0 = 1;
        }
    }
    ((struct Bits3c0 *)(*state + 0x3c0))->b0 = 1;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov278_020d30a8);
}
