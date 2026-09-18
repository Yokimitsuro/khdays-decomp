/* func_ov245_020cdd60 -- dive tick: while the actor is still falling (020cce48) the +0x14 height
 * follows the +0x20 speed, and the speed decays once per 0x88 of the scene's +0x2c frame step
 * (each step: speed *= 1.0 - 0.03125 * min(rest, 0x88) / 0x88); on landing the +0xc velocity is
 * the negated +0x4c8 anchor direction plus -1.5 times the +0x430 item's +0x3bc direction, and if
 * the item has no +0x38c target the actor is reset (020cce28) and the node moves to 020cde98. */
typedef struct { int x, y, z; } Vec3;

extern int func_ov245_020cce48(int actor);
extern int FX_Inv(int num, int den);
extern void func_01ffa724(int scale, const Vec3 *v, Vec3 *out);
extern void VEC_Add(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern void func_ov245_020cce28(int actor);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov245_020cde98(void);

void func_ov245_020cdd60(int *node) {
    int *state = (int *)node[1];
    Vec3 push;
    int rest;

    if (func_ov245_020cce48(*state) != 0) {
        state[5] = state[8];
        rest = *(int *)(node[0] + 0x2c);
        while (rest > 0) {
            int ratio = FX_Inv(rest <= 0x88 ? rest : 0x88, 0x88);
            int t = (int)(((long long)ratio * 0x80 + 0x800) >> 12);
            state[8] = (int)(((long long)state[8] * (0x1000 - t) + 0x800) >> 12);
            rest -= 0x88;
        }
        return;
    }
    func_01ffa724(-0x1000, (Vec3 *)(*(int *)(*state + 0x4c8) + 0x2c), (Vec3 *)(state + 3));
    func_01ffa724(-0x1800, (Vec3 *)(*(int *)(*state + 0x430) + 0x3bc), &push);
    VEC_Add((Vec3 *)(state + 3), &push, (Vec3 *)(state + 3));
    if (*(int *)(*(int *)(*state + 0x430) + 0x38c) != 0) {
        return;
    }
    func_ov245_020cce28(*state);
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov245_020cde98);
}
