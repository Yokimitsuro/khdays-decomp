/* Aim start of the ov283 actor: after the shared step (020ccb48) both headings (+0x38, +0x40) face the
 * target's +0x390 model point, and the body is placed 6.0 back from that point along the heading
 * (vertical part from the aim); the pose settles (020c9264 mode 3), an effect plays at the +8 point,
 * the actor moves to the new spot (020c5c54) and the brain waits on 020ce214. */

#include "nitro/fx_types.h"
#include "game/enemy_common.h"

extern void Ov283_MeasureTargetGap(int *node);
extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern int VEC_Normalize(const VecFx32 *v, VecFx32 *out);
extern fx16 FX_Atan2(int x, int z);
extern void ScaleVec3Fx12(int scale, const VecFx32 *v, VecFx32 *out);
extern void func_ov107_020c0b90(int owner, int mode, VecFx32 at, int flag);
extern void SetIndexedSlot(int *node, int slot, void *cb);
extern void Ov283_AiFaceTarget(void);
extern const short data_0203d210[];

#define ANG2IDX(a) ((unsigned short)(((long long)(a) * 0x28be60db9391LL + 0x80000000000LL) >> 44) >> 4)

void Ov283_AimStart(int *node)
{
    int *state = (int *)node[1];
    VecFx32 d;
    VecFx32 unit;
    VecFx32 back;
    VecFx32 target;

    Ov283_MeasureTargetGap(node);
    VEC_Subtract((VecFx32 *)(*(int *)(*state + 0x390) + 0x190), (VecFx32 *)(*state + 0x74), &d);
    VEC_Normalize(&d, &d);
    state[0xe] = state[0x10] = FX_Atan2(d.x, d.z);
    target = *(VecFx32 *)(*(int *)(*state + 0x390) + 0x190);
    VEC_Normalize(&d, &unit);
    {
        int idx = ANG2IDX(state[0xe]) * 2;

        back.x = data_0203d210[idx];
        back.y = unit.y;
        back.z = data_0203d210[idx + 1];
    }
    ScaleVec3Fx12(0x6000, &back, &back);
    VEC_Subtract(&target, &back, &target);
    Ov107_PostTagUpdate((Actor *)(*state), 3, 0);
    func_ov107_020c0b90(*state, 0, *(VecFx32 *)state[2], 0);
    Ov107_MoveNodeAndRelayout((Actor *)(*state), &target);
    SetIndexedSlot(node, *(signed char *)((char *)node + 0x20), Ov283_AiFaceTarget);
}
