/* func_ov025_02094044 -- Ov008_LiftTrackedNode: collect the cells of tracked
 * node pNode for dragging.  After the tracked grid cells are cleared, every
 * cell of the node's box (+0xc/+0xe, +0x14 x +0x16) on its page (+0xa) other
 * than the anchor (+0x10/+0x12) whose grid id (+0x1e88) is the node's id (+0)
 * and whose page slot (+0x19c4) holds a record gets a 0x18-byte lifted-cell
 * record {record, column / row offset from the anchor} appended to the lifted
 * list (+0x19b8); the cell's display cell (+0x10a0, 8 x 5) is put in state
 * 0x10 and the next drag cell (+0x184c, 0x28 each) activated in state 0x10
 * with the texture of the record's 1-based tag (+0x20).
 */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

#define GRID_PAGES 3
#define GRID_ROWS  8
#define GRID_COLS  5
#define CELL_STATE_LIFTED 0x10

typedef struct Ov008Message15Record {
    u8  pad_00[0x20];
    u16 nTag;                 /* 0x20: 1-based texture entry tag */
} Ov008Message15Record;

typedef struct Ov008TrackedNode {
    u8  nId;                  /* 0x00: grid cell id */
    u8  pad_01[9];
    u16 nPage;                /* 0x0a */
    u16 nLeft;                /* 0x0c */
    u16 nTop;                 /* 0x0e */
    u16 nAnchorCol;           /* 0x10 */
    u16 nAnchorRow;           /* 0x12 */
    u16 nWidth;               /* 0x14 */
    u16 nHeight;              /* 0x16 */
} Ov008TrackedNode;

typedef struct Ov008LiftedCell {
    Ov008Message15Record *pRecord; /* 0x00 */
    int nColOffset;           /* 0x04: from the anchor */
    int nRowOffset;           /* 0x08 */
    u8  pad_0c[0x18 - 0xc];
} Ov008LiftedCell;

typedef struct Ov008GridDisplayCell {
    int isActive;             /* 0x00 */
    int aTexture[6];          /* 0x04 */
    u8  pad_1c[2];
    u16 displayState;         /* 0x1e */
    u8  pad_20[8];
} Ov008GridDisplayCell;

typedef struct Ov008TextureEntry {
    u8    pad_00[4];
    int  *pParams;            /* 0x04 */
} Ov008TextureEntry;

typedef struct Ov008MenuContext {
    u8  pad_0000[0x10a0];
    Ov008GridDisplayCell gridDisplayCells[GRID_ROWS][GRID_COLS]; /* 0x10a0 */
    u8  pad_16e0[0x184c - 0x16e0];
    Ov008GridDisplayCell aDragCell[1];  /* 0x184c: one per lifted cell */
    u8  pad_1874[0x19b8 - 0x1874];
    u8  liftedList[12];       /* 0x19b8 */
    Ov008Message15Record *apPageSlot[GRID_PAGES][GRID_ROWS * GRID_COLS]; /* 0x19c4 */
    u8  pad_1ba4[0x1e88 - 0x1ba4];
    u8  aGrid[GRID_PAGES][GRID_ROWS][GRID_COLS]; /* 0x1e88 */
} Ov008MenuContext;

extern void  func_ov025_0208f09c(Ov008MenuContext *pCtx);                /* Ov008_ClearTrackedGridCells */
extern void *NNSi_FndAllocFromDefaultExpHeap(u32 nSize);                 /* AllocDefault */
extern void  MI_CpuFill8(void *pDst, int nValue, u32 nSize);
extern void  NNS_FndAppendListObject(void *pList, void *pObject);
extern Ov008TextureEntry *func_ov025_0208ffc4(Ov008MenuContext *pCtx, u32 nTag); /* Ov008_FindEntryBy1BasedTag */
extern void  func_ov025_0208a5f8(int *pTexture, int *pParams);           /* Ov008_GetTextureParams */

void func_ov025_02094044(Ov008MenuContext *pCtx, Ov008TrackedNode *pNode)
{
    u32 nPage;
    int nRow;
    int nCol;
    u32 nGridCol;
    u32 nGridRow;
    Ov008LiftedCell *pCell;
    int nLifted;

    nPage = pNode->nPage;
    func_ov025_0208f09c(pCtx);
    nLifted = 0;
    for (nRow = 0; nRow < pNode->nHeight; nRow++) {
        for (nCol = 0; nCol < pNode->nWidth; nCol++) {
            if (pNode->nAnchorCol == pNode->nLeft + nCol && pNode->nAnchorRow == pNode->nTop + nRow) {
                continue;
            }
            nGridCol = pNode->nLeft + nCol;
            nGridRow = pNode->nTop + nRow;
            if (pNode->nId != pCtx->aGrid[nPage][nGridRow][nGridCol]) {
                continue;
            }
            if (pCtx->apPageSlot[nPage][nGridRow * GRID_COLS + nGridCol] == 0) {
                continue;
            }
            pCell = NNSi_FndAllocFromDefaultExpHeap(sizeof(Ov008LiftedCell));
            MI_CpuFill8(pCell, 0, sizeof(Ov008LiftedCell));
            pCell->pRecord = pCtx->apPageSlot[nPage][nGridRow * GRID_COLS + nGridCol];
            pCell->nColOffset = nCol - (pNode->nAnchorCol - pNode->nLeft);
            pCell->nRowOffset = nRow - (pNode->nAnchorRow - pNode->nTop);
            NNS_FndAppendListObject(pCtx->liftedList, pCell);
            pCtx->gridDisplayCells[nGridRow][nGridCol].displayState = CELL_STATE_LIFTED;
            pCtx->aDragCell[nLifted].isActive = 1;
            pCtx->aDragCell[nLifted].displayState = CELL_STATE_LIFTED;
            func_ov025_0208a5f8(pCtx->aDragCell[nLifted].aTexture, func_ov025_0208ffc4(pCtx, pCell->pRecord->nTag)->pParams);
            nLifted++;
        }
    }
}
