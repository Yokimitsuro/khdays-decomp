/* func_ov245_020d403c -- charge-up (variant): clears the actor's +0x3a0, holds the state's +0x28
 * at 15 and counts the +0x2c timer up by the scene step; after 0.5 raises bit 0 of the +0x60 high byte and bit 0 of
 * the +0x388 item's +8 low byte, plays pose 0 and moves the node to 020d40e8. */
typedef unsigned short u16;
struct w8 { unsigned int lo : 8, rest : 24; };

extern void func_ov107_020c9264(int actor, int pose, int flag);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov245_020d40e8(void);

void func_ov245_020d403c(int *node) {
    int *state = (int *)node[1];

    *(int *)(*state + 0x3a0) = 0;
    state[10] = 0xf;
    state[0xb] += *(int *)(*node + 0x2c);
    if (state[0xb] < 0x800) {
        return;
    }
    {
        u16 hw = *(u16 *)(*state + 0x60);
        *(u16 *)(*state + 0x60) = (hw & ~0xff00) |
            ((((((unsigned int)hw << 0x10) >> 0x18) | 1) << 0x18) >> 0x10);
    }
    ((struct w8 *)(*(int *)(*state + 0x388) + 8))->lo |= 1;
    func_ov107_020c9264(*state, 0, 0);
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov245_020d40e8);
}
