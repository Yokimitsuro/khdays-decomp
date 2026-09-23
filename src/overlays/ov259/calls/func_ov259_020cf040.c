/* Wait entry of the ov259 actor: the +0x68 timer, +0x60 and the +0xac cue flags clear, +0x94 = 30,
 * bit 6 of the actor's +0x60 high byte is set, pose 0xf plays on the actor and its partner
 * (020cd524) and the node moves on to 020cf0bc. */
typedef unsigned char u8;
typedef unsigned short u16;

extern void func_ov107_020c9264(int actor, int pose, int loop);
extern void func_ov259_020cd524(int *node, int pose, int mode);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov259_020cf0bc(void);

void func_ov259_020cf040(int *node)
{
    int *state = (int *)node[1];

    state[0x1a] = 0;
    state[0x18] = 0;
    *((u8 *)state + 0xac) = 0;
    state[0x25] = 0x1e;
    {
        u16 hw = *(u16 *)(*state + 0x60);
        *(u16 *)(*state + 0x60) = (hw & ~0xff00) |
            ((((((unsigned int)hw << 0x10) >> 0x18) | 0x40) << 0x18) >> 0x10);
    }
    func_ov107_020c9264(*state, 0xf, 0);
    func_ov259_020cd524(node, 0xf, 0);
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov259_020cf0bc);
}
