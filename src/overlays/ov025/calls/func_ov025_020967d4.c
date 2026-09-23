/* func_ov025_020967d4 -- ov025 copy of Ov008_CanFillNodeGap: inspect the tracked node under
 * the cursor and test the first matching empty grid cell for a spare record.
 * The anchor record category selects which spare-record lookup to call.
 * Return 1 if a lookup succeeds, 0 otherwise.
 */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

#define GRID_PAGES 3
#define GRID_ROWS  8
#define GRID_COLS  5
#define ENTRY_KIND_SINGLE 1
#define ENTRY_KIND_PAIR   4

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
    u16 nColumn;              /* 0x0064 */
    u16 nRowSel;              /* 0x0066 */
    u8  pad_0068[0x19c4 - 0x68];
    Ov008Message15Record *apPageSlot[GRID_PAGES][GRID_ROWS * GRID_COLS]; /* 0x19c4 */
    u8  pad_1ba4[0x1e7c - 0x1ba4];
    u8  trackedNodeList[12];  /* 0x1e7c */
    u8  aGrid[GRID_PAGES][GRID_ROWS][GRID_COLS]; /* 0x1e88 */
} Ov008MenuContext;

extern Ov008TrackedNode *NNS_FndGetNextListObject(void *pList, void *pObject);
extern Ov008Message15Record *func_ov025_020961d8(Ov008MenuContext *pCtx, Ov008TrackedNode *pNode);
extern Ov008Message15Record *func_ov025_02096384(Ov008MenuContext *pCtx, Ov008TrackedNode *pNode, Ov008Message15Record *pAnchor);
extern Ov008Message15Record *func_ov025_020966f8(Ov008MenuContext *pCtx, Ov008Message15Record *pAnchor); /* Ov008_FindBestSpareItemForNode */

int func_ov025_020967d4(Ov008MenuContext *pCtx)
{
    u8 nId;
    Ov008TrackedNode *pNode;
    Ov008Message15Record *pAnchor;
    int nRow;
    int nCol;
    Ov008Message15Record *pSpare;

    nId = pCtx->aGrid[pCtx->nVisiblePage][pCtx->nRowSel][pCtx->nColumn];
    for (pNode = NNS_FndGetNextListObject(pCtx->trackedNodeList, 0); pNode != 0;
         pNode = NNS_FndGetNextListObject(pCtx->trackedNodeList, pNode)) {
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
                && pCtx->apPageSlot[pCtx->nVisiblePage][(u32)(nCol + nRow * GRID_COLS)] == 0) {
                goto found;
            }
        }
    }
    return 0;
found:
    switch (pAnchor->nCategory) {
    case ENTRY_KIND_SINGLE:
        pSpare = func_ov025_020961d8(pCtx, pNode);
        break;
    case ENTRY_KIND_PAIR:
        pSpare = func_ov025_02096384(pCtx, pNode, pAnchor);
        break;
    default:
        pSpare = func_ov025_020966f8(pCtx, pAnchor);
        break;
    }
    return pSpare != 0;
}
