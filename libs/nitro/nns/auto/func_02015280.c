typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;
typedef long fx32;

typedef struct NNSG3dResDictTreeNode {
    u8 refBit;
    u8 idxLeft;
    u8 idxRight;
    u8 idxEntry;
} NNSG3dResDictTreeNode;

typedef struct NNSG3dResDict {
    u8 revision;
    u8 numEntry;
    u16 sizeDictBlk;
    u16 dummy;
    u16 ofsEntry;
    NNSG3dResDictTreeNode node[1];
} NNSG3dResDict;

typedef struct NNSG3dResDictEntryHeader {
    u16 sizeUnit;
    u16 ofsName;
    u8 data[4];
} NNSG3dResDictEntryHeader;

typedef struct NNSG3dResDictMatData {
    u32 offset;
} NNSG3dResDictMatData;

typedef struct NNSG3dResDictPlttToMatIdxData {
    u16 offset;
    u8 numIdx;
    u8 flag;
} NNSG3dResDictPlttToMatIdxData;

typedef struct NNSG3dResDictPlttData {
    u16 offset;
    u16 flag;
} NNSG3dResDictPlttData;

typedef struct NNSG3dResMatData {
    u16 itemTag;
    u16 size;
    u32 diffAmb;
    u32 specEmi;
    u32 polyAttr;
    u32 polyAttrMask;
    u32 texImageParam;
    u32 texImageParamMask;
    u16 texPlttBase;
    u16 flag;
    u16 origWidth;
    u16 origHeight;
    fx32 magW;
    fx32 magH;
} NNSG3dResMatData;

typedef struct NNSG3dResMat {
    u16 ofsDictTexToMatList;
    u16 ofsDictPlttToMatList;
    NNSG3dResDict dict;
} NNSG3dResMat;

typedef struct NNSG3dResTex {
    u8 pad[0x2c];
    u32 plttVramKey;
} NNSG3dResTex;

static inline void *NNS_G3dGetResDataByIdx(const NNSG3dResDict *dict, u32 idx)
{
    NNSG3dResDictEntryHeader *hdr;

    if (dict != 0 && idx < dict->numEntry) {
        hdr = (NNSG3dResDictEntryHeader *)((u8 *)dict + dict->ofsEntry);
        return (void *)(&hdr->data[0] + hdr->sizeUnit * idx);
    } else {
        return 0;
    }
}

static inline NNSG3dResMatData *NNS_G3dGetMatDataByIdx(const NNSG3dResMat *mat, u32 idx)
{
    NNSG3dResDictMatData *data;

    if (mat) {
        data = (NNSG3dResDictMatData *)NNS_G3dGetResDataByIdx(&mat->dict, idx);
        if (data) {
            return (NNSG3dResMatData *)((u8 *)mat + data->offset);
        }
    }
    return 0;
}

static inline u32 NNS_GfdGetTexKeyAddr(u32 key)
{
    return (u32)((key & 0xffff) << 3);
}

void func_02015280(NNSG3dResMat *pMat,
                   NNSG3dResDictPlttToMatIdxData *pBindData,
                   const NNSG3dResTex *pTex,
                   const NNSG3dResDictPlttData *pPlttData)
{
    u8 *base = (u8 *)pMat + pBindData->offset;
    u16 plttBase = pPlttData->offset;
    u16 vramOffset = (u16)(NNS_GfdGetTexKeyAddr(pTex->plttVramKey) >> 3);
    u32 j;

    if (!(pPlttData->flag & 1)) {
        plttBase >>= 1;
        vramOffset >>= 1;
    }

    for (j = 0; j < pBindData->numIdx; ++j) {
        NNSG3dResMatData *matData = NNS_G3dGetMatDataByIdx(pMat, *(base + j));
        matData->texPlttBase = (u16)(plttBase + vramOffset);
    }

    pBindData->flag |= 1;
}
