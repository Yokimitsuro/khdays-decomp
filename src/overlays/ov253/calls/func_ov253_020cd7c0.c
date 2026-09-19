/* func_ov253_020cd7c0 -- seek tick: the +0x14 speed follows 1.5 times the frame step (30 / 20);
 * the nearest visible target facing the +0xc heading within 60.0 (020cd0d8) is kept at +0x24
 * and the +0x10 heading turned towards it; while the +0x30 delay is spent the +0x1c timer runs
 * up and picks the next decision at +0x28: 5 once the target sits within 30.0 for 10.0, a 5/4
 * coin toss under 9.0, 5 beyond 30.0 -- then the +0x38c item's +0xa8 flag clears and the node
 * moves to 020cd98c. Codegen: `+ (v - v)` is the documented random copy artifact. */
typedef struct { int x, y, z; } Vec3;

extern int func_ov253_020cd0d8(int self, const Vec3 *pos, const Vec3 *dir, int minDot, int maxDist);
extern void VEC_Subtract(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern int func_01ff8d18(const Vec3 *v, Vec3 *out);
extern int func_020050b4(int y, int x);
extern int func_02023eb4(int scale);
extern void func_0203c634(int *node, int slot, void *cb);
extern const short data_0203d210[];
extern void func_ov253_020cd98c(void);

static inline unsigned short FX_RadToIdx(int rad) {
    return (unsigned short)((0x28BE60DB9391LL * rad + 0x80000000000LL) >> 44);
}

void func_ov253_020cd7c0(int *node) {
    int *state = (int *)node[1];
    Vec3 dir;
    Vec3 d;
    int target;
    int dist;
    int v;

    state[5] = *(int *)(node[0] + 0x2c) * 0x1e / 20;
    dir.x = data_0203d210[(FX_RadToIdx(state[3]) >> 4) << 1];
    dir.y = 0;
    dir.z = data_0203d210[((FX_RadToIdx(state[3]) >> 4) << 1) + 1];
    target = func_ov253_020cd0d8(*state, (Vec3 *)state[2], &dir, -0x1000, 0x3c000);
    state[9] = target;
    if (target == 0) {
        return;
    }
    VEC_Subtract((Vec3 *)(target + 0x190), (Vec3 *)state[2], &d);
    dist = func_01ff8d18(&d, &d);
    state[4] = func_020050b4(d.x, d.z);
    if (state[0xc] > 0) {
        return;
    }
    state[7] += *(int *)(node[0] + 0x2c);
    if (dist < 0x1e000 && state[7] > 0xa000) {
        state[10] = 5;
    } else if (dist < 0x9000) {
        if (func_02023eb4(9) + (v - v) == 0) {
            state[10] = 5;
        } else {
            state[10] = 4;
        }
    } else if (dist > 0x1e000) {
        state[10] = 5;
    } else {
        return;
    }
    *(unsigned char *)(*(int *)(*state + 0x38c) + 0xa8) = 0;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov253_020cd98c);
}
