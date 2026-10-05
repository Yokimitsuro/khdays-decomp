/*
 * Acquire a target and face it. Ask ov107_020cab14 for one and cache it at ctx+0x5a8;
 * with none, latch phase 2 and dispatch. Otherwise measure the vector from the anchor
 * (ctx[2]) to the target (target+0x190), build the unit facing {sin, 0, cos} from the
 * STORED heading (ctx[0xd]) into ctx+0x28, scale it by 0xa00, kick animation 0xe, clear
 * the phase timer and the two one-shot bytes, and chain to the next state.
 *
 * Two faithful game quirks, preserved on purpose:
 *  - The freshly measured atan2 (FX_Atan2(d.x, d.z)) is COMPUTED AND DISCARDED; the
 *    facing is rebuilt from the stored heading instead. Same shape as ov231_020cdd3c's
 *    discarded VEC_DotProduct -- a likely original bug, reproduced, not fixed.
 *
 * The match turns on `const short data_0203d210[]`: without const, mwcc must assume the
 * stores through ctx could alias the table, so it pins the second table load after the
 * two stores (permuted schedule, still 292 B). const is the aliasing fact that lets both
 * table loads issue before the stores. One of a 3-member family (family).
 */

#include "nitro/fx_types.h"
#include "game/enemy_common.h"

extern int *Ov107_FindNearestObject(int a, int b);
extern int VEC_Subtract(void *a, void *b, void *out);
extern fx16 FX_Atan2(int a, int b);
extern void ScaleVec3Fx12(int s, VecFx32 *v, VecFx32 *out);
extern void SetIndexedSlot(void *self, int idx, void *cb);
extern void Ov212_ChargeAttackTick(void);
extern const short data_0203d210[];

#define ANG2IDX(a) ((unsigned short)(((long long)(a) * 0x28be60db9391LL + 0x80000000000LL) >> 44) >> 4)

void Ov212_EnterFaceTargetB(void *self) {
    int *ctx = *(int **)((char *)self + 4);
    VecFx32 d;
    unsigned int idx;
    int tgt;

    *(int *)(*ctx + 0x5a8) = (int)Ov107_FindNearestObject(*ctx, 0);
    tgt = *(int *)(*ctx + 0x5a8);
    if (tgt == 0) {
        *(char *)(*ctx + 0x1c7) = 2;
        SetIndexedSlot(self, *(signed char *)((char *)self + 0x20), 0);
        return;
    }
    VEC_Subtract((char *)tgt + 0x190, (void *)ctx[2], &d);
    FX_Atan2(d.x, d.z);
    idx = ANG2IDX(ctx[0xd]);
    ctx[0xa] = data_0203d210[idx * 2];
    ctx[0xb] = 0;
    ctx[0xc] = data_0203d210[idx * 2 + 1];
    ScaleVec3Fx12(0xa00, (VecFx32 *)(ctx + 0xa), (VecFx32 *)(ctx + 0xa));
    Ov107_PostTagUpdate((Actor *)(*ctx), 0xe, 0);
    ctx[0x10] = 0;
    *(char *)((char *)ctx + 0x5a) = 0;
    *(char *)((char *)ctx + 0x5b) = 0;
    SetIndexedSlot(self, *(signed char *)((char *)self + 0x20), Ov212_ChargeAttackTick);
}
