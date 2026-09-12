typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;
typedef signed long fx32;
typedef int BOOL;

typedef struct VecFx32 {
    fx32 x, y, z;
} VecFx32;

typedef struct MtxFx33 {
    fx32 _00, _01, _02;
    fx32 _10, _11, _12;
    fx32 _20, _21, _22;
} MtxFx33;

typedef struct NNSG3dResAnmHeader {
    u8 category0;
    u8 revision;
    u16 category1;
} NNSG3dResAnmHeader;

typedef struct NNSG3dResJntAnm {
    NNSG3dResAnmHeader anmHeader;
    u16 numFrame;
    u16 numNode;
    u32 flag;
    u32 ofsRot3;
    u32 ofsRot5;
} NNSG3dResJntAnm;

extern BOOL func_01ffae5c(MtxFx33 *pRot, const void *pArrayRot3,
                          const void *pArrayRot5, u32 info);
extern void func_01ffa7fc(VecFx32 *first, VecFx32 *second);
extern fx32 func_01ff8d18(const VecFx32 *src, VecFx32 *dst);

static inline void vecCross_(const VecFx32 *a, const VecFx32 *b, VecFx32 *axb)
{
    axb->x = (a->y * b->z - a->z * b->y) >> 12;
    axb->y = (a->z * b->x - a->x * b->z) >> 12;
    axb->z = (a->x * b->y - a->y * b->x) >> 12;
}

void func_02027300(MtxFx33 *pRot, fx32 Frame, const u32 *pData,
                   const NNSG3dResJntAnm *pJntAnm)
{
    u32 idx;
    u32 idxNext;
    fx32 frac;
    u32 weight;
    const void *pArrayRot3 = (const void *)((const u8 *)pJntAnm + pJntAnm->ofsRot3);
    const void *pArrayRot5 = (const void *)((const u8 *)pJntAnm + pJntAnm->ofsRot5);
    u32 info = pData[0];
    const u16 *p = (const u16 *)((const u8 *)pJntAnm + pData[1]);

    if (pJntAnm->numFrame - 1 == (u32)(Frame >> 12)) {
        idx = (u32)(Frame >> 12);
        if (info & 0xc0000000) {
            if (info & 0x40000000) {
                idx = (idx & 1) + (idx >> 1);
            } else {
                idx = (idx & 3) + (idx >> 2);
            }
        }
        if (pJntAnm->flag & 2) {
            idxNext = 0;
            goto DEFAULT_WEIGHT;
        }
        if (func_01ffae5c(pRot, pArrayRot3, pArrayRot5, p[idx])) {
            vecCross_((const VecFx32 *)&pRot->_00, (const VecFx32 *)&pRot->_10,
                      (VecFx32 *)&pRot->_20);
        } else {
            func_01ff8d18((VecFx32 *)&pRot->_20, (VecFx32 *)&pRot->_20);
        }
        return;
    }

    idx = (u32)(Frame >> 12);
    if (info & 0xc0000000) {
        u32 last_interp = (info & 0x1fff0000) >> 16;
        if (info & 0x40000000) {
            if (idx >= last_interp) {
                idx = last_interp >> 1;
                idxNext = idx + 1;
                goto DEFAULT_WEIGHT;
            }
            idx = idx >> 1;
            idxNext = idx + 1;
            weight = 2;
            frac = Frame & 0x1fff;
            goto BLEND;
        }
        if (idx >= last_interp) {
            idx = (idx & 3) + (idx >> 2);
            idxNext = idx + 1;
            goto DEFAULT_WEIGHT;
        }
        idx = idx >> 2;
        idxNext = idx + 1;
        weight = 4;
        frac = Frame & 0x3fff;
        goto BLEND;
    } else {
        idxNext = idx + 1;
        goto DEFAULT_WEIGHT;
    }

DEFAULT_WEIGHT:
    frac = Frame & 0xfff;
    weight = 1;

BLEND:
    {
        MtxFx33 tmp1, tmp2;
        BOOL doCross = 0;

        doCross |= func_01ffae5c(&tmp1, pArrayRot3, pArrayRot5, p[idx]);
        doCross |= func_01ffae5c(&tmp2, pArrayRot3, pArrayRot5, p[idxNext]);

        pRot->_00 = tmp1._00 * weight + ((frac * (tmp2._00 - tmp1._00)) >> 12);
        pRot->_01 = tmp1._01 * weight + ((frac * (tmp2._01 - tmp1._01)) >> 12);
        pRot->_02 = tmp1._02 * weight + ((frac * (tmp2._02 - tmp1._02)) >> 12);
        pRot->_10 = tmp1._10 * weight + ((frac * (tmp2._10 - tmp1._10)) >> 12);
        pRot->_11 = tmp1._11 * weight + ((frac * (tmp2._11 - tmp1._11)) >> 12);
        pRot->_12 = tmp1._12 * weight + ((frac * (tmp2._12 - tmp1._12)) >> 12);

        func_01ffa7fc((VecFx32 *)&pRot->_00, (VecFx32 *)&pRot->_10);

        if (!doCross) {
            pRot->_20 = tmp1._20 * weight + ((frac * (tmp2._20 - tmp1._20)) >> 12);
            pRot->_21 = tmp1._21 * weight + ((frac * (tmp2._21 - tmp1._21)) >> 12);
            pRot->_22 = tmp1._22 * weight + ((frac * (tmp2._22 - tmp1._22)) >> 12);
            func_01ff8d18((VecFx32 *)&pRot->_20, (VecFx32 *)&pRot->_20);
        } else {
            vecCross_((const VecFx32 *)&pRot->_00, (const VecFx32 *)&pRot->_10,
                      (VecFx32 *)&pRot->_20);
        }
    }
}
