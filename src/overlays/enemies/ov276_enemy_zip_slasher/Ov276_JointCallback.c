/* Joint callback of the ov276 enemy: when the render object reports the +0x3b4 joint, its
 * translation becomes that of the +0x3c0 transform and the two +0x3ec transforms are placed
 * 0x433 and 0x866 ahead of it along the actor's +0xa0 orientation; when it reports the +0x3b8
 * joint, its translation becomes that of the +0x444 transform. */

#include "nitro/fx_types.h"
#include "game/engine.h"

struct MtxFx43 { int m[9]; VecFx32 t; };

extern int NNS_G3dGetResultMtx(void *renderObj, struct MtxFx43 *out, void *b, int joint);
extern void Srt_SetTranslation(void *transform, VecFx32 *pos);
extern void VEC_Add(VecFx32 *a, VecFx32 *b, VecFx32 *d);

void Ov276_JointCallback(int item, int actor)
{
    struct MtxFx43 mtx;
    VecFx32 v;
    int i;

    if (NNS_G3dGetResultMtx((void *)(*(int *)(item + 0x88) + 0x20), &mtx, 0, *(int *)(actor + 0x3b4)) != 0) {
        Srt_SetTranslation((void *)(actor + 0x3c0), &mtx.t);
        for (i = 0; i < 2; i++) {
            v.x = 0;
            v.y = 0;
            v.z = i == 0 ? 0x866 / 2 : 0x866;
            Vec3TransformViaTempMtx(&v, (void *)(actor + 0xa0), &v);
            VEC_Add(&v, &mtx.t, &v);
            Srt_SetTranslation((void *)(actor + 0x3ec + i * 0x2c), &v);
        }
    }
    if (NNS_G3dGetResultMtx((void *)(*(int *)(item + 0x88) + 0x20), &mtx, 0, *(int *)(actor + 0x3b8)) != 0) {
        Srt_SetTranslation((void *)(actor + 0x444), &mtx.t);
    }
}
