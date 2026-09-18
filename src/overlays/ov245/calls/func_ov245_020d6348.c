/* func_ov245_020d6348 -- approach tick: refreshes the state's +8 target (020cab14, mode 0) and
 * stops without one; measures the flat distance from the actor's +0xb0 pose to the target's
 * +0x190 minus both +0x80 radii and gives up beyond the actor's +0x2d8 reach; otherwise aims
 * +0x14 at the target (atan2), requests sub-state 4 beyond 3.0, or counts the +0x40 timer down
 * and then requests 6 (within 0.5) or 7, releasing the node's slot either way. */
typedef struct { int x, y, z; } Vec3;

extern int func_ov107_020cab14(int actor, int mode);
extern void VEC_Subtract(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern int func_01ff8d18(const Vec3 *v, Vec3 *out);
extern int func_020050b4(int x, int z);
extern void func_0203c634(int *node, int slot, void *cb);

void func_ov245_020d6348(int *node) {
    int *state = (int *)node[1];
    Vec3 d;
    int gap;
    int target;
    int actor;

    state[2] = func_ov107_020cab14(*state, 0);
    if (state[2] == 0) {
        return;
    }
    VEC_Subtract((Vec3 *)(state[2] + 0x190), (Vec3 *)(*state + 0xb0), &d);
    target = state[2];
    actor = *state;
    gap = func_01ff8d18(&d, &d) - *(int *)(target + 0x80) - *(int *)(actor + 0x80);
    if (gap > *(int *)(*state + 0x2d8)) {
        return;
    }
    state[5] = func_020050b4(d.x, d.z);
    if (gap > 0x3000) {
        *(unsigned char *)(*state + 0x1c7) = 4;
        func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
        return;
    }
    state[0x10] -= *(int *)(*node + 0x2c);
    if (state[0x10] > 0) {
        return;
    }
    if (gap <= 0x800) {
        *(unsigned char *)(*state + 0x1c7) = 6;
    } else {
        *(unsigned char *)(*state + 0x1c7) = 7;
    }
    func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
}
