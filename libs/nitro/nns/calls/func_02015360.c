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

typedef union NNSG3dResName {
    char name[16];
    u32 val[4];
} NNSG3dResName;

typedef struct NNSG3dResDictPlttToMatIdxData {
    u16 offset;
    u8 numIdx;
    u8 flag;
} NNSG3dResDictPlttToMatIdxData;

typedef struct NNSG3dResDictPlttData {
    u16 offset;
    u16 flag;
} NNSG3dResDictPlttData;

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

typedef struct NNSG3dResPlttInfo {
    u32 vramKey;
    u16 sizePltt;
    u16 flag;
    u16 ofsDict;
    u16 dummy;
    u32 ofsPlttData;
} NNSG3dResPlttInfo;

typedef struct NNSG3dResTex {
    u32 headerKind;
    u32 headerSize;
    NNSG3dResTexInfo texInfo;
    NNSG3dResTex4x4Info tex4x4Info;
    NNSG3dResPlttInfo plttInfo;
    NNSG3dResDict dict;
} NNSG3dResTex;

extern void *func_02016d50(const NNSG3dResDict *dict, const NNSG3dResName *name);
extern void func_02015280(NNSG3dResMat *pMat,
                          NNSG3dResDictPlttToMatIdxData *pBindData,
                          const NNSG3dResTex *pTex,
                          const NNSG3dResDictPlttData *pPlttData);

static inline const NNSG3dResName *NNS_G3dGetResNameByIdx(const NNSG3dResDict *dict, u32 idx)
{
    NNSG3dResDictEntryHeader *hdr;

    if (dict != 0 && idx < dict->numEntry) {
        hdr = (NNSG3dResDictEntryHeader *)((u8 *)dict + dict->ofsEntry);
        return (NNSG3dResName *)((u8 *)hdr + hdr->ofsName + sizeof(NNSG3dResName) * idx);
    } else {
        return 0;
    }
}

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

static inline NNSG3dResDictPlttData *NNS_G3dGetPlttDataByName(
    const NNSG3dResTex *tex, const NNSG3dResName *name)
{
    NNSG3dResDict *dict;

    if (tex && tex->plttInfo.ofsDict != 0) {
        dict = (NNSG3dResDict *)((u8 *)tex + tex->plttInfo.ofsDict);
        return (NNSG3dResDictPlttData *)func_02016d50(dict, name);
    } else {
        return 0;
    }
}

BOOL func_02015360(NNSG3dResMdl *pMdl, const NNSG3dResTex *pTex)
{
    NNSG3dResMat *mat;
    NNSG3dResDict *dictPltt;
    u32 i;
    BOOL result = 1;

    mat = NNS_G3dGetMat(pMdl);
    dictPltt = (NNSG3dResDict *)((u8 *)mat + mat->ofsDictPlttToMatList);

    for (i = 0; i < dictPltt->numEntry; ++i) {
        const NNSG3dResName *name = NNS_G3dGetResNameByIdx(dictPltt, i);
        const NNSG3dResDictPlttData *plttData = NNS_G3dGetPlttDataByName(pTex, name);

        if (plttData) {
            NNSG3dResDictPlttToMatIdxData *data;
            data = (NNSG3dResDictPlttToMatIdxData *)NNS_G3dGetResDataByIdx(dictPltt, i);

            if (!(data->flag & 1)) {
                func_02015280(mat, data, pTex, plttData);
            }
        } else {
            result = 0;
        }
    }
    return result;
}
