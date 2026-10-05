/* Stalk tick of the ov173 enemy (and its byte-identical twins): acquires the target (020cab14) -- none
 * sends it to sub-state 2 -- then faces it (flattened direction from the actor's +0x74 to the
 * target position at +8, atan2 into the +0x74 quaternion around the up axis) and steps 0x600
 * along it; the hover height (+0x24) eases 1/30 of the way to the target's +0x78 + 0x2400 (or the
 * +0x18 override when +0x88 is set) above the target position. Beyond 0x3000 of surface
 * distance a 1-in-3 roll decides: 35 % with a free target (020ccb8c) go to sub-state 9, the rest
 * to 2; otherwise the +0x48 phase advances and at 0x3000 sub-state 6 follows. */

#include "nitro/fx_types.h"
#include "game/engine.h"

extern int Ov107_FindNearestObject(int obj, int b);
extern void SetIndexedSlot(int node, int slot, void *cb);
extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern int VEC_Normalize(const VecFx32 *v, VecFx32 *out);
extern fx16 FX_Atan2(int y, int x);
extern void ScaleVec3Fx12(int scale, const VecFx32 *v, VecFx32 *out);
extern int Ov173_DefaultStepDone(int node);
extern int data_02042264;

void Ov173_StalkTick(int node)
{
    int *state = *(int **)(node + 4);
    VecFx32 d;
    int dist;
    int target;
    int obj;
    int height;
    int diff;

    state[3] = Ov107_FindNearestObject(*state, 0);
    if (state[3] == 0) {
        *(unsigned char *)(*state + 0x1c7) = 2;
        SetIndexedSlot(node, *(signed char *)(node + 0x20), 0);
        return;
    }
    VEC_Subtract((VecFx32 *)state[2], (VecFx32 *)(state[3] + 0x74), &d);
    d.y = 0;
    target = state[3];
    obj = *state;
    dist = VEC_Normalize(&d, &d) - *(int *)(target + 0x80) - *(int *)(obj + 0x80);
    QuatFromAxisAngle(state + 0x1d, &data_02042264, FX_Atan2(d.x, d.z));
    ScaleVec3Fx12(0x600, &d, (VecFx32 *)(state + 8));
    if (state[0x22] != 0) {
        height = state[6];
    } else {
        height = *(int *)(state[3] + 0x78) + 0x2400;
    }
    diff = height - *(int *)(state[2] + 4);
    state[9] += (int)(((long long)(diff / 30) * 0x3000 + 0x800) >> 12);
    if (dist > 0x3000 && RandNextScaled(3) == 0) {
        if ((unsigned int)RandNextScaled(100) < 0x23 && Ov173_DefaultStepDone(node) != 0) {
            *(unsigned char *)(*state + 0x1c7) = 9;
            SetIndexedSlot(node, *(signed char *)(node + 0x20), 0);
            return;
        }
        *(unsigned char *)(*state + 0x1c7) = 2;
        SetIndexedSlot(node, *(signed char *)(node + 0x20), 0);
        return;
    }
    state[0x12] += *(int *)(*(int *)node + 0x2c);
    if (state[0x12] >= 0x3000) {
        *(unsigned char *)(*state + 0x1c7) = 6;
        SetIndexedSlot(node, *(signed char *)(node + 0x20), 0);
    }
}
