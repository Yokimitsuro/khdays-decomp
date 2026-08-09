typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;
typedef signed long fx32;
typedef signed long long fx64;
typedef int BOOL;

typedef struct VecFx32 {
    fx32 x, y, z;
} VecFx32;

typedef struct MtxFx33 {
    fx32 _00, _01, _02;
    fx32 _10, _11, _12;
    fx32 _20, _21, _22;
} MtxFx33;

typedef unsigned long NNSG3dJntAnmResultFlag;

typedef struct NNSG3dJntAnmResult {
    NNSG3dJntAnmResultFlag flag;
    VecFx32 scale;
    VecFx32 scaleEx0;
    VecFx32 scaleEx1;
    MtxFx33 rot;
    VecFx32 trans;
} NNSG3dJntAnmResult;

struct NNSG3dAnmObj;
typedef void (*NNSG3dFuncAnmJnt)(NNSG3dJntAnmResult *, const struct NNSG3dAnmObj *, u32);

typedef struct NNSG3dAnmObj {
    fx32 frame;
    fx32 ratio;
    void *resAnm;
    NNSG3dFuncAnmJnt funcAnm;
    struct NNSG3dAnmObj *next;
    const void *resTex;
    u8 priority;
    u8 numMapData;
    u16 mapData[1];
} NNSG3dAnmObj;

enum {
    NNS_G3D_ANMOBJ_MAPDATA_EXIST = 0x0100,
    NNS_G3D_ANMOBJ_MAPDATA_DISABLED = 0x0200,
    NNS_G3D_ANMOBJ_MAPDATA_DATAFIELD = 0x00ff,

    NNS_G3D_JNTANM_RESULTFLAG_SCALE_ONE = 0x00000001,
    NNS_G3D_JNTANM_RESULTFLAG_ROT_ZERO = 0x00000002,
    NNS_G3D_JNTANM_RESULTFLAG_TRANS_ZERO = 0x00000004,
    NNS_G3D_JNTANM_RESULTFLAG_SCALEEX0_ONE = 0x00000008,
    NNS_G3D_JNTANM_RESULTFLAG_SCALEEX1_ONE = 0x00000010
};

extern void MIi_CpuClearFast(u32 data, void *dest, u32 size);
extern void MIi_CpuCopy32(const void *src, void *dest, u32 size);
extern fx32 FX_Inv(fx32 numer, fx32 denom);
extern void func_02015d80(VecFx32 *v0, const VecFx32 *v1, fx32 ratio, BOOL isV1One);
extern void VEC_CrossProduct(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void func_01ff8d18(const VecFx32 *src, VecFx32 *dst);

BOOL func_02015df0(NNSG3dJntAnmResult *pResult, const NNSG3dAnmObj *pAnmObj, u32 nodeID)
{
    if (!pAnmObj) {
        return 0;
    }

    if (!pAnmObj->next) {
        u32 dataIdx;
        if (nodeID < pAnmObj->numMapData) {
            dataIdx = pAnmObj->mapData[nodeID];
            if ((dataIdx & (NNS_G3D_ANMOBJ_MAPDATA_EXIST |
                            NNS_G3D_ANMOBJ_MAPDATA_DISABLED)) ==
                NNS_G3D_ANMOBJ_MAPDATA_EXIST) {
                NNSG3dFuncAnmJnt func = pAnmObj->funcAnm;

                if (func) {
                    (*func)(pResult,
                            pAnmObj,
                            dataIdx & NNS_G3D_ANMOBJ_MAPDATA_DATAFIELD);
                    return 1;
                } else {
                    return 0;
                }
            } else {
                return 0;
            }
        } else {
            return 0;
        }
    } else {
        const NNSG3dAnmObj *p;
        NNSG3dJntAnmResult r;
        fx32 sumOfRatio = 0;
        const NNSG3dAnmObj *pLastAnmObj;
        int numBlend = 0;
        int i1 = 0;
        VecFx32 keepAxisX;
        VecFx32 keepAxisZ;

        p = pAnmObj;
        do {
            if (nodeID < p->numMapData) {
                u32 dataIdx = p->mapData[nodeID];
                if ((dataIdx & (NNS_G3D_ANMOBJ_MAPDATA_EXIST |
                                NNS_G3D_ANMOBJ_MAPDATA_DISABLED)) ==
                    NNS_G3D_ANMOBJ_MAPDATA_EXIST) {
                    if (p->ratio > 0x1000)
                        sumOfRatio += 0x1000;
                    else if (p->ratio > 0)
                        sumOfRatio += p->ratio;

                    pLastAnmObj = p;
                    ++numBlend;
                }
            }
            p = p->next;
        } while (p);

        if (sumOfRatio == 0) {
            return 0;
        }

        if (numBlend == 1) {
            NNSG3dFuncAnmJnt func = pLastAnmObj->funcAnm;
            u32 dataIdx = pLastAnmObj->mapData[nodeID];

            if (func) {
                (*func)(pResult, pLastAnmObj, dataIdx & NNS_G3D_ANMOBJ_MAPDATA_DATAFIELD);
                return 1;
            } else {
                return 0;
            }
        }

        MIi_CpuClearFast(0, pResult, sizeof(*pResult));
        pResult->flag = (NNSG3dJntAnmResultFlag)-1;

        p = pAnmObj;
        do {
            if (nodeID < p->numMapData) {
                u32 dataIdx = p->mapData[nodeID];
                if ((dataIdx & (NNS_G3D_ANMOBJ_MAPDATA_EXIST |
                                NNS_G3D_ANMOBJ_MAPDATA_DISABLED)) ==
                        NNS_G3D_ANMOBJ_MAPDATA_EXIST &&
                    (p->ratio > 0)) {
                    fx32 ratio;
                    NNSG3dFuncAnmJnt func = p->funcAnm;

                    if (func) {
                        (*func)(&r, p, dataIdx & NNS_G3D_ANMOBJ_MAPDATA_DATAFIELD);

                        if (i1 == 0) {
                            MIi_CpuCopy32(&r.rot._00, &keepAxisX, sizeof(VecFx32));
                            MIi_CpuCopy32(&r.rot._20, &keepAxisZ, sizeof(VecFx32));
                        }

                        if (sumOfRatio != 0x1000) {
                            ratio = FX_Inv(p->ratio, sumOfRatio);
                        } else {
                            ratio = p->ratio;
                        }

                        func_02015d80(&pResult->scale,
                                      &r.scale,
                                      ratio,
                                      r.flag & NNS_G3D_JNTANM_RESULTFLAG_SCALE_ONE);

                        func_02015d80(&pResult->scaleEx0,
                                      &r.scaleEx0,
                                      ratio,
                                      r.flag & NNS_G3D_JNTANM_RESULTFLAG_SCALEEX0_ONE);

                        func_02015d80(&pResult->scaleEx1,
                                      &r.scaleEx1,
                                      ratio,
                                      r.flag & NNS_G3D_JNTANM_RESULTFLAG_SCALEEX1_ONE);

                        if (!(r.flag & NNS_G3D_JNTANM_RESULTFLAG_TRANS_ZERO)) {
                            pResult->trans.x += (fx32)((fx64)ratio * r.trans.x >> 12);
                            pResult->trans.y += (fx32)((fx64)ratio * r.trans.y >> 12);
                            pResult->trans.z += (fx32)((fx64)ratio * r.trans.z >> 12);
                        }

                        if (!(r.flag & NNS_G3D_JNTANM_RESULTFLAG_ROT_ZERO)) {
                            pResult->rot._00 += ratio * r.rot._00 >> 12;
                            pResult->rot._01 += ratio * r.rot._01 >> 12;
                            pResult->rot._02 += ratio * r.rot._02 >> 12;
                            pResult->rot._10 += ratio * r.rot._10 >> 12;
                            pResult->rot._11 += ratio * r.rot._11 >> 12;
                            pResult->rot._12 += ratio * r.rot._12 >> 12;
                        } else {
                            pResult->rot._00 += ratio;
                            pResult->rot._11 += ratio;
                        }

                        pResult->flag &= r.flag;
                    }
                }
            }

            p = p->next;
            ++i1;
        } while (p);

        VEC_CrossProduct((VecFx32 *)&pResult->rot._00,
                         (VecFx32 *)&pResult->rot._10,
                         (VecFx32 *)&pResult->rot._20);

        if ((pResult->rot._00 == 0) &&
            (pResult->rot._01 == 0) &&
            (pResult->rot._02 == 0)) {
            MIi_CpuCopy32(&keepAxisX, &pResult->rot._00, sizeof(VecFx32));
        } else {
            func_01ff8d18((VecFx32 *)&pResult->rot._00, (VecFx32 *)&pResult->rot._00);
        }

        if ((pResult->rot._20 == 0) &&
            (pResult->rot._21 == 0) &&
            (pResult->rot._22 == 0)) {
            MIi_CpuCopy32(&keepAxisZ, &pResult->rot._20, sizeof(VecFx32));
        } else {
            func_01ff8d18((VecFx32 *)&pResult->rot._20, (VecFx32 *)&pResult->rot._20);
        }

        VEC_CrossProduct((VecFx32 *)&pResult->rot._20,
                         (VecFx32 *)&pResult->rot._00,
                         (VecFx32 *)&pResult->rot._10);

        return 1;
    }
}
