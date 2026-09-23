/* Blast entry of the ov260 actor: pose 0xc plays, the actor is knocked back at the origin (mode 0xa),
 * effects 0x16 and 0x1d start at the +0x10 point, +0x70 and the +0x7b flag clear and the node moves
 * on to 020d0834. */
typedef unsigned char u8;
typedef struct { int x, y, z; } Vec3;

extern void func_ov107_020c9264(int actor, int pose, int loop);
extern void func_ov107_020c0b90(int owner, int mode, Vec3 at, int flag);
extern void func_ov260_020cd148(int owner, int mode, int arg);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov260_020d0834(void);
extern const Vec3 data_02041dc8;

void func_ov260_020d07a0(int *node)
{
    int *state = (int *)node[1];

    func_ov107_020c9264(*state, 0xc, 0);
    func_ov107_020c0b90(*state, 0xa, data_02041dc8, 0);
    func_ov260_020cd148(*state, 0x16, state[4]);
    func_ov260_020cd148(*state, 0x1d, state[4]);
    state[0x1c] = 0;
    *((u8 *)state + 0x7b) = 0;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov260_020d0834);
}
