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

extern void func_02026cd0(fx32 *pVal, fx32 frame, const u32 *pData,
                          const NNSG3dResJntAnm *pJntAnm);
extern void func_02026a44(NNSG3dJntAnmResult *pResult);
extern void func_01ffaa14(MtxFx33 *pRot, fx32 frame, const u32 *pData,
                          const NNSG3dResJntAnm *pJntAnm);
extern BOOL func_01ffae5c(MtxFx33 *pRot, const void *pArrayRot3,
                          const void *pArrayRot5, u32 info);
extern void func_02026b70(NNSG3dJntAnmResult *pResult);
extern void func_02026f84(fx32 *pValues, fx32 frame, const u32 *pData,
                          const NNSG3dResJntAnm *pJntAnm);
extern void func_02026adc(NNSG3dJntAnmResult *pResult);

static inline void vecCross_(const VecFx32 *a, const VecFx32 *b, VecFx32 *axb)
{
    axb->x = (a->y * b->z - a->z * b->y) >> 12;
    axb->y = (a->z * b->x - a->x * b->z) >> 12;
    axb->z = (a->x * b->y - a->y * b->x) >> 12;
}

void func_01ffaf9c(const NNSG3dResJntAnm *pJntAnm,
                   const NNSG3dResJntAnmSRTTag *pAnmSRTTag,
                   u32 tag, fx32 frame, NNSG3dJntAnmResult *pResult,
                   fx32 *pS_invS)
{
    const u32 *pData =
        (const u32 *)((const u8 *)pAnmSRTTag + sizeof(NNSG3dResJntAnmSRTTag));

    if (!(tag & (0x00000002 | 0x00000004))) {
        if (!(tag & 0x00000008)) {
            func_02026cd0(&pResult->trans.x, frame, pData, pJntAnm);
            pData += 2;
        } else {
            pResult->trans.x = *(const fx32 *)pData;
            pData += 1;
        }

        if (!(tag & 0x00000010)) {
            func_02026cd0(&pResult->trans.y, frame, pData, pJntAnm);
            pData += 2;
        } else {
            pResult->trans.y = *(const fx32 *)pData;
            pData += 1;
        }

        if (!(tag & 0x00000020)) {
            func_02026cd0(&pResult->trans.z, frame, pData, pJntAnm);
            pData += 2;
        } else {
            pResult->trans.z = *(const fx32 *)pData;
            pData += 1;
        }
    } else {
        if (tag & 0x00000002) {
            pResult->flag |= 0x00000004;
        } else {
            func_02026a44(pResult);
        }
    }

    if (!(tag & (0x00000040 | 0x00000080))) {
        if (!(tag & 0x00000100)) {
            func_01ffaa14(&pResult->rot, frame, pData, pJntAnm);
            pData += 2;
        } else {
            if (func_01ffae5c(&pResult->rot,
                              (const u8 *)pJntAnm + pJntAnm->ofsRot3,
                              (const u8 *)pJntAnm + pJntAnm->ofsRot5,
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
            func_02026b70(pResult);
        }
    }

    if (!(tag & (0x00000200 | 0x00000400))) {
        if (!(tag & 0x00000800)) {
            fx32 sx_invsx[2];

            func_02026f84(&sx_invsx[0], frame, pData, pJntAnm);
            pS_invS[0] = sx_invsx[0];
            pS_invS[3] = sx_invsx[1];
        } else {
            const fx32 *pFx32 = (const fx32 *)pData;

            pS_invS[0] = pFx32[0];
            pS_invS[3] = pFx32[1];
        }
        pData += 2;

        if (!(tag & 0x00001000)) {
            fx32 sy_invsy[2];

            func_02026f84(&sy_invsy[0], frame, pData, pJntAnm);
            pS_invS[1] = sy_invsy[0];
            pS_invS[4] = sy_invsy[1];
        } else {
            const fx32 *pFx32 = (const fx32 *)pData;

            pS_invS[1] = pFx32[0];
            pS_invS[4] = pFx32[1];
        }
        pData += 2;

        if (!(tag & 0x00002000)) {
            fx32 sz_invsz[2];

            func_02026f84(&sz_invsz[0], frame, pData, pJntAnm);
            pS_invS[2] = sz_invsz[0];
            pS_invS[5] = sz_invsz[1];
        } else {
            const fx32 *pFx32 = (const fx32 *)pData;

            pS_invS[2] = pFx32[0];
            pS_invS[5] = pFx32[1];
        }
    } else {
        if (tag & 0x00000200) {
            pResult->flag |= 0x00000001;
        } else {
            func_02026adc(pResult);
        }
    }
}
