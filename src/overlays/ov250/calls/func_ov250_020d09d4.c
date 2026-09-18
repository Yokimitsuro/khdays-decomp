/* Circle tick of the ov250 enemy (and its byte-identical twin): the +0x20 step is 30 x dt / 20;
 * the closest target goes to +0x10 (none returns) and its surface distance (root minus both
 * +0x80 radii) must be inside the actor's +0x2d8 range. The offset from the +4 position to the
 * target's +0x190 gives a 0.03125 retreat (reversed, normalised) and the +0x18 heading; the
 * +0x54 velocity is the flattened offset's side vector (world Y x offset) normalised and scaled
 * by the +0x84 sense x 0x80. A 1/257 roll requests sub-state 5; otherwise beyond 7.0 a second
 * 1/257 roll (or an expired +0x74 timer) requests sub-state 4, and inside 7.0 an expired timer
 * requests 9 (beyond 3.0), 8 (beyond 1.0) or 7. */
typedef struct { int x, y, z; } Vec3;

extern int func_ov107_020cab14(int actor, int *distOut);
extern int FX_Sqrt(int x);
extern void VEC_Subtract(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern void func_01ffa724(int scale, const Vec3 *v, Vec3 *out);
extern int func_01ff8d18(const Vec3 *v, Vec3 *out);
extern int func_020050b4(int x, int z);
extern void VEC_CrossProduct(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern void VEC_Add(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern int func_02023eb4(int bound);
extern void func_0203c634(int node, int slot, void *cb);
extern const Vec3 data_02042264;

void func_ov250_020d09d4(int node)
{
    int *state = *(int **)(node + 4);
    int dist;
    Vec3 d;
    Vec3 back;
    int obj;
    int target;

    state[8] = *(int *)(*(int *)node + 0x2c) * 30 / 20;
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
    func_01ffa724(-0x1000, &d, &back);
    func_01ff8d18(&back, &back);
    func_01ffa724(0x80, &back, &back);
    state[6] = func_020050b4(d.x, d.z);
    d.y = 0;
    func_01ff8d18(&d, &d);
    VEC_CrossProduct(&d, &data_02042264, (Vec3 *)(state + 0x15));
    func_01ff8d18((Vec3 *)(state + 0x15), (Vec3 *)(state + 0x15));
    func_01ffa724(state[0x21] << 7, (Vec3 *)(state + 0x15), (Vec3 *)(state + 0x15));
    if (func_02023eb4(0x101) + (dist - dist) == 0) {
        *(unsigned char *)(*state + 0x1c7) = 5;
        func_0203c634(node, *(signed char *)(node + 0x20), 0);
        return;
    }
    if (dist > 0x7000) {
        if (func_02023eb4(0x101) + (dist - dist) != 0) {
            if (state[0x1d] > 0) {
                return;
            }
        }
        *(unsigned char *)(*state + 0x1c7) = 4;
        func_0203c634(node, *(signed char *)(node + 0x20), 0);
        return;
    }
    if (state[0x1d] > 0) {
        return;
    }
    if (dist > 0x3000) {
        *(unsigned char *)(*state + 0x1c7) = 9;
        func_0203c634(node, *(signed char *)(node + 0x20), 0);
        return;
    }
    if (dist > 0x1000) {
        *(unsigned char *)(*state + 0x1c7) = 8;
        func_0203c634(node, *(signed char *)(node + 0x20), 0);
        return;
    }
    *(unsigned char *)(*state + 0x1c7) = 7;
    func_0203c634(node, *(signed char *)(node + 0x20), 0);
}
