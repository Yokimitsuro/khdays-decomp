/* func_ov011_0205b8f8 -- blit one column of tiles from a pane's tileset into its VRAM
 * image, then hand the whole image to the graphics queue.
 *
 * A pane owns a 64 KB tile image at +0x908 and points at a tileset whose header carries
 * its size in tiles. This copies one 64-byte tile per row, walking down the source column
 * and wrapping the destination row at 32. Nothing happens if the requested column is
 * outside the tileset.
 *
 * Three things carry the match:
 *   - the row counter, the row cursor and the clamped row count are UNSIGNED; signed
 *     versions give ble/blt/movge where the ROM has bls/blo/movhs;
 *   - the destination row is copied into a local right before the loop, which is what
 *     delays the fifth argument's load past the two early returns -- read straight from
 *     the parameter, mwcc hoists that load above the guards and every instruction after
 *     it shifts by one;
 *   - the tileset is reached through a pointer to the pane's inner block rather than the
 *     pane itself, which is why the ROM builds two bases four bytes apart instead of one.
 */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

typedef struct Ov011Tileset {
    u16 wRows;
    u16 wCols;
    u8  pad_0004[0x14 - 4];
    const void *pTiles;
} Ov011Tileset;

typedef struct Ov011PaneCore {
    u8 pad_0000[4];
    const Ov011Tileset *pTileset;
} Ov011PaneCore;

typedef struct Ov011Pane {
    void         *pBuffer;
    Ov011PaneCore core;
    u8            pad_0000c[0x908 - 0xc];
    u8            aVram[0x10000];
    u8            pad_10908[0x1091a - 0x10908];
    u16           wScrollPhase;
    u8            pad_1091c[0x10931 - 0x1091c];
    u8            nPhase;
    u8            nFlag;
    u8            pad_10933[0x10938 - 0x10933];
    u32           nSpeed;
    u32           nAccum;
} Ov011Pane;

typedef struct Ov011Scene {
    int       nA;
    int       nMode;
    u8        pad_00008[4];
    u32       nArchiveBase;
    u8        pad_00010[4];
    Ov011Pane aPane[2];
} Ov011Scene;

typedef struct Ov011Globals {
    int         nCursor;
    Ov011Scene *pScene;
} Ov011Globals;

extern Ov011Globals data_ov011_0205e960;

extern void MIi_CpuCopy32(const void *pSrc, void *pDst, u32 nSize);
extern void GFXi_EnqueueCommand(int nType, int nOffset, const void *pSrc, u32 nSize);

void func_ov011_0205b8f8(int nPane, int nSrcX, int nSrcY, int nDstCol, u32 nDstRow)
{
    Ov011PaneCore *pCore = &data_ov011_0205e960.pScene->aPane[nPane].core;
    Ov011Pane *pPane = &data_ov011_0205e960.pScene->aPane[nPane];
    const u8 *pSrc;
    u8 *pDst;
    u32 i;
    u32 nRow;
    u32 nRows;

    pSrc = (const u8 *)pCore->pTileset->pTiles
           + ((nSrcY * pCore->pTileset->wCols + nSrcX) << 6);
    pDst = pPane->aVram + ((nDstCol & 0x1f) << 6);
    nRows = pCore->pTileset->wRows;
    if (nRows > 0x20) {
        nRows = 0x20;
    }
    if (nSrcX >= pCore->pTileset->wCols) {
        return;
    }
    if (nSrcX < 0) {
        return;
    }
    nRow = nDstRow;
    for (i = 0; i < nRows; i++) {
        if (nRow >= 0x20) {
            nRow = 0;
        }
        MIi_CpuCopy32(pSrc, pDst + (nRow << 11), 0x40);
        nRow++;
        pSrc += pCore->pTileset->wCols << 6;
    }
    GFXi_EnqueueCommand(nPane == 0 ? 6 : 0x16, 0, pPane->aVram, 0x10000);
}
