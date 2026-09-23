/* Stagger entry of the ov260 actor: bit 6 of the +0x60 high byte is set; in move 7 the partner's
 * queued move (+4 -> +0xad) clears, otherwise pose 0x19 plays; effect 0x19 starts at the +0x10 point,
 * +0x70 and the +0x7b flag clear and the node moves on to 020cf17c. */
typedef unsigned char u8;
typedef unsigned short u16;

extern void func_ov107_020c9264(int actor, int pose, int loop);
extern void func_ov260_020cd148(int owner, int mode, int arg);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov260_020cf17c(void);

void func_ov260_020cf0e8(int *node)
{
    int *state = (int *)node[1];

    {
        u16 hw = *(u16 *)(*state + 0x60);
        *(u16 *)(*state + 0x60) = (hw & ~0xff00) |
            ((((((unsigned int)hw << 0x10) >> 0x18) | 0x40) << 0x18) >> 0x10);
    }
    if (*(signed char *)(*state + 0x1c6) == 7) {
        *(u8 *)(state[1] + 0xad) = 0;
    } else {
        func_ov107_020c9264(*state, 0x19, 0);
    }
    func_ov260_020cd148(*state, 0x19, state[4]);
    state[0x1c] = 0;
    *((u8 *)state + 0x7b) = 0;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov260_020cf17c);
}
