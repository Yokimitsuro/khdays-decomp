/* Guard entry of the ov146 actor: pose 2 plays; with a partner guard (+0x58) the partner plays it too
 * and, with a pending move (+0x5c), the partner moves to the +0x1c point (020ce2d0) and the +0x3bc
 * effect stops. With a target (+0x54) both headings turn to it; +0x48 clears and the node moves on to
 * 020cdd74. */
typedef struct { int x, y, z; } Vec3;

extern void func_ov107_020c9264(int actor, int pose, int loop);
extern int func_ov146_020ce2d0(int partner, Vec3 at);
extern int func_ov146_020cee14(int param_1, int param_2);
extern void VEC_Subtract(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern int func_020050b4(int x, int z);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov146_020cdd74(void);

void func_ov146_020cdcb4(int *node)
{
    int *state = (int *)node[1];
    Vec3 d;

    func_ov107_020c9264(*state, 2, 0);
    if (state[0x16] != 0) {
        func_ov107_020c9264(state[2], 2, 0);
        if (state[0x17] != 0) {
            func_ov146_020ce2d0(state[2], *(Vec3 *)(state + 7));
            func_ov146_020cee14(*(int *)(*state + 0x3bc), 0);
        }
    }
    if (state[0x15] != 0) {
        VEC_Subtract((Vec3 *)(state[0x15] + 0x190), (Vec3 *)(*state + 0xb0), &d);
        state[0xa] = state[0xb] = func_020050b4(d.x, d.z);
    }
    state[0x12] = 0;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov146_020cdd74);
}
