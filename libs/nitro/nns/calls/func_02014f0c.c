typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;
typedef long s32;
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

typedef struct NNSG3dResDictTexToMatIdxData {
    u16 offset;
    u8 numIdx;
    u8 flag;
} NNSG3dResDictTexToMatIdxData;

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

typedef struct NNSG3dResTexInfo {
    u32 vramKey;
    u16 sizeTex;
    u16 ofsDict;
    u16 flag;
    u16 dummy;
    u32 ofsTex;
} NNSG3dResTexInfo;

typedef struct NNSG3dResTex4x4Info {
    u32 vramKey;
    u16 sizeTex;
    u16 ofsDict;
    u16 flag;
    u16 dummy;
    u32 ofsTex;
    u32 ofsTexPlttIdx;
} NNSG3dResTex4x4Info;

typedef struct NNSG3dResTex {
    u32 headerKind;
    u32 headerSize;
    NNSG3dResTexInfo texInfo;
    NNSG3dResTex4x4Info tex4x4Info;
} NNSG3dResTex;

typedef struct NNSG3dResDictTexData {
    u32 texImageParam;
    u32 extraParam;
} NNSG3dResDictTexData;

extern fx32 FX_Inv(fx32 numerator, fx32 denominator);

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

void func_02014f0c(NNSG3dResMat *pMat,
                   NNSG3dResDictTexToMatIdxData *pBindData,
                   const NNSG3dResTex *pTex,
                   const NNSG3dResDictTexData *pTexData)
{
    u8 *base = (u8 *)pMat + pBindData->offset;
    u32 vramOffset;
    u32 j;

    if ((pTexData->texImageParam & 0x1c000000) != (5 << 26)) {
        vramOffset = NNS_GfdGetTexKeyAddr(pTex->texInfo.vramKey) >> 3;
    } else {
        vramOffset = NNS_GfdGetTexKeyAddr(pTex->tex4x4Info.vramKey) >> 3;
    }

    for (j = 0; j < pBindData->numIdx; ++j) {
        s32 w, h;
        NNSG3dResMatData *matData = NNS_G3dGetMatDataByIdx(pMat, *(base + j));

        matData->texImageParam |= (pTexData->texImageParam + vramOffset);
        w = (s32)((pTexData->extraParam & 0x000007ff) >> 0);
        h = (s32)((pTexData->extraParam & 0x003ff800) >> 11);

        matData->magW = (w != matData->origWidth)
                            ? FX_Inv(w << 12, matData->origWidth << 12)
                            : 0x1000;
        matData->magH = (h != matData->origHeight)
                            ? FX_Inv(h << 12, matData->origHeight << 12)
                            : 0x1000;
    }

    pBindData->flag |= 1;
}
