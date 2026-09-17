typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed char s8;
typedef short s16;
typedef int s32;
typedef unsigned long long u64;
typedef long long s64;
typedef int BOOL;
typedef int OSIntrMode;
typedef void *OSMessage;
typedef volatile unsigned short vu16;
typedef volatile unsigned int vu32;
typedef volatile unsigned char vu8;

#define NULL ((void *)0)
#define TRUE 1
#define FALSE 0
#define HW_MAIN_MEM 0x02000000

#define offsetof(type, member) ((u32)&(((type *)0)->member))

#define REG_G3_POLYGON_ATTR_ID_SHIFT 24
#define REG_G3_POLYGON_ATTR_ID_MASK 0x3f000000

typedef s32 fx32;
typedef s16 fx16;
typedef int (*MIDeviceReadFunction)(void * userdata, void * buffer, u32 offset, u32 length);
typedef int (*MIDeviceWriteFunction)(void * userdata, const void * buffer, u32 offset, u32 length);
typedef enum {
    PXI_FIFO_TAG_EX = 0,
    PXI_FIFO_TAG_USER_0,
    PXI_FIFO_TAG_USER_1,
    PXI_FIFO_TAG_SYSTEM,
    PXI_FIFO_TAG_NVRAM,
    PXI_FIFO_TAG_RTC,
    PXI_FIFO_TAG_TOUCHPANEL,
    PXI_FIFO_TAG_SOUND,
    PXI_FIFO_TAG_PM,
    PXI_FIFO_TAG_MIC,
    PXI_FIFO_TAG_WM,
    PXI_FIFO_TAG_FS,
    PXI_FIFO_TAG_OS,
    PXI_FIFO_TAG_CTRDG,
    PXI_FIFO_TAG_CARD,
    PXI_FIFO_TAG_WVR,
    PXI_FIFO_TAG_CTRDG_Ex,
    PXI_FIFO_TAG_CTRDG_PHI,
    PXI_MAX_FIFO_TAG = 32
} PXIFifoTag;
typedef void (*PXIFifoCallback) (PXIFifoTag tag, u32 data, BOOL err);
typedef void * (*MIAllocatorAllocFunction)(void * userdata, u32 length, u32 alignment);
typedef void (*MIAllocatorFreeFunction)(void * userdata, void * buffer);
typedef u16 NNSG3dItemTag;
typedef struct NNSG3dResDictTreeNode_ {
    u8 refBit;
    u8 idxLeft;
    u8 idxRight;
    u8 idxEntry;
} NNSG3dResDictTreeNode;
typedef struct NNSG3dResDict_ {
    u8 revision;
    u8 numEntry;
    u16 sizeDictBlk;
    u16 dummy_;
    u16 ofsEntry;
    NNSG3dResDictTreeNode node[1];
} NNSG3dResDict;
typedef struct NNSG3dResDictEntryHeader_ {
    u16 sizeUnit;
    u16 ofsName;
    u8 data[4];
} NNSG3dResDictEntryHeader;
typedef struct NNSG3dResDictMatData_ {
    u32 offset;
} NNSG3dResDictMatData;
typedef struct NNSG3dResMatData_ {
    NNSG3dItemTag itemTag;
    u16 size;
    u32 diffAmb;
    u32 specEmi;
    u32 polyAttr;
    u32 polyAttrMask;
    u32 texImageParam;
    u32 texImageParamMask;
    u16 texPlttBase;
    u16 flag;
    u16 origWidth, origHeight;
    fx32 magW;
    fx32 magH;
} NNSG3dResMatData;
typedef struct NNSG3dResMat_ {
    u16 ofsDictTexToMatList;
    u16 ofsDictPlttToMatList;
    NNSG3dResDict dict;
} NNSG3dResMat;
typedef struct NNSG3dResMdlInfo_ {
    u8 sbcType;
    u8 scalingRule;
    u8 texMtxMode;
    u8 numNode;
    u8 numMat;
    u8 numShp;
    u8 firstUnusedMtxStackID;
    u8 dummy_;
    fx32 posScale;
    fx32 invPosScale;
    u16 numVertex;
    u16 numPolygon;
    u16 numTriangle;
    u16 numQuad;
    fx16 boxX, boxY, boxZ;
    fx16 boxW, boxH, boxD;
    fx32 boxPosScale;
    fx32 boxInvPosScale;
} NNSG3dResMdlInfo;
typedef struct NNSG3dResNodeInfo_ {
    NNSG3dResDict dict;
} NNSG3dResNodeInfo;
typedef struct NNSG3dResMdl_ {
    u32 size;
    u32 ofsSbc;
    u32 ofsMat;
    u32 ofsShp;
    u32 ofsEvpMtx;
    NNSG3dResMdlInfo info;
    NNSG3dResNodeInfo nodeInfo;
} NNSG3dResMdl;
inline void * NNS_G3dGetResDataByIdx(const NNSG3dResDict * dict, u32 idx);
inline NNSG3dResMat * NNS_G3dGetMat(const NNSG3dResMdl * mdl);
inline NNSG3dResMatData * NNS_G3dGetMatDataByIdx(const NNSG3dResMat * mat, u32 idx);
inline void * NNS_G3dGetResDataByIdx (const NNSG3dResDict * dict, u32 idx)
{
    NNSG3dResDictEntryHeader * hdr;
    if (dict != NULL && idx < dict->numEntry) {
        hdr = (NNSG3dResDictEntryHeader *)((u8 *)dict + dict->ofsEntry);
        return (void *)(&hdr->data[0] + hdr->sizeUnit * idx);
    } else {
        return NULL ;
    }
}
inline NNSG3dResMat * NNS_G3dGetMat (const NNSG3dResMdl * mdl)
{
    if (mdl && mdl->ofsMat != 0)
        return (NNSG3dResMat *)((u8 *)mdl + mdl->ofsMat);
    else
        return NULL ;
}
inline NNSG3dResMatData * NNS_G3dGetMatDataByIdx (const NNSG3dResMat * mat, u32 idx)
{
    NNSG3dResDictMatData * data;
    if (mat) {
        data = (NNSG3dResDictMatData *)NNS_G3dGetResDataByIdx(&mat->dict, idx);
        if (data) {
            return (NNSG3dResMatData *)((u8 *)mat + data->offset);
        }
    }
    return NULL ;
}

/* func_02016b60 -- NitroSystem model.c: NNS_G3dMdlSetMdlPolygonID. */
void func_02016b60 (NNSG3dResMdl * pMdl, u32 matID, int polygonID)
{
    NNSG3dResMatData * data;

    data = NNS_G3dGetMatDataByIdx(NNS_G3dGetMat(pMdl), matID);

    data->polyAttr = (data->polyAttr & ~REG_G3_POLYGON_ATTR_ID_MASK) |
                     (polygonID << REG_G3_POLYGON_ATTR_ID_SHIFT);
}
