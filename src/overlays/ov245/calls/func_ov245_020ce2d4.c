/* func_ov245_020ce2d4 -- hover tick: pushes the state's +0xc velocity along the world's +0x4c8
 * anchor's +0x2c direction, by -1.0 when the actor's +0x434 owner holds a +0x3a0 target and by the
 * negated +0x30 speed otherwise; then, when the animation gate (020cce48) reports idle, requests
 * sub-state 2 and releases the node's slot. */
typedef struct { int x, y, z; } Vec3;

extern void func_01ffa724(int scale, const Vec3 *v, Vec3 *out);
extern int func_ov245_020cce48(int self);
extern void func_0203c634(int *node, int slot, void *cb);

void func_ov245_020ce2d4(int *node) {
    int *state = (int *)node[1];
    int actor = *state;
    int scale;

    if (*(int *)(*(int *)(actor + 0x434) + 0x3a0) != 0) {
        scale = 0x400;
    } else {
        scale = state[0xc];
    }
    func_01ffa724(-scale, (Vec3 *)(*(int *)(actor + 0x4c8) + 0x2c), (Vec3 *)(state + 3));
    if (func_ov245_020cce48(*state) == 0) {
        *(unsigned char *)(*state + 0x1c7) = 2;
        func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
    }
}
