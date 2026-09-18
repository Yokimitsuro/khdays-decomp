/* func_ov245_020d64ac -- approach planner: refreshes the +8 target (020cab14); with none the
 * actor goes to sub-state 2 and the node's slot is released. Otherwise the flattened gap from
 * the actor's +0xb0 to the target's +0x190 (normalised, minus both +0x80 radii) and its heading
 * (+0x14) are taken, the +0x10 angle turned into a forward vector (sine table) which, scaled by
 * 0.1875, becomes the +0x1c step; inside 0.5 the actor goes to sub-state 2 and the slot is released. */
typedef struct { int x, y, z; } Vec3;

extern int func_ov107_020cab14(int actor, int a);
extern void func_0203c634(int *node, int slot, void *cb);
extern void VEC_Subtract(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern int func_01ff8d18(const Vec3 *v, Vec3 *out);
extern int func_020050b4(int x, int z);
extern int VEC_DotProduct(const Vec3 *a, const Vec3 *b);
extern void func_01ffa724(int scale, const Vec3 *v, Vec3 *out);
extern const short data_0203d210[];

void func_ov245_020d64ac(int *node) {
    int *state = (int *)node[1];
    Vec3 d;
    Vec3 fwd;
    int gap;
    int idx;
    int target;
    int actor;

    state[2] = func_ov107_020cab14(*state, 0);
    if (state[2] == 0) {
        *(unsigned char *)(*state + 0x1c7) = 2;
        func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
        return;
    }
    VEC_Subtract((Vec3 *)(state[2] + 0x190), (Vec3 *)(*state + 0xb0), &d);
    d.y = 0;
    target = state[2];
    actor = *state;
    gap = func_01ff8d18(&d, &d) - *(int *)(target + 0x80) - *(int *)(actor + 0x80);
    state[5] = func_020050b4(d.x, d.z);
    idx = (unsigned short)((0x28BE60DB9391LL * state[4] + 0x80000000000LL) >> 44);   /* FX_RAD_TO_IDX */
    fwd.x = data_0203d210[(idx >> 4) << 1];                                           /* FX_SinIdx */
    fwd.y = 0;
    fwd.z = data_0203d210[((idx >> 4) << 1) + 1];                                     /* FX_CosIdx */
    VEC_DotProduct(&fwd, &d);
    func_01ffa724(0x300, &fwd, (Vec3 *)(state + 7));
    if (gap >= 0x800) {
        return;
    }
    *(unsigned char *)(*state + 0x1c7) = 2;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
}
