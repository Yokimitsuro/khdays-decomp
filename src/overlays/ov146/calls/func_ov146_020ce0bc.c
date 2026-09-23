/* Recover tick of the ov146 actor: +0x3c accumulates the frame rate; after 0.83 the partner (+8) is
 * released from mode 0, bit 0 of the +0x60 high byte clears and bit 7 is set, the +0x3bc effect stops
 * (020cee14), the next move is 0 and the node ends. */
typedef unsigned short u16;

extern int func_ov146_020ce298(int a, int b);
extern int func_ov146_020cee14(int param_1, int param_2);
extern void func_0203c634(int *node, int slot, void *cb);

void func_ov146_020ce0bc(int *node)
{
    int *state = (int *)node[1];

    state[0xf] += *(int *)(node[0] + 0x2c);
    if (state[0xf] < 0xd48) {
        return;
    }
    func_ov146_020ce298(state[2], 0);
    {
        u16 hw = *(u16 *)(*state + 0x60);
        *(u16 *)(*state + 0x60) = (hw & ~0xff00) |
            (((unsigned int)(u16)((((unsigned int)hw << 0x10) >> 0x18) & ~1) << 0x18) >> 0x10);
    }
    {
        u16 hw = *(u16 *)(*state + 0x60);
        *(u16 *)(*state + 0x60) = (hw & ~0xff00) |
            ((((((unsigned int)hw << 0x10) >> 0x18) | 0x80) << 0x18) >> 0x10);
    }
    func_ov146_020cee14(*(int *)(*state + 0x3bc), 0);
    *(unsigned char *)(*state + 0x1c7) = 0;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
}
