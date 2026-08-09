typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;
typedef long fx32;

typedef struct NNSG3dResMdl NNSG3dResMdl;
typedef struct NNSG3dResTex NNSG3dResTex;

typedef struct NNSG3dResAnmHeader {
    u8 category0;
    u8 revision;
    u16 category1;
} NNSG3dResAnmHeader;

typedef struct NNSG3dAnmObj {
    fx32 frame;
    fx32 ratio;
    void *resAnm;
    void *funcAnm;
    struct NNSG3dAnmObj *next;
    const NNSG3dResTex *resTex;
    u8 priority;
    u8 numMapData;
    u16 mapData[1];
} NNSG3dAnmObj;

typedef struct NNSG3dRenderObj {
    u32 flag;
    NNSG3dResMdl *resMdl;
    NNSG3dAnmObj *anmMat;
    void *funcBlendMat;
    NNSG3dAnmObj *anmJnt;
    void *funcBlendJnt;
    NNSG3dAnmObj *anmVis;
    void *funcBlendVis;
    void *cbFunc;
    u8 cbCmd;
    u8 cbTiming;
    u16 dummy;
    void *cbInitFunc;
    void *ptrUser;
    u8 *ptrUserSbc;
    void *recJntAnm;
    void *recMatAnm;
    u32 hintMatAnmExist[2];
    u32 hintJntAnmExist[2];
    u32 hintVisAnmExist[2];
} NNSG3dRenderObj;

extern void func_02014c68(u32 *pVec, const NNSG3dAnmObj *pAnmObj);
extern void func_02014bb0(NNSG3dAnmObj **list, NNSG3dAnmObj *item);

void func_02014cd0(NNSG3dRenderObj *pRenderObj, NNSG3dAnmObj *pAnmObj)
{
    const NNSG3dResAnmHeader *hdr;

    if (pAnmObj && pAnmObj->resAnm) {
        hdr = (const NNSG3dResAnmHeader *)pAnmObj->resAnm;

        switch (hdr->category0) {
        case 'M':
            func_02014c68(&pRenderObj->hintMatAnmExist[0], pAnmObj);
            func_02014bb0(&pRenderObj->anmMat, pAnmObj);
            break;
        case 'J':
            func_02014c68(&pRenderObj->hintJntAnmExist[0], pAnmObj);
            func_02014bb0(&pRenderObj->anmJnt, pAnmObj);
            break;
        case 'V':
            func_02014c68(&pRenderObj->hintVisAnmExist[0], pAnmObj);
            func_02014bb0(&pRenderObj->anmVis, pAnmObj);
            break;
        default:
            break;
        }
    }
}
