/* func_ov008_0205fbc4 -- Ov008_InitPageGrid: reset the tracked-node list (link at
 * node +0x28) and lay out the 3 x 8 x 5 cell grid: the first nCellCount cells in
 * page/row/column order are free (0), the rest are blocked (0xff); the grid is
 * then copied into the working grid.
 */
typedef unsigned char u8;

#define GRID_PAGES 3
#define GRID_ROWS  8
#define GRID_COLS  5
#define CELL_FREE    0
#define CELL_BLOCKED 0xff

typedef struct NNSFndList {
    u8 pad[12];
} NNSFndList;

typedef struct Ov008MenuContext {
    u8         pad_0000[0x1e74];
    int        nCellCount;                                /* 0x1e74 */
    u8         pad_1e78[4];
    NNSFndList trackedNodeList;                           /* 0x1e7c */
    u8         aGrid[GRID_PAGES][GRID_ROWS][GRID_COLS];   /* 0x1e88 */
    u8         aWorkGrid[GRID_PAGES][GRID_ROWS][GRID_COLS]; /* 0x1f00 */
} Ov008MenuContext;

extern void NNS_FndInitList(NNSFndList *pList, unsigned short nOffset);
extern void MI_CpuCopy8(const void *pSrc, void *pDst, unsigned int nSize);

void func_ov008_0205fbc4(Ov008MenuContext *pCtx)
{
    int nCell = 0;
    int nPage;
    int nRow;
    int nCol;

    NNS_FndInitList(&pCtx->trackedNodeList, 0x28);
    for (nPage = 0; nPage < GRID_PAGES; nPage++) {
        for (nRow = 0; nRow < GRID_ROWS; nRow++) {
            for (nCol = 0; nCol < GRID_COLS; nCol++) {
                pCtx->aGrid[nPage][nRow][nCol] = nCell < pCtx->nCellCount ? CELL_FREE : CELL_BLOCKED;
                nCell++;
            }
        }
    }
    MI_CpuCopy8(pCtx->aGrid, pCtx->aWorkGrid, sizeof(pCtx->aGrid));
}
