/* Start of the ov146 actor's helper: no move is current or next, the +8 model's +0x5c bit 1 is set,
 * bit 0 of the actor's +0x60 high byte is set and the three helper slots start (020cf338 in slot 0,
 * 020cf3d0 in slot 1, 020cf3cc in slot 2). */
typedef unsigned short u16;

extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov146_020cf338(void);
extern void func_ov146_020cf3d0(void);
extern void func_ov146_020cf3cc(void);

void func_ov146_020cf290(int *node)
{
    int *state = (int *)node[1];

    *(unsigned char *)(*state + 0x1c6) = 0;
    *(signed char *)(*state + 0x1c7) = -1;
    *(int *)(state[2] + 0x5c) |= 2;
    {
        u16 hw = *(u16 *)(*state + 0x60);
        *(u16 *)(*state + 0x60) = (hw & ~0xff00) |
            ((((((unsigned int)hw << 0x10) >> 0x18) | 1) << 0x18) >> 0x10);
    }
    func_0203c634(node, 0, func_ov146_020cf338);
    func_0203c634(node, 1, func_ov146_020cf3d0);
    func_0203c634(node, 2, func_ov146_020cf3cc);
}
