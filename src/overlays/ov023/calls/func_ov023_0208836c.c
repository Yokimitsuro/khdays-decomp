/* func_ov023_0208836c -- Ov023_BuildRotation33: build a 3x3 rotation from three u16 angles:
 * the identity concatenated (MTX_Concat33) with the X, then Y, then Z rotations
 * (MTX_RotX33_ / MTX_RotY33_ / MTX_RotZ33_ from FX_SinCosTable_), each built on a fresh
 * identity. */
typedef struct MtxFx33 {
    int  a[9];                /* 0x00 */
} MtxFx33;

extern void MTX_Identity33_(MtxFx33 *pMtx);
extern void MTX_RotX33_(MtxFx33 *pMtx, int nSin, int nCos);
extern void MTX_RotY33_(MtxFx33 *pMtx, int nSin, int nCos);
extern void MTX_RotZ33_(MtxFx33 *pMtx, int nSin, int nCos);
extern void MTX_Concat33(const MtxFx33 *pA, const MtxFx33 *pB, MtxFx33 *pOut);
extern const short data_0203d210[];                                 /* FX_SinCosTable_: sin, cos pairs */

void func_ov023_0208836c(MtxFx33 *pOut, int nAngleX, int nAngleY, int nAngleZ)
{
    MtxFx33 mtx;

    MTX_Identity33_(pOut);
    MTX_Identity33_(&mtx);
    MTX_RotX33_(&mtx, data_0203d210[(nAngleX >> 4) * 2], data_0203d210[(nAngleX >> 4) * 2 + 1]);
    MTX_Concat33(pOut, &mtx, pOut);
    MTX_Identity33_(&mtx);
    MTX_RotY33_(&mtx, data_0203d210[(nAngleY >> 4) * 2], data_0203d210[(nAngleY >> 4) * 2 + 1]);
    MTX_Concat33(pOut, &mtx, pOut);
    MTX_Identity33_(&mtx);
    MTX_RotZ33_(&mtx, data_0203d210[(nAngleZ >> 4) * 2], data_0203d210[(nAngleZ >> 4) * 2 + 1]);
    MTX_Concat33(pOut, &mtx, pOut);
}
