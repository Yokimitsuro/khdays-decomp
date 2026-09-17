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
typedef enum {
    GX_OBJVRAMMODE_CHAR_2D      = (0 << 4 ) | (0 << 20 ),
    GX_OBJVRAMMODE_CHAR_1D_32K  = (1 << 4 ) | (0 << 20 ),
    GX_OBJVRAMMODE_CHAR_1D_64K  = (1 << 4 ) | (1 << 20 ),
    GX_OBJVRAMMODE_CHAR_1D_128K = (1 << 4 ) | (2 << 20 ),
    GX_OBJVRAMMODE_CHAR_1D_256K = (1 << 4 ) | (3 << 20 )
} GXOBJVRamModeChar;
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
typedef struct NNSG2dCharacterData {
    u16 H;
    u16 W;
    GXTexFmt pixelFmt;
    GXOBJVRamModeChar mappingType;
    u32 characterFmt;
    u32 szByte;
    void * pRawData;
} NNSG2dCharacterData;
typedef struct NNSG2dCharacterPosInfo {
    u16 srcPosX;
    u16 srcPosY;
    u16 srcW;
    u16 srcH;
} NNSG2dCharacterPosInfo;
typedef struct NNSG2dScreenData {
    u16 screenWidth;
    u16 screenHeight;
    u16 colorMode;
    u16 screenFormat;
    u32 szByte;
    u32 rawData[1];
} NNSG2dScreenData;
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
extern void func_02012e1c (NNSG2dBGSelect bg, const NNSG2dPaletteData * pPltData, const NNSG2dScreenData * pScnData, const NNSG2dPaletteCompressInfo * pCmpInfo);
extern void func_02012e90 (NNSG2dBGSelect bg, const NNSG2dCharacterData * pChrData, const NNSG2dCharacterPosInfo * pPosInfo);
extern void func_02012f54 (NNSG2dBGSelect bg, const NNSG2dScreenData * pScnData);

/* func_020133ac -- NitroSystem g2d_Screen.c: NNS_G2dBGLoadElementsEx. */
void func_020133ac (NNSG2dBGSelect bg, const NNSG2dScreenData * pScnData, const NNSG2dCharacterData * pChrData, const NNSG2dPaletteData * pPltData, const NNSG2dCharacterPosInfo * pPosInfo, const NNSG2dPaletteCompressInfo * pCmpInfo)
{


    if (pPltData != NULL && pScnData != NULL) {
        func_02012e1c(bg, pPltData, pScnData, pCmpInfo);
    }
    if (pChrData != NULL) {
        func_02012e90(bg, pChrData, pPosInfo);
    }
    if (pScnData != NULL) {
        func_02012f54(bg, pScnData);
    }
}
