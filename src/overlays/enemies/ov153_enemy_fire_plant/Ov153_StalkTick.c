/* Stalk tick of the ov153 enemy (x3: ov153/154/155): the +0x20 step is 30 x dt / 40; the ov107
 * hook picks the closest target (+0x18, with its squared distance) -- none returns. The surface
 * distance (root minus both +0x80 radii) must be under the actor's +0x2d8 range; then the +0x14
 * heading turns to the target's +0x190 and the +0x1c timer runs down by dt. With the +0x398
 * item idle (bit 0 of its +0x60 clear): a target ahead of the actor (unit offset . rotated Z
 * axis > 0.5) closer than 1.0 fires with 1/31 luck -- rearm the timer between +0x224 and +0x228
 * and go to sub-state 6, releasing the slot; otherwise the same happens when the timer has
 * expired and the target is under 15.0.
 * `+ (dist - dist)` is the documented copy artifact of RandNextScaled (`adds r0,r0,#0`); the
 * random rearm is the Ov178_CircleTick spelling. */

#include "nitro/fx_types.h"
#include "game/engine.h"

struct hw60 { unsigned short lo : 8, hi : 8; };

extern int Ov107_FindNearestObject(int actor, int *distOut);
extern int FX_Sqrt(int x);
extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern fx16 FX_Atan2(int x, int z);
extern int VEC_Normalize(const VecFx32 *v, VecFx32 *out);
extern int VEC_DotProduct(const VecFx32 *a, const VecFx32 *b);
extern void SetIndexedSlot(int node, int slot, void *cb);
extern const VecFx32 data_02042258;

void Ov153_StalkTick(int node)
{
    int *state = *(int **)(node + 4);
    VecFx32 d;
    VecFx32 fwd;
    int dist;
    int obj;
    int target;
    int lo;
    int diff;

    state[8] = *(int *)(*(int *)node + 0x2c) * 30 / 40;
    state[6] = Ov107_FindNearestObject(*state, &dist);
    target = state[6];
    if (target == 0) {
        return;
    }
    obj = *state;
    dist = FX_Sqrt(dist) - *(int *)(target + 0x80) - *(int *)(obj + 0x80);
    if (dist >= *(int *)(*state + 0x2d8)) {
        return;
    }
    VEC_Subtract((VecFx32 *)(state[6] + 0x190), (VecFx32 *)state[1], &d);
    state[5] = FX_Atan2(d.x, d.z);
    if (state[7] > 0) {
        state[7] -= *(int *)(*(int *)node + 0x2c);
    }
    if ((((struct hw60 *)(*(int *)(*state + 0x398) + 0x60))->lo & 1) != 0) {
        return;
    }
    VEC_Normalize(&d, &d);
    Vec3TransformViaTempMtx(&fwd, (void *)(*state + 0xa0), &data_02042258);
    if (VEC_DotProduct(&d, &fwd) > 0x800 && dist < 0x1000 && RandNextScaled(0x1f) + (dist - dist) == 0) {
        lo = *(int *)(*state + 0x224);
        diff = *(int *)(*state + 0x228) - lo;
        if (diff < 0) {
            diff = -diff;
        }
        state[7] = lo + RandNextScaled(diff + 1);
        *(unsigned char *)(*state + 0x1c7) = 6;
        SetIndexedSlot(node, *(signed char *)(node + 0x20), 0);
        return;
    }
    if (dist >= 0xf000) {
        return;
    }
    if (state[7] > 0) {
        return;
    }
    lo = *(int *)(*state + 0x224);
    diff = *(int *)(*state + 0x228) - lo;
    if (diff < 0) {
        diff = -diff;
    }
    state[7] = lo + RandNextScaled(diff + 1);
    *(unsigned char *)(*state + 0x1c7) = 6;
    SetIndexedSlot(node, *(signed char *)(node + 0x20), 0);
}
