/* Recoil entry of the ov260 actor: pose 0x1b plays, its +0x428 part takes motion 0x10, the +0x2c
 * push is normalised and scaled to 1/16, +0x30 = -0x3d2b and the node moves on to 020cf90c. */
typedef struct { int x, y, z; } Vec3;

extern void func_ov107_020c9264(int actor, int pose, int loop);
extern int func_ov107_020c9ee8(int part, int motion, int mode);
extern int func_01ff8d18(Vec3 *v, Vec3 *out);
extern void func_01ffa724(int scale, Vec3 *v, Vec3 *d);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov260_020cf90c(void);

void func_ov260_020cf89c(int *node)
{
    int *state = (int *)node[1];

    func_ov107_020c9264(*state, 0x1b, 0);
    func_ov107_020c9ee8(*(int *)(*state + 0x428), 0x10, 0);
    func_01ff8d18((Vec3 *)(state + 0xb), (Vec3 *)(state + 0xb));
    func_01ffa724(0x100, (Vec3 *)(state + 0xb), (Vec3 *)(state + 0xb));
    state[0xc] = -0x3d2b;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov260_020cf90c);
}
