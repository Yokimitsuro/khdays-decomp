/* func_ov253_020cd5a8 -- hold entry: raises bits 1 and 7 of the actor's +0x60 high byte, clears
 * bit 0 and raises bit 1 of the +0x444 item's +8 low byte and moves the node to 020cd638. */
typedef unsigned short u16;
struct w8 { unsigned int lo : 8, rest : 24; };

extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov253_020cd638(void);

void func_ov253_020cd5a8(int *node) {
    int *state = (int *)node[1];

    {
        u16 hw = *(u16 *)(*state + 0x60);
        *(u16 *)(*state + 0x60) = (hw & ~0xff00) |
            ((((((unsigned int)hw << 0x10) >> 0x18) | 0x82) << 0x18) >> 0x10);
    }
    ((struct w8 *)(*(int *)(*state + 0x444) + 8))->lo &= ~1;
    ((struct w8 *)(*(int *)(*state + 0x444) + 8))->lo |= 2;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov253_020cd638);
}
