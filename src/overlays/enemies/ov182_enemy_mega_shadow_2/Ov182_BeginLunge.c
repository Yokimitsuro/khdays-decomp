/* Acquire the target and set up the charge: with no target, latch entry-anim 2
 * and dispatch null. Otherwise take the distance the query wrote to the stack,
 * subtract both bodies' radii to get the gap, work out the approach speed from
 * the scene rate (x30/5), aim at the target, build the orientation matrix and
 * scale it, and -- unless the abort byte is up -- start animation 3 and hand
 * over to the charge handler. */

#include "nitro/fx_types.h"
#include "game/enemy_common.h"
#include "game/engine.h"

extern int Ov107_FindNearestObject(int owner, int *out);
extern void SetIndexedSlot(void *self, int index, void *handler);
extern int FX_Sqrt(int x);
extern void VEC_Subtract(void *a, void *b, VecFx32 *out);
extern fx16 FX_Atan2(int dx, int dz);
extern void ScaleVec3Fx12(int scale, void *dst, void *src);
extern const int data_02042258[];
extern void Ov182_AiStep_QueueAction2OnFlag0cClear(void);

void Ov182_BeginLunge(int *self) {
    int *obj = (int *)self[1];
    int gap;
    VecFx32 delta;
    int me;
    int target;

    target = obj[4] = Ov107_FindNearestObject(obj[0], &gap);

    if (target == 0) {
        *(unsigned char *)(obj[0] + 0x1c7) = 2;
        SetIndexedSlot(self, *(signed char *)((char *)self + 0x20), 0);
        return;
    }

    {
        me = obj[0];

        gap = FX_Sqrt(gap) - (*(int *)(target + 0x80) + *(int *)(me + 0x80));
    }

    obj[8] = *(int *)(self[0] + 0x2c) * 30 / 10;

    VEC_Subtract((void *)(obj[4] + 0x74), (void *)obj[2], &delta);
    obj[6] = FX_Atan2(delta.x, delta.z);

    Vec3TransformViaTempMtx((char *)obj + 0x54, (void *)(obj[0] + 0xa0), data_02042258);
    ScaleVec3Fx12(0x100, (char *)obj + 0x54, (char *)obj + 0x54);

    if (*(unsigned char *)obj[3] != 0) {
        return;
    }

    Ov107_PostTagUpdate((Actor *)obj[0], 4, 0);
    SetIndexedSlot(self, *(signed char *)((char *)self + 0x20), Ov182_AiStep_QueueAction2OnFlag0cClear);
}
