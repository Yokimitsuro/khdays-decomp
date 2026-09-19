/* Attack entry of the ov221 enemy: animation 6 with a +0x78 target (7 without) plays, the
 * zero-vector message of mode 1 goes out with flag 1 only when there is no target, reaction
 * 0x14c mode 6 fires at the +8 point, the +0x75 flag and +0x5c timer clear and the tick hands
 * over to func_ov226_020d2930. */
typedef struct { int x, y, z; } Vec3;

extern void func_ov107_020c9264(int owner, int anim, int mode);
extern void func_ov107_020c0b90(int owner, int mode, Vec3 v, int flag);
extern void func_ov107_020c5af8(int owner, int id, int mode, void *at);
extern void func_0203c634(int *node, int slot, void *cb);
extern Vec3 data_02041dc8;
extern void func_ov226_020d2930(int *node);

void func_ov226_020d288c(int *node)
{
    int *state = (int *)node[1];

    func_ov107_020c9264(*state, state[0x1e] != 0 ? 6 : 7, 0);
    func_ov107_020c0b90(*state, 1, data_02041dc8, (unsigned char)(state[0x1e] == 0));
    func_ov107_020c5af8(*state, 0x14c, 6, (void *)state[2]);
    *(unsigned char *)((char *)state + 0x75) = 0;
    state[0x17] = 0;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), (void *)func_ov226_020d2930);
}
