/* func_ov245_020ce1cc -- hover tick (armed variant): pushes the +0xc velocity along the +0x4c8
 * anchor's +0x2c direction by -1.0, accumulates the node origin's height change into +0x28
 * (tracking it at +0x30), then, once the +0x434 owner has no +0x39c target, or as soon as bit 0
 * of the owner's +0x1ac is set, resets the actor (020cce28 / pose 8), starts motion 2 of the
 * anchor, turns the accumulated height into the +0x30 ratio against 0xe40f (FX_Inv of the
 * negation) and moves the node to the hover tick (020ce2d4) or the strike (020ce33c). */
typedef struct { int x, y, z; } Vec3;

extern void func_01ffa724(int scale, const Vec3 *v, Vec3 *out);
extern void func_ov245_020cce28(int actor);
extern void func_ov107_020c9264(int actor, int pose, int flag);
extern void func_ov107_020c9ee8(int item, int motion, int flag);
extern int FX_Inv(int num, int den);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov245_020ce2d4(void);
extern void func_ov245_020ce33c(void);

void func_ov245_020ce1cc(int *node) {
    int *state = (int *)node[1];
    int owner;

    func_01ffa724(-0x1000, (Vec3 *)(*(int *)(*state + 0x4c8) + 0x2c), (Vec3 *)(state + 3));
    state[10] += *(int *)(state[2] + 8) - state[0xc];
    state[0xc] = *(int *)(state[2] + 8);
    owner = *(int *)(*state + 0x434);
    if (*(int *)(owner + 0x39c) == 0) {
        func_ov245_020cce28(*state);
        func_ov107_020c9ee8(*(int *)(*state + 0x4c8), 2, 0);
        state[0xc] = FX_Inv(-state[10], 0xe40f);
        func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov245_020ce2d4);
        return;
    }
    if ((*(unsigned short *)(owner + 0x100 + 0xac) & 1) == 0) {
        return;
    }
    func_ov107_020c9264(*state, 8, 0);
    func_ov107_020c9ee8(*(int *)(*state + 0x4c8), 2, 0);
    state[0xc] = FX_Inv(-state[10], 0xe40f);
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov245_020ce33c);
}
