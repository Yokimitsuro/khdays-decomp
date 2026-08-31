typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;
typedef struct NNSG3dResDict {
    u8 revision, numEntry;
    u16 sizeDictBlk, dummy, ofsEntry;
    u8 node[4];
} NNSG3dResDict;
typedef struct NNSG3dResDictEntryHeader {
    u16 sizeUnit, ofsName;
    u8 data[4];
} NNSG3dResDictEntryHeader;
typedef struct NNSG3dResTexInfo {
    u32 vramKey;
    u16 sizeTex, ofsDict, flag, dummy;
    u32 ofsTex;
} NNSG3dResTexInfo;
typedef struct NNSG3dResTex4x4Info {
    u32 vramKey;
    u16 sizeTex, ofsDict, flag, dummy;
    u32 ofsTex, ofsTexPlttIdx;
} NNSG3dResTex4x4Info;
typedef struct NNSG3dResPlttInfo {
    u32 vramKey;
    u16 sizePltt, flag, ofsDict, dummy;
    u32 ofsPlttData;
} NNSG3dResPlttInfo;
typedef struct NNSG3dResTex {
    u32 headerKind, headerSize;
    NNSG3dResTexInfo texInfo;
    NNSG3dResTex4x4Info tex4x4Info;
    NNSG3dResPlttInfo plttInfo;
    NNSG3dResDict dict;
} NNSG3dResTex;
typedef struct NNSG3dResDictTexData {u32 texImageParam, extraParam;} NNSG3dResDictTexData;
typedef struct NNSG3dResDictPlttData {u16 offset, flag;} NNSG3dResDictPlttData;
typedef struct NNSG3dResFileHeader NNSG3dResFileHeader;
typedef struct Ov005TextureParams {u32 texImageParam, texPlttBase;} Ov005TextureParams;
extern NNSG3dResTex *func_02017088(const NNSG3dResFileHeader *resource);

static inline void *NNS_G3dGetResDataByIdx(const NNSG3dResDict *dict, u32 idx) {
    NNSG3dResDictEntryHeader *hdr;
    if (dict != 0 && idx < dict->numEntry) {
        hdr = (NNSG3dResDictEntryHeader *)((u8 *)dict + dict->ofsEntry);
        return &hdr->data[0] + hdr->sizeUnit * idx;
    } else {
        return 0;
    }
}
static inline NNSG3dResDictTexData *NNS_G3dGetTexDataByIdx(const NNSG3dResTex *tex, u32 idx) {
    if (tex) return (NNSG3dResDictTexData *)NNS_G3dGetResDataByIdx(&tex->dict, idx);
    else return 0;
}
static inline NNSG3dResDictPlttData *NNS_G3dGetPlttDataByIdx(const NNSG3dResTex *tex, u32 idx) {
    if (tex && tex->plttInfo.ofsDict != 0)
        return (NNSG3dResDictPlttData *)NNS_G3dGetResDataByIdx((NNSG3dResDict *)((u8 *)tex + tex->plttInfo.ofsDict), idx);
    else return 0;
}

void func_ov005_02050d64(Ov005TextureParams *params, const NNSG3dResFileHeader *resource) {
    NNSG3dResTex *tex = func_02017088(resource);
    NNSG3dResDictTexData *texData = NNS_G3dGetTexDataByIdx(tex, 0);
    NNSG3dResDictPlttData *plttData = NNS_G3dGetPlttDataByIdx(tex, 0);
    u32 flag;
    u16 texOffset;
    u16 plttBase;
    u32 texImageParam;
    u16 plttOffset;
    texImageParam = texData->texImageParam;
    plttBase = (u16)tex->plttInfo.vramKey;
    if ((texImageParam & 0x1c000000) != 0x14000000)
        texOffset = tex->texInfo.vramKey;
    else
        texOffset = tex->tex4x4Info.vramKey;
    flag = plttData->flag;
    plttOffset = plttData->offset;
    if ((flag & 1) == 0) {
        plttOffset >>= 1;
        plttBase >>= 1;
    }
    params->texImageParam = texImageParam + texOffset;
    params->texPlttBase = (u16)(plttOffset + plttBase);
}
