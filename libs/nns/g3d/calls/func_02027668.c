/* func_02027668 -- evaluate one joint's SRT animation tag (NitroSystem G3D). NitroSystem's getJntSRTAnmResult_
 * (nsbca.c) as built here, without the decimal-frame variants and split out from its caller: given
 * the joint animation, the joint's SRT tag and its tag bits, it fills the result's translation
 * (+0x4c, animated through func_02026e28 or constant), rotation (+0x28, animated through func_02027300
 * or an indexed constant with the third row rebuilt as the cross product of the first two) and the
 * scale / inverse-scale pairs (func_0202716c or constant) into pS_invS. Identity parts only set the
 * result flag (+0x00: 1 scale one, 2 rotation zero, 4 translation zero); base parts copy the model's
 * own values (func_02026a44 / func_02026b70 / func_02026adc). */
typedef unsigned char u8;
typedef unsigned int u32;
typedef int fx32;

typedef struct { fx32 x, y, z; } VecFx32;
typedef struct { fx32 _00, _01, _02, _10, _11, _12, _20, _21, _22; } MtxFx33;

typedef struct NNSG3dResJntAnm {
    char anmHeader[8];                  /* +0x00 */
    u32 pad08;
    u32 ofsRot3;                        /* +0x0c */
    u32 ofsRot5;                        /* +0x10 */
} NNSG3dResJntAnm;

typedef struct NNSG3dResJntAnmSRTTag {
    u32 tag;                            /* +0x00 */
} NNSG3dResJntAnmSRTTag;

typedef struct NNSG3dJntAnmResult {
    u32 flag;                           /* +0x00 */
    VecFx32 scale;                      /* +0x04 */
    VecFx32 scaleEx0;                   /* +0x10 */
    VecFx32 scaleEx1;                   /* +0x1c */
    MtxFx33 rot;                        /* +0x28 */
    VecFx32 trans;                      /* +0x4c */
} NNSG3dJntAnmResult;

#define NNS_G3D_JNTANM_SRTINFO_IDENTITY_T 0x00000002
#define NNS_G3D_JNTANM_SRTINFO_BASE_T     0x00000004
#define NNS_G3D_JNTANM_SRTINFO_CONST_TX   0x00000008
#define NNS_G3D_JNTANM_SRTINFO_CONST_TY   0x00000010
#define NNS_G3D_JNTANM_SRTINFO_CONST_TZ   0x00000020
#define NNS_G3D_JNTANM_SRTINFO_IDENTITY_R 0x00000040
#define NNS_G3D_JNTANM_SRTINFO_BASE_R     0x00000080
#define NNS_G3D_JNTANM_SRTINFO_CONST_R    0x00000100
#define NNS_G3D_JNTANM_SRTINFO_IDENTITY_S 0x00000200
#define NNS_G3D_JNTANM_SRTINFO_BASE_S     0x00000400
#define NNS_G3D_JNTANM_SRTINFO_CONST_SX   0x00000800
#define NNS_G3D_JNTANM_SRTINFO_CONST_SY   0x00001000
#define NNS_G3D_JNTANM_SRTINFO_CONST_SZ   0x00002000

#define NNS_G3D_JNTANM_RESULTFLAG_SCALE_ONE  0x00000001
#define NNS_G3D_JNTANM_RESULTFLAG_ROT_ZERO   0x00000002
#define NNS_G3D_JNTANM_RESULTFLAG_TRANS_ZERO 0x00000004

extern void func_02026e28(fx32 *pVal, fx32 Frame, const u32 *pData, const NNSG3dResJntAnm *pJntAnm);   /* getTransData_ */
extern void func_02027300(MtxFx33 *pRot, fx32 Frame, const u32 *pData, const NNSG3dResJntAnm *pJntAnm); /* getRotData_ */
extern void func_0202716c(fx32 *s_invs, fx32 Frame, const u32 *pData, const NNSG3dResJntAnm *pJntAnm);  /* getScaleData_ */
extern int func_01ffae5c(MtxFx33 *pRot, const void *pArrayRot3, const void *pArrayRot5, u32 info);     /* getRotDataByIdx_ */
extern void func_02026a44(NNSG3dJntAnmResult *pResult);    /* getMdlTrans_ */
extern void func_02026b70(NNSG3dJntAnmResult *pResult);    /* getMdlRot_ */
extern void func_02026adc(NNSG3dJntAnmResult *pResult);    /* getMdlScale_ */

static inline void vecCross_(const VecFx32 *a, const VecFx32 *b, VecFx32 *axb)
{
    axb->x = (a->y * b->z - a->z * b->y) >> 12;
    axb->y = (a->z * b->x - a->x * b->z) >> 12;
    axb->z = (a->x * b->y - a->y * b->x) >> 12;
}

void func_02027668(const NNSG3dResJntAnm *pJntAnm, const NNSG3dResJntAnmSRTTag *pAnmSRTTag, u32 tag, fx32 Frame,
                   NNSG3dJntAnmResult *pResult, fx32 *pS_invS)
{
    const u32 *pData;

    pResult->flag = 0;
    pData = (const u32 *)((const u8 *)pAnmSRTTag + sizeof(NNSG3dResJntAnmSRTTag));

    if (!(tag & (NNS_G3D_JNTANM_SRTINFO_IDENTITY_T | NNS_G3D_JNTANM_SRTINFO_BASE_T))) {
        if (!(tag & NNS_G3D_JNTANM_SRTINFO_CONST_TX)) {
            func_02026e28(&pResult->trans.x, Frame, pData, pJntAnm);
            pData += 2;
        } else {
            pResult->trans.x = *(fx32 *)pData;
            pData += 1;
        }
        if (!(tag & NNS_G3D_JNTANM_SRTINFO_CONST_TY)) {
            func_02026e28(&pResult->trans.y, Frame, pData, pJntAnm);
            pData += 2;
        } else {
            pResult->trans.y = *(fx32 *)pData;
            pData += 1;
        }
        if (!(tag & NNS_G3D_JNTANM_SRTINFO_CONST_TZ)) {
            func_02026e28(&pResult->trans.z, Frame, pData, pJntAnm);
            pData += 2;
        } else {
            pResult->trans.z = *(fx32 *)pData;
            pData += 1;
        }
    } else {
        if (tag & NNS_G3D_JNTANM_SRTINFO_IDENTITY_T) {
            pResult->flag |= NNS_G3D_JNTANM_RESULTFLAG_TRANS_ZERO;
        } else {
            func_02026a44(pResult);
        }
    }

    if (!(tag & (NNS_G3D_JNTANM_SRTINFO_IDENTITY_R | NNS_G3D_JNTANM_SRTINFO_BASE_R))) {
        if (!(tag & NNS_G3D_JNTANM_SRTINFO_CONST_R)) {
            func_02027300(&pResult->rot, Frame, pData, pJntAnm);
            pData += 2;
        } else {
            if (func_01ffae5c(&pResult->rot, (void *)((u8 *)pJntAnm + pJntAnm->ofsRot3),
                              (void *)((u8 *)pJntAnm + pJntAnm->ofsRot5), *pData)) {
                vecCross_((const VecFx32 *)&pResult->rot._00, (const VecFx32 *)&pResult->rot._10,
                          (VecFx32 *)&pResult->rot._20);
            }
            pData += 1;
        }
    } else {
        if (tag & NNS_G3D_JNTANM_SRTINFO_IDENTITY_R) {
            pResult->flag |= NNS_G3D_JNTANM_RESULTFLAG_ROT_ZERO;
        } else {
            func_02026b70(pResult);
        }
    }

    if (!(tag & (NNS_G3D_JNTANM_SRTINFO_IDENTITY_S | NNS_G3D_JNTANM_SRTINFO_BASE_S))) {
        if (!(tag & NNS_G3D_JNTANM_SRTINFO_CONST_SX)) {
            fx32 sx_invsx[2];

            func_0202716c(&sx_invsx[0], Frame, pData, pJntAnm);
            *(pS_invS + 0) = sx_invsx[0];
            *(pS_invS + 3) = sx_invsx[1];
        } else {
            const fx32 *p_fx32 = (const fx32 *)pData;

            *(pS_invS + 0) = *(p_fx32 + 0);
            *(pS_invS + 3) = *(p_fx32 + 1);
        }
        pData += 2;

        if (!(tag & NNS_G3D_JNTANM_SRTINFO_CONST_SY)) {
            fx32 sy_invsy[2];

            func_0202716c(&sy_invsy[0], Frame, pData, pJntAnm);
            *(pS_invS + 1) = sy_invsy[0];
            *(pS_invS + 4) = sy_invsy[1];
        } else {
            const fx32 *p_fx32 = (const fx32 *)pData;

            *(pS_invS + 1) = *(p_fx32 + 0);
            *(pS_invS + 4) = *(p_fx32 + 1);
        }
        pData += 2;

        if (!(tag & NNS_G3D_JNTANM_SRTINFO_CONST_SZ)) {
            fx32 sz_invsz[2];

            func_0202716c(&sz_invsz[0], Frame, pData, pJntAnm);
            *(pS_invS + 2) = sz_invsz[0];
            *(pS_invS + 5) = sz_invsz[1];
        } else {
            const fx32 *p_fx32 = (const fx32 *)pData;

            *(pS_invS + 2) = *(p_fx32 + 0);
            *(pS_invS + 5) = *(p_fx32 + 1);
        }
        pData += 2;
    } else {
        if (tag & NNS_G3D_JNTANM_SRTINFO_IDENTITY_S) {
            pResult->flag |= NNS_G3D_JNTANM_RESULTFLAG_SCALE_ONE;
        } else {
            func_02026adc(pResult);
        }
    }
}
