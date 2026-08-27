typedef signed short s16;

typedef struct VecFx32 {
    int x;
    int y;
    int z;
} VecFx32;

typedef struct MtxFx33 {
    int a[9];
} MtxFx33;

/* data_ov002_0207ef80 and data_ov002_0207ef80_offsets are the SAME address under
 * two names, and that is required rather than cosmetic: the ROM's literal pool
 * holds 0x0207ef80 in two separate entries, and mwcc emits two only for two
 * distinct symbols.  One view flattens entry 1, the other reads the table. */
extern VecFx32 data_ov002_0207ef80[];
extern VecFx32 data_ov002_0207ef80_offsets[];
extern s16 data_0203d210[];             /* kSinCosTable */

extern int func_01fffe14(void);         /* the local peer */
extern int func_02020a9c(void);
extern void MTX_Identity33_(MtxFx33 *pMtx);
extern void MTX_RotY33_(MtxFx33 *pMtx, int nSin, int nCos);
extern void MTX_MultVec33(const VecFx32 *pVec, const MtxFx33 *pMtx,
                          VecFx32 *pDst);
extern void VEC_Add(const VecFx32 *pA, const VecFx32 *pB, VecFx32 *pDst);

/* Spreads one peer away from a shared place so several do not land on top of
   each other.  An nIndex of -1 means the local peer.  The slot's offset is
   rotated about Y by nAngle and added to pPlace. */
void func_ov002_02069878(const VecFx32 *pPlace, int nAngle, int nIndex,
                         VecFx32 *pOut)
{
    MtxFx33 mtx;
    VecFx32 vOffset;

    if (nIndex == -1) {
        nIndex = func_01fffe14();
    }
    if (func_02020a9c() == 0x2a) {
        data_ov002_0207ef80[1].x = 0;
        data_ov002_0207ef80[1].z = 0;
    }

    vOffset = data_ov002_0207ef80_offsets[nIndex];
    MTX_Identity33_(&mtx);
    MTX_RotY33_(&mtx, data_0203d210[(nAngle >> 4) * 2],
                data_0203d210[(nAngle >> 4) * 2 + 1]);
    MTX_MultVec33(&vOffset, &mtx, &vOffset);
    VEC_Add(&vOffset, pPlace, pOut);
}
