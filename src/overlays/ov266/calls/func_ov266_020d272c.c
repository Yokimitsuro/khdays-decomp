/*
 * Steer toward the anchor. If bit 0 of the hw60 lo byte is set, run 020ce120 first.
 * Take the vector from the anchor (ctx[2]) to the owner's point (owner+0x190), cache its
 * heading as a Q12-radian angle (atan2 = func_020050b4(dx, dz)) at ctx[0xf], and measure
 * how far past the owner's reach (+0x80) it is. Convert the heading to a 16-bit table
 * index, write {sin, 0, cos} into ctx[4..6], scale it by the owner's speed (+0x578) in
 * place, and once inside 0x2000 latch phase 2 and dispatch.
 *
 * Two levers hold the schedule:
 *  - `*ctx` is cached in a LOCAL across the func_01ff8d18 call; spelling the reach read
 *    as `- *(int *)(*ctx + 0x80)` makes mwcc reload *ctx after the call instead of
 *    hoisting it, permuting the tail.
 *  - `const short data_0203d210[]` is load-bearing: without const mwcc must assume the
 *    ctx stores could write the sin/cos table, which pins the second table load and
 *    ripples the whole multiply-chain schedule. const is the aliasing fact that matches.
 *
 * One of a 3-member family (family).
 */
struct vec3 { int x, y, z; };
struct hw60 { unsigned short lo : 8, hi : 8; };

extern void func_ov266_020cff18(void *self, int a, int b);
extern int VEC_Subtract(void *a, void *b, void *out);
extern int func_020050b4(int a, int b);
extern int func_01ff8d18(const struct vec3 *v, struct vec3 *out);
extern void func_01ffa724(int s, struct vec3 *v, struct vec3 *out);
extern void func_0203c634(void *self, int idx, void *cb);
extern const short data_0203d210[];

void func_ov266_020d272c(void *self) {
    int *ctx = *(int **)((char *)self + 4);
    struct vec3 d;
    int dist;
    unsigned int idx;

    if (((struct hw60 *)(*ctx + 0x60))->lo & 1) {
        func_ov266_020cff18(self, *ctx, ctx[2]);
    }
    VEC_Subtract((void *)(*ctx + 0x190), (void *)ctx[2], &d);
    ctx[0xf] = func_020050b4(d.x, d.z);
    { int node = *ctx;
    dist = func_01ff8d18(&d, &d) - *(int *)(node + 0x80); }
    idx = (unsigned short)(((long long)ctx[0xf] * 0x28be60db9391LL + 0x80000000000LL) >> 44) >> 4;
    ctx[4] = data_0203d210[idx * 2];
    ctx[5] = 0;
    ctx[6] = data_0203d210[idx * 2 + 1];
    func_01ffa724(*(int *)(*ctx + 0x578), (struct vec3 *)(ctx + 4), (struct vec3 *)(ctx + 4));
    if (dist >= 0x2000) {
        return;
    }
    *(char *)(*ctx + 0x1c7) = 2;
    func_0203c634(self, *(signed char *)((char *)self + 0x20), 0);
}
