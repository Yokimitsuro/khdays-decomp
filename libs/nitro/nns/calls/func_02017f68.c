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

extern BOOL func_020186c4(MtxFx33 *pRot, const void *pArrayRot3,
                          const void *pArrayRot5, u32 info);
extern void func_01ff8d18(const VecFx32 *src, VecFx32 *dst);

static inline void vecCross_(const VecFx32 *a, const VecFx32 *b, VecFx32 *axb)
{
    fx32 x, y, z;
    x = (a->y * b->z - a->z * b->y) >> 12;
    y = (a->z * b->x - a->x * b->z) >> 12;
    z = (a->x * b->y - a->y * b->x) >> 12;
    axb->x = x;
    axb->y = y;
    axb->z = z;
}

void func_02017f68(MtxFx33 *pRot, fx32 Frame, const u32 *pData,
                   const NNSG3dResJntAnm *pJntAnm)
{
    u32 frame = (u32)(Frame >> 12);
    const void *pArray = (const void *)((const u8 *)pJntAnm + *(pData + 1));
    const void *pArrayRot3 = (const void *)((const u8 *)pJntAnm + pJntAnm->ofsRot3);
    const void *pArrayRot5 = (const void *)((const u8 *)pJntAnm + pJntAnm->ofsRot5);
    u32 info = *pData;
    const u16 *p = (const u16 *)pArray;
    u32 last_interp;
    u32 idx;
    u32 idx_sub;

    if (!(info & 0xc0000000)) {
        idx = frame;
        goto ROT_NONINTERP;
    }

    last_interp = (info & 0x1fff0000) >> 16;

    if (info & 0x40000000) {
        if (frame & 1) {
            if (frame > last_interp) {
                idx = (last_interp >> 1) + 1;
                goto ROT_NONINTERP;
            } else {
                idx = frame >> 1;
                goto ROT_INTERP_2;
            }
        } else {
            idx = frame >> 1;
            goto ROT_NONINTERP;
        }
    } else {
        if (frame & 3) {
            if (frame > last_interp) {
                idx = (last_interp >> 2) + (frame & 3);
                goto ROT_NONINTERP;
            }

            if (frame & 1) {
                MtxFx33 tmp;
                BOOL doCross = 0;
                if (frame & 2) {
                    idx_sub = frame >> 2;
                    idx = idx_sub + 1;
                } else {
                    idx = frame >> 2;
                    idx_sub = idx + 1;
                }

                doCross |= func_020186c4(pRot, pArrayRot3, pArrayRot5, p[idx]);
                doCross |= func_020186c4(&tmp, pArrayRot3, pArrayRot5, p[idx_sub]);

                pRot->_00 = (pRot->_00 * 3 + tmp._00) >> 0;
                pRot->_01 = (pRot->_01 * 3 + tmp._01) >> 0;
                pRot->_02 = (pRot->_02 * 3 + tmp._02) >> 0;
                pRot->_10 = (pRot->_10 * 3 + tmp._10) >> 0;
                pRot->_11 = (pRot->_11 * 3 + tmp._11) >> 0;
                pRot->_12 = (pRot->_12 * 3 + tmp._12) >> 0;

                func_01ff8d18((VecFx32 *)&pRot->_00, (VecFx32 *)&pRot->_00);
                func_01ff8d18((VecFx32 *)&pRot->_10, (VecFx32 *)&pRot->_10);

                if (!doCross) {
                    pRot->_20 = (pRot->_20 * 3 + tmp._20) >> 0;
                    pRot->_21 = (pRot->_21 * 3 + tmp._21) >> 0;
                    pRot->_22 = (pRot->_22 * 3 + tmp._22) >> 0;
                    func_01ff8d18((VecFx32 *)&pRot->_20, (VecFx32 *)&pRot->_20);
                } else {
                    vecCross_((const VecFx32 *)&pRot->_00,
                              (const VecFx32 *)&pRot->_10,
                              (VecFx32 *)&pRot->_20);
                }
                return;
            } else {
                idx = frame >> 2;
                goto ROT_INTERP_2;
            }
        } else {
            idx = frame >> 2;
            goto ROT_NONINTERP;
        }
    }

ROT_INTERP_2:
    {
        MtxFx33 tmp;
        BOOL doCross = 0;
        doCross |= func_020186c4(pRot, pArrayRot3, pArrayRot5, p[idx]);
        doCross |= func_020186c4(&tmp, pArrayRot3, pArrayRot5, p[idx + 1]);

        pRot->_00 = (pRot->_00 + tmp._00) >> 0;
        pRot->_01 = (pRot->_01 + tmp._01) >> 0;
        pRot->_02 = (pRot->_02 + tmp._02) >> 0;
        pRot->_10 = (pRot->_10 + tmp._10) >> 0;
        pRot->_11 = (pRot->_11 + tmp._11) >> 0;
        pRot->_12 = (pRot->_12 + tmp._12) >> 0;

        func_01ff8d18((VecFx32 *)&pRot->_00, (VecFx32 *)&pRot->_00);
        func_01ff8d18((VecFx32 *)&pRot->_10, (VecFx32 *)&pRot->_10);

        if (!doCross) {
            pRot->_20 = (pRot->_20 + tmp._20) >> 0;
            pRot->_21 = (pRot->_21 + tmp._21) >> 0;
            pRot->_22 = (pRot->_22 + tmp._22) >> 0;
            func_01ff8d18((VecFx32 *)&pRot->_20, (VecFx32 *)&pRot->_20);
        } else {
            vecCross_((const VecFx32 *)&pRot->_00,
                      (const VecFx32 *)&pRot->_10,
                      (VecFx32 *)&pRot->_20);
        }
        return;
    }

ROT_NONINTERP:
    if (func_020186c4(pRot, pArrayRot3, pArrayRot5, p[idx])) {
        vecCross_((const VecFx32 *)&pRot->_00,
                  (const VecFx32 *)&pRot->_10,
                  (VecFx32 *)&pRot->_20);
    } else {
        func_01ff8d18((VecFx32 *)&pRot->_20, (VecFx32 *)&pRot->_20);
    }
}
