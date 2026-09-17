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
extern void InitializeVRamLocation_(NNSG2dVRamLocation * pVramLocation);
static inline void InitializeVRamLocation_ (NNSG2dVRamLocation * pVramLocation)
{
    int i;
    for (i = 0; i < NNS_G2D_VRAM_TYPE_MAX; i++) {
        pVramLocation->baseAddrOfVram[ i ] = 0xFFFFFFFF ;
    }
}

/* func_02011f3c -- NitroSystem g2d_Image.c: NNS_G2dInitImageProxy. */
void func_02011f3c (NNSG2dImageProxy * pImg)
{
    InitializeVRamLocation_(&pImg->vramLocation);
}
