typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;
typedef signed long fx32;
typedef int BOOL;

typedef struct MtxFx43 {
    fx32 m[4][3];
} MtxFx43;

typedef struct MtxFx33 {
    fx32 m[3][3];
} MtxFx33;

typedef struct NNSG3dResDict {
    u8 revision;
    u8 numEntry;
    u16 sizeDictBlk;
    u16 dummy_;
    u16 ofsEntry;
} NNSG3dResDict;

typedef struct NNSG3dResDictEntryHeader {
    u16 sizeUnit;
    u16 ofsName;
    u8 data[4];
} NNSG3dResDictEntryHeader;

typedef struct NNSG3dResDictNodeData {
    u32 offset;
} NNSG3dResDictNodeData;

typedef struct NNSG3dResNodeInfo {
    NNSG3dResDict dict;
} NNSG3dResNodeInfo;

typedef struct NNSG3dResNodeData {
    u16 flag;
} NNSG3dResNodeData;

typedef struct NNSG3dResMdl {
    u8 pad00_40[0x40];
    NNSG3dResNodeInfo nodeInfo;
} NNSG3dResMdl;

typedef struct NNSG3dRenderObj {
    u32 flag;
    NNSG3dResMdl *resMdl;
} NNSG3dRenderObj;

extern void func_01ff9f00(u32 op, const u32 *args, u32 num);
extern void func_02016294(MtxFx43 *pos, MtxFx33 *nrm);

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

static inline NNSG3dResNodeData *NNS_G3dGetNodeDataByIdx(const NNSG3dResNodeInfo *info, u32 idx)
{
    NNSG3dResDictNodeData *data;

    if (info) {
        data = (NNSG3dResDictNodeData *)NNS_G3dGetResDataByIdx(&info->dict, idx);
        if (data) {
            return (NNSG3dResNodeData *)((u8 *)info + data->offset);
        }
    }
    return 0;
}

static inline void NNS_G3dGeRestoreMtx(int num)
{
    func_01ff9f00(0x14, (u32 *)&num, 1);
}

BOOL func_02016320(const NNSG3dRenderObj *pRenderObj, MtxFx43 *pos, MtxFx33 *nrm, u32 nodeID)
{
    const NNSG3dResNodeData *nd;
    u32 stackID;

    nd = NNS_G3dGetNodeDataByIdx(&pRenderObj->resMdl->nodeInfo, nodeID);
    stackID = (nd->flag & 0xf800u) >> 11;

    if (stackID != 31) {
        NNS_G3dGeRestoreMtx((int)stackID);
        if (pos || nrm) {
            func_02016294(pos, nrm);
        }
        return 1;
    } else {
        return 0;
    }
}
