/* Take-off enter tick of an ov257 state: animation 0x1c plays, the +0x3d0 part plays motion 0x19,
 * bit 6 of the owner's +0x60 high byte is raised, the +0x54 timer and +0x76 clear and the tick
 * hands over to func_ov257_020d1c70. */
typedef unsigned short u16;

extern void func_ov107_020c9264(int owner, int anim, int mode);
extern void func_ov107_020c9ee8(int part, int motion, int mode);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov257_020d1c70(int *node);

void func_ov257_020d1bf8(int *node)
{
    int *state = (int *)node[1];
    u16 hw;

    func_ov107_020c9264(*state, 0x1c, 0);
    func_ov107_020c9ee8(*(int *)(*state + 0x3d0), 0x19, 0);
    hw = *(u16 *)(*state + 0x60);
    *(u16 *)(*state + 0x60) = (hw & ~0xff00) |
        ((((((unsigned int)hw << 0x10) >> 0x18) | 0x40) << 0x18) >> 0x10);
    state[0x15] = 0;
    *((unsigned char *)state + 0x76) = 0;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), (void *)func_ov257_020d1c70);
}
