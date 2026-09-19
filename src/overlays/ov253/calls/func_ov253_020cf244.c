/* func_ov253_020cf244 -- charge entry: raises bit 0 of the actor's +0x1ae, sets pose 2, raises
 * bit 0 of the +0x60 high byte, fires reaction 0x16c/7 at the +4 anchor and moves the node to
 * 020cf2c0. */
typedef unsigned short u16;

extern void func_ov107_020c9264(int actor, int pose, int flag);
extern void func_ov107_020c5af8(int actor, int id, int kind, void *anchor);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov253_020cf2c0(void);

void func_ov253_020cf244(int *node) {
    int *state = (int *)node[1];

    *(u16 *)(*state + 0x100 + 0xae) |= 1;
    func_ov107_020c9264(*state, 2, 0);
    {
        u16 hw = *(u16 *)(*state + 0x60);
        *(u16 *)(*state + 0x60) = (hw & ~0xff00) |
            ((((((unsigned int)hw << 0x10) >> 0x18) | 1) << 0x18) >> 0x10);
    }
    func_ov107_020c5af8(*state, 0x16c, 7, (void *)state[1]);
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov253_020cf2c0);
}
