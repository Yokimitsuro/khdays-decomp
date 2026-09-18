/* Leap entry of the ov298 enemy: clears the +0x8c flag, arms the +0x40 clock at 0x5fa0, sets
 * bit 6 of the +0x60 high byte, plays animation 2 and its held-item counterpart, points the
 * +0x1c velocity along the facing of the +0x2c yaw at 0xe00, sets the +0x4c height to 0x500
 * and hands off to d4da4. */
struct hw60 { unsigned short lo : 8, hi : 8; };

extern void func_ov107_020c9264(int actor, int anim, int flag);
extern void func_ov298_020d3f50(int actor, int anim);
extern void func_01ffa724(int scale, int *v, int *d);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov298_020d4da4(int *node);
extern const short data_0203d210[];

#define ANG2IDX(a) ((unsigned short)(((long long)(a) * 0x28be60db9391LL + 0x80000000000LL) >> 44) >> 4)

void func_ov298_020d4cb0(int *node)
{
    int *state = (int *)node[1];
    unsigned short *hw;
    unsigned int h;
    unsigned int idx;

    state[0x23] = 0;
    state[0x10] = 0x5fa0;
    hw = (unsigned short *)(*state + 0x60);
    h = *hw;
    *hw = h & ~0xff00 | (((((unsigned int)h << 0x10) >> 0x18 | 0x40) << 0x18) >> 0x10);
    func_ov107_020c9264(*state, 2, 0);
    func_ov298_020d3f50(*state, 2);
    idx = ANG2IDX(state[0xb]);
    state[7] = data_0203d210[idx * 2];
    state[8] = 0;
    state[9] = data_0203d210[idx * 2 + 1];
    func_01ffa724(0xe00, state + 7, state + 7);
    state[0x13] = 0x500;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov298_020d4da4);
}
