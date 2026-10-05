/* Hover-approach tick of the ov115 enemy (and its byte-identical twins): acquires a target (+0xc; none
 * requests sub-state 2); the flattened, normalised offset from the target's +0x74 to the +8
 * position gives the surface distance (length minus both +0x80 radii) and the heading, which
 * becomes the +0x74 orientation (quaternion about world Y) and, at 0.25, the +0x20 step. The
 * +0x24 height eases towards the target's +0x78 plus 3.0 (or the fixed +0x18 height when
 * +0x88 is set) by half the difference per second. Beyond 3.0 a 1/3 roll picks sub-state 8
 * with a free target (020ccaa0) or 2; otherwise the +0x48 timer grows and past 3.0 requests
 * sub-state 6. */

#include "nitro/fx_types.h"
#include "game/engine.h"

extern int Ov107_FindNearestObject(int actor, int mode);
extern void SetIndexedSlot(int node, int slot, void *cb);
extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern int VEC_Normalize(const VecFx32 *v, VecFx32 *out);
extern fx16 FX_Atan2(int x, int z);
extern void ScaleVec3Fx12(int scale, const VecFx32 *v, VecFx32 *out);
extern int Ov116_IsHeldSlotEmpty(int node);
extern int data_02042264;

void Ov116_HoverApproachTick(int node)
{
    int *state = *(int **)(node + 4);
    VecFx32 dir;
    int dist;
    int target;
    int obj;
    int h;
    int diff;

    state[3] = Ov107_FindNearestObject(*state, 0);
    if (state[3] == 0) {
        *(unsigned char *)(*state + 0x1c7) = 2;
        SetIndexedSlot(node, *(signed char *)(node + 0x20), 0);
        return;
    }
    VEC_Subtract((VecFx32 *)state[2], (VecFx32 *)(state[3] + 0x74), &dir);
    dir.y = 0;
    obj = *state;
    target = state[3];
    dist = VEC_Normalize(&dir, &dir) - *(int *)(target + 0x80) - *(int *)(obj + 0x80);
    QuatFromAxisAngle(state + 0x1d, &data_02042264, FX_Atan2(dir.x, dir.z));
    ScaleVec3Fx12(0x200, &dir, (VecFx32 *)(state + 8));
    h = state[0x22] != 0 ? state[6] : *(int *)(state[3] + 0x78) + 0x3000;
    diff = h - *(int *)(state[2] + 4);
    state[9] += (int)(((long long)(diff / 30) * 0x1000 + 0x800) >> 12);
    if (dist > 0x3000 && RandNextScaled(3) == 0) {
        if (Ov116_IsHeldSlotEmpty(node) != 0) {
            *(unsigned char *)(*state + 0x1c7) = 8;
            SetIndexedSlot(node, *(signed char *)(node + 0x20), 0);
            return;
        }
        *(unsigned char *)(*state + 0x1c7) = 2;
        SetIndexedSlot(node, *(signed char *)(node + 0x20), 0);
        return;
    }
    state[0x12] += *(int *)(*(int *)node + 0x2c);
    if (state[0x12] < 0x3000) {
        return;
    }
    *(unsigned char *)(*state + 0x1c7) = 6;
    SetIndexedSlot(node, *(signed char *)(node + 0x20), 0);
}
