/* Syncs the subitem pose to a model joint (ov216/217 variant of ov214/215/264: scale 1.25, offset 1.5, copy rescaled).
 *
 * Reads the world transform of joint id self+0x438 out of the model at
 * scene+0x88+0x20 with the geometry engine helper at 02016320, which reads back
 * the 3x3 vector matrix and then its translation row, so the single out buffer
 * is a 48 byte MtxFx43. When the read succeeds it takes that translation,
 * subtracts 0x1800 of the current camera vector at +0x7c, stores the result as
 * the translation of the SRT at self+0x3f4 with uniform scale 0x1400, and
 * publishes the raw joint translation to the two list nodes at self+0x3ac and
 * self+0x3b0.
 *
 * The 44 byte pose block copy from self+0xa0 to self+0x3c8 runs unconditionally,
 * which is why it sits outside the guard; the copy is then rescaled to 0x199a (1.6).
 */

#include "nitro/fx_types.h"
#include "game/enemy_common.h"

typedef struct { int m[9]; } MtxFx33;

typedef struct {
    MtxFx33 rotation;
    VecFx32 translation;
} MtxFx43;

typedef struct { int w[11]; } PoseBlock;

extern int NNS_G3dGetResultMtx(void *model, MtxFx43 *out, void *opt, unsigned int jointId);
extern void SrtTransform_SetIdentity(void *srt);
extern void ScaleVec3Fx12(int scale, const VecFx32 *src, VecFx32 *dst);
extern void VEC_Add(const VecFx32 *a, const VecFx32 *b, VecFx32 *dst);
extern void Srt_SetTranslation(void *srt, const VecFx32 *translation);
extern void Srt_SetScaleUniform(void *srt, int scale);

void Ov217_SyncSubitemPoseToJoint(int *scene, char *self)
{
    MtxFx43 jointXfm;
    VecFx32 position;
    VecFx32 cameraOffset;

    if (NNS_G3dGetResultMtx((char *)scene[0x22] + 0x20, &jointXfm, 0,
                      *(unsigned int *)(self + 0x438)) != 0) {
        position = jointXfm.translation;
        SrtTransform_SetIdentity(self + 0x3f4);
        ScaleVec3Fx12(-0x1800,
                      (const VecFx32 *)(*(char **)Ov107_GetActorManager() + 0x7c),
                      &cameraOffset);
        VEC_Add(&position, &cameraOffset, &position);
        Srt_SetTranslation(self + 0x3f4, &position);
        Srt_SetScaleUniform(self + 0x3f4, 0x1400);
        Srt_SetTranslation(*(char **)*(char **)(self + 0x3ac) + 0x10, &jointXfm.translation);
        Srt_SetTranslation(*(char **)(self + 0x3b0) + 0x10, &jointXfm.translation);
    }
    *(PoseBlock *)(self + 0x3c8) = *(PoseBlock *)(self + 0xa0);
    Srt_SetScaleUniform(self + 0x3c8, 0x199a);
}
