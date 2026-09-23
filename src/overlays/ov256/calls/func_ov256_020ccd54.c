/* Target pick of the ov256 actor: the nearest live entity (020cab14) becomes the +0x430 target;
 * without one the next move is the +0x74 mode + 2 and 0 is returned. Otherwise +0x34 is the unit
 * direction from the +0xb0 anchor to the target's +0x190 point, +0x58 the gap (distance minus both
 * +0x80 radii, at least 0), +0x44 the heading, and 1 is returned. */
typedef struct { int x, y, z; } Vec3;

extern int func_ov107_020cab14(int obj, int kind);
extern void VEC_Subtract(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern int func_01ff8d18(Vec3 *v, Vec3 *out);
extern int func_020050b4(int x, int y);

int func_ov256_020ccd54(int *node)
{
    int *state = (int *)node[1];

    *(int *)(*state + 0x430) = func_ov107_020cab14(*state, 0);
    if (*(int *)(*state + 0x430) == 0) {
        *(signed char *)(*state + 0x1c7) = state[0x1d] + 2;
        return 0;
    }
    VEC_Subtract((Vec3 *)(*(int *)(*state + 0x430) + 0x190), (Vec3 *)(*state + 0xb0), (Vec3 *)(state + 0xd));
    state[0x16] = func_01ff8d18((Vec3 *)(state + 0xd), (Vec3 *)(state + 0xd));
    if ((state[0x16] -= *(int *)(*(int *)(*state + 0x430) + 0x80) + *(int *)(*state + 0x80)) < 0) {
        state[0x16] = 0;
    }
    state[0x11] = func_020050b4(state[0xd], state[0xf]);
    return 1;
}
