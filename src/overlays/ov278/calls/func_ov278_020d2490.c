/* Approach tick: refreshes the +4 target (none: pose request 9), counts the +0x3c timer down
 * (expired: request 0xb), heads for the target (+0x30 = atan2 of the offset, +8 velocity =
 * 0.25 along it) and, once the surface gap (root of the squared distance minus both +0x80
 * radii, measured twice) closes under 2.0, rolls a strafe direction into +0x34, clears +0x38
 * and moves the node to 020d2628. */
typedef struct { int x, y, z; } Vec3;

extern int func_ov107_020cab14(int actor, int *distOut);
extern void func_0203c634(int *node, int slot, void *cb);
extern void VEC_Subtract(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern int func_01ff8d18(const Vec3 *v, Vec3 *out);
extern int func_020050b4(int x, int z);
extern void func_01ffa724(int scale, const Vec3 *v, Vec3 *out);
extern int FX_Sqrt(int x);
extern int func_02023eb4();  /* K&R decl: needed for the rand `+ (v - v)` copy artifact */
extern void func_ov278_020d25dc(void);

void func_ov278_020d2490(int *node) {
    int *state = (int *)node[1];
    Vec3 d;
    int dist;
    int v;

    state[1] = func_ov107_020cab14(*state, &dist);
    if (state[1] == 0) {
        *(unsigned char *)(*state + 0x1c7) = 9;
        func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
        return;
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
    state[0xc] = func_020050b4(d.x, d.z);
    func_01ffa724(0x400, &d, (Vec3 *)(state + 2));
    {
        int actor = state[0];
        int target = state[1];
        dist = FX_Sqrt(dist) - (*(int *)(target + 0x80) + *(int *)(actor + 0x80));
    }
    if (dist >= 0x2000) {
        return;
    }
    state[0xd] = (func_02023eb4(2) + (v - v)) != 0 ? -1 : 1;
    state[0xe] = 0;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov278_020d25dc);
}
