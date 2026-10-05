/* Approach decision of the ov204 enemy (and its byte-identical twin). Acquires the +4 target
 * (none ends the tick), aims the +0x38 yaw at it and measures the flat gap between the +0x24
 * position and the target beyond both +0x80 radii; within 0x4000 the +8 velocity backs off by
 * 0x100 along the facing of the +0x34 yaw. While the +0x30 timer runs, a gap inside the +0x2d8
 * range but at or beyond 0x8000 requests sub-state 4. Otherwise a gap at or beyond 0x6000
 * requests sub-state 6; else the timer is re-armed at random between the actor's +0x224 and
 * +0x228, the overlay's probe offset is rotated by the target yaw and a 0..100 roll picks
 * sub-state 6 (below 40, when the probe finds nothing), 0xb (70 and up) or 7. */

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
extern int Ov205_TestSubObjectHelperNonzero(int *node, VecFx32 *at);
extern void SetIndexedSlot(int *node, int slot, void *cb);
extern short data_0203d210[];
extern const VecFx32 data_ov205_020d7240;

#define ANG2IDX(a) ((unsigned short)(((long long)(a) * 0x28be60db9391LL + 0x80000000000LL) >> 44) >> 4)

static inline int RandRange(int low, int high)
{
    int span = high - low;
    if (span < 0) span = -span;
    return low + RandNextScaled(span + 1);
}

void Ov205_ApproachDecision(int *node)
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
    VEC_Subtract((void *)(state[1] + 0x74), (void *)state[9], &dir);
    dir.y = 0;
    actor = *state;
    target = state[1];
    gap = VEC_Normalize(&dir, &dir) - (*(int *)(target + 0x80) + *(int *)(actor + 0x80));
    state[0xe] = FX_Atan2(dir.x, dir.z);
    if (gap < 0x4000) {
        idx = ANG2IDX(state[0xd]);
        facing.x = data_0203d210[idx * 2];
        facing.y = 0;
        facing.z = data_0203d210[idx * 2 + 1];
        ScaleVec3Fx12(-0x100, &facing, (VecFx32 *)(state + 2));
    }
    if (state[0xc] <= 0) {
        if (gap < 0x6000) {
            probe = data_ov205_020d7240;
            state[0xc] = RandRange(*(int *)(*state + 0x224), *(int *)(*state + 0x228));
            idx = ANG2IDX(state[0xe]);
            MTX_RotY33_(&mtx, data_0203d210[idx * 2], data_0203d210[idx * 2 + 1]);
            MTX_MultVec33(&probe, &mtx, &probe);
            roll = RandRange(0, 0x64);
            if (roll < 0x28 && Ov205_TestSubObjectHelperNonzero(node, &probe) == 0) {
                *(unsigned char *)(*state + 0x1c7) = 6;
                SetIndexedSlot(node, *(signed char *)((char *)node + 0x20), 0);
                return;
            }
            if (roll < 0x46) {
                *(unsigned char *)(*state + 0x1c7) = 7;
                SetIndexedSlot(node, *(signed char *)((char *)node + 0x20), 0);
                return;
            }
            *(unsigned char *)(*state + 0x1c7) = 0xb;
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
    if (gap < 0x8000) {
        return;
    }
    *(unsigned char *)(*state + 0x1c7) = 4;
    SetIndexedSlot(node, *(signed char *)((char *)node + 0x20), 0);
}
