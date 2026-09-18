/* func_ov245_020d4fd4 -- entry of the sub-state: raises bit 7 and clears bit 0 of the actor's
 * +0x60 high byte, clears +0x390, bit 0 of +0x1ae and bit 0 of the +0x388 item's +8 low byte,
 * and installs 020d4038 in the node's slot. */
typedef unsigned short u16;
struct hw60 { unsigned short lo : 8, hi : 8; };
struct w8 { unsigned int lo : 8, rest : 24; };

extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov245_020d5088(void);

void func_ov245_020d4fd4(int *node) {
    int *state = (int *)node[1];

    {
        u16 hw = *(u16 *)(*state + 0x60);
        *(u16 *)(*state + 0x60) = (hw & ~0xff00) |
            ((((((unsigned int)hw << 0x10) >> 0x18) | 0x80) << 0x18) >> 0x10);
    }
    *(int *)(*state + 0x390) = 0;
    ((struct hw60 *)(*state + 0x60))->hi &= ~1;
    *(u16 *)(*state + 0x100 + 0xae) &= ~1;
    ((struct w8 *)(*(int *)(*state + 0x388) + 8))->lo &= ~1;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov245_020d5088);
}
