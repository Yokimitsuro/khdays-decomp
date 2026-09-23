/* Leap wind-up tick of the ov268 enemy (x3 with ov208/ov209). The +0x2c timer accumulates the
 * owner's rate; once past 0xeee reaction 0x15f mode 0xa fires at the +0xc point (once, flag
 * +0x49). When the +0x50 idle byte is clear, effect 4 spawns at the +8 point, bit 0 of +0x1ae is
 * raised, animation 0xc plays (mode 1) and the target is re-acquired into +0x10 with the +0x54
 * direction zeroed: with a target the flattened unit direction from the +8 point towards its
 * +0x190 is taken, or, when that is degenerate, the sine/cosine of the +0x30 heading, and the
 * direction is scaled by a twenty-fifth of the length; y then becomes 1.0, +0x34 takes the heading
 * of the direction and the tick hands over to func_ov268_020d2b5c. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef struct { int x, y, z; } Vec3;

static inline unsigned short FX_RadToIdx(int rad) {
    return (unsigned short)((0x28BE60DB9391LL * rad + 0x80000000000LL) >> 44);
}

extern void func_ov107_020c5af8(int owner, int id, int mode, void *at);
extern void func_ov107_020c0b90(int actor, int a, Vec3 v, int b);
extern void func_ov107_020c9264(int owner, int anim, int mode);
extern int func_ov107_020cab14(int owner, int flag);
extern void VEC_Subtract(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern int func_01ff8d18(const Vec3 *v, Vec3 *out);
extern void func_01ffa724(int scale, const Vec3 *v, Vec3 *out);
extern int func_020050b4(int x, int z);
extern void func_0203c634(int *node, int slot, void *cb);
extern const Vec3 data_02041dc8;
extern const short data_0203d210[];
extern void func_ov268_020d2b5c(int *node);

void func_ov268_020d2988(int *node)
{
    int *state = (int *)node[1];
    Vec3 d;
    int len;
    unsigned short idx;

    state[0xb] += *(int *)(node[0] + 0x2c);
    if (*(u8 *)((char *)state + 0x49) == 0 && state[0xb] >= 0xeee) {
        func_ov107_020c5af8(*state, 0x15f, 0xa, (void *)state[3]);
        *(u8 *)((char *)state + 0x49) = 1;
    }
    if (*(u8 *)state[0x14] != 0) {
        return;
    }
    func_ov107_020c0b90(*state, 4, *(Vec3 *)state[2], 0);
    *(u16 *)(*state + 0x100 + 0xae) |= 1;
    func_ov107_020c9264(*state, 0xc, 1);
    *(Vec3 *)(state + 0x15) = data_02041dc8;
    state[4] = func_ov107_020cab14(*state, 0);
    if (state[4] != 0) {
        VEC_Subtract((Vec3 *)(state[4] + 0x190), (Vec3 *)state[2], &d);
        d.y = 0;
        len = func_01ff8d18(&d, (Vec3 *)(state + 0x15));
        if (len == 0) {
            idx = FX_RadToIdx(state[0xc]);
            state[0x15] = data_0203d210[(idx >> 4) * 2];
            state[0x16] = 0;
            state[0x17] = data_0203d210[(idx >> 4) * 2 + 1];
        }
        func_01ffa724(len / 25, (Vec3 *)(state + 0x15), (Vec3 *)(state + 0x15));
    }
    state[0x16] = 0x1000;
    state[0xd] = func_020050b4(state[0x15], state[0x17]);
    func_0203c634(node, *(signed char *)((char *)node + 0x20), (void *)func_ov268_020d2b5c);
}
