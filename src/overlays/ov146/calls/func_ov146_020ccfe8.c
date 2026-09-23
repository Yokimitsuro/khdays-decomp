/* Wake tick of the ov146 actor: +0x3c accumulates the frame rate; after 0.43 bits 1 and 7 of both its
 * and its partner's (+8) +0x60 high byte clear, both play pose 0 and the node moves on to 020cd0a4. */
typedef unsigned short u16;

extern void func_ov107_020c9264(int actor, int pose, int loop);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov146_020cd0a4(void);

void func_ov146_020ccfe8(int *node)
{
    int *state = (int *)node[1];

    state[0xf] += *(int *)(node[0] + 0x2c);
    if (state[0xf] < 0x6ee) {
        return;
    }
    {
        u16 hw = *(u16 *)(*state + 0x60);
        *(u16 *)(*state + 0x60) = (hw & ~0xff00) |
            (((unsigned int)(u16)((((unsigned int)hw << 0x10) >> 0x18) & ~0x82) << 0x18) >> 0x10);
    }
    {
        u16 hw = *(u16 *)(state[2] + 0x60);
        *(u16 *)(state[2] + 0x60) = (hw & ~0xff00) |
            (((unsigned int)(u16)((((unsigned int)hw << 0x10) >> 0x18) & ~0x82) << 0x18) >> 0x10);
    }
    func_ov107_020c9264(*state, 0, 0);
    func_ov107_020c9264(state[2], 0, 0);
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov146_020cd0a4);
}
