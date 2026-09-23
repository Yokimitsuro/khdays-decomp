/* Hop entry of the ov283 actor: +0x74 clears, the +0x60 timer starts at 5.98, bit 6 of the +0x60 high
 * byte is set, pose 2 plays, the +0x1c drift points along the +0x38 heading at 0.875, +0x58 is 0.3125
 * and the node moves on to 020cd9e0. */
typedef unsigned short u16;
typedef struct { int x, y, z; } Vec3;

extern void func_ov107_020c9264(int actor, int pose, int loop);
extern void func_01ffa724(int scale, const Vec3 *v, Vec3 *out);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov283_020cd9e0(void);
extern const short data_0203d210[];

#define ANG2IDX(a) ((unsigned short)(((long long)(a) * 0x28be60db9391LL + 0x80000000000LL) >> 44) >> 4)

void func_ov283_020cd8f8(int *node)
{
    int *state = (int *)node[1];

    state[0x1d] = 0;
    state[0x18] = 0x5fa0;
    {
        u16 hw = *(u16 *)(*state + 0x60);
        *(u16 *)(*state + 0x60) = (hw & ~0xff00) |
            ((((((unsigned int)hw << 0x10) >> 0x18) | 0x40) << 0x18) >> 0x10);
    }
    func_ov107_020c9264(*state, 2, 0);
    {
        int idx = ANG2IDX(state[0xe]) * 2;

        state[7] = data_0203d210[idx];
        state[8] = 0;
        state[9] = data_0203d210[idx + 1];
    }
    func_01ffa724(0xe00, (Vec3 *)(state + 7), (Vec3 *)(state + 7));
    state[0x16] = 0x500;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov283_020cd9e0);
}
