/* Target check of the ov252 actor: the nearest target (020cab14) goes to +0x4e4; without one the next
 * move is 2 and 0 is returned. Otherwise returns the ground-plane gap between the two bodies (distance
 * minus both +0x80 radii, at least 0); with `face` the +0x58 heading turns toward the target, and
 * `delta` (when given) receives the ground-plane offset to it. */
typedef unsigned char u8;
typedef struct { int x, y, z; } Vec3;

extern int func_ov107_020cab14(int actor, int *distOut);
extern void VEC_Subtract(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern int func_01ff8d18(const Vec3 *v, Vec3 *out);
extern int func_020050b4(int x, int z);

int func_ov252_020cdfe8(int *node, Vec3 *delta, int face)
{
    int *state = (int *)node[1];
    Vec3 d;
    int gap;

    *(int *)(*state + 0x4e4) = func_ov107_020cab14(*state, 0);
    if (*(int *)(*state + 0x4e4) == 0) {
        *(u8 *)(*state + 0x1c7) = 2;
        return 0;
    }
    VEC_Subtract((Vec3 *)(*(int *)(*state + 0x4e4) + 0x190), (Vec3 *)(*state + 0xb0), &d);
    d.y = 0;
    gap = func_01ff8d18(&d, &d);
    gap -= (*(int *)(*(int *)(*state + 0x4e4) + 0x80) + *(int *)(*state + 0x80));
    if (gap < 0) {
        gap = 0;
    }
    if (face != 0) {
        state[0x16] = func_020050b4(d.x, d.z);
    }
    if (delta != 0) {
        *delta = d;
    }
    return gap;
}
