/* func_ov245_020cceb8 -- node initialiser: resets the actor's +0x1c6 state and +0x1c7 request,
 * clears bit 0 of the +0x3b4 item's +8 low byte, sets the state's +0x24 to 3.14 (0x3244) and
 * points +8 at the actor's +0xb0 pose, raises bits 1, 2 and 4 and clears bits 3
 * and 6 of the +0x60 high byte, and installs the three slot handlers (1: 020cd668, 0: 020ccfa8,
 * 2: 020cd1d0). */
typedef unsigned short u16;
struct w8 { unsigned int lo : 8, rest : 24; };

extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov245_020cd668(void);
extern void func_ov245_020ccfa8(void);
extern void func_ov245_020cd1d0(void);

void func_ov245_020cceb8(int *node) {
    int *state = (int *)node[1];

    *(unsigned char *)(*state + 0x1c6) = 0;
    *(signed char *)(*state + 0x1c7) = -1;
    ((struct w8 *)(*(int *)(*state + 0x3b4) + 8))->lo &= ~1;
    state[9] = 0x3244;
    state[2] = *state + 0xb0;
    {
        u16 hw = *(u16 *)(*state + 0x60);
        *(u16 *)(*state + 0x60) = (hw & ~0xff00) |
            ((((((unsigned int)hw << 0x10) >> 0x18) | 0x16) << 0x18) >> 0x10);
    }
    {
        u16 hw = *(u16 *)(*state + 0x60);
        *(u16 *)(*state + 0x60) = (hw & ~0xff00) |
            (((unsigned int)(unsigned short)((((unsigned int)hw << 0x10) >> 0x18) & ~0x48) << 0x18) >> 0x10);
    }
    func_0203c634(node, 1, func_ov245_020cd668);
    func_0203c634(node, 0, func_ov245_020ccfa8);
    func_0203c634(node, 2, func_ov245_020cd1d0);
}
