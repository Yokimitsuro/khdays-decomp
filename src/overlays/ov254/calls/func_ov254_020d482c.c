/* Move entry: the actor's +0x388 latch is set, bits 0 and 7 of its +0x60 high byte are set, pose
 * 0 plays, reaction 0x16d/7 fires at the +8 point, the +0x24 / +0x28 timers and +0x2c / +0x2d
 * flags clear and the node moves to 020d48bc. */
typedef unsigned char u8;
typedef unsigned short u16;

extern void func_ov107_020c9264(int actor, int pose, int flag);
extern void func_ov107_020c5af8(int owner, int id, int mode, void *at);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov254_020d48bc(void);

void func_ov254_020d482c(int *node)
{
    int *state = (int *)node[1];

    *(int *)(*state + 0x388) = 1;
    {
        u16 hw = *(u16 *)(*state + 0x60);
        *(u16 *)(*state + 0x60) = (hw & ~0xff00) |
            ((((((unsigned int)hw << 0x10) >> 0x18) | 0x81) << 0x18) >> 0x10);
    }
    func_ov107_020c9264(*state, 0, 0);
    func_ov107_020c5af8(*state, 0x16d, 7, (void *)state[2]);
    state[9] = 0;
    state[10] = 0;
    *((u8 *)state + 0x2d) = 0;
    *((u8 *)state + 0x2c) = 0;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov254_020d48bc);
}
