typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed char s8;
typedef short s16;
typedef int s32;
typedef unsigned long long u64;
typedef long long s64;
typedef int BOOL;
typedef int OSIntrMode;
typedef void *OSMessage;
typedef volatile unsigned short vu16;
typedef volatile unsigned int vu32;
typedef volatile unsigned char vu8;

#define NULL ((void *)0)
#define TRUE 1
#define FALSE 0
#define HW_MAIN_MEM 0x02000000

#define offsetof(type, member) ((u32)&(((type *)0)->member))



typedef enum {
    GX_TEXFMT_NONE       = 0,
    GX_TEXFMT_A3I5       = 1,
    GX_TEXFMT_PLTT4      = 2,
    GX_TEXFMT_PLTT16     = 3,
    GX_TEXFMT_PLTT256    = 4,
    GX_TEXFMT_COMP4x4    = 5,
    GX_TEXFMT_A5I3       = 6,
    GX_TEXFMT_DIRECT     = 7
} GXTexFmt;
typedef struct NNSG2dPaletteCompressInfo {
    u16 numPalette;
    u16 pad16;
    void * pPlttIdxTbl;
} NNSG2dPaletteCompressInfo;
typedef struct NNSG2dPaletteData {
    GXTexFmt fmt;
    BOOL bExtendedPlt;
    u32 szByte;
    void * pRawData;
} NNSG2dPaletteData;
typedef enum NNSG2dBGSelect {
    NNS_G2D_BGSELECT_MAIN0,
    NNS_G2D_BGSELECT_MAIN1,
    NNS_G2D_BGSELECT_MAIN2,
    NNS_G2D_BGSELECT_MAIN3,
    NNS_G2D_BGSELECT_SUB0,
    NNS_G2D_BGSELECT_SUB1,
    NNS_G2D_BGSELECT_SUB2,
    NNS_G2D_BGSELECT_SUB3,
    NNS_G2D_BGSELECT_NUM
} NNSG2dBGSelect;
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
extern void func_0201292c (NNSG2dBGExtPlttSlot slot, const NNSG2dPaletteData * pPltData, const NNSG2dPaletteCompressInfo * pCmpInfo);
extern void func_02012a5c (NNSG2dBGSelect bg, const NNSG2dPaletteData * pPltData, const NNSG2dPaletteCompressInfo * pCmpInfo);
extern NNSG2dBGExtPlttSlot func_02012b6c (NNSG2dBGSelect bg);

/* func_02012de4 -- NitroSystem g2d_Screen.c: LoadBGPaletteSelect. */
void func_02012de4 (NNSG2dBGSelect bg, BOOL bToExtPltt, const NNSG2dPaletteData * pPltData, const NNSG2dPaletteCompressInfo * pCmpInfo)
{

    if (bToExtPltt) {
        NNSG2dBGExtPlttSlot slot = func_02012b6c(bg);
        func_0201292c(slot, pPltData, pCmpInfo);
    } else {
        func_02012a5c(bg, pPltData, pCmpInfo);
    }
}
