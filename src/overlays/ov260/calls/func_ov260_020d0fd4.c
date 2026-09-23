/* Start of the ov260 actor's brain: +0x18 points at its +0xb0 anchor, no move is current or pending
 * (+0x1c6 = 0, +0x1c7 = -1), bit 6 of the +0x60 high byte is set and bit 0 dropped, bit 0 of +0x1ae
 * clears and the three slots take the think (020d10a0), watch (020d1178) and facing (020d1118)
 * handlers. */
typedef unsigned short u16;

extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov260_020d10a0(void);
extern void func_ov260_020d1178(void);
extern void func_ov260_020d1118(void);

void func_ov260_020d0fd4(int *node)
{
    int *state = (int *)node[1];

    state[6] = *state + 0xb0;
    *(signed char *)(*state + 0x1c6) = 0;
    *(signed char *)(*state + 0x1c7) = -1;
    {
        u16 hw = *(u16 *)(*state + 0x60);
        *(u16 *)(*state + 0x60) = (hw & ~0xff00) |
            ((((((unsigned int)hw << 0x10) >> 0x18) | 0x40) << 0x18) >> 0x10);
    }
    {
        u16 hw = *(u16 *)(*state + 0x60);
        *(u16 *)(*state + 0x60) = (hw & ~0xff00) |
            (((unsigned int)(u16)((((unsigned int)hw << 0x10) >> 0x18) & ~1) << 0x18) >> 0x10);
    }
    *(u16 *)(*state + 0x1ae) &= ~1;
    func_0203c634(node, 0, func_ov260_020d10a0);
    func_0203c634(node, 1, func_ov260_020d1178);
    func_0203c634(node, 2, func_ov260_020d1118);
}
