/* Enter tick of an ov235 state: bit 6 of the owner's +0x60 high byte is raised, the +0x40 and
 * +0x54 timers and the +0x8c/+0x8d flags clear, animation 0x15 plays, the +0x3a8 part plays motion
 * 0x11 and the tick hands over to func_ov235_020cfffc. */
extern void func_ov107_020c9264(int owner, int anim, int mode);
extern void func_ov107_020c9ee8(int part, int motion, int mode);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov235_020cfffc(int *node);

void func_ov235_020cff80(int *node)
{
    int *state = (int *)node[1];
    unsigned short v = *(unsigned short *)(*state + 0x60);

    *(unsigned short *)(*state + 0x60) =
        (unsigned short)((v & ~0xff00) | (((((unsigned int)v << 0x10) >> 0x18 | 0x40) << 0x18) >> 0x10));
    state[0x10] = 0;
    state[0x15] = 0;
    *((unsigned char *)state + 0x8c) = 0;
    *((unsigned char *)state + 0x8d) = 0;
    func_ov107_020c9264(*state, 0x15, 0);
    func_ov107_020c9ee8(*(int *)(*state + 0x3a8), 0x11, 0);
    func_0203c634(node, *(signed char *)((char *)node + 0x20), (void *)func_ov235_020cfffc);
}
