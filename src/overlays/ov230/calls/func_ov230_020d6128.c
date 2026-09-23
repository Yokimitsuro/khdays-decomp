/* Wait tick of the ov230 actor: the +0x10 delay runs down at the frame rate; when it expires bit 0 of
 * the owner's +0x60 high byte is raised and bit 7 cleared, pose 0 plays, the +0xc clock and the +0x14
 * flag reset and brain slot +0x20 runs 020d61d0. */
typedef unsigned short u16;

extern void func_ov107_020c9264(int actor, int pose, int loop);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov230_020d61d0(void);

void func_ov230_020d6128(int *node)
{
    int *state = (int *)node[1];

    if ((state[4] -= *(int *)(node[0] + 0x2c)) > 0) {
        return;
    }
    {
        u16 hw = *(u16 *)(*state + 0x60);

        *(u16 *)(*state + 0x60) = (hw & ~0xff00) |
            ((((((unsigned int)hw << 0x10) >> 0x18) | 1) << 0x18) >> 0x10);
    }
    {
        u16 hw = *(u16 *)(*state + 0x60);

        *(u16 *)(*state + 0x60) = (hw & ~0xff00) |
            (((unsigned int)(unsigned short)((((unsigned int)hw << 0x10) >> 0x18) & ~0x80) << 0x18) >> 0x10);
    }
    func_ov107_020c9264(*state, 0, 0);
    state[3] = 0;
    *((unsigned char *)state + 0x14) = 0;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov230_020d61d0);
}
