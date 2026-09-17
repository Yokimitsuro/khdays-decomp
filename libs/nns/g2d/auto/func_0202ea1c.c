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



typedef s32 fx32;
typedef union {
        struct {
            fx32 _00, _01, _02;
            fx32 _10, _11, _12;
            fx32 _20, _21, _22;
            fx32 _30, _31, _32;
        };
        fx32 m[4][3];
        fx32 a[12];
    } MtxFx43;
typedef union {
        struct {
            fx32 _00, _01;
            fx32 _10, _11;
        };
        fx32 m[2][2];
        fx32 a[4];
    } MtxFx22;
typedef enum {
    TP_REQUEST_COMMAND_SAMPLING         = 0x0,
    TP_REQUEST_COMMAND_AUTO_ON          = 0x1,
    TP_REQUEST_COMMAND_AUTO_OFF         = 0x2,
    TP_REQUEST_COMMAND_SET_STABILITY    = 0x3,
    TP_REQUEST_COMMAND_AUTO_SAMPLING    = 0x10
} TPRequestCommand;
typedef enum {
    TP_RESULT_SUCCESS = 0,
    TP_RESULT_INVALID_PARAMETER,
    TP_RESULT_ILLEGAL_STATUS,
    TP_RESULT_EXCLUSIVE,
    TP_RESULT_PXI_BUSY
} TPRequestResult;
typedef void (*TPRecvCallback) (TPRequestCommand command, TPRequestResult result, u16 index);
typedef enum MICResult {
    MIC_RESULT_SUCCESS = 0,
    MIC_RESULT_BUSY,
    MIC_RESULT_ILLEGAL_PARAMETER,
    MIC_RESULT_SEND_ERROR,
    MIC_RESULT_INVALID_COMMAND,
    MIC_RESULT_ILLEGAL_STATUS,
    MIC_RESULT_FATAL_ERROR,
    MIC_RESULT_MAX
} MICResult;
typedef void (*MICCallback) (MICResult result, void * arg);
typedef void (*PMCallback) (u32 result, void * arg);
typedef enum RTCResult {
    RTC_RESULT_SUCCESS = 0,
    RTC_RESULT_BUSY,
    RTC_RESULT_ILLEGAL_PARAMETER,
    RTC_RESULT_SEND_ERROR,
    RTC_RESULT_INVALID_COMMAND,
    RTC_RESULT_ILLEGAL_STATUS,
    RTC_RESULT_FATAL_ERROR,
    RTC_RESULT_MAX
} RTCResult;
typedef void (*RTCCallback) (RTCResult result, void * arg);
typedef enum {
    GX_TEXSIZE_S8       = 0,
    GX_TEXSIZE_S16      = 1,
    GX_TEXSIZE_S32      = 2,
    GX_TEXSIZE_S64      = 3,
    GX_TEXSIZE_S128     = 4,
    GX_TEXSIZE_S256     = 5,
    GX_TEXSIZE_S512     = 6,
    GX_TEXSIZE_S1024    = 7
} GXTexSizeS;
typedef enum {
    GX_TEXSIZE_T8       = 0,
    GX_TEXSIZE_T16      = 1,
    GX_TEXSIZE_T32      = 2,
    GX_TEXSIZE_T64      = 3,
    GX_TEXSIZE_T128     = 4,
    GX_TEXSIZE_T256     = 5,
    GX_TEXSIZE_T512     = 6,
    GX_TEXSIZE_T1024    = 7
} GXTexSizeT;
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
    GX_TEXPLTTCOLOR0_USE  = 0,
    GX_TEXPLTTCOLOR0_TRNS = 1
} GXTexPlttColor0;
typedef enum {
    GX_OBJVRAMMODE_CHAR_2D      = (0 << 4 ) | (0 << 20 ),
    GX_OBJVRAMMODE_CHAR_1D_32K  = (1 << 4 ) | (0 << 20 ),
    GX_OBJVRAMMODE_CHAR_1D_64K  = (1 << 4 ) | (1 << 20 ),
    GX_OBJVRAMMODE_CHAR_1D_128K = (1 << 4 ) | (2 << 20 ),
    GX_OBJVRAMMODE_CHAR_1D_256K = (1 << 4 ) | (3 << 20 )
} GXOBJVRamModeChar;
typedef struct {
        union {
            u32 attr01;
            struct {
                u16 attr0;
                u16 attr1;
            };
            struct {
                u32 y : 8;
                u32 rsMode : 2;
                u32 objMode : 2;
                u32 mosaic : 1;
                u32 colorMode : 1;
                u32 shape : 2;
                u32 x : 9;
                u32 rsParam : 5;
                u32 size : 2;
            };
            struct {
                u32 _0 : 28;
                u32 flipH : 1;
                u32 flipV : 1;
                u32 _1 : 2;
            };
        };
        union {
            struct {
                u16 attr2;
                u16 _3;
            };
            u32 attr23;
            struct {
                u32 charNo : 10;
                u32 priority : 2;
                u32 cParam : 4;
                u32 _2 : 16;
            };
        };
    } GXOamAttr;
typedef struct WMGameInfo {
    u16 magicNumber;
    u8 ver;
    u8 platform;
    u32 ggid;
    u16 tgid;
    u8 userGameInfoLength;
    union {
        u8 gameNameCount_attribute;
        u8 attribute;
    };
    u16 parentMaxSize;
    u16 childMaxSize;
    union {
        u16 userGameInfo[112 / sizeof(u16)];
        struct {
            u16 userName[8 / sizeof(u16)];
            u16 gameName[16 / sizeof(u16)];
            u16 padd1[44];
        } old_type;
    };
} WMGameInfo, WMgameInfo;
typedef struct WMStartScanCallback {
    u16 apiid;
    u16 errcode;
    u16 wlCmdID;
    u16 wlResult;
    u16 state;
    u8 macAddress[6 ];
    u16 channel;
    u16 linkLevel;
    u16 ssidLength;
    u16 ssid[32 / sizeof(u16)];
    u16 gameInfoLength;
    WMGameInfo gameInfo;
} WMStartScanCallback, WMstartScanCallback;
typedef enum WVRResult {
    WVR_RESULT_SUCCESS = 0,
    WVR_RESULT_OPERATING,
    WVR_RESULT_DISABLE,
    WVR_RESULT_INVALID_PARAM,
    WVR_RESULT_FIFO_ERROR,
    WVR_RESULT_ILLEGAL_STATUS,
    WVR_RESULT_VRAM_LOCKED,
    WVR_RESULT_FATAL_ERROR,
    WVR_RESULT_MAX
} WVRResult;
typedef void (*WVRCallbackFunc) (void * arg, WVRResult result);
typedef void (*MBFakeScanCallbackFunc) (u16 type, void * arg);
typedef BOOL (*MBFakeCompareGGIDCallbackFunc) (WMStartScanCallback * arg, u32 defaultGGID);
typedef struct NNSG2dFVec2 {
    fx32 x;
    fx32 y;
} NNSG2dFVec2;
typedef union {
        struct {
            fx32 _00, _01;
            fx32 _10, _11;
            fx32 _20, _21;
        };
        fx32 m[3][2];
        fx32 a[6];
    }
    MtxFx32;
typedef struct NNSG2dCellOAMAttrData {
    u16 attr0;
    u16 attr1;
    u16 attr2;
} NNSG2dCellOAMAttrData;
typedef struct NNSG2dCellData {
    u16 numOAMAttrs;
    u16 cellAttr;
    NNSG2dCellOAMAttrData * pOamAttrArray;
} NNSG2dCellData;
typedef enum NNSG2dRendererAffineTypeOverwiteMode {
    NNS_G2D_RND_AFFINE_OVERWRITE_NONE,
    NNS_G2D_RND_AFFINE_OVERWRITE_NORMAL,
    NNS_G2D_RND_AFFINE_OVERWRITE_DOUBLE
} NNSG2dRendererAffineTypeOverwiteMode;
typedef enum NNSG2dSurfaceType {
    NNS_G2D_SURFACETYPE_MAIN3D = 0x00,
    NNS_G2D_SURFACETYPE_MAIN2D = 0x01,
    NNS_G2D_SURFACETYPE_SUB2D  = 0x02,
    NNS_G2D_SURFACETYPE_MAX    = 0x03
} NNSG2dSurfaceType;
typedef struct NNSG2dRndCore2DMtxCache {
    MtxFx22 m22;
    u16 affineIndex[0x04 ][2 ];
} NNSG2dRndCore2DMtxCache;
typedef struct NNSG2dViewRect {
    NNSG2dFVec2 posTopLeft;
    NNSG2dFVec2 sizeView;
} NNSG2dViewRect;
typedef BOOL (*NNSG2dOamRegisterFunction)(const GXOamAttr * pOam, u16 affineIndex, BOOL bDoubleAffine);
typedef BOOL (*NNSG2dOamBlockRegisterFunction)(const GXOamAttr * pOam, u16 num);
typedef u16 (*NNSG2dAffineRegisterFunction)(const MtxFx22 * mtx);
struct NNSG2dRndCoreInstance;
struct NNSG2dRndCoreSurface;
typedef void (*NNSG2dRndCoreDrawCellCallBack)(struct NNSG2dRndCoreInstance * pRend, const NNSG2dCellData * pCell);
typedef void (*NNSG2dRndCoreDrawOamCallBack)(struct NNSG2dRndCoreInstance * pRend, const NNSG2dCellData * pCell, u16                             oamIdx);
typedef struct NNSG2dRndCoreSurface {
    NNSG2dViewRect viewRect;
    BOOL bActive;
    NNSG2dSurfaceType type;
    NNSG2dRndCoreDrawCellCallBack pBeforeDrawCellBackFunc;
    NNSG2dRndCoreDrawCellCallBack pAfterDrawCellBackFunc;
    NNSG2dRndCoreDrawOamCallBack pBeforeDrawOamBackFunc;
    NNSG2dRndCoreDrawOamCallBack pAfterDrawOamBackFunc;
} NNSG2dRndCoreSurface;
struct NNSG2dImageProxy;
struct NNSG2dImagePaletteProxy;
typedef struct NNSG2dRndCoreInstance {
    NNSG2dRndCoreSurface * pCurrentTargetSurface;
    NNSG2dRendererAffineTypeOverwiteMode affineOverwriteMode;
    const struct NNSG2dImageProxy * pImgProxy;
    const struct NNSG2dImagePaletteProxy * pPltProxy;
    u32 base2DCharOffset;
    u32 baseTexAddr3D;
    u32 basePltAddr3D;
    NNSG2dOamRegisterFunction pFuncOamRegister;
    NNSG2dAffineRegisterFunction pFuncOamAffineRegister;
    u32 flipFlag;
    NNSG2dRndCore2DMtxCache * pCurrentMtxCacheFor2D;
    const MtxFx32 * pCurrentMxt;
    BOOL bDrawEnable;
    fx32 zFor3DSoftwareSprite;
    GXOamAttr currentOam;
    MtxFx43 mtxFor3DGE;
} NNSG2dRndCoreInstance;
struct NNSG2dImageProxy;
struct NNSG2dImagePaletteProxy;
typedef enum NNS_G2D_VRAM_TYPE {
    NNS_G2D_VRAM_TYPE_3DMAIN = 0,
    NNS_G2D_VRAM_TYPE_2DMAIN = 1,
    NNS_G2D_VRAM_TYPE_2DSUB  = 2,
    NNS_G2D_VRAM_TYPE_2DBOTH = 3,
    NNS_G2D_VRAM_TYPE_MAX    = 3
} NNS_G2D_VRAM_TYPE;
typedef struct NNSG2dImageAttr {
    GXTexSizeS sizeS;
    GXTexSizeT sizeT;
    GXTexFmt fmt;
    BOOL bExtendedPlt;
    GXTexPlttColor0 plttUse;
    GXOBJVRamModeChar mappingType;
} NNSG2dImageAttr;
typedef struct NNSG2dVRamLocation {
    u32 baseAddrOfVram[NNS_G2D_VRAM_TYPE_MAX];
} NNSG2dVRamLocation;
typedef struct NNSG2dImageProxy {
    NNSG2dVRamLocation vramLocation;
    NNSG2dImageAttr attr;
} NNSG2dImageProxy;
typedef struct NNSG2dImagePaletteProxy {
    GXTexFmt fmt;
    BOOL bExtendedPlt;
    NNSG2dVRamLocation vramLocation;
} NNSG2dImagePaletteProxy;
typedef enum NNS_GFD_DST_TYPE {
    NNS_GFD_DST_3D_TEX_VRAM = 0,
    NNS_GFD_DST_3D_TEX_PLTT,
    NNS_GFD_DST_3D_CLRIMG_COLOR,
    NNS_GFD_DST_3D_CLRIMG_DEPTH,
    NNS_GFD_DST_2D_BG0_CHAR_MAIN,
    NNS_GFD_DST_2D_BG1_CHAR_MAIN,
    NNS_GFD_DST_2D_BG2_CHAR_MAIN,
    NNS_GFD_DST_2D_BG3_CHAR_MAIN,
    NNS_GFD_DST_2D_BG0_SCR_MAIN,
    NNS_GFD_DST_2D_BG1_SCR_MAIN,
    NNS_GFD_DST_2D_BG2_SCR_MAIN,
    NNS_GFD_DST_2D_BG3_SCR_MAIN,
    NNS_GFD_DST_2D_BG2_BMP_MAIN,
    NNS_GFD_DST_2D_BG3_BMP_MAIN,
    NNS_GFD_DST_2D_OBJ_PLTT_MAIN,
    NNS_GFD_DST_2D_BG_PLTT_MAIN,
    NNS_GFD_DST_2D_OBJ_EXTPLTT_MAIN,
    NNS_GFD_DST_2D_BG_EXTPLTT_MAIN,
    NNS_GFD_DST_2D_OBJ_OAM_MAIN,
    NNS_GFD_DST_2D_OBJ_CHAR_MAIN,
    NNS_GFD_DST_2D_BG0_CHAR_SUB,
    NNS_GFD_DST_2D_BG1_CHAR_SUB,
    NNS_GFD_DST_2D_BG2_CHAR_SUB,
    NNS_GFD_DST_2D_BG3_CHAR_SUB,
    NNS_GFD_DST_2D_BG0_SCR_SUB,
    NNS_GFD_DST_2D_BG1_SCR_SUB,
    NNS_GFD_DST_2D_BG2_SCR_SUB,
    NNS_GFD_DST_2D_BG3_SCR_SUB,
    NNS_GFD_DST_2D_BG2_BMP_SUB,
    NNS_GFD_DST_2D_BG3_BMP_SUB,
    NNS_GFD_DST_2D_OBJ_PLTT_SUB,
    NNS_GFD_DST_2D_BG_PLTT_SUB,
    NNS_GFD_DST_2D_OBJ_EXTPLTT_SUB,
    NNS_GFD_DST_2D_BG_EXTPLTT_SUB,
    NNS_GFD_DST_2D_OBJ_OAM_SUB,
    NNS_GFD_DST_2D_OBJ_CHAR_SUB,
    NNS_GFD_DST_MAX
} NNS_GFD_DST_TYPE;
typedef BOOL (*VramTransferTaskRegisterFuncPtr)(NNS_GFD_DST_TYPE type, u32 dstAddr, void * pSrc, u32 szByte);

/* func_0202ea1c -- NitroSystem g2d_RendererCore.c: NNS_G2dSetRndCoreAffineOverwriteMode. */
void func_0202ea1c (NNSG2dRndCoreInstance * pRnd, NNSG2dRendererAffineTypeOverwiteMode mode)
{

    pRnd->affineOverwriteMode = mode;
}
