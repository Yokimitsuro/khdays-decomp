/* Ov159_AiEnterApproach -- face the target and arm the timed follow-up.
 * Without a target the owner drops to state 2 (+0x1c7) and the action is dispatched with no
 * continuation. With one, the offset from the reference point (+0x4c) to the target (+0x190) is
 * taken, FLATTENED to the ground plane (y forced to 0) and normalised, and its bearing cached at
 * +0x10. Flag 8 is set on the owner's +0x1ae halfword, the follow-up delay at +0x14 is computed
 * from the caller's per-tick amount, and the action is dispatched with Ov159_ArmMovePhase2.
 *
 * The delay is `x * 30 / 5` -- kept unfolded on purpose. mwcc emits mul #0x1e then the 0x66666667
 * magic with asr #1 (that shift is /5, not the /10 you get with asr #2); hand-folding it to `x * 6`
 * would change behaviour, since the x*30 intermediate can overflow. */

#include "nitro/fx_types.h"

extern int Ov107_FindNearestObject(int owner, int kind);
extern void SetIndexedSlot(int self, int action, void (*cb)(void));
extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern int VEC_Normalize(const VecFx32 *v, VecFx32 *out);
extern fx16 FX_Atan2(int x, int z);
extern void Ov159_ArmMovePhase2(void);

void Ov159_AiEnterApproach(int self) {
    int *ctx;
    VecFx32 v;
    int target;

    ctx = *(int **)(self + 4);
    target = Ov107_FindNearestObject(ctx[0], 0);
    ctx[2] = target;
    if (target == 0) {
        *(unsigned char *)(ctx[0] + 0x1c7) = 2;
        SetIndexedSlot(self, *(signed char *)(self + 0x20), 0);
        return;
    }

    VEC_Subtract((const VecFx32 *)(target + 0x190), (const VecFx32 *)ctx[0x13], &v);
    v.y = 0;
    VEC_Normalize(&v, &v);
    ctx[4] = FX_Atan2(v.x, v.z);

    *(unsigned short *)(ctx[0] + 0x1ae) |= 8;
    ctx[5] = *(int *)(*(int *)self + 0x2c) * 30 / 5;
    SetIndexedSlot(self, *(signed char *)(self + 0x20), Ov159_ArmMovePhase2);
}
