/* Bounce entry of the ov283 actor: the +0x10 velocity rests, +0x54 clears, sound 0x173/0xc plays at
 * the +8 point (020cc92c), pose 0xd plays, effects 2 and 3 fire there and the node moves on to
 * 020cdeac. */
typedef struct { int x, y, z; } Vec3;

extern void func_ov283_020cc92c(int actor, int bank, int variant, int at);
extern void func_ov107_020c9264(int actor, int pose, int loop);
extern void func_ov107_020c0b90(int owner, int mode, Vec3 at, int flag);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov283_020cdeac(void);
extern const Vec3 data_02041dc8;

void func_ov283_020cddec(int *node)
{
    int *state = (int *)node[1];

    *(Vec3 *)(state + 4) = data_02041dc8;
    state[0x15] = 0;
    func_ov283_020cc92c(*state, 0x173, 0xc, state[2]);
    func_ov107_020c9264(*state, 0xd, 0);
    func_ov107_020c0b90(*state, 2, *(Vec3 *)state[2], 0);
    func_ov107_020c0b90(*state, 3, *(Vec3 *)state[2], 0);
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov283_020cdeac);
}
