/* func_ov106_020b84b8 -- Ov106_LoadNoiseTexture: load the noise overlay's texture into the
 * state block data_ov106_020b8b68 points at.  The resource is opened (0201ef9c, kind 0xd),
 * set up under the handler pair (0201f390 0 / 1, 02025138) and its texture block taken
 * (NNS_G3dGetTex 02017088); from the first texture and palette entries the block keeps the
 * texture image parameter plus the VRAM key of its format (+0x74, with bit 29 set), the
 * palette base (+0x78, offset plus key, halved for 16-colour palettes), the width (+0x7c) and
 * height (+0x80) fields of the extra parameter; the resource file is freed.
 * PROVENANCE: byte-identical twin of ov023's Ov023_LoadNoiseTexture (func_ov023_02089760), same code and
 * pool layout in the ov106 event scene; the ov023 source is the analysed one. */
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

typedef struct Ov023NoiseState {
    u8   pad_00[0x74];
    u32  nTexImageParam;      /* 0x74 */
    u32  nPlttBase;           /* 0x78 */
    u32  nWidth;              /* 0x7c */
    u32  nHeight;             /* 0x80 */
} Ov023NoiseState;

extern NNSG3dResFileHeader *func_0201ef9c(const char *pszName, int nKind); /* open a resource file */
extern void func_0201f390(int bPhase);                                    /* InstallHandlerPairByFlag */
extern void func_02025138(NNSG3dResFileHeader *pResource);               /* set a resource up */
extern NNSG3dResTex *func_02017088(const NNSG3dResFileHeader *resource);  /* NNS_G3dGetTex */
extern void NNSi_FndFreeFromDefaultHeap(void *pBlock);
extern Ov023NoiseState *data_ov106_020b8b68;                              /* the noise overlay state */

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

void func_ov106_020b84b8(const char *pszTexture)
{
    NNSG3dResFileHeader *pResource;
    NNSG3dResTex *tex;
    NNSG3dResDictTexData *texData;
    NNSG3dResDictPlttData *plttData;
    u16 texOffset;
    u16 plttOffset;
    u16 plttBase;

    pResource = func_0201ef9c(pszTexture, 0xd);
    func_0201f390(0);
    func_02025138(pResource);
    func_0201f390(1);
    tex = func_02017088(pResource);
    texData = NNS_G3dGetTexDataByIdx(tex, 0);
    plttData = NNS_G3dGetPlttDataByIdx(tex, 0);
    plttOffset = plttData->offset;
    plttBase = (u16)tex->plttInfo.vramKey;
    if ((texData->texImageParam & 0x1c000000) != 0x14000000) {
        texOffset = tex->texInfo.vramKey;
    } else {
        texOffset = tex->tex4x4Info.vramKey;
    }
    if ((plttData->flag & 1) == 0) {
        plttOffset >>= 1;
        plttBase >>= 1;
    }
    data_ov106_020b8b68->nWidth = (u16)(texData->extraParam & 0x7ff);
    data_ov106_020b8b68->nHeight = (u16)((texData->extraParam >> 11) & 0x7ff);
    data_ov106_020b8b68->nPlttBase = (u16)(plttOffset + plttBase);
    data_ov106_020b8b68->nTexImageParam = (texData->texImageParam + texOffset) | 0x20000000;
    NNSi_FndFreeFromDefaultHeap(pResource);
}
