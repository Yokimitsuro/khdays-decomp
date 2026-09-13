/* func_ov008_02064fb8 -- Ov008_LoadGridFromSave: rebuild the grid menu's
 * pages from the save's equipped items.  The page slots (+0x19c4) and the
 * per-item grid counts (+0x1bf0, 0x277 bytes) are cleared; then for every
 * page and cell the equipped item id (GameState 0xee0, 3 x 40) selects a
 * panel record (+0x207c, 0x9c each, kept at +0x19b4 meanwhile): while the
 * player owns more copies (GameState 0x810) than are already on the grid the
 * count is bumped, the record put in the page slot and, when it is placed
 * (+0x24), a 0x34-byte tracked node allocated for it -- link -1, shape entry
 * (+0x2080, 0x18 each) of the placed slot, id assigned, registered on the
 * page at the cell minus the record's anchor offset (+0x28 / +0x29), and the
 * page, left / top, anchor column / row recorded.  Afterwards every page slot
 * holding a category 4 / 5 record whose grid cell (+0x1e88) carries no id is
 * emptied again and its count undone.  The grid gfx queue (+0xac) is
 * flushed and the view rebuilt from the slots and the tracked node list
 * (+0x1e7c) into the summary (+0x1f78).  Codegen: the sweep reuses the
 * counters of the first pass (page in j, column in i) -- the registers follow
 * the variables; the category test is written !(a != 4 && a != 5).
 */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;
typedef signed short   s16;

#define GRID_PAGES  3
#define GRID_ROWS   8
#define GRID_COLS   5
#define GRID_CELLS  (GRID_ROWS * GRID_COLS)
#define ITEM_ID_END 0x277
#define CATEGORY_LINK_A 4
#define CATEGORY_LINK_B 5

typedef struct Ov008ShapeEntry {
    u8  pad_00[0x18];
} Ov008ShapeEntry;

typedef struct Ov008Message15Record {
    u8  pad_00[0x14];
    int nItemId;              /* 0x14 */
    int nCategory;            /* 0x18 */
    u8  pad_1c[8];
    int nPlacedSlot;          /* 0x24: -1 = not placed */
    u8  nOffsetCol;           /* 0x28: anchor offset inside the shape */
    u8  nOffsetRow;           /* 0x29 */
    u8  pad_2a[0x9c - 0x2a];
} Ov008Message15Record;

typedef struct Ov008TrackedNode {
    u8  nId;                  /* 0x00 */
    u8  pad_01[9];
    u16 nPage;                /* 0x0a */
    u16 nLeft;                /* 0x0c */
    u16 nTop;                 /* 0x0e */
    u16 nAnchorCol;           /* 0x10 */
    u16 nAnchorRow;           /* 0x12 */
    u8  pad_14[0xc];
    int nLink;                /* 0x20 */
    Ov008ShapeEntry *pEntry;  /* 0x24 */
    u8  pad_28[0x34 - 0x28];
} Ov008TrackedNode;

typedef struct Ov008MenuContext {
    u8  pad_0000[0xac];
    u8  gridSurface[0x19b4 - 0xac]; /* 0x00ac */
    Ov008Message15Record *pListNode; /* 0x19b4 */
    u8  pad_19b8[0xc];
    Ov008Message15Record *apPageSlot[GRID_PAGES][GRID_CELLS]; /* 0x19c4 */
    u8  pad_1ba4[0x1bf0 - 0x1ba4];
    u8  aGridCount[ITEM_ID_END]; /* 0x1bf0: copies of each item on the grid */
    u8  pad_1e67[0x1e7c - 0x1e67];
    u8  nodeList[0xc];        /* 0x1e7c */
    u8  aGrid[GRID_PAGES][GRID_ROWS][GRID_COLS]; /* 0x1e88 */
    u8  pad_1f00[0x1f78 - 0x1f00];
    u8  summary[0x207c - 0x1f78]; /* 0x1f78 */
    Ov008Message15Record *pRecords; /* 0x207c */
    Ov008ShapeEntry *pShapeEntries; /* 0x2080 */
} Ov008MenuContext;

typedef struct GameState {
    u8  pad_0000[0x810];
    u8  aItemCount[0xee0 - 0x810]; /* 0x810 */
    u16 aEquipped[GRID_PAGES][GRID_CELLS]; /* 0xee0 */
} GameState;

extern GameState *data_0204be18;
extern void  MI_CpuFill8(void *pDst, int nValue, u32 nSize);
extern void *NNSi_FndAllocFromDefaultExpHeap(int nSize);
extern void  func_ov008_02060944(Ov008MenuContext *pCtx, Ov008TrackedNode *pNode); /* Ov008_AssignTrackedNodeId */
extern int   func_ov008_020604e4(Ov008MenuContext *pCtx, Ov008TrackedNode *pNode, int nPage, int nCol, int nRow, int nArg); /* register the node */
extern void  func_020300f8(void *pSurface);                                 /* EnqueueObjGfxCommand */
extern void  func_ov008_02053470(void *pSummary, void *pSlots, void *pList); /* RebuildViewAndCountCells */

void func_ov008_02064fb8(Ov008MenuContext *pCtx)
{
    int i;                    /* page, then the column of the sweep */
    int j;                    /* cell, then the page of the sweep */
    int nCol;
    int nRow;
    int nItemId;
    Ov008TrackedNode *pNode;
    Ov008Message15Record *pRecord;

    MI_CpuFill8(pCtx->apPageSlot, 0, sizeof(pCtx->apPageSlot));
    MI_CpuFill8(pCtx->aGridCount, 0, ITEM_ID_END);
    for (i = 0; i < GRID_PAGES; i++) {
        for (j = 0; j < GRID_CELLS; j++) {
            if (data_0204be18->aEquipped[i][j] != 0) {
                pCtx->pListNode = &pCtx->pRecords[data_0204be18->aEquipped[i][j]];
                nItemId = pCtx->pListNode->nItemId;
                if (pCtx->aGridCount[nItemId] < data_0204be18->aItemCount[nItemId]) {
                    pCtx->aGridCount[nItemId]++;
                    pCtx->apPageSlot[i][j] = pCtx->pListNode;
                    if (pCtx->pListNode->nPlacedSlot >= 0) {
                        nCol = j % GRID_COLS;
                        nRow = j / GRID_COLS;
                        pNode = NNSi_FndAllocFromDefaultExpHeap(sizeof(Ov008TrackedNode));
                        MI_CpuFill8(pNode, 0, sizeof(Ov008TrackedNode));
                        pNode->nLink = -1;
                        pNode->pEntry = &pCtx->pShapeEntries[pCtx->pListNode->nPlacedSlot];
                        func_ov008_02060944(pCtx, pNode);
                        func_ov008_020604e4(pCtx, pNode, i, nCol - pCtx->pListNode->nOffsetCol, nRow - pCtx->pListNode->nOffsetRow, 0);
                        pNode->nPage = i;
                        pNode->nLeft = nCol - pCtx->pListNode->nOffsetCol;
                        pNode->nTop = nRow - pCtx->pListNode->nOffsetRow;
                        pNode->nAnchorCol = nCol;
                        pNode->nAnchorRow = nRow;
                    }
                }
                pCtx->pListNode = 0;
            }
        }
    }
    for (j = 0; j < GRID_PAGES; j++) {
        for (nRow = 0; nRow < GRID_ROWS; nRow++) {
            for (i = 0; i < GRID_COLS; i++) {
                pRecord = pCtx->apPageSlot[j][nRow * GRID_COLS + i];
                if (pRecord != 0
                    && !(pRecord->nCategory != CATEGORY_LINK_A && pRecord->nCategory != CATEGORY_LINK_B)
                    && pCtx->aGrid[j][nRow][i] == 0) {
                    pCtx->apPageSlot[j][nRow * GRID_COLS + i] = 0;
                    pCtx->aGridCount[pRecord->nItemId]--;
                }
            }
        }
    }
    func_020300f8(pCtx->gridSurface);
    func_ov008_02053470(pCtx->summary, pCtx->apPageSlot, pCtx->nodeList);
}
