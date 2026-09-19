/* func_ov253_020d0bbc -- stun entry: sends message data_ov253_020d4964 + 8 (kind 4) to the
 * actor's +0x24 hook when set, fires reaction 0x16c/6 at the +4 anchor, raises bit 0 of +0x1ae,
 * raises bits 1 and 7 then clears bit 0 of the +0x60 high byte, clears bit 0 of the +0x3b4
 * item's +8 low byte and releases the node slot. */
typedef unsigned short u16;
struct hpair { unsigned short a, b; };
struct w8 { unsigned int lo : 8, rest : 24; };

extern void func_ov107_020c5af8(int actor, int id, int kind, void *anchor);
extern void func_0203c634(int *node, int slot, void *cb);
extern int data_ov253_020d4964;

void func_ov253_020d0bbc(int *node) {
    int *state = (int *)node[1];
    struct hpair msg = *(struct hpair *)((char *)&data_ov253_020d4964 + 8);
    void (*hook)(int, struct hpair *, int) = *(void (**)(int, struct hpair *, int))(*state + 0x24);

    if (hook != 0) {
        hook(*state, &msg, 4);
    }
    func_ov107_020c5af8(*state, 0x16c, 6, (void *)state[1]);
    *(u16 *)(*state + 0x100 + 0xae) |= 1;
    {
        u16 hw = *(u16 *)(*state + 0x60);
        *(u16 *)(*state + 0x60) = (hw & ~0xff00) |
            ((((((unsigned int)hw << 0x10) >> 0x18) | 0x82) << 0x18) >> 0x10);
    }
    {
        u16 hw = *(u16 *)(*state + 0x60);
        *(u16 *)(*state + 0x60) = (hw & ~0xff00) |
            (((unsigned int)(unsigned short)((((unsigned int)hw << 0x10) >> 0x18) & ~1) << 0x18) >> 0x10);
    }
    ((struct w8 *)(*(int *)(*state + 0x3b4) + 8))->lo &= ~1;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
}
