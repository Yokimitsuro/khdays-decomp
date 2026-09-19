/* func_ov253_020cd1bc -- sub-state root: clears the actor's +0x1c6 kind and +0x1c7 sub-state
 * (-1), points the state at the +0x38c item's +0xad flag and the actor's +0xb0 vector, seeds the
 * +0xc / +0x10 angles with atan2(0, 1.0) and atan2(1.0, 0), clears bit 0 of the +0x444 item's
 * +8 low byte, raises bits 1, 2 and 4 of the +0x60 high byte and installs the three sub-nodes
 * (slot 1: 020cd5a8, slot 0: 020cd2a4, slot 2: 020cd484). */
typedef unsigned short u16;
struct w8 { unsigned int lo : 8, rest : 24; };

extern int func_020050b4(int y, int x);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov253_020cd5a8(void);
extern void func_ov253_020cd2a4(void);
extern void func_ov253_020cd484(void);

void func_ov253_020cd1bc(int *node) {
    int *state = (int *)node[1];

    *(unsigned char *)(*state + 0x1c6) = 0;
    *(signed char *)(*state + 0x1c7) = -1;
    state[1] = *(int *)(*state + 0x38c) + 0xad;
    state[2] = *state + 0xb0;
    state[3] = func_020050b4(0, 0x1000);
    state[4] = func_020050b4(0x1000, 0);
    ((struct w8 *)(*(int *)(*state + 0x444) + 8))->lo &= ~1;
    {
        u16 hw = *(u16 *)(*state + 0x60);
        *(u16 *)(*state + 0x60) = (hw & ~0xff00) |
            ((((((unsigned int)hw << 0x10) >> 0x18) | 0x16) << 0x18) >> 0x10);
    }
    func_0203c634(node, 1, func_ov253_020cd5a8);
    func_0203c634(node, 0, func_ov253_020cd2a4);
    func_0203c634(node, 2, func_ov253_020cd484);
}
