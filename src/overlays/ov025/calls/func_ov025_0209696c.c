/* func_ov025_0209696c -- Ov008_FillCursorCellFromSpares: fill the empty grid
 * cell under the cursor (+0x64 / +0x66) on the visible page (+0x18) with a
 * spare record.  The cell's grid id (+0x1e88) names a tracked node (list
 * +0x1e7c, id at +0); the node's anchor cell (+0x10 / +0x12) must hold a
 * record (+0x19c4) and the node's box (+0xc / +0xe, +0x14 x +0x16) is
 * scanned for its first empty cell carrying that id.  A spare record is then
 * picked by the anchor record's category (+0x18): 1 = a spare single, 4 =
 * a spare of the anchor's kind (02063e58), else the best spare item.  When one
 * is found and it can be placed at that cell (02060d38), the record's row
 * counter is bumped, the grid gfx queue (+0xac) flushed and the record
 * dispatched by kind; the grid hits are rebuilt and 1 returned.  Returns 0
 * otherwise.
 */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

#define GRID_PAGES 3
#define GRID_ROWS  8
#define GRID_COLS  5
#define CATEGORY_SINGLE 1
#define CATEGORY_KIND   4

typedef struct NNSFndList {
    u8 pad_00[0xc];
} NNSFndList;

typedef struct Ov008Message15Record {
    u8  pad_00[0x14];
    int nItemId;              /* 0x14 */
    int nCategory;            /* 0x18 */
} Ov008Message15Record;

typedef struct Ov008TrackedNode {
    u8  nId;                  /* 0x00: grid cell id */
    u8  pad_01[0xb];
    u16 nLeft;                /* 0x0c */
    u16 nTop;                 /* 0x0e */
    u16 nAnchorCol;           /* 0x10 */
    u16 nAnchorRow;           /* 0x12 */
    u16 nWidth;               /* 0x14 */
    u16 nHeight;              /* 0x16 */
} Ov008TrackedNode;

typedef struct Ov008MenuContext {
    u8  pad_0000[0x18];
    u32 nVisiblePage;         /* 0x0018 */
    u8  pad_001c[0x64 - 0x1c];
    u16 nCursorCol;           /* 0x0064 */
    u16 nCursorRow;           /* 0x0066 */
    u8  pad_0068[0xac - 0x68];
    u8  gfxQueue[0x19c4 - 0xac]; /* 0x00ac */
    Ov008Message15Record *apPageSlot[GRID_PAGES][GRID_ROWS * GRID_COLS]; /* 0x19c4 */
    u8  pad_1ba4[0x1e7c - 0x1ba4];
    NNSFndList nodeList;      /* 0x1e7c */
    u8  aGrid[GRID_PAGES][GRID_ROWS][GRID_COLS]; /* 0x1e88 */
} Ov008MenuContext;

extern Ov008TrackedNode *NNS_FndGetNextListObject(NNSFndList *pList, void *pObject);
extern Ov008Message15Record *func_ov025_020961d8(Ov008MenuContext *pCtx, Ov008TrackedNode *pNode); /* Ov008_FindSpareSingleForNode */
extern Ov008Message15Record *func_ov025_02096384(Ov008MenuContext *pCtx, Ov008TrackedNode *pNode, Ov008Message15Record *pAnchor);
extern Ov008Message15Record *func_ov025_020966f8(Ov008MenuContext *pCtx, Ov008Message15Record *pAnchor); /* Ov008_FindBestSpareItemForNode */
extern int  func_ov025_02093288(Ov008MenuContext *pCtx, Ov008Message15Record *pRecord, u32 nPage, u32 nCol, u16 nRow); /* place at cell */
extern void func_ov025_02090d04(Ov008MenuContext *pCtx, int nItemId, int nDelta); /* Ov008_BumpRowCounter */
extern void func_020300f8(void *pQueue);                                  /* EnqueueObjGfxCommand */
extern void func_020343cc(Ov008Message15Record **ppRecord);               /* DispatchByNodeKind */
extern void func_ov025_02093038(Ov008MenuContext *pCtx);                  /* Ov008_RebuildGridHits */

int func_ov025_0209696c(Ov008MenuContext *pCtx)
{
    int bFilled;
    Ov008Message15Record *pRecord;
    Ov008TrackedNode *pNode;
    Ov008Message15Record *pAnchor;
    int nRow;
    int nCol;
    u8 nId;                   /* declared last: colours r6 */

    pRecord = 0;
    bFilled = 0;
    nId = pCtx->aGrid[pCtx->nVisiblePage][pCtx->nCursorRow][pCtx->nCursorCol];
    for (pNode = NNS_FndGetNextListObject(&pCtx->nodeList, 0); pNode != 0;
         pNode = NNS_FndGetNextListObject(&pCtx->nodeList, pNode)) {
        if (pNode->nId == nId) {
            break;
        }
    }
    if (pNode == 0) {
        return 0;
    }
    pAnchor = pCtx->apPageSlot[pCtx->nVisiblePage][pNode->nAnchorRow * GRID_COLS + pNode->nAnchorCol];
    if (pAnchor == 0) {
        return 0;
    }
    for (nRow = pNode->nTop; nRow < pNode->nTop + pNode->nHeight; nRow++) {
        for (nCol = pNode->nLeft; nCol < pNode->nLeft + pNode->nWidth; nCol++) {
            if (nId == pCtx->aGrid[pCtx->nVisiblePage][nRow][nCol]
                && pCtx->apPageSlot[pCtx->nVisiblePage][(u32)(nCol + nRow * GRID_COLS)] == 0) { /* u32 index: keeps nRow * 5 out of the hoisted base */
                goto found;
            }
        }
    }
    return 0;
found:
    switch (pAnchor->nCategory) {
    case CATEGORY_SINGLE:
        pRecord = func_ov025_020961d8(pCtx, pNode);
        break;
    case CATEGORY_KIND:
        pRecord = func_ov025_02096384(pCtx, pNode, pAnchor);
        break;
    default:
        pRecord = func_ov025_020966f8(pCtx, pAnchor);
        break;
    }
    if (pRecord != 0) {
        if (func_ov025_02093288(pCtx, pRecord, pCtx->nVisiblePage, (u16)nCol, (u16)nRow) != 0) {
            func_ov025_02090d04(pCtx, pRecord->nItemId, 1);
            func_020300f8(pCtx->gfxQueue);
            func_020343cc(&pRecord);
        }
        func_ov025_02093038(pCtx);
        bFilled = 1;
    }
    return bFilled;
}
