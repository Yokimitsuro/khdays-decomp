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

#define NNS_G2D_BINBLK_SIG_PALETTEDATA (u32)'PLTT'

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
typedef struct NNSG2dBinaryFileHeader {
    u32 signature;
    u16 byteOrder;
    u16 version;
    u32 fileSize;
    u16 headerSize;
    u16 dataBlocks;
} NNSG2dBinaryFileHeader;
typedef struct NNSG2dBinaryBlockHeader {
    u32 kind;
    u32 size;
} NNSG2dBinaryBlockHeader;
typedef struct NNSG2dPaletteData {
    GXTexFmt fmt;
    BOOL bExtendedPlt;
    u32 szByte;
    void * pRawData;
} NNSG2dPaletteData;
typedef struct NNSG2dPaletteDataBlock {
    NNSG2dBinaryBlockHeader blockHeader;
    NNSG2dPaletteData paletteData;
} NNSG2dPaletteDataBlock;
void func_02011a5c(NNSG2dPaletteData * pPlttData);
NNSG2dBinaryBlockHeader * func_02011aa0(NNSG2dBinaryFileHeader * pBinFileHeader, u32 signature);
extern void func_02011a5c (NNSG2dPaletteData * pPlttData);

/* func_02011a20 -- NitroSystem g2d_NCL_load.c: NNS_G2dGetUnpackedPaletteData. */
BOOL func_02011a20 (void * pNclrFile, NNSG2dPaletteData ** ppPltData)
{

    {
        const NNSG2dBinaryFileHeader * pBinFile = pNclrFile;

    }


    {
        NNSG2dBinaryFileHeader * pBinFile = (NNSG2dBinaryFileHeader *)pNclrFile;
        {
            NNSG2dPaletteDataBlock * pBinBlk =
                (NNSG2dPaletteDataBlock *)func_02011aa0(pBinFile,
                                                                 NNS_G2D_BINBLK_SIG_PALETTEDATA);
            if (pBinBlk) {
                func_02011a5c((void *)&pBinBlk->paletteData);
                *ppPltData = &pBinBlk->paletteData;
                return TRUE;
            } else {
                *ppPltData = NULL;
                return FALSE;

            }
        }
    }
}
