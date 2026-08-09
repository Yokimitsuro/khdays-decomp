typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;

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

typedef struct NNSG3dResDictTexToMatIdxData {
    u16 offset;
    u8 numIdx;
    u8 flag;
} NNSG3dResDictTexToMatIdxData;

typedef struct NNSG3dResMat {
    u16 ofsDictTexToMatList;
    u16 ofsDictPlttToMatList;
    NNSG3dResDict dict;
} NNSG3dResMat;

typedef struct NNSG3dResMdl {
    u32 size;
    u32 ofsSbc;
    u32 ofsMat;
} NNSG3dResMdl;

extern void func_0201503c(NNSG3dResMat *pMat, NNSG3dResDictTexToMatIdxData *pData);

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

static inline NNSG3dResMat *NNS_G3dGetMat(const NNSG3dResMdl *mdl)
{
    if (mdl && mdl->ofsMat != 0) {
        return (NNSG3dResMat *)((u8 *)mdl + mdl->ofsMat);
    } else {
        return 0;
    }
}

void func_020151f4(NNSG3dResMdl *pMdl)
{
    NNSG3dResMat *mat;
    NNSG3dResDict *dictTex;
    u32 i;

    mat = NNS_G3dGetMat(pMdl);
    dictTex = (NNSG3dResDict *)((u8 *)mat + mat->ofsDictTexToMatList);

    for (i = 0; i < dictTex->numEntry; ++i) {
        NNSG3dResDictTexToMatIdxData *data =
            (NNSG3dResDictTexToMatIdxData *)NNS_G3dGetResDataByIdx(dictTex, i);

        if (data->flag & 1) {
            func_0201503c(mat, data);
        }
    }
}
