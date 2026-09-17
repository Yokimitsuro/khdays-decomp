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

#define NNS_G2D_BINBLK_SIG_SCRDATA (u32)'SCRN'

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
typedef struct NNSG2dScreenData {
    u16 screenWidth;
    u16 screenHeight;
    u16 colorMode;
    u16 screenFormat;
    u32 szByte;
    u32 rawData[1];
} NNSG2dScreenData;
typedef struct NNSG2dScreenDataBlock {
    NNSG2dBinaryBlockHeader blockHeader;
    NNSG2dScreenData screenData;
} NNSG2dScreenDataBlock;
NNSG2dBinaryBlockHeader * func_02011aa0(NNSG2dBinaryFileHeader * pBinFileHeader, u32 signature);

/* func_02011a6c -- NitroSystem g2d_NSC_load.c: NNS_G2dGetUnpackedScreenData. */
BOOL func_02011a6c (void * pNscrFile, NNSG2dScreenData ** ppScrData)
{

    {
        NNSG2dBinaryFileHeader * pBinFile = (NNSG2dBinaryFileHeader *)pNscrFile;
        {
            NNSG2dScreenDataBlock * pBinBlk =
                (NNSG2dScreenDataBlock *)func_02011aa0(pBinFile,
                                                                NNS_G2D_BINBLK_SIG_SCRDATA);
            if (pBinBlk) {

                *ppScrData = &(pBinBlk->screenData);

                return TRUE;
            } else {
                *ppScrData = NULL;
                return FALSE;

            }
        }
    }
}
