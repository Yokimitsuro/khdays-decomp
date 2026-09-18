/* func_ov245_020d2434 -- charge-up tick: flags the actor's +0x38c, holds the state's +0x18 at
 * 10 and advances +0x1c by the scene's +0x2c step; after 0.5 raises bit 0 of the +0x60 high
 * byte, plays pose 0 and moves the node to 020d24bc. */
typedef unsigned short u16;

extern void func_ov107_020c9264(int actor, int pose, int flag);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov245_020d24bc(void);

void func_ov245_020d2434(int *node) {
    int *state = (int *)node[1];

    *(int *)(*state + 0x38c) = 1;
    state[6] = 10;
    state[7] += *(int *)(*node + 0x2c);
    if (state[7] < 0x800) {
        return;
    }
    {
        u16 hw = *(u16 *)(*state + 0x60);
        *(u16 *)(*state + 0x60) = (hw & ~0xff00) |
            ((((((unsigned int)hw << 0x10) >> 0x18) | 1) << 0x18) >> 0x10);
    }
    func_ov107_020c9264(*state, 0, 0);
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov245_020d24bc);
}
