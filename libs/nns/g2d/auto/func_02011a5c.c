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

#define NNS_G2D_UNPACK_OFFSET_PTR(ptr, baseOffs) (ptr) = (void *)((u32)(ptr) + (u32)baseOffs)

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
typedef struct NNSG2dPaletteData {
    GXTexFmt fmt;
    BOOL bExtendedPlt;
    u32 szByte;
    void * pRawData;
} NNSG2dPaletteData;

/* func_02011a5c -- NitroSystem g2d_NCL_load.c: NNS_G2dUnpackNCL. */
void func_02011a5c (NNSG2dPaletteData * pPlttData)
{

    pPlttData->pRawData = NNS_G2D_UNPACK_OFFSET_PTR(pPlttData->pRawData, pPlttData);

}
