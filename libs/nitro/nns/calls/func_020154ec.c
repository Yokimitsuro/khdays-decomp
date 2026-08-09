typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;
typedef int BOOL;

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

typedef struct NNSG3dResDictMdlSetData {
    u32 offset;
} NNSG3dResDictMdlSetData;

typedef struct NNSG3dResMdl NNSG3dResMdl;
typedef struct NNSG3dResTex NNSG3dResTex;

typedef struct NNSG3dResMdlSet {
    u32 headerKind;
    u32 headerSize;
    NNSG3dResDict dict;
} NNSG3dResMdlSet;

extern BOOL func_020150f4(NNSG3dResMdl *pMdl, const NNSG3dResTex *pTex);
extern BOOL func_02015360(NNSG3dResMdl *pMdl, const NNSG3dResTex *pTex);

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

static inline NNSG3dResMdl *NNS_G3dGetMdlByIdx(const NNSG3dResMdlSet *mdlSet, u32 idx)
{
    NNSG3dResDictMdlSetData *data;

    if (mdlSet) {
        data = (NNSG3dResDictMdlSetData *)NNS_G3dGetResDataByIdx(&mdlSet->dict, idx);
        if (data) {
            return (NNSG3dResMdl *)((u8 *)mdlSet + data->offset);
        }
    }
    return 0;
}

BOOL func_020154ec(NNSG3dResMdlSet *pMdlSet, const NNSG3dResTex *pTex)
{
    u32 i;
    BOOL result = 1;

    for (i = 0; i < pMdlSet->dict.numEntry; ++i) {
        NNSG3dResMdl *mdl = NNS_G3dGetMdlByIdx(pMdlSet, i);

        result &= func_020150f4(mdl, pTex);
        result &= func_02015360(mdl, pTex);
    }
    return result;
}
