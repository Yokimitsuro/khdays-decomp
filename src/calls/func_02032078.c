/* func_02032078 -- write a display object's cell into OAM, MAIN. Skipped unless the object is
 * visible (bit 0 of +0x78) and both scales (+0x84/+0x88) are non-zero. A scale below 1.0 needs
 * an affine entry; a scale above 1.0 or any rotation (cos +0x7c != 1.0 or sin +0x80 != 0) needs
 * a double-size one. For affine objects the rotation is scaled for the cell layout, its inverse
 * scaled by 1/scale is registered as an OBJ affine parameter (func_020319fc), and the cell is
 * expanded at +0xc through NNS_G2dMakeCellToOams into a local 128-entry OAM buffer that
 * func_02031f2c hands to the renderer with the parameter index. */
typedef unsigned short u16;
typedef unsigned int u32;
typedef int fx32;
typedef int BOOL;

typedef struct { fx32 _00, _01, _10, _11; } MtxFx22;
typedef struct { fx32 x, y; } NNSG2dFVec2;
typedef struct { u32 attr01; u16 attr2; u16 _3; } GXOamAttr;
typedef struct NNSG2dCellData NNSG2dCellData;

struct DispObjFlags { unsigned int visible : 1; };

typedef struct DispObj {
    char pad00[0xc];
    NNSG2dFVec2 pos;                    /* +0x0c */
    char pad14[0x44 - 0x14];
    const NNSG2dCellData *pCell;        /* +0x44 */
    char pad48[0x78 - 0x48];
    struct DispObjFlags flags;          /* +0x78 */
    fx32 rotCos;                        /* +0x7c */
    fx32 rotSin;                        /* +0x80 */
    fx32 scaleX;                        /* +0x84 */
    fx32 scaleY;                        /* +0x88 */
} DispObj;

extern void MTX_Rot22_(MtxFx22 *pDst, fx32 sinVal, fx32 cosVal);
extern void MI_CpuCopy8(const void *src, void *dest, u32 size);
extern void MTX_ScaleApply22(const MtxFx22 *src, MtxFx22 *dst, fx32 x, fx32 y);
extern fx32 FX_Inv_0x01ff8a40(fx32 v);
extern int func_020319fc(void *base, MtxFx22 *pMtx);
extern u16 func_020124e0(GXOamAttr *pDstOams, u16 numDstOam, const NNSG2dCellData *pCell,
                         const MtxFx22 *pMtxSR, const NNSG2dFVec2 *pBaseTrans, u16 affineIndex,
                         BOOL bDoubleAffine);   /* NNS_G2dMakeCellToOams */
extern void func_02031f2c(void *base, DispObj *obj, GXOamAttr *pOams, u16 numOams, int affineIndex);

void func_02032078(void *base, DispObj *obj)
{
    BOOL bAffine = 0;
    BOOL bDouble = 0;
    fx32 sx = obj->scaleX;
    fx32 sy = obj->scaleY;
    int affineIndex;
    MtxFx22 *pMtx;
    MtxFx22 mtxSR;
    MtxFx22 mtxInv;
    GXOamAttr oams[128];

    if (!obj->flags.visible) {
        return;
    }
    if (sx == 0 || sy == 0) {
        return;
    }
    if (sx < 0x1000 || sy < 0x1000) {
        bAffine = 1;
    }
    if (sx > 0x1000 || sy > 0x1000) {
        bDouble = bAffine = 1;
    }
    if (obj->rotCos != 0x1000 || obj->rotSin != 0) {
        bDouble = bAffine = 1;
    }
    if (bAffine) {
        MTX_Rot22_(&mtxSR, obj->rotSin, obj->rotCos);
        MI_CpuCopy8(&mtxSR, &mtxInv, sizeof(MtxFx22));
        MTX_ScaleApply22(&mtxSR, &mtxSR, sx, sy);
        MTX_ScaleApply22(&mtxInv, &mtxInv, FX_Inv_0x01ff8a40(sx), FX_Inv_0x01ff8a40(sy));
        affineIndex = func_020319fc(base, &mtxInv);
        pMtx = &mtxSR;
    } else {
        affineIndex = 0;
        pMtx = 0;
    }
    func_02031f2c(base, obj, oams,
                  func_020124e0(oams, 128, obj->pCell, pMtx, &obj->pos, (u16)affineIndex, bDouble),
                  affineIndex);
}
