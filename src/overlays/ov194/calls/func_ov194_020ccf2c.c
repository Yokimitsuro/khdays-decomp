/* Decision tick of the ov194 enemy (x3: ov194/195/196): acquires the closest target (+8, with
 * its squared distance) -- none returns; the surface distance (root minus both +0x80 radii)
 * must be inside the actor's +0x2d8 range; the +0x10 heading turns to the target's +0x190
 * from the actor's +0xb0. A running +0x44 timer requests sub-state 4. Otherwise, while the
 * +0x34 timer runs: beyond 10.0 request 4; inside 1.0 the target ahead of the actor's forward
 * (dot > 0.5) requests 0xe, else the sign of the cross product picks 0xc (left) or 0xd
 * (right); inside 3.0 request 6; further out a 1/61 roll decides an attack: a 0..1 roll of 0
 * requests 0xa and of 1 requests 0xb, each with a 1..3 repeat count in +0x48. With the +0x34
 * timer expired: inside 3.0 request 6, else arm the +0x44 timer (1 if not positive) and
 * request 4. */
typedef struct { int x, y, z; } Vec3;

extern int func_ov107_020cab14(int actor, int *distOut);
extern int FX_Sqrt(int x);
extern void VEC_Subtract(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern int func_020050b4(int x, int z);
extern void func_0203c634(int node, int slot, void *cb);
extern int func_01ff8d18(const Vec3 *v, Vec3 *out);
extern void func_0202f384(Vec3 *out, void *rotation, const Vec3 *in);
extern int VEC_DotProduct(const Vec3 *a, const Vec3 *b);
extern int func_02023eb4(int bound);
extern const Vec3 data_02042258;

void func_ov194_020ccf2c(int node)
{
    int *state = *(int **)(node + 4);
    int dist;
    Vec3 d;
    Vec3 fwd;
    int obj;
    int target;
    int roll;

    state[2] = func_ov107_020cab14(*state, &dist);
    target = state[2];
    if (target == 0) {
        return;
    }
    obj = *state;
    dist = FX_Sqrt(dist) - (*(int *)(target + 0x80) + *(int *)(obj + 0x80));
    if (dist > *(int *)(*state + 0x2d8)) {
        return;
    }
    VEC_Subtract((Vec3 *)(state[2] + 0x190), (Vec3 *)(*state + 0xb0), &d);
    state[4] = func_020050b4(d.x, d.z);
    if (state[0x11] > 0) {
        *(unsigned char *)(*state + 0x1c7) = 4;
        func_0203c634(node, *(signed char *)(node + 0x20), 0);
        return;
    }
    if (state[0xd] <= 0) {
        if (dist < 0x3000) {
            *(unsigned char *)(*state + 0x1c7) = 6;
            func_0203c634(node, *(signed char *)(node + 0x20), 0);
            return;
        }
        if (state[0x11] <= 0) {
            state[0x11] = 1;
        }
        *(unsigned char *)(*state + 0x1c7) = 4;
        func_0203c634(node, *(signed char *)(node + 0x20), 0);
        return;
    }
    if (dist > 0xa000) {
        *(unsigned char *)(*state + 0x1c7) = 4;
        func_0203c634(node, *(signed char *)(node + 0x20), 0);
        return;
    }
    if (dist < 0x1000) {
        func_01ff8d18(&d, &d);
        func_0202f384(&fwd, (void *)(*state + 0xa0), &data_02042258);
        if (VEC_DotProduct(&d, &fwd) > 0x800) {
            *(unsigned char *)(*state + 0x1c7) = 0xe;
            func_0203c634(node, *(signed char *)(node + 0x20), 0);
            return;
        }
        if ((int)(((long long)d.x * fwd.z + 0x800) >> 12) - (int)(((long long)d.z * fwd.x + 0x800) >> 12) < 0) {
            *(unsigned char *)(*state + 0x1c7) = 0xc;
            func_0203c634(node, *(signed char *)(node + 0x20), 0);
            return;
        }
        *(unsigned char *)(*state + 0x1c7) = 0xd;
        func_0203c634(node, *(signed char *)(node + 0x20), 0);
        return;
    }
    if (dist < 0x3000) {
        *(unsigned char *)(*state + 0x1c7) = 6;
        func_0203c634(node, *(signed char *)(node + 0x20), 0);
        return;
    }
    if (func_02023eb4(0x3d) + (dist - dist) != 0) {
        return;
    }
    roll = func_02023eb4(2) + (dist - dist);
    if (roll == 0) {
        state[0x12] = func_02023eb4(3) + 1;
        *(unsigned char *)(*state + 0x1c7) = 0xa;
        func_0203c634(node, *(signed char *)(node + 0x20), 0);
        return;
    }
    if (roll != 1) {
        return;
    }
    state[0x12] = func_02023eb4(3) + 1;
    *(unsigned char *)(*state + 0x1c7) = 0xb;
    func_0203c634(node, *(signed char *)(node + 0x20), 0);
}
