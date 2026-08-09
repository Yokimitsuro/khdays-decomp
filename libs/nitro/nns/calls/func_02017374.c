typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;
typedef signed short fx16;
typedef signed long fx32;

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

typedef struct NNSG3dResDictTreeNode {
    u8 refBit, idxLeft, idxRight, idxEntry;
} NNSG3dResDictTreeNode;

typedef struct NNSG3dResDict {
    u8 revision;
    u8 numEntry;
    u16 sizeDictBlk;
    u16 dummy_;
    u16 ofsEntry;
    NNSG3dResDictTreeNode node[1];
} NNSG3dResDict;

typedef struct NNSG3dResDictEntryHeader {
    u16 sizeUnit;
    u16 ofsName;
    u8 data[4];
} NNSG3dResDictEntryHeader;

typedef struct NNSG3dResNodeInfo {
    NNSG3dResDict dict;
} NNSG3dResNodeInfo;

typedef struct NNSG3dResDictNodeData {
    u32 offset;
} NNSG3dResDictNodeData;

typedef struct NNSG3dResNodeData {
    u16 flag;
    fx16 _00;
} NNSG3dResNodeData;

typedef void (*NNSG3dFuncJntScale)(NNSG3dJntAnmResult *, const fx32 *, const u8 *, u32);

typedef struct NNSG3dRS {
    const u8 *c;
    u8 padding_004_to_0d4[0xd0];
    const NNSG3dResNodeInfo *pResNodeInfo;
    u8 padding_0d8_to_0e8[0x10];
    NNSG3dFuncJntScale funcJntScale;
} NNSG3dRS;

extern NNSG3dRS *data_020475d0;

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

static inline const NNSG3dResNodeData *NNS_G3dGetNodeDataByIdx(const NNSG3dResNodeInfo *info, u32 idx)
{
    NNSG3dResDictNodeData *data;

    if (info) {
        data = (NNSG3dResDictNodeData *)NNS_G3dGetResDataByIdx(&info->dict, idx);
        if (data) {
            return (const NNSG3dResNodeData *)((const u8 *)info + data->offset);
        }
    }
    return 0;
}

void func_02017374(NNSG3dJntAnmResult *pResult)
{
    u32 idxNode;
    const NNSG3dResNodeData *pNd;
    const u8 *p;

    idxNode = *(data_020475d0->c + 1);

    pNd = NNS_G3dGetNodeDataByIdx(data_020475d0->pResNodeInfo, idxNode);
    p = (const u8 *)pNd + sizeof(*pNd);

    if (!(pNd->flag & 1)) {
        p += 3 * sizeof(fx32);
    }

    if (!(pNd->flag & 2)) {
        if (pNd->flag & 8) {
            p += 2 * sizeof(fx16);
        } else {
            p += 8 * sizeof(fx16);
        }
    }

    (*data_020475d0->funcJntScale)(pResult, (const fx32 *)p,
                                   data_020475d0->c, pNd->flag);
}
