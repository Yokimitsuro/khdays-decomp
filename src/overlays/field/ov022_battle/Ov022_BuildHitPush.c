/* Ov022_BuildHitPush -- work out which way a hit throws what it struck.
 *
 * The push always keeps the hit's own rise. Where it points depends on the hit's
 * mode: mode 0 sends it along the striker's facing, flattened and scaled to the
 * length the hit carries; mode 1 sends it away from the striker, turning the
 * hit's own vector by the angle from the target back to the striker, sampled
 * from the shared sine table. Any other mode leaves the push at whatever the
 * caller's buffer already held.
 */

#include "nitro/types.h"
#include "nitro/fx_types.h"

struct MtxFx33 {
    int m[9];
};

struct SweepHit {
    u8 pad00[0x14];
    VecFx32 vecPush;          /* 0x14 */
    int nMode;                       /* 0x20 */
};

/* Two signed halfwords per angle step: the sine first, then the cosine. */
extern short data_0203d210[];

extern int VEC_Mag(VecFx32 *pVec);
extern void VEC_Normalize(VecFx32 *pIn, VecFx32 *pOut);
extern void ScaleVec3Fx12(int nScale, VecFx32 *pIn, VecFx32 *pOut);
extern void VEC_Subtract(VecFx32 *pA, VecFx32 *pB,
                         VecFx32 *pOut);
extern short FX_Atan2Idx(int x, int y);
extern void MTX_RotY33_(struct MtxFx33 *pMtx, int nSin, int nCos);
extern void MTX_MultVec33(VecFx32 *pIn, struct MtxFx33 *pMtx,
                          VecFx32 *pOut);

#define HIT_ALONG_FACING 0
#define HIT_AWAY_FROM_STRIKER 1

void Ov022_BuildHitPush(VecFx32 *pOut, struct SweepHit *pHit,
                         VecFx32 *pAt, VecFx32 *pFrom,
                         VecFx32 *pFacing)
{
    VecFx32 vecAim;
    VecFx32 vecPush;
    VecFx32 vecOut;
    struct MtxFx33 mtx;
    short nAngle;
    int nIndex;

    vecOut.y = pHit->vecPush.y;
    switch (pHit->nMode) {
    case HIT_ALONG_FACING:
        vecAim = *pFacing;
        vecAim.y = 0;
        if (VEC_Mag(&vecAim) != 0) {
            VEC_Normalize(&vecAim, &vecAim);
        }
        vecPush = pHit->vecPush;
        vecPush.y = 0;
        ScaleVec3Fx12(VEC_Mag(&vecPush), &vecAim, &vecAim);
        vecOut.x = vecAim.x;
        vecOut.z = vecAim.z;
        break;
    case HIT_AWAY_FROM_STRIKER:
        VEC_Subtract(pAt, pFrom, &vecAim);
        vecPush = pHit->vecPush;
        vecPush.y = 0;
        nAngle = FX_Atan2Idx(-vecAim.x, -vecAim.z);
        nIndex = nAngle >> 4;
        MTX_RotY33_(&mtx, data_0203d210[nIndex * 2],
                    data_0203d210[nIndex * 2 + 1]);
        MTX_MultVec33(&vecPush, &mtx, &vecPush);
        vecOut.x = vecPush.x;
        vecOut.z = vecPush.z;
        break;
    }
    *pOut = vecOut;
}
