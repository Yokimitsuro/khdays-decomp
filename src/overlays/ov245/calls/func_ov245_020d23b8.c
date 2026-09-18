/* func_ov245_020d23b8 -- entry of a sub-state: clears the actor's +0x38c handle, raises bit 7
 * and clears bit 0 of the +0x60 high byte, and installs 020d2430 in the node's slot. */
typedef unsigned short u16;
struct hw60 { unsigned short lo : 8, hi : 8; };

extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov245_020d2430(void);

void func_ov245_020d23b8(int *node) {
    int *state = (int *)node[1];

    *(int *)(*state + 0x38c) = 0;
    {
        u16 hw = *(u16 *)(*state + 0x60);
        *(u16 *)(*state + 0x60) = (hw & ~0xff00) |
            ((((((unsigned int)hw << 0x10) >> 0x18) | 0x80) << 0x18) >> 0x10);
    }
    ((struct hw60 *)(*state + 0x60))->hi &= ~1;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov245_020d2430);
}
