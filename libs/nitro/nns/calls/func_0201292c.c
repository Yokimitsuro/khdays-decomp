typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;
typedef int BOOL;

#define NULL ((void *)0)

typedef enum GXTexFmt {
    GX_TEXFMT_NONE = 0,
    GX_TEXFMT_A3I5 = 1,
    GX_TEXFMT_PLTT4 = 2,
    GX_TEXFMT_PLTT16 = 3,
    GX_TEXFMT_PLTT256 = 4
} GXTexFmt;

typedef enum NNSG2dBGExtPlttSlot {
    NNS_G2D_BGEXTPLTTSLOT_MAIN0,
    NNS_G2D_BGEXTPLTTSLOT_MAIN1,
    NNS_G2D_BGEXTPLTTSLOT_MAIN2,
    NNS_G2D_BGEXTPLTTSLOT_MAIN3,
    NNS_G2D_BGEXTPLTTSLOT_SUB0,
    NNS_G2D_BGEXTPLTTSLOT_SUB1,
    NNS_G2D_BGEXTPLTTSLOT_SUB2,
    NNS_G2D_BGEXTPLTTSLOT_SUB3
} NNSG2dBGExtPlttSlot;

typedef struct NNSG2dPaletteCompressInfo {
    u16 numPalette;
    u16 pad16;
    void *pPlttIdxTbl;
} NNSG2dPaletteCompressInfo;

typedef struct NNSG2dPaletteData {
    GXTexFmt fmt;
    BOOL bExtendedPlt;
    u32 szByte;
    void *pRawData;
} NNSG2dPaletteData;

typedef u16 GXBGPltt16[16];
typedef u16 GXBGPltt256[256];

extern void DC_FlushRange(const void *startAddr, u32 nBytes);
extern void GX_BeginLoadBGExtPltt(void);
extern void GX_LoadBGExtPltt(const void *src, u32 destSlotAddr, u32 szByte);
extern void GX_EndLoadBGExtPltt(void);
extern void GXS_BeginLoadBGExtPltt(void);
extern void GXS_LoadBGExtPltt(const void *src, u32 destSlotAddr, u32 szByte);
extern void GXS_EndLoadBGExtPltt(void);

static inline BOOL IsMainBGExtPlttSlot(NNSG2dBGExtPlttSlot slot)
{
    return slot <= NNS_G2D_BGEXTPLTTSLOT_MAIN3;
}

static inline u32 GetCompressedPlttOriginalIndex(
    const NNSG2dPaletteCompressInfo *pCmpInfo,
    int idx)
{
    return ((u16 *)pCmpInfo->pPlttIdxTbl)[idx];
}

static inline u32 GetPlttSize(const NNSG2dPaletteData *pPltData)
{
    switch (pPltData->fmt) {
    case GX_TEXFMT_PLTT16:
        return sizeof(GXBGPltt16);
    case GX_TEXFMT_PLTT256:
        return sizeof(GXBGPltt256);
    default:
        break;
    }
    return 0;
}

#pragma opt_dead_assignments off
void func_0201292c(NNSG2dBGExtPlttSlot slot,
                   const NNSG2dPaletteData *pPltData,
                   const NNSG2dPaletteCompressInfo *pCmpInfo)
{
    u32 offset;
    void (*prepairLoad)(void);
    void (*cleanupLoad)(void);
    void (*loader)(const void *, u32, u32);
    int i;
    u32 szOnePltt;
    u16 offsetAddr;

    offset = 0;
    i = 0;
    offsetAddr = 0;
    szOnePltt = 0;
    offset = (u32)(slot * 0x2000);

    DC_FlushRange(pPltData->pRawData, pPltData->szByte);

    if (slot <= NNS_G2D_BGEXTPLTTSLOT_MAIN3) {
        prepairLoad = GX_BeginLoadBGExtPltt;
        cleanupLoad = GX_EndLoadBGExtPltt;
        loader = GX_LoadBGExtPltt;
    } else {
        offset -= 0x2000 * NNS_G2D_BGEXTPLTTSLOT_SUB0;
        prepairLoad = GXS_BeginLoadBGExtPltt;
        cleanupLoad = GXS_EndLoadBGExtPltt;
        loader = GXS_LoadBGExtPltt;
    }

    if (pCmpInfo != NULL) {
        szOnePltt = GetPlttSize(pPltData);
        const int numIdx = pCmpInfo->numPalette;
        i = 0;

        if (numIdx <= 0) {
            return;
        }

        do {
            offsetAddr = GetCompressedPlttOriginalIndex(pCmpInfo, i);
            const void *pSrc =
                (u8 *)pPltData->pRawData + szOnePltt * i;

            prepairLoad();
            loader(pSrc, offset + szOnePltt * offsetAddr, szOnePltt);
            cleanupLoad();
            i++;
        } while (i < numIdx);
    } else {
        prepairLoad();
        loader(pPltData->pRawData, offset, pPltData->szByte);
        cleanupLoad();
    }
}
