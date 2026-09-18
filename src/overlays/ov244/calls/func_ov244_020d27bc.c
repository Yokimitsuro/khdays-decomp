/* Approach tick of the ov114 enemy: the closest target goes to +0x10 (none requests sub-state
 * 2); the offset from the +4 position to its +0x190 gives the +0x18 heading, and the +0x50
 * velocity is the facing (sin, 0, cos) of the +0x14 yaw at 0x180. Once the +0x4c timer has
 * expired the surface distance (root minus both +0x80 radii) decides: sub-state 6, or 2 when it
 * is still inside 1.0. */
typedef struct { int x, y, z; } Vec3;

extern int func_ov107_020cab14(int actor, int *distOut);
extern void func_0203c634(int node, int slot, void *cb);
extern void VEC_Subtract(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern int func_020050b4(int x, int z);
extern void func_01ffa724(int scale, const Vec3 *v, Vec3 *out);
extern int FX_Sqrt(int x);
extern const short data_0203d210[];

#define ANG2IDX(a) ((unsigned short)(((long long)(a) * 0x28be60db9391LL + 0x80000000000LL) >> 44) >> 4)

void func_ov244_020d27bc(int node)
{
    int *state = *(int **)(node + 4);
    int dist;
    Vec3 d;
    int obj;
    int target;
    unsigned int idx;

    state[4] = func_ov107_020cab14(*state, &dist);
    if (state[4] == 0) {
        *(unsigned char *)(*state + 0x1c7) = 2;
        func_0203c634(node, *(signed char *)(node + 0x20), 0);
        return;
    }
    VEC_Subtract((Vec3 *)(state[4] + 0x190), (Vec3 *)state[1], &d);
    state[6] = func_020050b4(d.x, d.z);
    idx = ANG2IDX(state[5]);
    state[0x14] = data_0203d210[idx * 2];                                     /* FX_SinIdx */
    state[0x15] = 0;
    state[0x16] = data_0203d210[idx * 2 + 1];                                 /* FX_CosIdx */
    func_01ffa724(0x180, (Vec3 *)(state + 0x14), (Vec3 *)(state + 0x14));
    obj = *state;
    target = state[4];
    dist = FX_Sqrt(dist) - (*(int *)(target + 0x80) + *(int *)(obj + 0x80));
    if (state[0x13] <= 0) {
        *(unsigned char *)(*state + 0x1c7) = 6;
        func_0203c634(node, *(signed char *)(node + 0x20), 0);
        return;
    }
    if (dist > 0x1000) {
        return;
    }
    *(unsigned char *)(*state + 0x1c7) = 2;
    func_0203c634(node, *(signed char *)(node + 0x20), 0);
}
