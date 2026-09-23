/* Move entry: the actor's +0x390 latch is set, bits 1-3 and 7 of its +0x60 high byte and bit 0
 * of +0x1ae are set, pose 0 plays, reaction 0x16d/9 fires at the +0x18 point, the +0x30 vector
 * clears and the node moves to 020d34ac. */
typedef unsigned short u16;

extern void func_ov107_020c9264(int actor, int pose, int flag);
extern void func_ov107_020c5af8(int owner, int id, int mode, void *at);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov254_020d34ac(void);

void func_ov254_020d340c(int *node)
{
    int *state = (int *)node[1];

    *(int *)(*state + 0x390) = 1;
    {
        u16 hw = *(u16 *)(*state + 0x60);
        *(u16 *)(*state + 0x60) = (hw & ~0xff00) |
            ((((((unsigned int)hw << 0x10) >> 0x18) | 0x8e) << 0x18) >> 0x10);
    }
    *(u16 *)(*state + 0x100 + 0xae) |= 1;
    func_ov107_020c9264(*state, 0, 0);
    func_ov107_020c5af8(*state, 0x16d, 9, (void *)state[6]);
    state[0xc] = 0;
    state[0xd] = 0;
    state[0xe] = 0;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov254_020d34ac);
}
