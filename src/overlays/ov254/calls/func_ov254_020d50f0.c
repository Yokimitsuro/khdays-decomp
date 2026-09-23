/* Mount-follow tick: while in a positive move and the +0x388 mount has a +0x4dc rider slot, bit 0
 * of the actor's +0x60 high byte is set and bit 7 cleared, the actor lands on the mount's +0xb0
 * point (020c5c54) and takes its +0xa0 pose. */
typedef unsigned short u16;

extern void func_ov107_020c5c54(int actor, void *at);
extern void func_0203c9d0(void *pose, void *q);

void func_ov254_020d50f0(int *node)
{
    int *state = (int *)node[1];
    int actor = *state;

    if (*(signed char *)(actor + 0x100 + 0xc6) <= 0) {
        return;
    }
    if (*(int *)(*(int *)(actor + 0x388) + 0x4dc) == 0) {
        return;
    }
    {
        u16 hw = *(u16 *)(actor + 0x60);
        *(u16 *)(actor + 0x60) = (hw & ~0xff00) |
            ((((((unsigned int)hw << 0x10) >> 0x18) | 1) << 0x18) >> 0x10);
    }
    {
        int a = *state;
        u16 hw = *(u16 *)(a + 0x60);
        *(u16 *)(a + 0x60) = (hw & ~0xff00) |
            (((unsigned int)(unsigned short)((((unsigned int)hw << 0x10) >> 0x18) & ~0x80) << 0x18) >> 0x10);
    }
    func_ov107_020c5c54(*state, (void *)(*(int *)(*state + 0x388) + 0xb0));
    func_0203c9d0((void *)(*state + 0xa0), (void *)(*(int *)(*state + 0x388) + 0xa0));
}
