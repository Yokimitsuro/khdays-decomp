/* Circle decision tick of the ov114 enemy: the closest target goes to +0x10 (none returns) and
 * its surface distance (root minus both +0x80 radii) must be inside the actor's +0x2d8 range.
 * The offset from the +4 position to the target's +0x190 gives the +0x18 heading; the +0x50
 * velocity is the flattened offset's side vector (offset x world Y) normalised and scaled by
 * the +0x48 sense x 0x40. A 1/257 roll requests sub-state 6; otherwise beyond 4.0 a second
 * 1/257 roll (or an expired +0x4c timer) requests sub-state 4, and inside 4.0 an expired timer
 * requests 0xa (beyond 0.5) or 9. */

#include "nitro/fx_types.h"
#include "game/engine.h"

extern int Ov107_FindNearestObject(int actor, int *distOut);
extern int FX_Sqrt(int x);
extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern fx16 FX_Atan2(int x, int z);
extern int VEC_Normalize(const VecFx32 *v, VecFx32 *out);
extern void VEC_CrossProduct(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void ScaleVec3Fx12(int scale, const VecFx32 *v, VecFx32 *out);
extern void SetIndexedSlot(int node, int slot, void *cb);
extern const VecFx32 data_02042264;

void Ov244_CircleDecision(int node)
{
    int *state = *(int **)(node + 4);
    int dist;
    VecFx32 d;
    int obj;
    int target;

    state[4] = Ov107_FindNearestObject(*state, &dist);
    target = state[4];
    if (target == 0) {
        return;
    }
    obj = *state;
    dist = FX_Sqrt(dist) - (*(int *)(target + 0x80) + *(int *)(obj + 0x80));
    if (dist > *(int *)(*state + 0x2d8)) {
        return;
    }
    VEC_Subtract((VecFx32 *)(state[4] + 0x190), (VecFx32 *)state[1], &d);
    state[6] = FX_Atan2(d.x, d.z);
    d.y = 0;
    VEC_Normalize(&d, &d);
    VEC_CrossProduct(&d, &data_02042264, (VecFx32 *)(state + 0x14));
    ScaleVec3Fx12(*(signed char *)((char *)state + 0x48) << 6, (VecFx32 *)(state + 0x14), (VecFx32 *)(state + 0x14));
    if (RandNextScaled(0x101) + (dist - dist) == 0) {
        *(unsigned char *)(*state + 0x1c7) = 6;
        SetIndexedSlot(node, *(signed char *)(node + 0x20), 0);
        return;
    }
    if (dist > 0x4000) {
        if (RandNextScaled(0x101) + (dist - dist) != 0) {
            if (state[0x13] > 0) {
                return;
            }
        }
        *(unsigned char *)(*state + 0x1c7) = 4;
        SetIndexedSlot(node, *(signed char *)(node + 0x20), 0);
        return;
    }
    if (state[0x13] > 0) {
        return;
    }
    if (dist > 0x800) {
        *(unsigned char *)(*state + 0x1c7) = 0xa;
        SetIndexedSlot(node, *(signed char *)(node + 0x20), 0);
        return;
    }
    *(unsigned char *)(*state + 0x1c7) = 9;
    SetIndexedSlot(node, *(signed char *)(node + 0x20), 0);
}
