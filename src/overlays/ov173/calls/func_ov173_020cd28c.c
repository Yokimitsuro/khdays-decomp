/* Orbit tick of the ov173 enemy (x3: ov173/167/168), variant of the matched ov178 sibling:
 * acquires the target (+0xc) -- none returns at once; beyond the +0x2d8 range the +0x20 velocity
 * is zeroed, otherwise it circles the target sideways (cross product of up and the direction,
 * scaled by the +0x4c/+0x60 speed product), bobs in height on a sine of the +0x50 phase over the
 * +0x54 period (re-armed at random + 0x78), and is pulled in/out by 0x100 below 0x2000 / above
 * 0x3000. Past half the +0x2d8 range sub-state 4 is requested; inside it the +0x5c timer counts
 * down and then rolls sub-state 4 (1/120 or too far) or 5 (1/20). */
typedef struct { int x, y, z; } Vec3;

extern int func_ov107_020cab14(int obj, int b);
extern int func_ov173_020ccad4(int node, Vec3 *out);
extern void VEC_CrossProduct(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern int func_01ff8d18(const Vec3 *v, Vec3 *out);
extern void func_01ffa724(int scale, const Vec3 *v, Vec3 *out);
extern int func_02023eb4(int bound);
extern int func_02020400(int a, int b);
extern void VEC_Add(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern void func_0203c634(int node, int slot, void *cb);
extern short data_0203d210[];
extern Vec3 data_02041dc8;
extern int data_02042264;

void func_ov173_020cd28c(int node)
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

    state[3] = func_ov107_020cab14(*state, 0);
    if (state[3] == 0) {
        return;
    }
    dist = func_ov173_020ccad4(node, &dir);
    if (dist > *(int *)(*state + 0x2d8)) {
        *(Vec3 *)(state + 8) = data_02041dc8;
    } else {
        VEC_CrossProduct((Vec3 *)&data_02042264, &dir, &side);
        func_01ff8d18(&side, &side);
        func_01ffa724((int)(((long long)(state[0x13] * state[0x18]) * 0x3000 + 0x800) >> 12), &side, &side);
        state[8] = side.x;
        state[9] = 0;
        state[10] = side.z;
        state[0x14] += *(int *)(*(int *)node + 0x2c) * 30;
        if (state[0x14] >= state[0x15] << 12) {
            state[0x14] = 0;
            state[0x15] = func_02023eb4(0x15) + 0x14;
        }
        if (state[0x22] == 0) {
            h = *(int *)(state[3] + 0x78) + 0x1800;
            if (state[0x11] > 0x1800) {
                h -= state[0x11] - 0x1800;
            }
        } else {
            h = state[6];
        }
        t = func_02020400((int)(((long long)state[0x14] * 0x6488 + 0x800) >> 12), state[0x15]);
        idx = (unsigned short)((0x28BE60DB9391LL * t + 0x80000000000LL) >> 44);          /* FX_RAD_TO_IDX */
        s = data_0203d210[(idx >> 4) << 1] > 0 ? 0x1000 : -0x1000;                           /* sign of FX_SinIdx */
        diff = h + s - *(int *)(state[2] + 4);
        state[9] += diff / 10;
    }
    if (dist < 0x2000) {
        dir.y = 0;
        func_01ff8d18(&dir, &dir);
        func_01ffa724(-0x180, &dir, &pull);
        VEC_Add((Vec3 *)(state + 8), &pull, (Vec3 *)(state + 8));
    } else if (dist > 0x3000) {
        dir.y = 0;
        func_01ff8d18(&dir, &dir);
        func_01ffa724(0x180, &dir, &pull);
        VEC_Add((Vec3 *)(state + 8), &pull, (Vec3 *)(state + 8));
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
    *(unsigned char *)(*state + 0x1c7) = 9;
    func_0203c634(node, *(signed char *)(node + 0x20), 0);
}
