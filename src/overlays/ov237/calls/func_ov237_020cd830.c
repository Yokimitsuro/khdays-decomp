/* Target gap helper of the ov237 enemy: the nearest target (020cab14) is kept in the owner's +0x3dc;
 * without one sub-state 2 is requested and -1 returned. Otherwise the gap between the target's
 * +0x190 point and the owner's +0xb0 point less both +0x80 radii (never negative) is returned and
 * the heading to it (020050b4) is stored in +0x14. */
typedef struct { int x, y, z; } VecFx32;

extern int func_ov107_020cab14(int a, int b);
extern void VEC_Subtract(VecFx32 *a, VecFx32 *b, VecFx32 *out);
extern int func_01ff8d18(VecFx32 *src, VecFx32 *dst);
extern int func_020050b4(int x, int z);

int func_ov237_020cd830(int this_) {
    int *state = (int *)(*(int *)(this_ + 4));
    int t = func_ov107_020cab14(*state, 0);
    VecFx32 delta;
    int dist, radiusSum;

    *(int *)(*state + 0x3dc) = t;
    if (*(int *)(*state + 0x3dc) == 0) {
        *(signed char *)(*state + 0x1c7) = 2;
        return -1;
    }
    VEC_Subtract((VecFx32 *)(*(int *)(*state + 0x3dc) + 0x190),
                 (VecFx32 *)(*state + 0xb0), &delta);
    dist = func_01ff8d18(&delta, &delta);
    radiusSum = *(int *)(*(int *)(*state + 0x3dc) + 0x80) + *(int *)(*state + 0x80);
    dist -= radiusSum;
    if (dist < 0) dist = 0;
    *(int *)((int)state + 0x14) = func_020050b4(delta.x, delta.z);
    return dist;
}
