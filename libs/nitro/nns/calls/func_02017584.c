typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;
typedef signed long fx32;
typedef signed long long fx64;
typedef int BOOL;

typedef struct VecFx32 {
    fx32 x, y, z;
} VecFx32;

typedef union MtxFx33 {
    struct {
        fx32 _00, _01, _02;
        fx32 _10, _11, _12;
        fx32 _20, _21, _22;
    };
    fx32 a[9];
} MtxFx33;

typedef struct NNSG3dJntAnmResult {
    u32 flag;
    VecFx32 scale;
    VecFx32 scaleEx0;
    VecFx32 scaleEx1;
    MtxFx33 rot;
    VecFx32 trans;
} NNSG3dJntAnmResult;

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

typedef struct NNSG3dResJntAnmSRTTag {
    u32 tag;
} NNSG3dResJntAnmSRTTag;

typedef void (*NNSG3dFuncJntScale)(NNSG3dJntAnmResult *, const fx32 *, const u8 *, u32);

typedef struct NNSG3dRS {
    const u8 *c;
    u8 padding_004_to_0e8[0xe4];
    NNSG3dFuncJntScale funcJntScale;
} NNSG3dRS;

extern NNSG3dRS *data_020475d0;

extern void func_02017938(fx32 *pVal, fx32 Frame, const u32 *pData,
                          const NNSG3dResJntAnm *pJntAnm);
extern void func_02017a90(fx32 *pVal, fx32 Frame, const u32 *pData,
                          const NNSG3dResJntAnm *pJntAnm);
extern void func_02017bec(fx32 *s_invs, fx32 Frame, const u32 *pData,
                          const NNSG3dResJntAnm *pJntAnm);
extern void func_02017dd4(fx32 *s_invs, fx32 Frame, const u32 *pData,
                          const NNSG3dResJntAnm *pJntAnm);
extern void func_02017f68(MtxFx33 *pRot, fx32 Frame, const u32 *pData,
                          const NNSG3dResJntAnm *pJntAnm);
extern void func_02018380(MtxFx33 *pRot, fx32 Frame, const u32 *pData,
                          const NNSG3dResJntAnm *pJntAnm);
extern BOOL func_020186c4(MtxFx33 *pRot, const void *pArrayRot3,
                          const void *pArrayRot5, u32 info);
extern void func_020172dc(NNSG3dJntAnmResult *pResult);
extern void func_02017404(NNSG3dJntAnmResult *pResult);
extern void func_02017374(NNSG3dJntAnmResult *pResult);

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

void func_02017584(const NNSG3dResJntAnm *pJntAnm, u32 dataIdx,
                   fx32 Frame, NNSG3dJntAnmResult *pResult)
{
    NNSG3dResJntAnmSRTTag *pAnmSRTTag;
    u32 tag;
    const u32 *pData;
    BOOL IsDecimalFrame;
    fx32 pS_invS[6];

    {
        const u16 *ofsTag = (const u16 *)((const u8 *)pJntAnm + sizeof(NNSG3dResJntAnm));
        pAnmSRTTag = (NNSG3dResJntAnmSRTTag *)((u8 *)pJntAnm + ofsTag[dataIdx]);
        tag = pAnmSRTTag->tag;
    }

    if (tag & 0x00000001) {
        pResult->flag = 0x00000001 | 0x00000002 | 0x00000004;
        goto GET_JOINTSCALE;
    }

    pData = (const u32 *)((const u8 *)pAnmSRTTag + sizeof(NNSG3dResJntAnmSRTTag));

    IsDecimalFrame = (BOOL)((Frame & (0x1000 - 1)) &&
                            (pJntAnm->flag & 1));

    pResult->flag = 0;

    if (!(tag & (0x00000002 | 0x00000004))) {
        if (!(tag & 0x00000008)) {
            if (IsDecimalFrame) {
                func_02017a90(&pResult->trans.x, Frame, pData, pJntAnm);
            } else {
                func_02017938(&pResult->trans.x, Frame, pData, pJntAnm);
            }
            pData += 2;
        } else {
            pResult->trans.x = *(fx32 *)pData;
            pData += 1;
        }

        if (!(tag & 0x00000010)) {
            if (IsDecimalFrame) {
                func_02017a90(&pResult->trans.y, Frame, pData, pJntAnm);
            } else {
                func_02017938(&pResult->trans.y, Frame, pData, pJntAnm);
            }
            pData += 2;
        } else {
            pResult->trans.y = *(fx32 *)pData;
            pData += 1;
        }

        if (!(tag & 0x00000020)) {
            if (IsDecimalFrame) {
                func_02017a90(&pResult->trans.z, Frame, pData, pJntAnm);
            } else {
                func_02017938(&pResult->trans.z, Frame, pData, pJntAnm);
            }
            pData += 2;
        } else {
            pResult->trans.z = *(fx32 *)pData;
            pData += 1;
        }
    } else {
        if (tag & 0x00000002) {
            pResult->flag |= 0x00000004;
        } else {
            func_020172dc(pResult);
        }
    }

    if (!(tag & (0x00000040 | 0x00000080))) {
        if (!(tag & 0x00000100)) {
            if (IsDecimalFrame) {
                func_02018380(&pResult->rot, Frame, pData, pJntAnm);
            } else {
                func_02017f68(&pResult->rot, Frame, pData, pJntAnm);
            }
            pData += 2;
        } else {
            if (func_020186c4(&pResult->rot,
                              (void *)((u8 *)pJntAnm + pJntAnm->ofsRot3),
                              (void *)((u8 *)pJntAnm + pJntAnm->ofsRot5),
                              *pData)) {
                vecCross_((const VecFx32 *)&pResult->rot._00,
                          (const VecFx32 *)&pResult->rot._10,
                          (VecFx32 *)&pResult->rot._20);
            }
            pData += 1;
        }
    } else {
        if (tag & 0x00000040) {
            pResult->flag |= 0x00000002;
        } else {
            func_02017404(pResult);
        }
    }

    if (!(tag & (0x00000200 | 0x00000400))) {
        if (!(tag & 0x00000800)) {
            fx32 sx_invsx[2];
            if (IsDecimalFrame) {
                func_02017dd4(&sx_invsx[0], Frame, pData, pJntAnm);
            } else {
                func_02017bec(&sx_invsx[0], Frame, pData, pJntAnm);
            }
            *(pS_invS + 0) = sx_invsx[0];
            *(pS_invS + 3) = sx_invsx[1];
        } else {
            const fx32 *p_fx32 = (const fx32 *)pData;
            *(pS_invS + 0) = *(p_fx32 + 0);
            *(pS_invS + 3) = *(p_fx32 + 1);
        }

        pData += 2;

        if (!(tag & 0x00001000)) {
            fx32 sy_invsy[2];
            if (IsDecimalFrame) {
                func_02017dd4(&sy_invsy[0], Frame, pData, pJntAnm);
            } else {
                func_02017bec(&sy_invsy[0], Frame, pData, pJntAnm);
            }
            *(pS_invS + 1) = sy_invsy[0];
            *(pS_invS + 4) = sy_invsy[1];
        } else {
            const fx32 *p_fx32 = (const fx32 *)pData;
            *(pS_invS + 1) = *(p_fx32 + 0);
            *(pS_invS + 4) = *(p_fx32 + 1);
        }

        pData += 2;

        if (!(tag & 0x00002000)) {
            fx32 sz_invsz[2];
            if (IsDecimalFrame) {
                func_02017dd4(&sz_invsz[0], Frame, pData, pJntAnm);
            } else {
                func_02017bec(&sz_invsz[0], Frame, pData, pJntAnm);
            }
            *(pS_invS + 2) = sz_invsz[0];
            *(pS_invS + 5) = sz_invsz[1];
        } else {
            const fx32 *p_fx32 = (const fx32 *)pData;
            *(pS_invS + 2) = *(p_fx32 + 0);
            *(pS_invS + 5) = *(p_fx32 + 1);
        }

        pData += 2;
    } else {
        if (tag & 0x00000200) {
            pResult->flag |= 0x00000001;
        } else {
            func_02017374(pResult);
            return;
        }
    }

GET_JOINTSCALE:
    (*data_020475d0->funcJntScale)(
        pResult,
        pS_invS,
        data_020475d0->c,
        ((pResult->flag & 0x00000001) ? 0x00000004 : 0));
}
