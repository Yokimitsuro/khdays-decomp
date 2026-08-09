typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;
typedef signed long fx32;
typedef int BOOL;

typedef struct NNSG3dVisAnmResult {
    BOOL isVisible;
} NNSG3dVisAnmResult;

struct NNSG3dAnmObj;
typedef void (*NNSG3dFuncAnmVis)(NNSG3dVisAnmResult *, const struct NNSG3dAnmObj *, u32);

typedef struct NNSG3dAnmObj {
    fx32 frame;
    fx32 ratio;
    void *resAnm;
    NNSG3dFuncAnmVis funcAnm;
    struct NNSG3dAnmObj *next;
    const void *resTex;
    u8 priority;
    u8 numMapData;
    u16 mapData[1];
} NNSG3dAnmObj;

enum {
    NNS_G3D_ANMOBJ_MAPDATA_EXIST = 0x0100,
    NNS_G3D_ANMOBJ_MAPDATA_DISABLED = 0x0200,
    NNS_G3D_ANMOBJ_MAPDATA_DATAFIELD = 0x00ff
};

BOOL func_020161dc(NNSG3dVisAnmResult *pResult, const NNSG3dAnmObj *pAnmObj, u32 nodeID)
{
    BOOL rval = 0;
    const NNSG3dAnmObj *p;
    NNSG3dVisAnmResult tmp;

    p = pAnmObj;
    pResult->isVisible = 0;
    do {
        if (nodeID < p->numMapData) {
            u32 dataIdx = p->mapData[nodeID];

            if ((dataIdx & (NNS_G3D_ANMOBJ_MAPDATA_EXIST |
                            NNS_G3D_ANMOBJ_MAPDATA_DISABLED)) ==
                NNS_G3D_ANMOBJ_MAPDATA_EXIST) {
                NNSG3dFuncAnmVis func = p->funcAnm;
                if (func) {
                    (*func)(&tmp, p, dataIdx & NNS_G3D_ANMOBJ_MAPDATA_DATAFIELD);
                    pResult->isVisible |= tmp.isVisible;
                    rval = 1;
                }
            }
        }
        p = p->next;
    } while (p);

    return rval;
}
