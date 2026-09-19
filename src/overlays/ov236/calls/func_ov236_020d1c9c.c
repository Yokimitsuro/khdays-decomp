/* Node initialiser (first rider form): resets the actor's +0x1c6 state and +0x1c7 request,
 * clears bit 0 of the +0x3b0 / +0x3b4 items' +8 low byte, points the state's +0x1c at the
 * actor's +0xb0 pose, +0x20 at its +0x74 position and +0x24 at the +0x384 item's +0xad, raises
 * bits 1-2 of the +0x60 high byte and installs the three slot handlers (1: 020d2130,
 * 0: 020d1d98, 2: 020d2070). */
typedef unsigned short u16;
struct w8 { unsigned int lo : 8, rest : 24; };

extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov236_020d2130(void);
extern void func_ov236_020d1d98(void);
extern void func_ov236_020d2070(void);

void func_ov236_020d1c9c(int *node) {
    int *state = (int *)node[1];
    int zero = 0;

    *(signed char *)(*state + 0x1c6) = zero;
    *(signed char *)(*state + 0x1c7) = zero - 1;
    ((struct w8 *)(*(int *)(*state + 0x3b0) + 8))->lo &= ~1;
    ((struct w8 *)(*(int *)(*state + 0x3b4) + 8))->lo &= ~1;
    state[7] = *state + 0xb0;
    state[8] = *state + 0x74;
    state[9] = *(int *)(*state + 0x384) + 0xad;
    {
        u16 hw = *(u16 *)(*state + 0x60);
        *(u16 *)(*state + 0x60) = (hw & ~0xff00) |
            ((((((unsigned int)hw << 0x10) >> 0x18) | 6) << 0x18) >> 0x10);
    }
    func_0203c634(node, 1, func_ov236_020d2130);
    func_0203c634(node, 0, func_ov236_020d1d98);
    func_0203c634(node, 2, func_ov236_020d2070);
}
