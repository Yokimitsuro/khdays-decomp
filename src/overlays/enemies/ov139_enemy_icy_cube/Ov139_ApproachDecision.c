/* Approach decision of the ov139 enemy (and its byte-identical twin). Acquires the +4 target
 * (none ends the tick), aims the +0xc yaw at it and measures the flat gap between the +0x4c
 * position and the target beyond both +0x80 radii; within 0x2000 the +0x14 velocity backs off
 * by 0x100 along the facing of the +8 yaw. With the gap at most 0x4000 and the +0x40 timer
 * spent, the overlay's probe offset is rotated by the target yaw and a 0..100 roll below 70
 * with a clear probe requests sub-state 5, anything else sub-state 6. Otherwise a gap inside
 * the +0x2d8 range but at or beyond 0x4000 requests sub-state 4. */

#include "nitro/fx_types.h"
#include "game/engine.h"

typedef struct { int m[9]; } Mtx33;

extern int Ov107_FindNearestObject(int actor, int mode);
extern void VEC_Subtract(void *a, void *b, VecFx32 *d);
extern int VEC_Normalize(VecFx32 *v, VecFx32 *d);
extern fx16 FX_Atan2(int x, int z);
extern void ScaleVec3Fx12(int scale, VecFx32 *v, VecFx32 *d);
extern void MTX_RotY33_(Mtx33 *m, int sin, int cos);
extern void MTX_MultVec33(VecFx32 *v, Mtx33 *m, VecFx32 *d);
extern int Ov139_TestSubObjectHelperNonzero(int *node, VecFx32 *at);
extern void SetIndexedSlot(int *node, int slot, void *cb);
extern short data_0203d210[];
extern const VecFx32 data_ov139_020cec14;

#define ANG2IDX(a) ((unsigned short)(((long long)(a) * 0x28be60db9391LL + 0x80000000000LL) >> 44) >> 4)

static inline int RandRange(int low, int high)
{
    int span = high - low;
    if (span < 0) span = -span;
    return low + RandNextScaled(span + 1);
}

void Ov139_ApproachDecision(int *node)
{
    int *state = (int *)node[1];
    VecFx32 dir;
    VecFx32 facing;
    Mtx33 mtx;
    VecFx32 probe;
    int gap;
    int actor;
    int target;
    int roll;
    unsigned int idx;

    state[1] = Ov107_FindNearestObject(*state, 0);
    if (state[1] == 0) {
        return;
    }
    VEC_Subtract((void *)(state[1] + 0x74), (void *)state[0x13], &dir);
    dir.y = 0;
    actor = *state;
    target = state[1];
    gap = VEC_Normalize(&dir, &dir) - (*(int *)(target + 0x80) + *(int *)(actor + 0x80));
    state[3] = FX_Atan2(dir.x, dir.z);
    if (gap < 0x2000) {
        idx = ANG2IDX(state[2]);
        facing.x = data_0203d210[idx * 2];
        facing.y = 0;
        facing.z = data_0203d210[idx * 2 + 1];
        ScaleVec3Fx12(-0x100, &facing, (VecFx32 *)(state + 5));
    }
    if (gap <= 0x4000 && state[0x10] <= 0) {
        probe = data_ov139_020cec14;
        roll = RandRange(0, 0x64);
        idx = ANG2IDX(state[3]);
        MTX_RotY33_(&mtx, data_0203d210[idx * 2], data_0203d210[idx * 2 + 1]);
        MTX_MultVec33(&probe, &mtx, &probe);
        if (roll < 0x46 && Ov139_TestSubObjectHelperNonzero(node, &probe) == 0) {
            *(unsigned char *)(*state + 0x1c7) = 5;
            SetIndexedSlot(node, *(signed char *)((char *)node + 0x20), 0);
            return;
        }
        *(unsigned char *)(*state + 0x1c7) = 6;
        SetIndexedSlot(node, *(signed char *)((char *)node + 0x20), 0);
        return;
    }
    if (gap >= *(int *)(*state + 0x2d8)) {
        return;
    }
    if (gap < 0x4000) {
        return;
    }
    *(unsigned char *)(*state + 0x1c7) = 4;
    SetIndexedSlot(node, *(signed char *)((char *)node + 0x20), 0);
}
