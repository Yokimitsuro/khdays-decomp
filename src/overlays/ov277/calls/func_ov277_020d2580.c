/* Circle decision tick of the ov114 enemy: the closest target goes to +0x10 (none returns) and
 * its surface distance (root minus both +0x80 radii) must be inside the actor's +0x2d8 range.
 * The offset from the +4 position to the target's +0x190 gives the +0x18 heading; the +0x50
 * velocity is the flattened offset's side vector (offset x world Y) normalised and scaled by
 * the +0x48 sense x 0x40. A 1/257 roll requests sub-state 6; otherwise beyond 4.0 a second
 * 1/257 roll (or an expired +0x4c timer) requests sub-state 4, and inside 4.0 an expired timer
 * requests 0xa (beyond 0.5) or 9. */
typedef struct { int x, y, z; } Vec3;

extern int func_ov107_020cab14(int actor, int *distOut);
extern int FX_Sqrt(int x);
extern void VEC_Subtract(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern int func_020050b4(int x, int z);
extern int func_01ff8d18(const Vec3 *v, Vec3 *out);
extern void VEC_CrossProduct(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern void func_01ffa724(int scale, const Vec3 *v, Vec3 *out);
extern int func_02023eb4(int bound);
extern void func_0203c634(int node, int slot, void *cb);
extern const Vec3 data_02042264;

void func_ov277_020d2580(int node)
{
    int *state = *(int **)(node + 4);
    int dist;
    Vec3 d;
    int obj;
    int target;

    state[4] = func_ov107_020cab14(*state, &dist);
    target = state[4];
    if (target == 0) {
        return;
    }
    obj = *state;
    dist = FX_Sqrt(dist) - (*(int *)(target + 0x80) + *(int *)(obj + 0x80));
    if (dist > *(int *)(*state + 0x2d8)) {
        return;
    }
    VEC_Subtract((Vec3 *)(state[4] + 0x190), (Vec3 *)state[1], &d);
    state[6] = func_020050b4(d.x, d.z);
    d.y = 0;
    func_01ff8d18(&d, &d);
    VEC_CrossProduct(&d, &data_02042264, (Vec3 *)(state + 0x14));
    func_01ffa724(*(signed char *)((char *)state + 0x48) << 6, (Vec3 *)(state + 0x14), (Vec3 *)(state + 0x14));
    if (func_02023eb4(0x101) + (dist - dist) == 0) {
        *(unsigned char *)(*state + 0x1c7) = 6;
        func_0203c634(node, *(signed char *)(node + 0x20), 0);
        return;
    }
    if (dist > 0x4000) {
        if (func_02023eb4(0x101) + (dist - dist) != 0) {
            if (state[0x13] > 0) {
                return;
            }
        }
        *(unsigned char *)(*state + 0x1c7) = 4;
        func_0203c634(node, *(signed char *)(node + 0x20), 0);
        return;
    }
    if (state[0x13] > 0) {
        return;
    }
    if (dist > 0x800) {
        *(unsigned char *)(*state + 0x1c7) = 0xa;
        func_0203c634(node, *(signed char *)(node + 0x20), 0);
        return;
    }
    *(unsigned char *)(*state + 0x1c7) = 9;
    func_0203c634(node, *(signed char *)(node + 0x20), 0);
}
