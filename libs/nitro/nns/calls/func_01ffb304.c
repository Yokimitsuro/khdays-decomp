typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;
typedef signed long s32;
typedef signed long fx32;
typedef signed long long s64;
typedef unsigned long long u64;
typedef int BOOL;
typedef volatile unsigned short vu16;
typedef volatile unsigned long vu32;
typedef volatile signed long long vs64;
typedef volatile unsigned long long vu64;

typedef struct VecFx32 {
    fx32 x, y, z;
} VecFx32;

typedef struct MtxFx33 {
    fx32 _00, _01, _02;
    fx32 _10, _11, _12;
    fx32 _20, _21, _22;
} MtxFx33;

typedef u32 NNSG3dJntAnmResultFlag;

typedef struct NNSG3dJntAnmResult {
    NNSG3dJntAnmResultFlag flag;
    VecFx32 scale;
    VecFx32 scaleEx0;
    VecFx32 scaleEx1;
    MtxFx33 rot;
    VecFx32 trans;
} NNSG3dJntAnmResult;

typedef struct NNSG3dAnmObj {
    fx32 frame;
    fx32 ratio;
    void *resAnm;
    void *funcAnm;
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

#define REG_DIVCNT          (*(vu16 *)0x04000280)
#define REG_DIV_NUMER       (*(vu64 *)0x04000290)
#define REG_DIV_DENOM       (*(vs64 *)0x04000298)
#define REG_DIV_RESULT      (*(vs64 *)0x040002a0)
#define REG_SQRTCNT         (*(vu16 *)0x040002b0)
#define REG_SQRT_RESULT     (*(vu32 *)0x040002b4)
#define REG_SQRT_PARAM      (*(u64 *)0x040002b8)

extern void func_01ffb234(NNSG3dJntAnmResult *pResult,
                          const NNSG3dAnmObj *pAnmObj, u32 dataIdx);
extern void MIi_CpuClearFast(u32 data, void *dest, u32 size);
extern fx32 FX_Inv(fx32 numer, fx32 denom);
extern void func_02027908(VecFx32 *v0, const VecFx32 *v1,
                          fx32 ratio, BOOL isV1One);
extern void VEC_CrossProduct(const VecFx32 *a,
                             const VecFx32 *b, VecFx32 *out);

static inline s64 VecSquareMagnitude(const VecFx32 *v)
{
    int x;
    fx32 y;
    y = v->y;
    x = v->x;
    s64 result = (s64)y * y;

    result += (s64)x * x;
    result += (s64)v->z * v->z;
    return result;
}

static inline void StartNormalize(s64 squaredMagnitude)
{
    REG_DIVCNT = 2;
    REG_DIV_NUMER = 0x0100000000000000ULL;
    REG_DIV_DENOM = squaredMagnitude;
    REG_SQRTCNT = 1;
    REG_SQRT_PARAM = (u64)(squaredMagnitude * 4);
}

static inline s64 ReadNormalizeScale(void)
{
    fx32 magnitude;
    s64 scale;

    while (REG_SQRTCNT & 0x8000) {
    }
    magnitude = (fx32)REG_SQRT_RESULT;
    while (REG_DIVCNT & 0x8000) {
    }
    scale = REG_DIV_RESULT;
    return scale * magnitude;
}

static inline void ApplyNormalize(VecFx32 *v, s64 scale)
{
    v->x = (fx32)((scale * v->x + (1LL << 44)) >> 45);
    v->y = (fx32)((scale * v->y + (1LL << 44)) >> 45);
    v->z = (fx32)((scale * v->z + (1LL << 44)) >> 45);
}

BOOL func_01ffb304(NNSG3dJntAnmResult *pResult,
                   const NNSG3dAnmObj *pAnmObj, u32 nodeID, u32 unused)
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
                func_01ffb234(pResult, pAnmObj,
                              dataIdx & NNS_G3D_ANMOBJ_MAPDATA_DATAFIELD);
                return 1;
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
        s64 squareAxisX;
        s64 squareAxisZ;
        s64 normalizeScaleX;
        s64 normalizeScaleZ;

        p = pAnmObj;
        do {
            if (nodeID < p->numMapData) {
                u32 dataIdx = p->mapData[nodeID];

                if ((dataIdx & (NNS_G3D_ANMOBJ_MAPDATA_EXIST |
                                NNS_G3D_ANMOBJ_MAPDATA_DISABLED)) ==
                    NNS_G3D_ANMOBJ_MAPDATA_EXIST) {
                    if (p->ratio > 0x1000) {
                        sumOfRatio += 0x1000;
                    } else if (p->ratio > 0) {
                        sumOfRatio += p->ratio;
                    }
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
            u32 dataIdx = pLastAnmObj->mapData[nodeID];

            func_01ffb234(pResult, pLastAnmObj,
                          dataIdx & NNS_G3D_ANMOBJ_MAPDATA_DATAFIELD);
            return 1;
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
                    p->ratio > 0) {
                    fx32 ratio;

                    func_01ffb234(&r, p,
                                  dataIdx & NNS_G3D_ANMOBJ_MAPDATA_DATAFIELD);

                    if (i1 == 0) {
                        keepAxisX.x = pResult->rot._00;
                        keepAxisX.y = pResult->rot._01;
                        keepAxisX.z = pResult->rot._02;
                        keepAxisZ.x = pResult->rot._20;
                        keepAxisZ.y = pResult->rot._21;
                        keepAxisZ.z = pResult->rot._22;
                    }

                    if (sumOfRatio != 0x1000) {
                        ratio = FX_Inv(p->ratio, sumOfRatio);
                    } else {
                        ratio = p->ratio;
                    }

                    func_02027908(&pResult->scale, &r.scale, ratio,
                                  r.flag & NNS_G3D_JNTANM_RESULTFLAG_SCALE_ONE);
                    func_02027908(&pResult->scaleEx0, &r.scaleEx0, ratio,
                                  r.flag & NNS_G3D_JNTANM_RESULTFLAG_SCALEEX0_ONE);
                    func_02027908(&pResult->scaleEx1, &r.scaleEx1, ratio,
                                  r.flag & NNS_G3D_JNTANM_RESULTFLAG_SCALEEX1_ONE);

                    if (!(r.flag & NNS_G3D_JNTANM_RESULTFLAG_TRANS_ZERO)) {
                        pResult->trans.x += (fx32)((s64)ratio * r.trans.x >> 12);
                        pResult->trans.y += (fx32)((s64)ratio * r.trans.y >> 12);
                        pResult->trans.z += (fx32)((s64)ratio * r.trans.z >> 12);
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
            p = p->next;
            ++i1;
        } while (p);

        VEC_CrossProduct((VecFx32 *)&pResult->rot._00,
                         (VecFx32 *)&pResult->rot._10,
                         (VecFx32 *)&pResult->rot._20);

        squareAxisX =
            (s64)pResult->rot._00 * pResult->rot._00 +
            (s64)pResult->rot._01 * pResult->rot._01 +
            (s64)pResult->rot._02 * pResult->rot._02;
        if (squareAxisX != 0) {
            StartNormalize(squareAxisX);
        }

        squareAxisZ =
            (s64)pResult->rot._20 * pResult->rot._20 +
            (s64)pResult->rot._21 * pResult->rot._21 +
            (s64)pResult->rot._22 * pResult->rot._22;
        if (squareAxisX != 0) {
            normalizeScaleX = ReadNormalizeScale();
        }
        if (squareAxisZ != 0) {
            StartNormalize(squareAxisZ);
        }

        if (squareAxisX != 0) {
            ApplyNormalize((VecFx32 *)&pResult->rot._00, normalizeScaleX);
        } else {
            pResult->rot._00 = keepAxisX.x;
            pResult->rot._01 = keepAxisX.y;
            pResult->rot._02 = keepAxisX.z;
        }

        if (squareAxisZ != 0) {
            normalizeScaleZ = ReadNormalizeScale();
            ApplyNormalize((VecFx32 *)&pResult->rot._20, normalizeScaleZ);
        } else {
            pResult->rot._20 = keepAxisZ.x;
            pResult->rot._21 = keepAxisZ.y;
            pResult->rot._22 = keepAxisZ.z;
        }

        VEC_CrossProduct((VecFx32 *)&pResult->rot._20,
                         (VecFx32 *)&pResult->rot._00,
                         (VecFx32 *)&pResult->rot._10);
        return 1;
    }
}
