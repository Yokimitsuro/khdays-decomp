/* func_ov245_020ceef0 -- charge delay: counts the state's +0x30 timer up by the scene step; at
 * 0.3125 raises bit 0 of the actor's +0x60 high byte and bit 0 of the +0x388 item's +8 low byte,
 * fires reaction 0x15a of kind 0xf at the +8 position (020c5af8), clears the timer and moves the
 * node to 020cef98. */
typedef unsigned short u16;
struct w8 { unsigned int lo : 8, rest : 24; };

extern void func_ov107_020c5af8(int actor, int id, int kind, void *anchor);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov245_020cef98(void);

void func_ov245_020ceef0(int *node) {
    int *state = (int *)node[1];

    state[0xc] += *(int *)(*node + 0x2c);
    if (state[0xc] < 0x500) {
        return;
    }
    {
        u16 hw = *(u16 *)(*state + 0x60);
        *(u16 *)(*state + 0x60) = (hw & ~0xff00) |
            ((((((unsigned int)hw << 0x10) >> 0x18) | 1) << 0x18) >> 0x10);
    }
    ((struct w8 *)(*(int *)(*state + 0x388) + 8))->lo |= 1;
    func_ov107_020c5af8(*state, 0x15a, 0xf, (void *)state[2]);
    state[0xc] = 0;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov245_020cef98);
}
