/* Target acquisition of the ov258 actor: the nearest target (020cab14) becomes the actor's +0x454;
 * without one the next move is 2 and 0 is returned. Otherwise the flat direction from the +0xc point
 * to the target's +0x190 point is normalised into +0x10, +0x40 is the gap left between both +0x80
 * radii (at least 0) and, when `face` is set, +0x2c turns toward it. Returns 1. */
typedef struct { int x, y, z; } Vec3;

extern int func_ov107_020cab14(int actor, int kind);
extern void VEC_Subtract(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern int func_01ff8d18(const Vec3 *v, Vec3 *out);
extern int func_020050b4(int x, int z);

int func_ov258_020cd028(int *node, int face)
{
    int *state = (int *)node[1];
    Vec3 to;
    Vec3 from;

    from = *(Vec3 *)state[3];
    *(int *)(*state + 0x454) = func_ov107_020cab14(*state, 0);
    if (*(int *)(*state + 0x454) == 0) {
        *(signed char *)(*state + 0x1c7) = 2;
        return 0;
    }
    to = *(Vec3 *)(*(int *)(*state + 0x454) + 0x190);
    from.y = 0;
    to.y = 0;
    VEC_Subtract(&to, &from, (Vec3 *)(state + 4));
    state[0x10] = func_01ff8d18((Vec3 *)(state + 4), (Vec3 *)(state + 4));
    state[0x10] -= *(int *)(*(int *)(*state + 0x454) + 0x80) + *(int *)(*state + 0x80);
    if (state[0x10] < 0) {
        state[0x10] = 0;
    }
    if (face != 0) {
        state[0xb] = func_020050b4(state[4], state[6]);
    }
    return 1;
}
