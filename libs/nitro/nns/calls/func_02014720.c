typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;
typedef int BOOL;

#define FALSE 0
#define TRUE 1
#define NNS_G2D_BINFILE_SIG_FONTDATA 0x4e465452
#define NNS_G2D_NFTR_VER 0x0101
#define NNS_G2D_NFTR_PREV_VER 0x0100
#define NNS_G2D_BINBLK_SIG_FINFDATA 0x46494e46

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

typedef struct NNSG2dFontGlyph {
    u8 reserved[7];
    u8 flags;
} NNSG2dFontGlyph;

typedef struct NNSG2dFontInformation {
    u8 reserved[8];
    NNSG2dFontGlyph *pGlyph;
} NNSG2dFontInformation;

extern void OS_Terminate(void);
extern void func_02014874(NNSG2dBinaryFileHeader *pHeader);
extern NNSG2dBinaryBlockHeader *func_02011aa0(
    NNSG2dBinaryFileHeader *pHeader, u32 kind);

static inline BOOL NNSi_G2dIsBinFileSignatureValid(
    const NNSG2dBinaryFileHeader *pBinFile, u32 binFileSig)
{
    if (pBinFile != 0) {
        if (pBinFile->signature == binFileSig) {
            return TRUE;
        }
    }
    return FALSE;
}

static inline BOOL NNSi_G2dIsBinFileVersionValid(
    const NNSG2dBinaryFileHeader *pBinFile, u16 version)
{
    if (pBinFile != 0) {
        if (pBinFile->version >= version) {
            return TRUE;
        }
    }
    return FALSE;
}

static inline BOOL NNS_G2dIsBinFileValid(
    const NNSG2dBinaryFileHeader *pBinFile, u32 binFileSig, u16 version)
{
    if (pBinFile != 0) {
        return NNSi_G2dIsBinFileSignatureValid(pBinFile, binFileSig) &&
               NNSi_G2dIsBinFileVersionValid(pBinFile, version);
    }
    return FALSE;
}

BOOL func_02014720(void *pNftrFile, NNSG2dFontInformation **ppRes)
{
    BOOL isOldVer = FALSE;

    if (!NNS_G2dIsBinFileValid((NNSG2dBinaryFileHeader *)pNftrFile,
                               NNS_G2D_BINFILE_SIG_FONTDATA,
                               NNS_G2D_NFTR_VER)) {
        if (!NNS_G2dIsBinFileValid((NNSG2dBinaryFileHeader *)pNftrFile,
                                   NNS_G2D_BINFILE_SIG_FONTDATA,
                                   NNS_G2D_NFTR_PREV_VER)) {
            OS_Terminate();
        }

        isOldVer = TRUE;
    }

    {
        NNSG2dBinaryFileHeader *pBinFile =
            (NNSG2dBinaryFileHeader *)pNftrFile;
        NNSG2dBinaryBlockHeader *pBinBlock;

        func_02014874(pBinFile);
        pBinBlock = func_02011aa0(pBinFile, NNS_G2D_BINBLK_SIG_FINFDATA);

        if (pBinBlock == 0) {
            *ppRes = 0;
            return FALSE;
        }

        *ppRes = (NNSG2dFontInformation *)((u8 *)pBinBlock + sizeof(*pBinBlock));
        if (isOldVer) {
            (*ppRes)->pGlyph->flags = 0;
        }
    }

    return TRUE;
}
