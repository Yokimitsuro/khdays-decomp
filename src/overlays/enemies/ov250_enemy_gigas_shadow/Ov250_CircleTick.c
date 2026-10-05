/* Circle tick of the ov250 enemy (and its byte-identical twin): the +0x20 step is 30 x dt / 20;
 * the closest target goes to +0x10 (none returns) and its surface distance (root minus both
 * +0x80 radii) must be inside the actor's +0x2d8 range. The offset from the +4 position to the
 * target's +0x190 gives a 0.03125 retreat (reversed, normalised) and the +0x18 heading; the
 * +0x54 velocity is the flattened offset's side vector (world Y x offset) normalised and scaled
 * by the +0x84 sense x 0x80. A 1/257 roll requests sub-state 5; otherwise beyond 7.0 a second
 * 1/257 roll (or an expired +0x74 timer) requests sub-state 4, and inside 7.0 an expired timer
 * requests 9 (beyond 3.0), 8 (beyond 1.0) or 7. */

#include "nitro/fx_types.h"
#include "game/engine.h"

extern int Ov107_FindNearestObject(int actor, int *distOut);
extern int FX_Sqrt(int x);
extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void ScaleVec3Fx12(int scale, const VecFx32 *v, VecFx32 *out);
extern int VEC_Normalize(const VecFx32 *v, VecFx32 *out);
extern fx16 FX_Atan2(int x, int z);
extern void VEC_CrossProduct(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void VEC_Add(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void SetIndexedSlot(int node, int slot, void *cb);
extern const VecFx32 data_02042264;

void Ov250_CircleTick(int node)
{
    int *state = *(int **)(node + 4);
    int dist;
    VecFx32 d;
    VecFx32 back;
    int obj;
    int target;

    state[8] = *(int *)(*(int *)node + 0x2c) * 30 / 20;
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
    ScaleVec3Fx12(-0x1000, &d, &back);
    VEC_Normalize(&back, &back);
    ScaleVec3Fx12(0x80, &back, &back);
    state[6] = FX_Atan2(d.x, d.z);
    d.y = 0;
    VEC_Normalize(&d, &d);
    VEC_CrossProduct(&d, &data_02042264, (VecFx32 *)(state + 0x15));
    VEC_Normalize((VecFx32 *)(state + 0x15), (VecFx32 *)(state + 0x15));
    ScaleVec3Fx12(state[0x21] << 7, (VecFx32 *)(state + 0x15), (VecFx32 *)(state + 0x15));
    if (RandNextScaled(0x101) + (dist - dist) == 0) {
        *(unsigned char *)(*state + 0x1c7) = 5;
        SetIndexedSlot(node, *(signed char *)(node + 0x20), 0);
        return;
    }
    if (dist > 0x7000) {
        if (RandNextScaled(0x101) + (dist - dist) != 0) {
            if (state[0x1d] > 0) {
                return;
            }
        }
        *(unsigned char *)(*state + 0x1c7) = 4;
        SetIndexedSlot(node, *(signed char *)(node + 0x20), 0);
        return;
    }
    if (state[0x1d] > 0) {
        return;
    }
    if (dist > 0x3000) {
        *(unsigned char *)(*state + 0x1c7) = 9;
        SetIndexedSlot(node, *(signed char *)(node + 0x20), 0);
        return;
    }
    if (dist > 0x1000) {
        *(unsigned char *)(*state + 0x1c7) = 8;
        SetIndexedSlot(node, *(signed char *)(node + 0x20), 0);
        return;
    }
    *(unsigned char *)(*state + 0x1c7) = 7;
    SetIndexedSlot(node, *(signed char *)(node + 0x20), 0);
}
