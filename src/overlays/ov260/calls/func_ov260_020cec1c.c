/* Hover entry of the ov260 actor: pose 0xf plays, its +0x428 part takes motion 7, the +0x2c push
 * becomes (0, 0.25, 0) and is copied to +0x20, effect 0x1f starts at the +0x10 point (020cd148) and
 * the node moves on to 020cec98. */
typedef struct { int x, y, z; } Vec3;

extern void func_ov107_020c9264(int actor, int pose, int loop);
extern int func_ov107_020c9ee8(int part, int motion, int mode);
extern void func_ov260_020cd148(int owner, int mode, int arg);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov260_020cec98(void);

void func_ov260_020cec1c(int *node)
{
    int *state = (int *)node[1];

    func_ov107_020c9264(*state, 0xf, 0);
    func_ov107_020c9ee8(*(int *)(*state + 0x428), 7, 0);
    state[0xb] = 0;
    state[0xc] = 0x400;
    state[0xd] = 0;
    *(Vec3 *)(state + 8) = *(Vec3 *)(state + 0xb);
    func_ov260_020cd148(*state, 0x1f, state[4]);
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov260_020cec98);
}
