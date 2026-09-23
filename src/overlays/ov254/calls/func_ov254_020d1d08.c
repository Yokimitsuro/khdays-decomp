/* Move entry: the actor's +0x388 latch is set, bit 0 of its +0x60 high byte is set, pose 0 plays,
 * reaction 0x16d/0x13 fires at the +8 point, the +0xc timer clears and the node moves to
 * 020d1d8c. */
typedef unsigned short u16;

extern void func_ov107_020c9264(int actor, int pose, int flag);
extern void func_ov107_020c5af8(int owner, int id, int mode, void *at);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov254_020d1d8c(void);

void func_ov254_020d1d08(int *node)
{
    int *state = (int *)node[1];

    *(int *)(*state + 0x388) = 1;
    {
        u16 hw = *(u16 *)(*state + 0x60);
        *(u16 *)(*state + 0x60) = (hw & ~0xff00) |
            ((((((unsigned int)hw << 0x10) >> 0x18) | 1) << 0x18) >> 0x10);
    }
    func_ov107_020c9264(*state, 0, 0);
    func_ov107_020c5af8(*state, 0x16d, 0x13, (void *)state[2]);
    state[3] = 0;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov254_020d1d8c);
}
