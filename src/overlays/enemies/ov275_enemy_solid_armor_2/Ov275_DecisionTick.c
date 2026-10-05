/* Decision tick of the ov274 enemy. The target is re-acquired into +0x10 (none: sub-state 2
 * and the state ends). The flattened direction from the +4 point to the target's +0x190 gives
 * the gap (less both +0x80 radii), the +0x3c rate takes 30 x rate / 30 and +0x44 the heading
 * (atan2 of the direction). The +0x14 aim takes the owner's +0xa0 basis turned by the +0x3b4
 * aim (9f48), scaled by its reach and normalised. Once the +0xc idle byte is clear a roll of
 * 101 decides: under 20 sub-state 0xa, under 40 sub-state 5; otherwise, closer than 4.0 a dot
 * product of the direction and the aim above 0x200 gives sub-state 6, else nothing, and
 * farther the same test gives sub-state 5 or a second roll (under 50: 0xa, else 9). Every
 * decision ends the state. */

#include "nitro/fx_types.h"
#include "game/enemy_common.h"
#include "game/engine.h"

extern int Ov107_FindNearestObject(int owner, int flag);
extern void SetIndexedSlot(int *node, int slot, void *cb);
extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern int VEC_Normalize(const VecFx32 *v, VecFx32 *out);
extern fx16 FX_Atan2(int x, int z);
extern void ScaleVec3Fx12(int scale, const VecFx32 *v, VecFx32 *out);
static inline int RandRange(int lo, int hi) { return (int)RandNextScaled(hi - lo + 1) + lo; }
extern int VEC_DotProduct(const VecFx32 *a, const VecFx32 *b);

void Ov275_DecisionTick(int *node)
{
    int *state = (int *)node[1];
    VecFx32 dir;
    VecFx32 aim;
    int gap;
    int target;
    int owner;
    int reach;
    int roll;

    state[4] = Ov107_FindNearestObject(*state, 0);
    if (state[4] == 0) {
        *(unsigned char *)(*state + 0x1c7) = 2;
        SetIndexedSlot(node, *(signed char *)((char *)node + 0x20), 0);
        return;
    }
    VEC_Subtract((VecFx32 *)(state[4] + 0x190), (VecFx32 *)state[1], &dir);
    target = state[4];
    owner = *state;
    gap = VEC_Normalize(&dir, &dir) - (*(int *)(owner + 0x80) + *(int *)(target + 0x80));
    state[0xf] = *(int *)(node[0] + 0x2c) * 30 / 30;
    state[0x11] = FX_Atan2(dir.x, dir.z);
    reach = Ov107_ActionResource_GetOffsetAndScale(*(int *)(*state + 0x3b4), &aim);
    Vec3TransformViaTempMtx((VecFx32 *)(state + 5), (char *)*state + 0xa0, &aim);
    ScaleVec3Fx12(reach, (VecFx32 *)(state + 5), (VecFx32 *)(state + 5));
    VEC_Normalize((VecFx32 *)(state + 5), &aim);
    if (*(unsigned char *)state[3] != 0) {
        return;
    }
    roll = RandRange(0, 100);
    if (roll < 20) {
        *(unsigned char *)(*state + 0x1c7) = 0xa;
        SetIndexedSlot(node, *(signed char *)((char *)node + 0x20), 0);
        return;
    }
    if (roll < 40) {
        *(unsigned char *)(*state + 0x1c7) = 5;
        SetIndexedSlot(node, *(signed char *)((char *)node + 0x20), 0);
        return;
    }
    if (gap < 0x4000) {
        if (VEC_DotProduct(&dir, &aim) <= 0x200) {
            return;
        }
        *(unsigned char *)(*state + 0x1c7) = 6;
        SetIndexedSlot(node, *(signed char *)((char *)node + 0x20), 0);
        return;
    }
    if (VEC_DotProduct(&dir, &aim) > 0x200) {
        *(unsigned char *)(*state + 0x1c7) = 5;
        SetIndexedSlot(node, *(signed char *)((char *)node + 0x20), 0);
        return;
    }
    roll = RandRange(0, 100);
    if (roll < 50) {
        *(unsigned char *)(*state + 0x1c7) = 0xa;
        SetIndexedSlot(node, *(signed char *)((char *)node + 0x20), 0);
        return;
    }
    *(unsigned char *)(*state + 0x1c7) = 9;
    SetIndexedSlot(node, *(signed char *)((char *)node + 0x20), 0);
}
