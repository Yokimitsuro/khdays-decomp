/* Strafe tick: refreshes the +4 target (none: pose request 9) and measures the surface gap
 * (root of the squared distance minus both +0x80 radii). Every 2.0 of the +0x18 timer the +0x34
 * strafe direction is re-rolled and the +0x38 speed halved; the +0x3c timer counts down to pose
 * request 0xb. The +8 velocity is the offset's side vector (world Y x offset) scaled by the
 * direction x speed (the +0x30 heading = atan2 of the offset), the speed eases a fiftieth
 * towards 0x500 and the velocity drops 0x300 in y. Beyond a 4.0 gap the node moves to
 * 020d24dc; inside 2.0 the velocity is -0x100 along the offset instead. */
typedef struct { int x, y, z; } Vec3;

extern int func_ov107_020cab14(int actor, int *distOut);
extern void func_0203c634(int *node, int slot, void *cb);
extern int FX_Sqrt(int x);
extern int func_02023eb4();  /* K&R decl: needed for the rand `+ (v - v)` copy artifact */
extern void VEC_Subtract(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern int func_01ff8d18(const Vec3 *v, Vec3 *out);
extern void VEC_CrossProduct(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern int func_020050b4(int x, int z);
extern void func_01ffa724(int scale, const Vec3 *v, Vec3 *out);
extern const Vec3 data_02042264;
extern void func_ov278_020d2490(void);

void func_ov278_020d25dc(int *node) {
    int *state = (int *)node[1];
    int dist;
    Vec3 d;
    Vec3 side;
    int actor;
    int target;
    int v;

    target = state[1] = func_ov107_020cab14(*state, &dist);
    if (target == 0) {
        *(unsigned char *)(*state + 0x1c7) = 9;
        func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
        return;
    }
    actor = *state;
    dist = FX_Sqrt(dist) - (*(int *)(target + 0x80) + *(int *)(actor + 0x80));
    state[6] += *(int *)(*node + 0x2c);
    if (state[6] >= 0x2000) {
        state[0xd] = (func_02023eb4(2) + (v - v)) != 0 ? -1 : 1;
        state[6] = 0;
        state[0xe] = state[0xe] / 2;
    }
    state[0xf] -= *(int *)(*node + 0x2c);
    if (state[0xf] < 0) {
        *(unsigned char *)(*state + 0x1c7) = 0xb;
        func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
        return;
    }
    VEC_Subtract((Vec3 *)(state[1] + 0x74), (Vec3 *)(*state + 0x74), &d);
    {
        int actor = state[0];
        int target = state[1];
        dist = func_01ff8d18(&d, &d) - (*(int *)(target + 0x80) + *(int *)(actor + 0x80));
    }
    VEC_CrossProduct(&data_02042264, &d, &side);
    state[0xc] = func_020050b4(d.x, d.z);
    func_01ffa724(state[0xe] * state[0xd], &side, (Vec3 *)(state + 2));
    state[0xe] += (0x500 - state[0xe]) / 50;
    state[3] -= 0x300;
    if (dist > 0x4000) {
        func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov278_020d2490);
        return;
    }
    if (dist >= 0x2000) {
        return;
    }
    func_01ffa724(-0x100, &d, (Vec3 *)(state + 2));
}
