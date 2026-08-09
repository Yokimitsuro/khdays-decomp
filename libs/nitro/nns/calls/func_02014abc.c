typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;
typedef long fx32;

typedef struct NNSG3dResMdl NNSG3dResMdl;
typedef struct NNSG3dResTex NNSG3dResTex;

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

typedef struct NNSG3dResAnmHeader {
    u8 category0;
    u8 revision;
    u16 category1;
} NNSG3dResAnmHeader;

typedef void (*NNSG3dAnimInitFunc)(NNSG3dAnmObj *, void *, const NNSG3dResMdl *);

typedef struct NNSG3dAnmObjInitFunc {
    u8 category0;
    u8 dummy;
    u16 category1;
    NNSG3dAnimInitFunc func;
} NNSG3dAnmObjInitFunc;

extern u32 data_02042490;
extern NNSG3dAnmObjInitFunc data_020424b4[];

void func_02014abc(NNSG3dAnmObj *pAnmObj, void *pResAnm,
                   const NNSG3dResMdl *pResMdl, const NNSG3dResTex *pResTex)
{
    const NNSG3dResAnmHeader *hdr;
    u32 i;

    pAnmObj->frame = 0;
    pAnmObj->resAnm = pResAnm;

    pAnmObj->next = 0;
    pAnmObj->priority = 127;
    pAnmObj->ratio = 0x1000;
    pAnmObj->resTex = pResTex;
    pAnmObj->numMapData = 0;
    pAnmObj->funcAnm = 0;

    hdr = (const NNSG3dResAnmHeader *)pResAnm;

    for (i = 0; i < data_02042490; ++i) {
        if (data_020424b4[i].category0 == hdr->category0 &&
            data_020424b4[i].category1 == hdr->category1) {
            if (data_020424b4[i].func) {
                (*data_020424b4[i].func)(pAnmObj, pResAnm, pResMdl);
            }
            break;
        }
    }
}
