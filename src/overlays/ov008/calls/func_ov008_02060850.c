/* func_ov008_02060850 -- Ov008_ClearNodeCells: free every grid cell covered by a
 * tracked node's shape.  For each (row, col) of the node's w x h box whose bit
 * (col + 8 * row) is set in the entry's 64-bit cell mask, the page grid byte at
 * (page, top + row, left + col) is cleared and the cell is released through
 * Ov008_ClearGridSlot; then the grid surface upload is queued.
 */
typedef unsigned char      u8;
typedef unsigned short     u16;
typedef unsigned long long u64;

#define GRID_PAGES 3
#define GRID_ROWS  8
#define GRID_COLS  5

typedef struct Ov008ShapeEntry {
    u8  pad_00[0x10];
    u64 nCellMask;            /* 0x10: bit col + 8*row */
} Ov008ShapeEntry;

typedef struct Ov008TrackedNode {
    u8  pad_00[0xa];
    u16 nPage;                /* 0x0a */
    u16 nLeft;                /* 0x0c */
    u16 nTop;                 /* 0x0e */
    u8  pad_10[4];
    u16 nWidth;               /* 0x14 */
    u16 nHeight;              /* 0x16 */
    u8  pad_18[0x24 - 0x18];
    Ov008ShapeEntry *pEntry;  /* 0x24 */
} Ov008TrackedNode;

typedef struct Ov008MenuContext {
    u8 pad_0000[0xac];
    u8 gridSurface[0x1e88 - 0xac];                        /* 0x00ac */
    u8 aGrid[GRID_PAGES][GRID_ROWS][GRID_COLS];           /* 0x1e88 */
} Ov008MenuContext;

extern void func_ov008_02061e64(Ov008MenuContext *pCtx, u16 nPage, u16 nX, u16 nY); /* Ov008_ClearGridSlot */
extern void func_020300f8(void *pSurface);                                   /* EnqueueObjGfxCommand */

void func_ov008_02060850(Ov008MenuContext *pCtx, Ov008TrackedNode *pNode)
{
    int nRow;
    int nCol;
    int nX;
    int nY;

    for (nRow = 0; nRow < pNode->nHeight; nRow++) {
        for (nCol = 0; nCol < pNode->nWidth; nCol++) {
            nX = pNode->nLeft + nCol;
            nY = pNode->nTop + nRow;
            if ((pNode->pEntry->nCellMask & (1ULL << (nCol + nRow * 8))) != 0) {
                pCtx->aGrid[pNode->nPage][nY][nX] = 0;
                func_ov008_02061e64(pCtx, pNode->nPage, nX, nY);
            }
        }
    }
    func_020300f8(pCtx->gridSurface);
}
