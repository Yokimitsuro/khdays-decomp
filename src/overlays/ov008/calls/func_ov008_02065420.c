/* func_ov008_02065420 -- Ov008_ClearGridMenu: empty the grid menu.  Resets the
 * grid, rebuilds the panel reveal mask, removes every tracked node from the
 * node list, zeroes the 0x277-byte block at +0x1bf0 and the page slot table
 * (+0x19c4, 0x1e0 bytes), drops the cursor cell, then hides each grid display
 * cell of the visible page up to the first blocked (0xff) cell of every row,
 * and all nine column-header cells.
 */
typedef unsigned char u8;
typedef unsigned int  u32;

#define GRID_PAGES 3
#define GRID_ROWS  8
#define GRID_COLS  5
#define COL_HEADERS 9
#define CELL_BLOCKED 0xff
#define SCRATCH_SIZE 0x277

typedef struct Ov008GridDisplayCell {
    int isActive;             /* 0x00 */
    u8  pad_04[0x28 - 0x4];
} Ov008GridDisplayCell;

typedef struct Ov008MenuContext {
    u8  pad_0000[0x18];
    u32 nVisiblePage;         /* 0x0018 */
    u8  pad_001c[0x10a0 - 0x1c];
    Ov008GridDisplayCell gridDisplayCells[GRID_ROWS][GRID_COLS];  /* 0x10a0 */
    u8  pad_16e0[0x1820 - 0x16e0];
    Ov008GridDisplayCell cursorCell;                              /* 0x1820 */
    u8  pad_1848[4];
    Ov008GridDisplayCell colHeaderCells[COL_HEADERS];             /* 0x184c */
    u8  pad_19b4[0x19c4 - 0x19b4];
    void *apPageSlot[GRID_PAGES][GRID_ROWS * GRID_COLS];          /* 0x19c4 */
    u8  pad_1ba4[0x1bf0 - 0x1ba4];
    u8  scratch[SCRATCH_SIZE];                                    /* 0x1bf0 */
    u8  pad_1e67[0x1e7c - 0x1e67];
    u8  trackedNodeList[12];                                      /* 0x1e7c */
    u8  aGrid[GRID_PAGES][GRID_ROWS][GRID_COLS];                  /* 0x1e88 */
} Ov008MenuContext;

extern void func_ov008_020615dc(Ov008MenuContext *pCtx, int nArg);        /* grid reset */
extern void func_ov008_02060a0c(Ov008MenuContext *pCtx);                  /* Ov008_RebuildPanelRevealMask */
extern void *NNS_FndGetNextListObject(void *pList, void *pObject);
extern void func_ov008_020609e4(Ov008MenuContext *pCtx, void *pNode);     /* remove a tracked node */
extern void MI_CpuFill8(void *pDst, int nValue, u32 nSize);
extern void INITi_CpuClear32_0x01ff86fc(int nValue, void *pDst, u32 nSize);

void func_ov008_02065420(Ov008MenuContext *pCtx)
{
    void *pNode;
    void *pNext;
    int nRow;
    int nCol;

    func_ov008_020615dc(pCtx, 0);
    func_ov008_02060a0c(pCtx);
    pNode = NNS_FndGetNextListObject(pCtx->trackedNodeList, 0);
    while (pNode != 0) {
        pNext = NNS_FndGetNextListObject(pCtx->trackedNodeList, pNode);
        func_ov008_020609e4(pCtx, pNode);
        pNode = pNext;
    }
    MI_CpuFill8(pCtx->scratch, 0, SCRATCH_SIZE);
    INITi_CpuClear32_0x01ff86fc(0, pCtx->apPageSlot, sizeof(pCtx->apPageSlot));
    pCtx->cursorCell.isActive = 0;
    for (nRow = 0; nRow < GRID_ROWS; nRow++) {
        for (nCol = 0; nCol < GRID_COLS; nCol++) {
            if (pCtx->aGrid[pCtx->nVisiblePage][nRow][nCol] == CELL_BLOCKED) {
                break;
            }
            pCtx->gridDisplayCells[nRow][nCol].isActive = 0;
        }
    }
    for (nCol = 0; nCol < COL_HEADERS; nCol++) {
        pCtx->colHeaderCells[nCol].isActive = 0;
    }
}
