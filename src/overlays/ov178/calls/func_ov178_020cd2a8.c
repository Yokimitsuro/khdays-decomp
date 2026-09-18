/* Orbit tick of the ov178 enemy (x3: ov178/179/180): acquires the target -- none returns at
 * once. Beyond the actor's +0x2d8 range the step is zeroed; within it the step is the tangent
 * (up x direction, normalised) scaled by the +0x4c speed times the +0x60 orbit sense, the
 * +0x50 bob phase advances by 30x the node's +0x2c speed (wrapping at +0x54 seconds, re-rolled
 * to 40 + rand(1)), and the hover height eases 1/10 of the way to the target's +0x78 + 0x1c00
 * (lowered by the excess of +0x44 over 0x1c00, or the +0x18 override) plus half a sine of the
 * phase, scaled by 0x800. Closer than 0x2000 the flattened direction pushes 0x100 back, beyond
 * 0x3000 it pulls 0x100 in. Then: no free target (020ccb8c) or a target beyond half the range
 * ends in sub-state 4; inside the range the +0x5c timer runs down and at zero a roll picks:
 * 1-in-120 (or a target beyond 0x4000) -> 4, 1-in-20 -> 5, else with a free target 70 % -> 8 and
 * 30 % -> 9. */
typedef struct { int x, y, z; } Vec3;

extern int func_ov107_020cab14(int obj, int b);
extern int func_ov178_020ccaf4(int node, Vec3 *out);
extern void VEC_CrossProduct(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern int func_01ff8d18(const Vec3 *v, Vec3 *out);
extern void func_01ffa724(int scale, const Vec3 *v, Vec3 *out);
extern int func_02023eb4(int bound);
extern int func_02020400(int a, int b);
extern void VEC_Add(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern void func_0203c634(int node, int slot, void *cb);
extern int func_ov178_020ccb8c(int node);
extern short data_0203d210[];
extern Vec3 data_02041dc8;
extern int data_02042264;

void func_ov178_020cd2a8(int node)
{
    int *state = *(int **)(node + 4);
    Vec3 dir;
    Vec3 side;
    Vec3 pull;
    int dist;
    int h;
    int t;
    int idx;
    int s;
    int diff;
    int obj;
    int mode;

    state[3] = func_ov107_020cab14(*state, 0);
    if (state[3] == 0) {
        return;
    }
    dist = func_ov178_020ccaf4(node, &dir);
    if (dist > *(int *)(*state + 0x2d8)) {
        *(Vec3 *)(state + 8) = data_02041dc8;
    } else {
        VEC_CrossProduct((Vec3 *)&data_02042264, &dir, &side);
        func_01ff8d18(&side, &side);
        func_01ffa724((int)(((long long)(state[0x13] * state[0x18]) * 0x2000 + 0x800) >> 12), &side, &side);
        state[8] = side.x;
        state[9] = 0;
        state[10] = side.z;
        state[0x14] += *(int *)(*(int *)node + 0x2c) * 30;
        if (state[0x14] >= state[0x15] << 12) {
            state[0x14] = 0;
            state[0x15] = func_02023eb4(1) + 0x28;
        }
        if (state[0x22] == 0) {
            h = *(int *)(state[3] + 0x78) + 0x1c00;
            if (state[0x11] > 0x1c00) {
                h -= state[0x11] - 0x1c00;
            }
        } else {
            h = state[6];
        }
        t = func_02020400((int)(((long long)state[0x14] * 0x6488 + 0x800) >> 12), state[0x15]);
        idx = (unsigned short)((0x28BE60DB9391LL * t + 0x80000000000LL) >> 44);          /* FX_RAD_TO_IDX */
        s = data_0203d210[(idx >> 4) << 1] / 2;                                            /* FX_SinIdx / 2 */
        diff = h + (int)(((long long)s * 0x800 + 0x800) >> 12) - *(int *)(state[2] + 4);
        state[9] += (int)(((long long)(diff / 10) * 0x2000 + 0x800) >> 12);
    }
    if (dist < 0x2000) {
        dir.y = 0;
        func_01ff8d18(&dir, &dir);
        func_01ffa724(-0x100, &dir, &pull);
        VEC_Add((Vec3 *)(state + 8), &pull, (Vec3 *)(state + 8));
    } else if (dist > 0x3000) {
        dir.y = 0;
        func_01ff8d18(&dir, &dir);
        func_01ffa724(0x100, &dir, &pull);
        VEC_Add((Vec3 *)(state + 8), &pull, (Vec3 *)(state + 8));
    }
    if (func_ov178_020ccb8c(node) == 0) {
        *(unsigned char *)(*state + 0x1c7) = 4;
        func_0203c634(node, *(signed char *)(node + 0x20), 0);
        return;
    }
    obj = *state;
    if (dist > *(int *)(obj + 0x2d8) / 2) {
        *(unsigned char *)(obj + 0x1c7) = 4;
        func_0203c634(node, *(signed char *)(node + 0x20), 0);
        return;
    }
    if (dist >= *(int *)(obj + 0x2d8)) {
        return;
    }
    state[0x17] -= *(int *)(*(int *)node + 0x2c);
    if (state[0x17] > 0) {
        return;
    }
    state[0x17] = 0;
    if (func_02023eb4(0x78) == 0 || dist > 0x4000) {
        *(unsigned char *)(*state + 0x1c7) = 4;
        func_0203c634(node, *(signed char *)(node + 0x20), 0);
        return;
    }
    if (func_02023eb4(0x14) == 0) {
        *(unsigned char *)(*state + 0x1c7) = 5;
        func_0203c634(node, *(signed char *)(node + 0x20), 0);
        return;
    }
    if (func_ov178_020ccb8c(node) == 0) {
        return;
    }
    mode = ((unsigned int)func_02023eb4(100) < 0x46) ? 8 : 9;
    *(unsigned char *)(*state + 0x1c7) = mode;
    func_0203c634(node, *(signed char *)(node + 0x20), 0);
}
