/* Approach decision of the ov139 enemy (and its byte-identical twin). Acquires the +4 target
 * (none ends the tick), aims the +0xc yaw at it and measures the flat gap between the +0x4c
 * position and the target beyond both +0x80 radii; within 0x2000 the +0x14 velocity backs off
 * by 0x100 along the facing of the +8 yaw. With the gap at most 0x4000 and the +0x40 timer
 * spent, the overlay's probe offset is rotated by the target yaw and a 0..100 roll below 70
 * with a clear probe requests sub-state 5, anything else sub-state 6. Otherwise a gap inside
 * the +0x2d8 range but at or beyond 0x4000 requests sub-state 4. */
typedef struct Vec3 { int x, y, z; } Vec3;
typedef struct { int m[9]; } Mtx33;

extern int func_ov107_020cab14(int actor, int mode);
extern void VEC_Subtract(void *a, void *b, Vec3 *d);
extern int func_01ff8d18(Vec3 *v, Vec3 *d);
extern int func_020050b4(int x, int z);
extern void func_01ffa724(int scale, Vec3 *v, Vec3 *d);
extern int func_02023eb4(int range);
extern void MTX_RotY33_(Mtx33 *m, int sin, int cos);
extern void MTX_MultVec33(Vec3 *v, Mtx33 *m, Vec3 *d);
extern int func_ov140_020d0614(int *node, Vec3 *at);
extern void func_0203c634(int *node, int slot, void *cb);
extern short data_0203d210[];
extern const Vec3 data_ov140_020d2854;

#define ANG2IDX(a) ((unsigned short)(((long long)(a) * 0x28be60db9391LL + 0x80000000000LL) >> 44) >> 4)

static inline int RandRange(int low, int high)
{
    int span = high - low;
    if (span < 0) span = -span;
    return low + func_02023eb4(span + 1);
}

void func_ov140_020d0948(int *node)
{
    int *state = (int *)node[1];
    Vec3 dir;
    Vec3 facing;
    Mtx33 mtx;
    Vec3 probe;
    int gap;
    int actor;
    int target;
    int roll;
    unsigned int idx;

    state[1] = func_ov107_020cab14(*state, 0);
    if (state[1] == 0) {
        return;
    }
    VEC_Subtract((void *)(state[1] + 0x74), (void *)state[0x13], &dir);
    dir.y = 0;
    actor = *state;
    target = state[1];
    gap = func_01ff8d18(&dir, &dir) - (*(int *)(target + 0x80) + *(int *)(actor + 0x80));
    state[3] = func_020050b4(dir.x, dir.z);
    if (gap < 0x2000) {
        idx = ANG2IDX(state[2]);
        facing.x = data_0203d210[idx * 2];
        facing.y = 0;
        facing.z = data_0203d210[idx * 2 + 1];
        func_01ffa724(-0x100, &facing, (Vec3 *)(state + 5));
    }
    if (gap <= 0x4000 && state[0x10] <= 0) {
        probe = data_ov140_020d2854;
        roll = RandRange(0, 0x64);
        idx = ANG2IDX(state[3]);
        MTX_RotY33_(&mtx, data_0203d210[idx * 2], data_0203d210[idx * 2 + 1]);
        MTX_MultVec33(&probe, &mtx, &probe);
        if (roll < 0x46 && func_ov140_020d0614(node, &probe) == 0) {
            *(unsigned char *)(*state + 0x1c7) = 5;
            func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
            return;
        }
        *(unsigned char *)(*state + 0x1c7) = 6;
        func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
        return;
    }
    if (gap >= *(int *)(*state + 0x2d8)) {
        return;
    }
    if (gap < 0x4000) {
        return;
    }
    *(unsigned char *)(*state + 0x1c7) = 4;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
}
