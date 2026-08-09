typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;
typedef signed short fx16;
typedef signed long fx32;

typedef struct VecFx32 {
    fx32 x, y, z;
} VecFx32;

typedef union MtxFx33 {
    struct {
        fx32 _00, _01, _02;
        fx32 _10, _11, _12;
        fx32 _20, _21, _22;
    };
    fx32 a[9];
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

typedef struct NNSG3dRS {
    const u8 *c;
    u8 padding_004_to_0d4[0xd0];
    const NNSG3dResNodeInfo *pResNodeInfo;
} NNSG3dRS;

extern NNSG3dRS *data_020475d0;
extern const u8 data_02041ae0[];
extern const u8 data_02041ae1[];
extern const u8 data_02041ae2[];
extern const u8 data_02041ae3[];
extern void MI_Zero36B(void *dest);

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

void func_02017404(NNSG3dJntAnmResult *pResult)
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
            fx32 A = *(fx16 *)(p + 0);
            fx32 B = *(fx16 *)(p + sizeof(fx16));
            u32 idxPivot = (u32)((pNd->flag & 0x00f0) >> 4);

            MI_Zero36B(&pResult->rot);

            pResult->rot.a[idxPivot] =
                (pNd->flag & 0x0100) ? -0x1000 : 0x1000;

            pResult->rot.a[data_02041ae0[idxPivot * 4]] = A;
            pResult->rot.a[data_02041ae1[idxPivot * 4]] = B;

            pResult->rot.a[data_02041ae2[idxPivot * 4]] =
                (pNd->flag & 0x0200) ? -B : B;

            pResult->rot.a[data_02041ae3[idxPivot * 4]] =
                (pNd->flag & 0x0400) ? -A : A;
        } else {
            const fx16 *pp = (const fx16 *)p;

            pResult->rot.a[0] = pNd->_00;
            pResult->rot.a[1] = *(pp + 0);
            pResult->rot.a[2] = *(pp + 1);
            pResult->rot.a[3] = *(pp + 2);
            pResult->rot.a[4] = *(pp + 3);
            pResult->rot.a[5] = *(pp + 4);
            pResult->rot.a[6] = *(pp + 5);
            pResult->rot.a[7] = *(pp + 6);
            pResult->rot.a[8] = *(pp + 7);
        }
    } else {
        pResult->flag |= 2;
    }
}
