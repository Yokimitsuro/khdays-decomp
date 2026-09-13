/* func_ov025_02092360 -- Ov008_CanPlaceShape: can shape pEntry be placed with
 * its top-left cell at (nLeft, nTop) of page nPage?  Walks the 8 x 5 box of the
 * entry's 64-bit cell mask (bit col + 8 * row), tracking the shape's used width
 * and height; any covered cell that is already taken in the page grid (+0x1e88)
 * refuses at once, and the shape must also fit inside the 5 x 8 page.  Negative
 * coordinates refuse.  Either way the context's "count" text pointer (+0x2078)
 * is refreshed from variable record 0x1b of the records at +0x28c.
 */
typedef unsigned char      u8;
typedef unsigned long long u64;

#define GRID_PAGES 3
#define GRID_ROWS  8
#define GRID_COLS  5
#define TEXT_COUNT 0x1b

typedef struct Ov008ShapeEntry {
    u8  pad_00[0x10];
    u64 nCellMask;            /* 0x10: bit col + 8*row */
} Ov008ShapeEntry;

typedef struct Ov008MenuContext {
    u8    pad_0000[0x28c];
    u8    records[0x1e88 - 0x28c];                        /* 0x028c: variable text records */
    u8    aGrid[GRID_PAGES][GRID_ROWS][GRID_COLS];        /* 0x1e88 */
    u8    pad_1f00[0x2078 - 0x1f00];
    void *pCountText;                                     /* 0x2078 */
} Ov008MenuContext;

extern void *func_ov025_02089894(void *pRecords, int nIndex);           /* GetVarRecordByIndex */

int func_ov025_02092360(Ov008MenuContext *pCtx, Ov008ShapeEntry *pEntry, int nPage, int nLeft, int nTop)
{
    int bFits;
    int nRow;
    int nCol;
    int nWidth;
    int nHeight;

    bFits = 0;
    nWidth = 0;
    nHeight = 0;
    if (nLeft >= 0 && nTop >= 0) {
        for (nRow = 0; nRow < GRID_ROWS; nRow++) {
            for (nCol = 0; nCol < GRID_COLS; nCol++) {
                if ((pEntry->nCellMask & (1ULL << (nCol + nRow * 8))) != 0) {
                    if (nCol + 1 > nWidth) {
                        nWidth = nCol + 1;
                    }
                    if (nRow + 1 > nHeight) {
                        nHeight = nRow + 1;
                    }
                    if (pCtx->aGrid[nPage][nTop + nRow][nLeft + nCol] != 0) {
                        goto done;
                    }
                }
            }
        }
        if (nLeft + nWidth <= GRID_COLS && nTop + nHeight <= GRID_ROWS) {
            bFits = 1;
        }
    }
done:
    pCtx->pCountText = func_ov025_02089894(pCtx->records, TEXT_COUNT);
    return bFits;
}
