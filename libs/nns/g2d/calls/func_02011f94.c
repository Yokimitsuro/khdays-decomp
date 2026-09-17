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




typedef vu32 REGType32v;
void DC_FlushRange(const void * startAddr, u32 nBytes);
typedef int (*MIDeviceReadFunction)(void * userdata, void * buffer, u32 offset, u32 length);
typedef int (*MIDeviceWriteFunction)(void * userdata, const void * buffer, u32 offset, u32 length);
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
extern void GX_SetOBJVRamModeChar(GXOBJVRamModeChar mode);
extern void GXS_SetOBJVRamModeChar(GXOBJVRamModeChar mode);
static inline void GX_SetOBJVRamModeChar (GXOBJVRamModeChar mode)
{
    (*( REGType32v *) (0x04000000 + 0x000)) = (u32)((*( REGType32v *) (0x04000000 + 0x000)) &
                           ~(0x00300000 | 0x00000010 ) | mode);
}
static inline void GXS_SetOBJVRamModeChar (GXOBJVRamModeChar mode)
{
    (*( REGType32v *) (0x04000000 + 0x1000)) = (u32)((*( REGType32v *) (0x04000000 + 0x1000)) &
                               ~(0x00300000 |
                                 0x00000010 ) | mode);
}
void GX_LoadOBJ(const void * pSrc, u32 offset, u32 szByte);
void GXS_LoadOBJ(const void * pSrc, u32 offset, u32 szByte);
void GX_BeginLoadTex(void);
void GX_LoadTex(const void * pSrc, u32 destSlotAddr, u32 szByte);
void GX_EndLoadTex(void);
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
typedef void * (*MIAllocatorAllocFunction)(void * userdata, u32 length, u32 alignment);
typedef void (*MIAllocatorFreeFunction)(void * userdata, void * buffer);
typedef enum NNSG2dCharacterFmt {
    NNS_G2D_CHARACTER_FMT_CHAR,
    NNS_G2D_CHARACTER_FMT_BMP,
    NNS_G2D_CHARACTER_FMT_MAX
} NNSG2dCharacterFmt;
typedef struct NNSG2dCharacterData {
    u16 H;
    u16 W;
    GXTexFmt pixelFmt;
    GXOBJVRamModeChar mappingType;
    u32 characterFmt;
    u32 szByte;
    void * pRawData;
} NNSG2dCharacterData;
inline NNSG2dCharacterFmt NNSi_G2dGetCharacterFmtType (u32 characterFmt)
{
    return (NNSG2dCharacterFmt)
           (0xFF & (characterFmt >> 0 ));
}
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
void func_02011f58(NNSG2dImageProxy * pImg, NNS_G2D_VRAM_TYPE type, u32 addr);
static inline int GetPow_ (u16 num)
{
    switch (num) {
    case 1:
        return GX_TEXSIZE_S8;
    case 2:
        return GX_TEXSIZE_S16;
    case 4:
        return GX_TEXSIZE_S32;
    case 8:
        return GX_TEXSIZE_S64;
    case 16:
        return GX_TEXSIZE_S128;
    case 32:
        return GX_TEXSIZE_S256;
    default:
        ((void)0) ;
        return GX_TEXSIZE_S8;
    }
}
static inline void CopyCharDataToImageAttr_ (const NNSG2dCharacterData * pSrc, NNSG2dImageAttr * pDst)
{
    if (pSrc->mappingType == GX_OBJVRAMMODE_CHAR_2D) {
        pDst->sizeS = (GXTexSizeS)(GetPow_(pSrc->W));
        pDst->sizeT = (GXTexSizeT)(GetPow_(pSrc->H));
    } else {
        ((void) 0)                       ;
        pDst->sizeS = (GXTexSizeS)pSrc->W;
        pDst->sizeT = (GXTexSizeT)pSrc->H;
    }
    pDst->fmt = pSrc->pixelFmt;
    pDst->bExtendedPlt = 0 ;
    pDst->plttUse = GX_TEXPLTTCOLOR0_TRNS;
    pDst->mappingType = pSrc->mappingType;
}
static inline void DoLoadingToVram_ (const NNSG2dCharacterData * pSrcData, u32 baseAddr, NNS_G2D_VRAM_TYPE type)
{
    const NNSG2dCharacterFmt charFmt = NNSi_G2dGetCharacterFmtType(pSrcData->characterFmt);
    ((void) 0)                      ;
    DC_FlushRange(pSrcData->pRawData, pSrcData->szByte);
    switch (type) {
    case NNS_G2D_VRAM_TYPE_3DMAIN:
        GX_BeginLoadTex();
        GX_LoadTex((void *)pSrcData->pRawData, baseAddr, pSrcData->szByte);
        GX_EndLoadTex();
        break;
    case NNS_G2D_VRAM_TYPE_2DMAIN:
        GX_LoadOBJ((void *)pSrcData->pRawData, baseAddr, pSrcData->szByte);
        break;
    case NNS_G2D_VRAM_TYPE_2DSUB:
        GXS_LoadOBJ((void *)pSrcData->pRawData, baseAddr, pSrcData->szByte);
        break;
    default:
    }
}
static inline void SetOBJVRamModeCharacterMapping_ (NNS_G2D_VRAM_TYPE vramType, GXOBJVRamModeChar vramMode)
{
    switch (vramType) {
    case NNS_G2D_VRAM_TYPE_3DMAIN:
        break;
    case NNS_G2D_VRAM_TYPE_2DMAIN:
        GX_SetOBJVRamModeChar(vramMode);
        break;
    case NNS_G2D_VRAM_TYPE_2DSUB:
        GXS_SetOBJVRamModeChar(vramMode);
        break;
    default:
    }
}
static inline void SetupImageProxyPrams_ (const NNSG2dCharacterData * pSrcData, u32 baseAddr, NNS_G2D_VRAM_TYPE type, NNSG2dImageProxy * pImgProxy)
{
    CopyCharDataToImageAttr_(pSrcData, &pImgProxy->attr);
    func_02011f58(pImgProxy, type, baseAddr);
}
extern void func_02011f58 (NNSG2dImageProxy * pImg, NNS_G2D_VRAM_TYPE type, u32 addr);

/* func_02011f94 -- NitroSystem g2d_Image.c: NNS_G2dLoadImage1DMapping. */
void func_02011f94 (const NNSG2dCharacterData * pSrcData, u32 baseAddr, NNS_G2D_VRAM_TYPE type, NNSG2dImageProxy * pImgProxy)
{

    SetOBJVRamModeCharacterMapping_(type, pSrcData->mappingType);

    DoLoadingToVram_(pSrcData, baseAddr, type);

    SetupImageProxyPrams_(pSrcData, baseAddr, type, pImgProxy);
}
