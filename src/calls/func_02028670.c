/* Computes the TEXIMAGE_PARAM / PLTT_BASE pair of texture 0 and palette 0 of a TEX0 file
 * (optionally set up first with the loader's texture flag off): the texture's image parameter plus
 * its vram base (4x4 textures use the 4x4 key) with repeat-S set, and the palette offset plus the
 * palette vram base, both halved for non-4-color palettes. Returns 1. Codegen: the palette values
 * are read offset first, then base (declared in that order after texBase). */
#pragma thumb on
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct {
    u8 revision;
    u8 numEntry;
    u16 sizeDictBlk;
    u16 dummy_;
    u16 ofsEntry;
} NNSG3dResDict;

typedef struct {
    u16 sizeUnit;
    u16 sizeName;
    u8 data[4];
} NNSG3dResDictEntryHeader;

typedef struct {
    u16 offset;
    u16 flag;
} NNSG3dResDictPlttData;

typedef struct {
    u32 header[2];
    u32 texVramKey;         /* 0x08 */
    u8 pad0c[0x18 - 0x0c];
    u32 tex4x4VramKey;      /* 0x18 */
    u8 pad1c[0x2c - 0x1c];
    u32 plttVramKey;        /* 0x2c */
    u16 sizePltt;           /* 0x30 */
    u16 plttFlag;           /* 0x32 */
    u16 plttOfsDict;        /* 0x34 */
    u16 pad36;
    u32 ofsPlttData;        /* 0x38 */
    NNSG3dResDict dict;     /* 0x3c */
} NNSG3dResTex;

extern void func_0201f390(int flag);
extern void func_02025138(void *file);
extern NNSG3dResTex *func_02017088(void *file);   /* NNS_G3dGetTex */

static inline void *GetResDataByIdx(const NNSG3dResDict *dict, u32 idx)
{
    if (dict != 0 && idx < dict->numEntry) {
        const NNSG3dResDictEntryHeader *hdr = (const NNSG3dResDictEntryHeader *)((u8 *)dict + dict->ofsEntry);

        return (void *)&hdr->data[idx * hdr->sizeUnit];
    }
    return 0;
}

int func_02028670(u32 *out, void *file, int setup)
{
    NNSG3dResTex *tex;
    const u32 *texData;
    const NNSG3dResDictPlttData *plttData;
    u16 texBase;
    u32 plttOfs;
    u32 plttBase;

    if (setup) {
        func_0201f390(0);
        func_02025138(file);
        func_0201f390(1);
    }
    tex = func_02017088(file);
    texData = tex ? GetResDataByIdx(&tex->dict, 0) : 0;
    if (tex && tex->plttOfsDict) {
        plttData = GetResDataByIdx((const NNSG3dResDict *)((u8 *)tex + tex->plttOfsDict), 0);
    } else {
        plttData = 0;
    }
    plttOfs = plttData->offset;
    plttBase = (u16)tex->plttVramKey;
    if (((*texData) & (7 << 26)) != (5 << 26)) {
        texBase = (u16)tex->texVramKey;
    } else {
        texBase = (u16)tex->tex4x4VramKey;
    }
    if (!(plttData->flag & 1)) {
        plttOfs = plttOfs << 15 >> 16;
        plttBase = plttBase << 15 >> 16;
    }
    out[0] = ((*texData) + texBase) | (2 << 28);
    out[1] = (u16)(plttOfs + plttBase);
    return 1;
}
