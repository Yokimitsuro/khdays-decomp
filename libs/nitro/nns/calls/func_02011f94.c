typedef unsigned long u32;
typedef unsigned short u16;
typedef int BOOL;

#define FALSE 0

typedef enum GXTexFmt {
    GX_TEXFMT_NONE = 0
} GXTexFmt;

typedef enum GXTexSizeS {
    GX_TEXSIZE_S8 = 0,
    GX_TEXSIZE_S16,
    GX_TEXSIZE_S32,
    GX_TEXSIZE_S64,
    GX_TEXSIZE_S128,
    GX_TEXSIZE_S256
} GXTexSizeS;

typedef enum GXTexSizeT {
    GX_TEXSIZE_T8 = 0
} GXTexSizeT;

typedef enum GXTexPlttColor0 {
    GX_TEXPLTTCOLOR0_USE = 0,
    GX_TEXPLTTCOLOR0_TRNS = 1
} GXTexPlttColor0;

typedef enum GXOBJVRamModeChar {
    GX_OBJVRAMMODE_CHAR_2D = 0
} GXOBJVRamModeChar;

typedef enum NNS_G2D_VRAM_TYPE {
    NNS_G2D_VRAM_TYPE_3DMAIN = 0,
    NNS_G2D_VRAM_TYPE_2DMAIN = 1,
    NNS_G2D_VRAM_TYPE_2DSUB = 2
} NNS_G2D_VRAM_TYPE;

typedef struct NNSG2dCharacterData {
    u16 H;
    u16 W;
    GXTexFmt pixelFmt;
    GXOBJVRamModeChar mappingType;
    u32 characterFmt;
    u32 szByte;
    void *pRawData;
} NNSG2dCharacterData;

typedef struct NNSG2dImageAttr {
    GXTexSizeS sizeS;
    GXTexSizeT sizeT;
    GXTexFmt fmt;
    BOOL bExtendedPlt;
    GXTexPlttColor0 plttUse;
    GXOBJVRamModeChar mappingType;
} NNSG2dImageAttr;

typedef struct NNSG2dVRamLocation {
    u32 baseAddrOfVram[3];
} NNSG2dVRamLocation;

typedef struct NNSG2dImageProxy {
    NNSG2dVRamLocation vramLocation;
    NNSG2dImageAttr attr;
} NNSG2dImageProxy;

extern void DC_FlushRange(const void *startAddr, u32 nBytes);
extern void GX_BeginLoadTex(void);
extern void GX_LoadTex(const void *pSrc, u32 destSlotAddr, u32 szByte);
extern void GX_EndLoadTex(void);
extern void GX_LoadOBJ(const void *pSrc, u32 offset, u32 szByte);
extern void GXS_LoadOBJ(const void *pSrc, u32 offset, u32 szByte);
extern void func_02011f58(NNSG2dVRamLocation *pVramLocation,
                          NNS_G2D_VRAM_TYPE type, u32 addr);

static inline int GetPow_(u16 num)
{
    switch (num) {
    case 1:
        return 0;
    case 2:
        return 1;
    case 4:
        return 2;
    case 8:
        return 3;
    case 16:
        return 4;
    case 32:
        return 5;
    default:
        (void)0;
        return 0;
    }
}

static inline void CopyCharDataToImageAttr_(const NNSG2dCharacterData *pSrc,
                                             NNSG2dImageAttr *pDst)
{
    (void)0;
    (void)0;
    if (pSrc->mappingType == GX_OBJVRAMMODE_CHAR_2D) {
        pDst->sizeS = (GXTexSizeS)GetPow_(pSrc->W);
        pDst->sizeT = (GXTexSizeT)GetPow_(pSrc->H);
    } else {
        (void)0;
        pDst->sizeS = (GXTexSizeS)pSrc->W;
        pDst->sizeT = (GXTexSizeT)pSrc->H;
    }
    pDst->fmt = pSrc->pixelFmt;
    pDst->bExtendedPlt = FALSE;
    pDst->plttUse = GX_TEXPLTTCOLOR0_TRNS;
    pDst->mappingType = pSrc->mappingType;
}

static inline void DoLoadingToVram_(const NNSG2dCharacterData *pSrcData,
                                     u32 baseAddr, NNS_G2D_VRAM_TYPE type)
{
    (void)0;
    DC_FlushRange(pSrcData->pRawData, pSrcData->szByte);
    switch (type) {
    case NNS_G2D_VRAM_TYPE_3DMAIN:
        (void)0;
        GX_BeginLoadTex();
        GX_LoadTex((void *)pSrcData->pRawData, baseAddr, pSrcData->szByte);
        GX_EndLoadTex();
        break;
    case NNS_G2D_VRAM_TYPE_2DMAIN:
        (void)0;
        GX_LoadOBJ((void *)pSrcData->pRawData, baseAddr, pSrcData->szByte);
        break;
    case NNS_G2D_VRAM_TYPE_2DSUB:
        (void)0;
        GXS_LoadOBJ((void *)pSrcData->pRawData, baseAddr, pSrcData->szByte);
        break;
    default:
        (void)0;
    }
}

static inline void SetOBJVRamModeCharacterMapping_(NNS_G2D_VRAM_TYPE vramType,
                                                    GXOBJVRamModeChar vramMode)
{
    (void)0;
    switch (vramType) {
    case NNS_G2D_VRAM_TYPE_3DMAIN:
        break;
    case NNS_G2D_VRAM_TYPE_2DMAIN:
        *(volatile u32 *)0x04000000 =
            (*(volatile u32 *)0x04000000 & 0xffcfffef) | vramMode;
        break;
    case NNS_G2D_VRAM_TYPE_2DSUB:
        *(volatile u32 *)0x04001000 =
            (*(volatile u32 *)0x04001000 & 0xffcfffef) | vramMode;
        break;
    default:
        (void)0;
    }
}

static inline void SetupImageProxyPrams_(const NNSG2dCharacterData *pSrcData,
                                          u32 baseAddr,
                                          NNS_G2D_VRAM_TYPE type,
                                          NNSG2dImageProxy *pImgProxy)
{
    CopyCharDataToImageAttr_(pSrcData, &pImgProxy->attr);
    func_02011f58(&pImgProxy->vramLocation, type, baseAddr);
}

void func_02011f94(const NNSG2dCharacterData *pSrcData, u32 baseAddr,
                   NNS_G2D_VRAM_TYPE type, NNSG2dImageProxy *pImgProxy)
{
    (void)0;
    (void)0;
    (void)0;
    (void)0;
    SetOBJVRamModeCharacterMapping_(type, pSrcData->mappingType);
    DoLoadingToVram_(pSrcData, baseAddr, type);
    SetupImageProxyPrams_(pSrcData, baseAddr, type, pImgProxy);
}
