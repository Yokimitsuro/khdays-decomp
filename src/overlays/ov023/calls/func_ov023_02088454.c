/* func_ov023_02088454 -- Ov023_RotTweenStep: advance a rotation tween (target angles +0, start
 * angles +0xc, a word at +0x18, duration +0x1c, remaining +0x20, easing mode +0x24) one frame and build its
 * 3x3 matrix (Ov023_BuildRotation33 0208836c).  The remaining count drops to at most 0; while
 * it is not 0 the blend factor is eased by mode -- 2: linear, 3: half-sine eased both ends,
 * 4: sine eased, 5: cosine -- exactly as Anim_GetBlendFactor (0202136c) does, and the angles
 * are start + (target - start) * factor; at 0 they are the target.  Returns pOut. */
typedef unsigned char  u8;
typedef unsigned short u16;

typedef struct VecFx32 {
    int  x;                   /* 0x00 */
    int  y;                   /* 0x04 */
    int  z;                   /* 0x08 */
} VecFx32;

typedef struct MtxFx33 {
    int  a[9];                /* 0x00 */
} MtxFx33;

typedef struct FxSinCos {
    short nSin;               /* 0x00 */
    short nCos;               /* 0x02 */
} FxSinCos;

typedef struct Ov023RotTween {
    VecFx32 vTarget;          /* 0x00 */
    VecFx32 vFrom;            /* 0x0c */
    int  nField18;            /* 0x18 */
    unsigned int nDuration;   /* 0x1c */
    int  nRemaining;          /* 0x20 */
    int  nMode;               /* 0x24 */
} Ov023RotTween;

extern int  FX_Inv(int nNumerator, int nDenominator);              /* the SDK divide */
extern int  func_02020400(int nNumerator, int nDenominator);        /* the 64-bit divide, low word */
extern void VEC_Subtract(const VecFx32 *pA, const VecFx32 *pB, VecFx32 *pOut);
extern MtxFx33 *func_ov023_0208836c(MtxFx33 *pOut, int nAngleX, int nAngleY, int nAngleZ); /* Ov023_BuildRotation33 */
extern const FxSinCos data_0203d210[];                              /* FX_SinCosTable_ */

MtxFx33 *func_ov023_02088454(Ov023RotTween *pTween, MtxFx33 *pOut)
{
    VecFx32 vDelta;
    int nFactor;
    int nElapsed;
    int nAngle;
    int nX;
    int nY;
    int nZ;

    if (pTween->nRemaining > 0) {
        pTween->nRemaining--;
    }
    nFactor = 0;
    if (pTween->nRemaining != 0) {
        nElapsed = pTween->nDuration - pTween->nRemaining;
        switch (pTween->nMode) {
        case 0:
        case 1:
            break;
        case 2:
            nFactor = FX_Inv(nElapsed * 0x1000, pTween->nDuration << 12);
            break;
        case 3:
            nAngle = func_02020400(nElapsed * 0x8000, pTween->nDuration) - 0x4000;
            if (nAngle < 0) {
                nAngle += 0x10000;
            }
            nFactor = (data_0203d210[nAngle >> 4].nSin + 0x1000) / 2;
            break;
        case 4:
            nAngle = func_02020400(nElapsed * 0x8000, pTween->nDuration << 1) - 0x4000;
            if (nAngle < 0) {
                nAngle += 0x10000;
            }
            nFactor = data_0203d210[nAngle >> 4].nSin + 0x1000;
            break;
        case 5:
            nAngle = func_02020400(pTween->nRemaining << 15, pTween->nDuration << 1) + 0x4000;
            if (nAngle < 0) {
                nAngle += 0x10000;
            }
            nFactor = data_0203d210[nAngle >> 4].nSin;
            break;
        }
    }
    if (pTween->nRemaining == 0) {
        nX = pTween->vTarget.x;
        nY = pTween->vTarget.y;
        nZ = pTween->vTarget.z;
    } else {
        VEC_Subtract(&pTween->vTarget, &pTween->vFrom, &vDelta);
        nX = pTween->vFrom.x + (int)(((long long)vDelta.x * nFactor + 0x800) >> 12);
        nY = pTween->vFrom.y + (int)(((long long)vDelta.y * nFactor + 0x800) >> 12);
        nZ = pTween->vFrom.z + (int)(((long long)vDelta.z * nFactor + 0x800) >> 12);
    }
    func_ov023_0208836c(pOut, (u16)nX, (u16)nY, (u16)nZ);
    return pOut;
}
