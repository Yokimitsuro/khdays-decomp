/* func_ov025_020961d8 -- Ov008_FindSpareSingleForNode: pick a panel item
 * record (0x9c each, table at ctx+0x207c) the player still has spare copies
 * of (stock at GameState 0x810 above the grid count) and that is not yet
 * placed (+0x24 < 0), to fill tracked node pNode.  First the node's own box
 * (+0xc/+0xe, +0x14 x +0x16) on the visible page is scanned, skipping the
 * anchor cell (+0x10/+0x12) and cells outside the shape's 64-bit cell mask
 * (+0x24 -> +0x10, bit col + 8 * row); the first page slot holding a spare
 * record wins.  Otherwise the record table is walked from id 1 for the first
 * category-1 record with spare copies.  Returns the record, or 0.
 */
typedef unsigned char      u8;
typedef unsigned short     u16;
typedef unsigned int       u32;
typedef unsigned long long u64;

#define GRID_PAGES 3
#define GRID_ROWS  8
#define GRID_COLS  5
#define ITEM_ID_END 0x277
#define CATEGORY_SINGLE 1

typedef struct Ov008ShapeEntry {
    u8  pad_00[0x10];
    u64 nCellMask;            /* 0x10: bit col + 8*row */
} Ov008ShapeEntry;

typedef struct Ov008Message15Record {
    u8  pad_00[0x14];
    int nItemId;              /* 0x14 */
    int nCategory;            /* 0x18 */
    u8  pad_1c[8];
    int nPlacedSlot;          /* 0x24: -1 = not placed */
    u8  pad_28[0x9c - 0x28];
} Ov008Message15Record;

typedef struct Ov008TrackedNode {
    u8  pad_00[0xc];
    u16 nLeft;                /* 0x0c */
    u16 nTop;                 /* 0x0e */
    u16 nAnchorCol;           /* 0x10 */
    u16 nAnchorRow;           /* 0x12 */
    u16 nWidth;               /* 0x14 */
    u16 nHeight;              /* 0x16 */
    u8  pad_18[0xc];
    Ov008ShapeEntry *pEntry;  /* 0x24 */
} Ov008TrackedNode;

typedef struct Ov008MenuContext {
    u8  pad_0000[0x18];
    u32 nVisiblePage;         /* 0x0018 */
    u8  pad_001c[0x19c4 - 0x1c];
    Ov008Message15Record *apPageSlot[GRID_PAGES][GRID_ROWS * GRID_COLS]; /* 0x19c4 */
    u8  pad_1ba4[0x207c - 0x1ba4];
    Ov008Message15Record *pRecords; /* 0x207c */
} Ov008MenuContext;

typedef struct GameState {
    u8 pad_0000[0x810];
    u8 aItemCount[0x8d0];     /* 0x810 */
} GameState;

extern GameState *data_0204be18;
extern char func_ov025_02090ca8(Ov008MenuContext *pCtx, int nItemId);  /* Ov008_CountGridEntriesForOwner */

Ov008Message15Record *func_ov025_020961d8(Ov008MenuContext *pCtx, Ov008TrackedNode *pNode)
{
    int nRow;
    int nCol;
    Ov008Message15Record *pRecord;
    Ov008Message15Record *pItem;

    for (nRow = pNode->nTop; nRow < pNode->nTop + pNode->nHeight; nRow++) {
        for (nCol = pNode->nLeft; nCol < pNode->nLeft + pNode->nWidth; nCol++) {
            if (pNode->nAnchorCol == nCol && pNode->nAnchorRow == nRow) {
                continue;
            }
            if ((pNode->pEntry->nCellMask & (1ULL << ((nCol - pNode->nLeft) + (nRow - pNode->nTop) * 8))) == 0) {
                continue;
            }
            pRecord = *(Ov008Message15Record **)((u8 *)pCtx->apPageSlot[pCtx->nVisiblePage] + (nRow * GRID_COLS + nCol) * 4);
            if (pRecord == 0) {
                continue;
            }
            if (pRecord->nPlacedSlot >= 0) {
                continue;
            }
            if ((u32)func_ov025_02090ca8(pCtx, pRecord->nItemId) < data_0204be18->aItemCount[pRecord->nItemId]) {
                return pRecord;
            }
        }
    }
    /* the row counter doubles as the record index (register allocation) */
    for (nRow = 1; nRow < ITEM_ID_END; nRow++) {
        pItem = &pCtx->pRecords[nRow];
        if (pItem->nCategory == CATEGORY_SINGLE && pItem->nPlacedSlot < 0
            && (u32)func_ov025_02090ca8(pCtx, pItem->nItemId) < data_0204be18->aItemCount[pItem->nItemId]) {
            return pItem;
        }
    }
    return 0;
}
