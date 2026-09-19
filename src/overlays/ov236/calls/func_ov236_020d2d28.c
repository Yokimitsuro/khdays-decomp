/* Buck entry: raises bits 1-2 and 6 of the actor's +0x60 high byte and bit 0 of +0x1ae,
 * deactivates the +0x3b0 / +0x3b4 items, plays pose 5, keeps the +0xa0 pose at +0x64 and the
 * +0x1c anchor's position at +0x58, throws the +0x40 velocity along a random yaw (+-0x3244)
 * at 20.0 plus a random 0..10.0, the +0x4c one straight down (-1.0 in y) at 40.0 plus a random
 * 0..10.0, clears the +0x14 timer and moves the node to 020d2ed4. */
typedef unsigned short u16;
typedef struct Vec3 { int x, y, z; } Vec3;
struct m4 { int w[4]; };
struct w8 { unsigned int lo : 8, rest : 24; };

extern void func_ov107_020c9264(int actor, int anim, int flag);
extern int func_02023eb4(int range);
extern void func_01ffa724(int scale, Vec3 *v, Vec3 *d);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov236_020d2ed4(int *node);
extern const short data_0203d210[];

static inline unsigned short FX_RadToIdx(int rad) {
    return (unsigned short)((0x28BE60DB9391LL * rad + 0x80000000000LL) >> 44);
}

void func_ov236_020d2d28(int *node)
{
    int *state = (int *)node[1];
    unsigned short idx;
    int zero;

    {
        u16 hw = *(u16 *)(*state + 0x60);
        *(u16 *)(*state + 0x60) = (hw & ~0xff00) |
            ((((((unsigned int)hw << 0x10) >> 0x18) | 0x46) << 0x18) >> 0x10);
    }
    *(u16 *)(*state + 0x100 + 0xae) |= 1;
    ((struct w8 *)(*(int *)(*state + 0x3b0) + 8))->lo &= ~1;
    ((struct w8 *)(*(int *)(*state + 0x3b4) + 8))->lo &= ~1;
    func_ov107_020c9264(*state, 5, 0);
    *(struct m4 *)(state + 0x19) = *(struct m4 *)(*state + 0xa0);
    *(Vec3 *)(state + 0x16) = *(Vec3 *)state[7];
    idx = FX_RadToIdx(func_02023eb4(0x6489) - 0x3244);
    state[0x10] = data_0203d210[(idx >> 4) << 1];                             /* FX_SinIdx */
    state[0x11] = 0;
    state[0x12] = data_0203d210[((idx >> 4) << 1) + 1];                       /* FX_CosIdx */
    func_01ffa724(func_02023eb4(0xa001) + 0x14000, (Vec3 *)(state + 0x10), (Vec3 *)(state + 0x10));
    zero = 0;
    state[0x13] = zero;
    state[0x14] = zero - 0x1000;
    state[0x15] = zero;
    func_01ffa724(func_02023eb4(0xa001) + 0x28000, (Vec3 *)(state + 0x13), (Vec3 *)(state + 0x13));
    state[5] = 0;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov236_020d2ed4);
}
