/* Bite entry of the ov272 enemy: effect 1 spawns at the +0x4c point,
 * animation 1 plays (looping), bit 0 of the +0x388 part's flag byte clears, bit 1 of the +0x60
 * high byte and bit 0 of +0x1ae are raised, reaction 0x167 mode 4 fires at the point, the +0x50
 * timer restarts and the tick hands over to func_ov272_020d2240. */
typedef struct { int x, y, z; } Vec3;
typedef struct { unsigned int lo : 8, rest : 24; } Byte8;

extern void func_ov107_020c0b90(int actor, int a, Vec3 v, int b);
extern void func_ov107_020c9264(int owner, int anim, int mode);
extern void func_ov107_020c5af8(int owner, int id, int mode, void *at);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov272_020d2240(int *node);

void func_ov272_020d215c(int *node)
{
    int *state = (int *)node[1];
    unsigned short v;

    func_ov107_020c0b90(*state, 1, *(Vec3 *)state[0x13], 0);
    func_ov107_020c9264(*state, 1, 1);
    ((Byte8 *)(*(int *)(*state + 0x388) + 8))->lo &= ~1;
    v = *(unsigned short *)(*state + 0x60);
    *(unsigned short *)(*state + 0x60) = (unsigned short)((v & ~0xff00) | (((((unsigned int)v << 0x10) >> 0x18 | 2) << 0x18) >> 0x10));
    *(unsigned short *)(*state + 0x100 + 0xae) |= 1;
    func_ov107_020c5af8(*state, 0x167, 4, (void *)state[0x13]);
    state[0x14] = 0;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), (void *)func_ov272_020d2240);
}
