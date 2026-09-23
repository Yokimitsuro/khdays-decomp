/* Shoot entry of the ov259 actor: the +0x68 timer and +0xac cue flags clear, +0x94 = 180; with a
 * +0xc aim target it faces it (+0x78 / +0x7c heading); +0x58 is set, pose 0xc plays on the actor
 * and its partner (020cd524), the shot is armed (020cd628: pose 0xf after 0x2a8) and the node moves
 * on to 020ce944. */
typedef unsigned char u8;
typedef struct { int x, y, z; } Vec3;

extern void VEC_Subtract(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern int func_020050b4(int x, int y);
extern void func_ov107_020c9264(int actor, int pose, int loop);
extern void func_ov259_020cd524(int *node, int pose, int mode);
extern void func_ov259_020cd628(int *node, int pose, int delay);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov259_020ce944(void);

void func_ov259_020ce898(int *node)
{
    int *state = (int *)node[1];
    Vec3 d;

    state[0x1a] = 0;
    *((u8 *)state + 0xac) = 0;
    state[0x25] = 0xb4;
    if (state[3] != 0) {
        VEC_Subtract((Vec3 *)(state[3] + 0x190), (Vec3 *)(*state + 0xb0), &d);
        state[0x1e] = state[0x1f] = func_020050b4(d.x, d.z);
    }
    state[0x16] = 1;
    func_ov107_020c9264(*state, 0xc, 0);
    func_ov259_020cd524(node, 0xc, 0);
    func_ov259_020cd628(node, 0xf, 0x2a8);
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov259_020ce944);
}
