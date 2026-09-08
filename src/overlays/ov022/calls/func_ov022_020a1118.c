/* Ov022_BuildHitPush -- work out which way a hit throws what it struck.
 *
 * The push always keeps the hit's own rise. Where it points depends on the hit's
 * mode: mode 0 sends it along the striker's facing, flattened and scaled to the
 * length the hit carries; mode 1 sends it away from the striker, turning the
 * hit's own vector by the angle from the target back to the striker, sampled
 * from the shared sine table. Any other mode leaves the push at whatever the
 * caller's buffer already held.
 */

typedef unsigned char u8;

struct VecFx32 {
    int x;
    int y;
    int z;
};

struct MtxFx33 {
    int m[9];
};

struct SweepHit {
    u8 pad00[0x14];
    struct VecFx32 vecPush;          /* 0x14 */
    int nMode;                       /* 0x20 */
};

/* Two signed halfwords per angle step: the sine first, then the cosine. */
extern short data_0203d210[];

extern int VEC_Mag(struct VecFx32 *pVec);
extern void func_01ff8d18(struct VecFx32 *pIn, struct VecFx32 *pOut);
extern void func_01ffa724(int nScale, struct VecFx32 *pIn, struct VecFx32 *pOut);
extern void VEC_Subtract(struct VecFx32 *pA, struct VecFx32 *pB,
                         struct VecFx32 *pOut);
extern short FX_Atan2(int x, int y);
extern void MTX_RotY33_(struct MtxFx33 *pMtx, int nSin, int nCos);
extern void MTX_MultVec33(struct VecFx32 *pIn, struct MtxFx33 *pMtx,
                          struct VecFx32 *pOut);

#define HIT_ALONG_FACING 0
#define HIT_AWAY_FROM_STRIKER 1

void func_ov022_020a1118(struct VecFx32 *pOut, struct SweepHit *pHit,
                         struct VecFx32 *pAt, struct VecFx32 *pFrom,
                         struct VecFx32 *pFacing)
{
    struct VecFx32 vecAim;
    struct VecFx32 vecPush;
    struct VecFx32 vecOut;
    struct MtxFx33 mtx;
    short nAngle;
    int nIndex;

    vecOut.y = pHit->vecPush.y;
    switch (pHit->nMode) {
    case HIT_ALONG_FACING:
        vecAim = *pFacing;
        vecAim.y = 0;
        if (VEC_Mag(&vecAim) != 0) {
            func_01ff8d18(&vecAim, &vecAim);
        }
        vecPush = pHit->vecPush;
        vecPush.y = 0;
        func_01ffa724(VEC_Mag(&vecPush), &vecAim, &vecAim);
        vecOut.x = vecAim.x;
        vecOut.z = vecAim.z;
        break;
    case HIT_AWAY_FROM_STRIKER:
        VEC_Subtract(pAt, pFrom, &vecAim);
        vecPush = pHit->vecPush;
        vecPush.y = 0;
        nAngle = FX_Atan2(-vecAim.x, -vecAim.z);
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
