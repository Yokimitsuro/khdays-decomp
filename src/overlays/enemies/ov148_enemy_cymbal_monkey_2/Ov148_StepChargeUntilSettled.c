/* Per-frame step of the charge: keep steering, and end it when the timer runs out.
 *
 * Re-runs the steering helper with the stored direction at ctx+0x28 -- note that direction
 * is passed BY VALUE.  The ROM's `ldm r1, {r1, r2, r3}` is not a bulk load of three
 * separate arguments, it is mwcc putting a 12-byte struct into r1-r3, which is what the
 * calling convention does with a VecFx32.  Writing it as three int arguments compiles but
 * does not match.
 *
 * The state ends only when all three of the owner's nodes at +0x398 have gone idle (their
 * +0x38c cleared), the countdown at ctx[0x10] has been spent, and the steering helper's
 * own result is under 0x20000 -- i.e. everything has settled AND the target is close.
 * Otherwise it falls through to the keep-going tail, which re-aims at the tracked node and
 * pokes the owner with mode 3, unless the flag byte at ctx[1]+0xad says to stop.
 *
 * The node walk uses the displacement form, `(char *)*ctx + i * sizeof(int)` with +0x398
 * at the access, which is what keeps the ROM's `add r1, r3, r2, lsl #2`.  mwcc hoists the
 * `*ctx` load out of the loop by itself; doing it by hand is not needed.
 */

#include "nitro/fx_types.h"
#include "game/enemy_common.h"

extern int Ov148_BuildHeadingRotation(int *self, VecFx32 v, int flag);
extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *dst);
extern void SetIndexedSlot(int *self, int action, void *cb);
extern void Ov148_PointHeadingCheckPose(void);

void Ov148_StepChargeUntilSettled(int *self) {
    int *ctx = (int *)self[1];
    int reach;
    int i;

    reach = Ov148_BuildHeadingRotation(ctx, *(VecFx32 *)((char *)ctx + 0x28), 1);

    for (i = 0; i < 3; i++) {
        if (*(int *)(*(int *)((char *)*ctx + i * sizeof(int) + 0x398) + 0x38c) != 0) {
            break;
        }
    }

    if (i >= 3) {
        ctx[0x10] = ctx[0x10] - *(int *)(self[0] + 0x2c);
        if (ctx[0x10] <= 0) {
            ctx[0x10] = 0;
            if (reach < 0x20000) {
                *(int *)(*ctx + 0x3e8) = 0;
                SetIndexedSlot(self, *(signed char *)((char *)self + 0x20), &Ov148_PointHeadingCheckPose);
                return;
            }
        }
    }

    if (*(unsigned char *)(ctx[1] + 0xad) != 0) {
        return;
    }
    if (*(int *)(*ctx + 0x394) != 0) {
        VEC_Subtract((const VecFx32 *)(*(int *)(*ctx + 0x394) + 0x190), (const VecFx32 *)ctx[3],
                     (VecFx32 *)((char *)ctx + 0x28));
    }
    Ov107_PostTagUpdate((Actor *)(*ctx), 3, 0);
}
