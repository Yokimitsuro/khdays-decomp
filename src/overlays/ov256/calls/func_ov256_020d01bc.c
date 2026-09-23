/* Wander tick of an ov256 part: the +0x4c timer accumulates the frame rate and the +0x10 velocity is
 * the +0x450 owner's +0x2c vector turned by its heading (020cd054). After 5.0 of wandering, once the
 * partner holds no queued move, pose 0x1d plays, the +0x450 part takes motion 0xe and the node moves
 * on to 020d02a0; before that each idle partner restarts pose 0x1c / motion 0xd. */
typedef unsigned char u8;
typedef struct { int x, y, z; } Vec3;

extern void func_ov256_020cd054(int *out, int param_2, int *vec);
extern void func_ov107_020c9264(int actor, int pose, int loop);
extern int func_ov107_020c9ee8(int part, int motion, int mode);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov256_020d02a0(void);

void func_ov256_020d01bc(int *node)
{
    int *state = (int *)node[1];
    Vec3 v;

    state[0x13] += *(int *)(node[0] + 0x2c);
    func_ov256_020cd054((int *)&v, (int)node, (int *)(*(int *)(*state + 0x450) + 0x2c));
    *(Vec3 *)(state + 4) = v;
    if (state[0x13] >= 0x5000 && *(u8 *)(state[1] + 0xad) == 0) {
        func_ov107_020c9264(*state, 0x1d, 0);
        func_ov107_020c9ee8(*(int *)(*state + 0x450), 0xe, 0);
        func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov256_020d02a0);
        return;
    }
    if (*(u8 *)(state[1] + 0xad) != 0) {
        return;
    }
    func_ov107_020c9264(*state, 0x1c, 0);
    func_ov107_020c9ee8(*(int *)(*state + 0x450), 0xd, 0);
}
