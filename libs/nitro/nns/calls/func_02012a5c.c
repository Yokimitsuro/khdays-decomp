typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;
typedef int BOOL;

#define NULL ((void *)0)
#define GX_DMA_NOT_USE (-1)
#define HW_BG_PLTT ((void *)0x05000000)
#define HW_DB_BG_PLTT ((void *)0x05000400)

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

extern int data_020422b8;
extern void DC_FlushRange(const void *startAddr, u32 nBytes);
extern void MI_DmaCopy16(u32 dmaNo, const void *src, void *dest, u32 size);
extern void MIi_CpuCopy16(const void *src, void *dest, u32 size);

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

void func_02012a5c(NNSG2dBGExtPlttSlot slot,
                   const NNSG2dPaletteData *pPltData,
                   const NNSG2dPaletteCompressInfo *pCmpInfo)
{
    void *pPlttBase;

    DC_FlushRange(pPltData->pRawData, pPltData->szByte);

    if (slot <= NNS_G2D_BGEXTPLTTSLOT_MAIN3) {
        pPlttBase = HW_BG_PLTT;
    } else {
        pPlttBase = HW_DB_BG_PLTT;
    }

    if (pCmpInfo != NULL) {
        const u32 szOnePltt = GetPlttSize(pPltData);
        const int numIdx = pCmpInfo->numPalette;
        int i = 0;

        if (numIdx <= 0) {
            return;
        }

        do {
            const u32 offsetAddr =
                GetCompressedPlttOriginalIndex(pCmpInfo, i) * szOnePltt;
            const void *pSrc =
                (u8 *)pPltData->pRawData + szOnePltt * i;

            if (data_020422b8 != GX_DMA_NOT_USE) {
                MI_DmaCopy16(data_020422b8, pSrc,
                             (u8 *)pPlttBase + offsetAddr, szOnePltt);
            } else {
                MIi_CpuCopy16(pSrc, (u8 *)pPlttBase + offsetAddr,
                              szOnePltt);
            }
            i++;
        } while (i < numIdx);
    } else {
        const u32 szByte = pPltData->szByte;
        const void *pRawData = pPltData->pRawData;

        if (data_020422b8 != GX_DMA_NOT_USE) {
            MI_DmaCopy16(data_020422b8, pRawData, pPlttBase, szByte);
        } else {
            MIi_CpuCopy16(pRawData, pPlttBase, szByte);
        }
    }
}
