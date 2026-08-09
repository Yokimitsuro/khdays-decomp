typedef unsigned short u16;
typedef unsigned long u32;

typedef enum NNSG2dBGSelect {
    NNS_G2D_BGSELECT_MAIN0,
    NNS_G2D_BGSELECT_MAIN1,
    NNS_G2D_BGSELECT_MAIN2,
    NNS_G2D_BGSELECT_MAIN3,
    NNS_G2D_BGSELECT_SUB0,
    NNS_G2D_BGSELECT_SUB1,
    NNS_G2D_BGSELECT_SUB2,
    NNS_G2D_BGSELECT_SUB3
} NNSG2dBGSelect;

typedef enum NNSG2dScreenFormat {
    NNS_G2D_SCREENFORMAT_TEXT,
    NNS_G2D_SCREENFORMAT_AFFINE,
    NNS_G2D_SCREENFORMAT_AFFINEEXT
} NNSG2dScreenFormat;

typedef enum NNSG2dScreenColorMode {
    NNS_G2D_SCREENCOLORMODE_16x16,
    NNS_G2D_SCREENCOLORMODE_256x1
} NNSG2dScreenColorMode;

typedef enum GXBGColorMode {
    GX_BG_COLORMODE_16,
    GX_BG_COLORMODE_256
} GXBGColorMode;

typedef int GXBGScrBase;
typedef int GXBGCharBase;

typedef struct NNSG2dScreenData {
    u16 screenWidth;
    u16 screenHeight;
    u16 colorMode;
    u16 screenFormat;
    u32 szByte;
    u32 rawData[1];
} NNSG2dScreenData;

typedef struct NNSG2dCharacterData NNSG2dCharacterData;
typedef struct NNSG2dPaletteData NNSG2dPaletteData;
typedef struct NNSG2dCharacterPosInfo NNSG2dCharacterPosInfo;
typedef struct NNSG2dPaletteCompressInfo NNSG2dPaletteCompressInfo;

extern void func_02013020(NNSG2dBGSelect bg,
                          NNSG2dScreenFormat screenFormat,
                          GXBGColorMode colorMode,
                          int screenWidth, int screenHeight,
                          GXBGScrBase screenBase,
                          GXBGCharBase characterBase);
extern void func_020133ac(NNSG2dBGSelect bg,
                          const NNSG2dScreenData *pScreenData,
                          const NNSG2dCharacterData *pCharacterData,
                          const NNSG2dPaletteData *pPaletteData,
                          const NNSG2dCharacterPosInfo *pPositionInfo,
                          const NNSG2dPaletteCompressInfo *pCompressInfo);

static inline GXBGColorMode GetScreenColorMode(const NNSG2dScreenData *pScreenData)
{
    return pScreenData->colorMode == NNS_G2D_SCREENCOLORMODE_16x16
         ? GX_BG_COLORMODE_16 : GX_BG_COLORMODE_256;
}

static inline NNSG2dScreenFormat GetScreenFormat(const NNSG2dScreenData *pScreenData)
{
    return (NNSG2dScreenFormat)pScreenData->screenFormat;
}

void func_02013408(NNSG2dBGSelect bg,
                   const NNSG2dScreenData *pScreenData,
                   const NNSG2dCharacterData *pCharacterData,
                   const NNSG2dPaletteData *pPaletteData,
                   const NNSG2dCharacterPosInfo *pPositionInfo,
                   const NNSG2dPaletteCompressInfo *pCompressInfo,
                   GXBGScrBase screenBase,
                   GXBGCharBase characterBase)
{
    func_02013020(bg,
                  GetScreenFormat(pScreenData),
                  GetScreenColorMode(pScreenData),
                  pScreenData->screenWidth,
                  pScreenData->screenHeight,
                  screenBase,
                  characterBase);
    func_020133ac(bg, pScreenData, pCharacterData, pPaletteData,
                  pPositionInfo, pCompressInfo);
}
