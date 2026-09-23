/* Enter tick of an ov235 state: bit 0 of the owner's +0x1ae is raised, bit 0 of its +0x39c part's
 * flag byte cleared and bit 6 of the +0x60 high byte raised; animation 0x1b plays and the tick hands
 * over to func_ov235_020cd66c. */
typedef struct { unsigned int lo : 8, rest : 24; } Byte8;

extern void func_ov107_020c9264(int owner, int anim, int mode);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov235_020cd66c(int *node);

void func_ov235_020cd5d8(int *node)
{
    int *state = (int *)node[1];
    unsigned short v;

    *(unsigned short *)(*state + 0x100 + 0xae) |= 1;
    ((Byte8 *)(*(int *)(*state + 0x39c) + 8))->lo &= ~1;
    v = *(unsigned short *)(*state + 0x60);
    *(unsigned short *)(*state + 0x60) =
        (unsigned short)((v & ~0xff00) | (((((unsigned int)v << 0x10) >> 0x18 | 0x40) << 0x18) >> 0x10));
    func_ov107_020c9264(*state, 0x1b, 0);
    func_0203c634(node, *(signed char *)((char *)node + 0x20), (void *)func_ov235_020cd66c);
}
