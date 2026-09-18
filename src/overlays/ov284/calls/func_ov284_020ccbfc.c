/* Idle tick of the ov284 enemy: re-acquires the target into +0xc and aims the +0x14 yaw at its
 * +0x190 point from the +4 position; the surface distance (root minus both +0x80 radii) is
 * measured and, once the +0x20 timer is spent, sub-state 7 is requested and the state ends. */
typedef struct { int x, y, z; } Vec3;
extern int func_ov107_020cab14(int actor, int *distOut);
extern void VEC_Subtract(const void *a, const void *b, Vec3 *out);
extern int func_020050b4(int x, int z);
extern int FX_Sqrt(int x);
extern void func_0203c634(int *node, int slot, void *cb);

void func_ov284_020ccbfc(int *node)
{
    int *state = (int *)node[1];
    int dist;
    Vec3 d;
    int target;
    int actor;

    state[3] = func_ov107_020cab14(*state, &dist);
    if (state[3] != 0) {
        VEC_Subtract((void *)(state[3] + 0x190), (void *)state[1], &d);
        state[5] = func_020050b4(d.x, d.z);
    }
    target = state[3];
    actor = *state;
    dist = FX_Sqrt(dist) - *(int *)(target + 0x80) - *(int *)(actor + 0x80);
    if (state[8] > 0) {
        return;
    }
    *(unsigned char *)(*state + 0x1c7) = 7;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
}
