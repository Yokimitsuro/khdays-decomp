/* Dock entry of an ov260 helper: its owner is marked busy (+0x388), bit 7 of the +0x60 high byte
 * drops and bit 0 is set, pose 0 plays, +0xc and the +0x10 flag clear and the node moves on to
 * 020d2888. */
typedef unsigned char u8;
typedef unsigned short u16;

extern void func_ov107_020c9264(int actor, int pose, int loop);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov260_020d2888(void);

void func_ov260_020d27ec(int *node)
{
    int *state = (int *)node[1];

    *(int *)(*state + 0x388) = 1;
    {
        u16 hw = *(u16 *)(*state + 0x60);
        *(u16 *)(*state + 0x60) = (hw & ~0xff00) |
            (((unsigned int)(u16)((((unsigned int)hw << 0x10) >> 0x18) & ~0x80) << 0x18) >> 0x10);
    }
    {
        u16 hw = *(u16 *)(*state + 0x60);
        *(u16 *)(*state + 0x60) = (hw & ~0xff00) |
            ((((((unsigned int)hw << 0x10) >> 0x18) | 1) << 0x18) >> 0x10);
    }
    func_ov107_020c9264(*state, 0, 0);
    state[3] = 0;
    *((u8 *)state + 0x10) = 0;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov260_020d2888);
}
