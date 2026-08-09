typedef unsigned long u32;
typedef unsigned short u16;
typedef signed short s16;
typedef signed long s32;
typedef signed long fx32;
typedef signed long long s64;
typedef int BOOL;

#define NULL ((void *)0)
#define TRUE 1
#define FALSE 0
#define FX32_SHIFT 12
#define FX32_ONE (1 << FX32_SHIFT)

#define GX_OAM_ATTR01_Y_SHIFT 0
#define GX_OAM_ATTR01_Y_MASK 0x000000ff
#define GX_OAM_ATTR01_RSENABLE_SHIFT 8
#define GX_OAM_ATTR01_RSENABLE_MASK 0x00000300
#define GX_OAM_ATTR01_SHAPE_SHIFT 14
#define GX_OAM_ATTR01_SHAPE_MASK 0x0000c000
#define GX_OAM_ATTR01_X_SHIFT 16
#define GX_OAM_ATTR01_X_MASK 0x01ff0000
#define GX_OAM_ATTR01_RS_SHIFT 25
#define GX_OAM_ATTR01_RS_MASK 0x3e000000
#define GX_OAM_ATTR01_FLIP_MASK 0x30000000
#define GX_OAM_ATTR01_SIZE_SHIFT 30
#define GX_OAM_ATTR01_SIZE_MASK 0xc0000000

typedef enum GXOamEffect {
    GX_OAM_EFFECT_NONE = 0,
    GX_OAM_EFFECT_AFFINE = 0x100,
    GX_OAM_EFFECT_NODISPLAY = 0x200,
    GX_OAM_EFFECT_AFFINE_DOUBLE = 0x300
} GXOamEffect;

typedef enum GXOamShape {
    GX_OAM_SHAPE_8x8 = 0
} GXOamShape;

typedef struct GXOamAttr {
    union {
        u32 attr01;
        struct {
            u16 attr0;
            u16 attr1;
        };
    };
    u16 attr2;
    u16 _3;
} GXOamAttr;

typedef struct MtxFx22 {
    fx32 _00;
    fx32 _01;
    fx32 _10;
    fx32 _11;
} MtxFx22;

typedef struct NNSG2dFVec2 {
    fx32 x;
    fx32 y;
} NNSG2dFVec2;

typedef struct NNSG2dCellOAMAttrData {
    u16 attr0;
    u16 attr1;
    u16 attr2;
} NNSG2dCellOAMAttrData;

typedef struct NNSG2dCellData {
    u16 numOAMAttrs;
    u16 cellAttr;
    NNSG2dCellOAMAttrData *pOamAttrArray;
} NNSG2dCellData;

extern const u16 data_020419dc[3][4];
extern const u16 data_020419c4[3][4];

inline void NNS_G2dCopyCellAsOamAttr(const NNSG2dCellData *pCell,
                                     u16 idx,
                                     GXOamAttr *pDst)
{
    const NNSG2dCellOAMAttrData *pSrc = pCell->pOamAttrArray + idx;
    pDst->attr0 = pSrc->attr0;
    pDst->attr1 = pSrc->attr1;
    pDst->attr2 = pSrc->attr2;
}

inline s16 NNSi_G2dGetOamX(const GXOamAttr *oamAttr)
{
    s16 val =
        (s16)((GX_OAM_ATTR01_X_MASK & oamAttr->attr01) >>
              GX_OAM_ATTR01_X_SHIFT);
    return val;
}

inline s16 NNSi_G2dGetOamY(const GXOamAttr *oamAttr)
{
    s16 val =
        (s16)((GX_OAM_ATTR01_Y_MASK & oamAttr->attr01) >>
              GX_OAM_ATTR01_Y_SHIFT);
    return val;
}

inline s16 NNS_G2dRepeatXinCellSpace(s16 srcX)
{
    if (srcX > 255) {
        srcX |= 0xff00;
    }
    return srcX;
}

inline s16 NNS_G2dRepeatYinCellSpace(s16 srcY)
{
    if (srcY > 127) {
        srcY |= 0xff00;
    }
    return srcY;
}

inline void NNS_G2dGetOamTransFx32(const GXOamAttr *pOam,
                                   NNSG2dFVec2 *pRet)
{
    pRet->x =
        (fx32)(NNS_G2dRepeatXinCellSpace(NNSi_G2dGetOamX(pOam)) * FX32_ONE);
    pRet->y =
        (fx32)(NNS_G2dRepeatYinCellSpace(NNSi_G2dGetOamY(pOam)) * FX32_ONE);
}

inline GXOamEffect G2_GetOBJEffect(const GXOamAttr *oam)
{
    GXOamEffect effect;
    effect = (GXOamEffect)(oam->attr01 & GX_OAM_ATTR01_RSENABLE_MASK);
    if (effect == GX_OAM_EFFECT_AFFINE ||
        effect == GX_OAM_EFFECT_AFFINE_DOUBLE) {
        return effect;
    }
    return (GXOamEffect)(effect | (oam->attr01 & GX_OAM_ATTR01_FLIP_MASK));
}

inline GXOamShape NNS_G2dGetOAMSize(const GXOamAttr *oamAttr)
{
    const GXOamShape result =
        (GXOamShape)((GX_OAM_ATTR01_SHAPE_MASK |
                      GX_OAM_ATTR01_SIZE_MASK) & oamAttr->attr01);
    return result;
}

inline int NNS_G2dGetOamSizeX(const GXOamShape *oamShape)
{
    return data_020419dc[(*oamShape & GX_OAM_ATTR01_SHAPE_MASK) >>
                         GX_OAM_ATTR01_SHAPE_SHIFT]
                        [(*oamShape & GX_OAM_ATTR01_SIZE_MASK) >>
                         GX_OAM_ATTR01_SIZE_SHIFT];
}

inline int NNS_G2dGetOamSizeY(const GXOamShape *oamShape)
{
    return data_020419c4[(*oamShape & GX_OAM_ATTR01_SHAPE_MASK) >>
                         GX_OAM_ATTR01_SHAPE_SHIFT]
                        [(*oamShape & GX_OAM_ATTR01_SIZE_MASK) >>
                         GX_OAM_ATTR01_SIZE_SHIFT];
}

inline void NNSi_G2dRemovePositionAdjustmentFromDoubleAffineOBJ(
    const GXOamAttr *pOam,
    NNSG2dFVec2 *pV)
{
    if (G2_GetOBJEffect(pOam) == GX_OAM_EFFECT_AFFINE_DOUBLE) {
        const GXOamShape oamShape = NNS_G2dGetOAMSize(pOam);
        const int halfW = NNS_G2dGetOamSizeX(&oamShape) << (FX32_SHIFT - 1);
        const int halfH = NNS_G2dGetOamSizeY(&oamShape) << (FX32_SHIFT - 1);
        pV->x += halfW;
        pV->y += halfH;
    }
}

inline void MulMtx22(const MtxFx22 *m,
                     const NNSG2dFVec2 *pSrc,
                     NNSG2dFVec2 *pDst)
{
    NNSG2dFVec2 temp;
    NNSG2dFVec2 *pV = pDst;
    if (pDst == pSrc) {
        pV = &temp;
    }
    pV->x = (fx32)((((s64)(m->_00) * pSrc->x + 0x800LL) +
                     ((s64)(m->_10) * pSrc->y + 0x800LL)) >>
                    FX32_SHIFT);
    pV->y = (fx32)((((s64)(m->_01) * pSrc->x + 0x800LL) +
                     ((s64)(m->_11) * pSrc->y + 0x800LL)) >>
                    FX32_SHIFT);
    if (pV == &temp) {
        *pDst = temp;
    }
}

static inline void G2_SetOBJEffect(GXOamAttr *oam,
                                   GXOamEffect effect,
                                   int rsParam)
{
    if (GX_OAM_EFFECT_AFFINE != effect &&
        GX_OAM_EFFECT_AFFINE_DOUBLE != effect) {
        oam->attr01 =
            ((oam->attr01 &
              ~(GX_OAM_ATTR01_RSENABLE_MASK | GX_OAM_ATTR01_RS_MASK)) |
             effect);
    } else {
        oam->attr01 =
            ((oam->attr01 &
              ~(GX_OAM_ATTR01_RSENABLE_MASK | GX_OAM_ATTR01_RS_MASK)) |
             effect | (rsParam << GX_OAM_ATTR01_RS_SHIFT));
    }
}

inline void NNSi_G2dAdjustDifferenceOfRotateOrientation(
    const GXOamAttr *pOam,
    const MtxFx22 *pM,
    NNSG2dFVec2 *pV,
    BOOL adjustDoubleAffine)
{
    const GXOamShape oamShape = NNS_G2dGetOAMSize(pOam);
    const int halfW = NNS_G2dGetOamSizeX(&oamShape) >> 1;
    const int halfH = NNS_G2dGetOamSizeY(&oamShape) >> 1;
    pV->x += -(halfW << FX32_SHIFT) + pM->_00 * halfW + pM->_10 * halfH;
    pV->y += -(halfH << FX32_SHIFT) + pM->_01 * halfW + pM->_11 * halfH;
    if (adjustDoubleAffine) {
        pV->x -= halfW << FX32_SHIFT;
        pV->y -= halfH << FX32_SHIFT;
    }
}

static inline void G2_SetOBJPosition(GXOamAttr *oam, int x, int y)
{
    oam->attr01 =
        ((oam->attr01 & ~(GX_OAM_ATTR01_Y_MASK | GX_OAM_ATTR01_X_MASK)) |
         (y & GX_OAM_ATTR01_Y_MASK) |
         ((x & (GX_OAM_ATTR01_X_MASK >> GX_OAM_ATTR01_X_SHIFT)) <<
          GX_OAM_ATTR01_X_SHIFT));
}

u16 func_020124e0(GXOamAttr *pDstOams,
                  u16 numDstOam,
                  const NNSG2dCellData *pCell,
                  const MtxFx22 *pMtxSR,
                  const NNSG2dFVec2 *pBaseTrans,
                  u16 affineIndex,
                  BOOL bDoubleAffine)
{
    u16 i = 0;
    NNSG2dFVec2 objTrans;
    GXOamAttr *pDstOam = NULL;
    const u16 numOBJ =
        (numDstOam < pCell->numOAMAttrs) ? numDstOam : pCell->numOAMAttrs;

    for (i = 0; i < numOBJ; i++) {
        pDstOam = &pDstOams[i];
        NNS_G2dCopyCellAsOamAttr(pCell, i, pDstOam);
        if (pMtxSR != NULL || pBaseTrans != NULL) {
            NNS_G2dGetOamTransFx32(pDstOam, &objTrans);
            if (pMtxSR != NULL) {
                NNSi_G2dRemovePositionAdjustmentFromDoubleAffineOBJ(pDstOam,
                                                                    &objTrans);
                {
                    const GXOamEffect effectTypeAfter =
                        (bDoubleAffine) ? GX_OAM_EFFECT_AFFINE_DOUBLE
                                        : GX_OAM_EFFECT_AFFINE;
                    const BOOL bShouldAdjust =
                        (effectTypeAfter == GX_OAM_EFFECT_AFFINE_DOUBLE);
                    MulMtx22(pMtxSR, &objTrans, &objTrans);
                    G2_SetOBJEffect(pDstOam, effectTypeAfter, affineIndex);
                    NNSi_G2dAdjustDifferenceOfRotateOrientation(
                        pDstOam, pMtxSR, &objTrans, bShouldAdjust);
                }
            }
            if (pBaseTrans != NULL) {
                objTrans.x += pBaseTrans->x;
                objTrans.y += pBaseTrans->y;
            }
            G2_SetOBJPosition(pDstOam,
                              (objTrans.x + 0x800) >> FX32_SHIFT,
                              (objTrans.y + 0x800) >> FX32_SHIFT);
        }
    }
    return numOBJ;
}
