/* Homing dash tick: snapshots the +8 target's +0x10 position into +0x70, runs the +0x18 timer,
 * faces the target from the +4 anchor (+0x30, slerped into the +0x20 pose by 30/2 of the frame
 * step; +0x40 from data_0204227c), clamps the +0x1c range to the current distance, and sets the
 * +0xc velocity to the pose forward (data_02042258) scaled by 0.8125 of its alignment with the
 * target direction (floored at 0). Within 1.0 of the target, or once the timer passes 1.0, pose
 * request 0 is queued and the node dispatches null. */
typedef struct { int x, y, z; } Vec3;

static inline int FX_Mul(int a, int b) {
    return (int)(((long long)a * b + 0x800) >> 12);
}

extern void VEC_Subtract(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern int func_01ff8d18(const Vec3 *v, Vec3 *out);
extern void func_0202ed60(void *rotation, const Vec3 *from, const Vec3 *to);
extern void func_0202f55c(void *a, int s, void *b, void *m);
extern void func_0202f384(Vec3 *out, void *rotation, const Vec3 *in);
extern int VEC_DotProduct(const Vec3 *a, const Vec3 *b);
extern void func_01ffa724(int scale, const Vec3 *v, Vec3 *out);
extern void func_0203c634(int *node, int slot, void *cb);
extern const Vec3 data_02042258;
extern const Vec3 data_0204227c;

void func_ov213_020d1208(int *node) {
    int *state = (int *)node[1];
    Vec3 dir;
    Vec3 fwd;
    int dist;
    int align;

    *(Vec3 *)(state + 0x1c) = *(Vec3 *)(state[2] + 0x10);
    state[6] += *(int *)(node[0] + 0x2c);
    VEC_Subtract((Vec3 *)(state + 0x1c), (Vec3 *)state[1], &dir);
    func_01ff8d18(&dir, &dir);
    func_0202ed60((void *)(state + 0xc), &data_02042258, &dir);
    func_0202f55c(state + 8, *(int *)(node[0] + 0x2c) * 30 / 2, state + 8, state + 0xc);
    func_0202ed60((void *)(state + 0x10), &data_0204227c, &dir);
    VEC_Subtract((Vec3 *)(state + 0x1c), (Vec3 *)state[1], &dir);
    dist = func_01ff8d18(&dir, &dir);
    if (dist < state[7]) state[7] = dist;
    func_0202f384(&fwd, (void *)(state + 8), &data_02042258);
    align = VEC_DotProduct(&dir, &fwd);
    if (align < 0) align = 0;
    state[7] = FX_Mul(align, 0xd00);
    func_01ffa724(state[7], &fwd, (Vec3 *)(state + 3));
    if (dist >= 0x1000) {
        if (state[6] <= 0x1000) return;
    }
    *(unsigned char *)(*state + 0x1c7) = 0;
    func_0203c634(node, *(signed char *)(node + 8), 0);
}
