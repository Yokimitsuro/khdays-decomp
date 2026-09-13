/* Ov011_BlitTileRow -- copy one tileset row into a pane's 32x32-tile VRAM image. */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

typedef struct Ov011Tileset {
    u16 wRows;
    u16 wCols;
    u8  pad_0004[0x14 - 4];
    const u8 *pTiles;
} Ov011Tileset;

typedef struct Ov011PaneCore {
    u8 pad_0000[4];
    const Ov011Tileset *pTileset;
} Ov011PaneCore;

typedef struct Ov011Pane {
    void          *pBuffer;
    Ov011PaneCore  core;
    u8             pad_0000c[0x908 - 0xc];
    u8             aVram[0x10000];
    u8             pad_10908[0x1091a - 0x10908];
    u16            wScrollPhase;
    u8             pad_1091c[0x10931 - 0x1091c];
    u8             nPhase;
    u8             nFlag;
    u8             pad_10933[0x10938 - 0x10933];
    u32            nSpeed;
    u32            nAccum;
} Ov011Pane;

typedef struct Ov011Scene {
    int       nA;
    int       nMode;
    u8        pad_00008[4];
    u32       nArchiveBase;
    u8        pad_00010[4];
    Ov011Pane aPane[2];
} Ov011Scene;

/* khdays: shared-bss */
int data_ov011_0205e960 = 0;
Ov011Scene *data_ov011_0205e964 = 0;

extern void MIi_CpuCopy32(const void *pSrc, void *pDst, u32 nSize);
extern void GFXi_EnqueueCommand(int nType, int nOffset, const void *pSrc,
                                u32 nSize);

void func_ov011_0205b814(int nPane, int nSrcX, int nSrcY, int nDstCol,
                         u32 nDstRow, u32 nCols)
{
    Ov011PaneCore *pCore = &data_ov011_0205e964->aPane[nPane].core;
    nCols = pCore->pTileset->wCols;
    Ov011Pane *pPane = &data_ov011_0205e964->aPane[nPane];
    u32 nCol = nDstCol & 0x1f;
    const u8 *pSrc = pCore->pTileset->pTiles
                     + ((nSrcY * nCols + nSrcX) << 6);
    u8 *pDst = pPane->aVram
               + ((nCol + ((nDstRow & 0x1f) << 5)) << 6);

    if (nCols > 0x20) {
        nCols = 0x20;
    }
    if (nSrcY >= pCore->pTileset->wRows) {
        return;
    }
    if (nSrcY < 0) {
        return;
    }
    if (nCol + nCols <= 0x20) {
        MIi_CpuCopy32(pSrc, pDst, nCols << 6);
    } else {
        u32 nFirst = 0x20 - nCol;
        MIi_CpuCopy32(pSrc, pDst, nFirst << 6);
        pDst -= nCol << 6;
        pSrc += nFirst << 6;
        MIi_CpuCopy32(pSrc, pDst, (nCols - nFirst) << 6);
    }
    GFXi_EnqueueCommand(nPane == 0 ? 6 : 0x16, 0, pPane->aVram, 0x10000);
}
