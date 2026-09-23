/* Dash entry of the ov228 enemy (x2 with ov229): the +0x28 heading follows the owner's +0x398
 * direction, which is also kept at +0x14; bit 0 of the owner's +0x60 high byte is raised and bits
 * 2, 3 and 7 cleared, bit 0 of its +0x388 part's flag byte is raised, reaction 0x12b mode 0xd fires
 * at the +4 point, animation 0 plays, effect 0 spawns at the owner's +0x74 position, and the dash
 * state (+0x20 = 0, +0x24 = 0xc0, +0x2c = 0, +0x30 = 0x700, +0x38 = 1, +0x34 = 0) is armed before
 * the tick hands over to func_ov229_020d6444. */
typedef struct { int x, y, z; } Vec3;
struct hw60 { unsigned short lo : 8, hi : 8; };
typedef struct { unsigned int lo : 8, rest : 24; } Byte8;

extern int func_020050b4(int x, int z);
extern void func_ov107_020c5af8(int owner, int id, int mode, void *at);
extern void func_ov107_020c9264(int owner, int anim, int mode);
extern void func_ov107_020c0b90(int actor, int a, Vec3 v, int b);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov229_020d6444(int *node);

void func_ov229_020d6300(int *node)
{
    int *state = (int *)node[1];
    unsigned short v;

    state[0xa] = func_020050b4(*(int *)(*state + 0x398), *(int *)(*state + 0x3a0));
    *(Vec3 *)(state + 5) = *(Vec3 *)(*state + 0x398);
    v = *(unsigned short *)(*state + 0x60);
    *(unsigned short *)(*state + 0x60) = (unsigned short)((v & ~0xff00) | (((((unsigned int)v << 0x10) >> 0x18 | 1) << 0x18) >> 0x10));
    ((struct hw60 *)(*state + 0x60))->hi &= ~0x8c;
    ((Byte8 *)(*(int *)(*state + 0x388) + 8))->lo |= 1;
    func_ov107_020c5af8(state[0], 0x12b, 0xd, (void *)state[1]);
    func_ov107_020c9264(*state, 0, 0);
    func_ov107_020c0b90(*state, 0, *(Vec3 *)(*state + 0x74), 0);
    state[8] = 0;
    state[9] = 0xc0;
    state[0xb] = 0;
    state[0xc] = 0x700;
    state[0xe] = 1;
    *((unsigned char *)state + 0x34) = 0;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), (void *)func_ov229_020d6444);
}
