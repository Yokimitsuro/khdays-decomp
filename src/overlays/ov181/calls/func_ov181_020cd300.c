/* Approach tick of the ov181 enemy (x4: ov181/182/183/184): acquires the closest target (+0x10,
 * with its squared distance) -- none ends in sub-state 2 with the slot released. The surface
 * distance (root minus both +0x80 radii) is kept; the +0x20 step is 30 x dt / 20; the +0x18
 * heading turns towards the target's +0x74 from the +8 position; the +0x54 velocity is the
 * actor's forward (world Z through its +0xa0 placement) scaled to 0.1875. With the +0x74
 * timer spent the actor requests sub-state 5 and releases the slot; otherwise, once the target
 * is within the actor's +0x2d8 range or beyond 2.0, the +0x384 item's +0xa8 byte is cleared and
 * handler 020cd458 takes over. */
typedef struct { int x, y, z; } Vec3;

extern int func_ov107_020cab14(int actor, int *distOut);
extern void func_0203c634(int node, int slot, void *cb);
extern int FX_Sqrt(int x);
extern void VEC_Subtract(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern int func_020050b4(int x, int z);
extern void func_0202f384(Vec3 *out, void *rotation, const Vec3 *in);
extern void func_01ffa724(int scale, const Vec3 *v, Vec3 *out);
extern void func_ov181_020cd458(void);
extern const Vec3 data_02042258;

void func_ov181_020cd300(int node)
{
    int *state = *(int **)(node + 4);
    int dist;
    Vec3 d;
    int obj;
    int target;

    state[4] = func_ov107_020cab14(*state, &dist);
    target = state[4];
    if (target == 0) {
        *(unsigned char *)(*state + 0x1c7) = 2;
        func_0203c634(node, *(signed char *)(node + 0x20), 0);
        return;
    }
    obj = *state;
    dist = FX_Sqrt(dist) - (*(int *)(target + 0x80) + *(int *)(obj + 0x80));
    state[8] = *(int *)(*(int *)node + 0x2c) * 30 / 20;
    VEC_Subtract((Vec3 *)(state[4] + 0x74), (Vec3 *)state[2], &d);
    state[6] = func_020050b4(d.x, d.z);
    func_0202f384((Vec3 *)(state + 0x15), (void *)(*state + 0xa0), &data_02042258);
    func_01ffa724(0x300, (Vec3 *)(state + 0x15), (Vec3 *)(state + 0x15));
    if (state[0x1d] <= 0) {
        *(unsigned char *)(*state + 0x1c7) = 5;
        func_0203c634(node, *(signed char *)(node + 0x20), 0);
        return;
    }
    if (dist < *(int *)(*state + 0x2d8) && dist > 0x2000) {
        return;
    }
    *(unsigned char *)(*(int *)(*state + 0x384) + 0xa8) = 0;
    func_0203c634(node, *(signed char *)(node + 0x20), func_ov181_020cd458);
}
