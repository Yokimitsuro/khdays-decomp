/* Ov274_AiWaitThenTarget -- accumulate time and, once past the threshold, re-face and hand on.
 * The elapsed counter at +0x24 always advances by the caller's per-tick amount (+0x2c of self[0])
 * and is always stored back; below 0x6ee that is all that happens.
 * Past it, the target is re-acquired and, if there is one, the bearing from the cached point
 * (+0x8) to the target's +0x74 is written to BOTH +0x40 and +0x44. Flags 0x82 are then cleared
 * from the high byte of the owner's +0x60 halfword, the owner is retuned (mode 0), and the action
 * dispatched with Ov274_AiStep_QueueAction2OnFlag0cClear.
 *
 * The +0x60 update uses the BITFIELD form on purpose, unlike Ov206_EnterMoveState's explicit
 * extract/reassemble. Both are in the ROM and they are not interchangeable: the bitfield form
 * emits a redundant `lsl #0x10 ; lsr #0x10` truncation, which this function HAS and 020cd464 does
 * not. Match the presence of that pair to pick the form -- see codegen-cracks.md. */

#include "nitro/fx_types.h"
#include "game/enemy_common.h"

typedef struct {
    unsigned short lo : 8;
    unsigned short hi : 8;
} Hw60;

extern int Ov107_FindNearestObject(int owner, int kind);
extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern fx16 FX_Atan2(int x, int z);
extern void SetIndexedSlot(int self, int action, void (*cb)(void));
extern void Ov274_AiStep_QueueAction2OnFlag0cClear(void);

void Ov274_AiWaitThenTarget(int self) {
    int *ctx;
    VecFx32 v;
    int target;

    ctx = *(int **)(self + 4);
    ctx[9] = ctx[9] + *(int *)(*(int *)self + 0x2c);
    if (ctx[9] < 0x6ee) {
        return;
    }

    target = Ov107_FindNearestObject(ctx[0], 0);
    ctx[4] = target;
    if (target != 0) {
        VEC_Subtract((const VecFx32 *)(target + 0x74), (const VecFx32 *)ctx[2], &v);
        ctx[0x11] = FX_Atan2(v.x, v.z);
        ctx[0x10] = ctx[0x11];
    }

    ((Hw60 *)(ctx[0] + 0x60))->hi &= ~0x82;
    Ov107_PostTagUpdate((Actor *)ctx[0], 0, 0);
    SetIndexedSlot(self, *(signed char *)(self + 0x20), Ov274_AiStep_QueueAction2OnFlag0cClear);
}
