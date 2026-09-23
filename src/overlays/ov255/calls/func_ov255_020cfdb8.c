/* Enter tick of an ov255 state: bit 6 of the owner's +0x60 high byte is raised, the +0x40 rate,
 * the +0x50 timer and the +0x78/+0x79 flags clear, animation 0x15 plays, the +0x3a4 part plays
 * motion 0x11 and the tick hands over to func_ov255_020cfe34. */
typedef unsigned short u16;

extern void func_ov107_020c9264(int owner, int anim, int mode);
extern void func_ov107_020c9ee8(int part, int motion, int mode);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov255_020cfe34(int *node);

void func_ov255_020cfdb8(int *node)
{
    int *state = (int *)node[1];
    u16 hw;

    hw = *(u16 *)(*state + 0x60);
    *(u16 *)(*state + 0x60) = (hw & ~0xff00) |
        ((((((unsigned int)hw << 0x10) >> 0x18) | 0x40) << 0x18) >> 0x10);
    state[0x10] = 0;
    state[0x14] = 0;
    *((unsigned char *)state + 0x78) = 0;
    *((unsigned char *)state + 0x79) = 0;
    func_ov107_020c9264(*state, 0x15, 0);
    func_ov107_020c9ee8(*(int *)(*state + 0x3a4), 0x11, 0);
    func_0203c634(node, *(signed char *)((char *)node + 0x20), (void *)func_ov255_020cfe34);
}
