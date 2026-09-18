/* func_ov245_020cd85c -- descend tick: the +0xc velocity is the negated +0x4c8 anchor direction
 * (+0x2c); the +0x14 height grows by itself times the +0x38 factor clamped to 0..1; then the
 * height-gap check (020ccda4 with mode 0) feeds the arrival test (020ccb30) and on success the
 * node's slot is released. */
typedef struct { int x, y, z; } Vec3;

extern void func_01ffa724(int scale, const Vec3 *v, Vec3 *out);
extern int func_ov245_020ccda4(int *node, int flat);
extern int func_ov245_020ccb30(int *node, int gap);
extern void func_0203c634(int *node, int slot, void *cb);

void func_ov245_020cd85c(int *node) {
    int *state = (int *)node[1];
    int factor;

    func_01ffa724(-0x1000, (Vec3 *)(*(int *)(*state + 0x4c8) + 0x2c), (Vec3 *)(state + 3));
    factor = state[0xe];
    if (factor > 0x1000) {
        factor = 0x1000;
    } else if (factor < 0) {
        factor = 0;
    }
    state[5] = state[5] + (int)(((long long)state[5] * factor + 0x800) >> 12);
    if (func_ov245_020ccb30(node, func_ov245_020ccda4(node, 0)) != 0) {
        func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
    }
}
