/* func_ov025_02093288 -- Ov008_PlaceNodeOnPage: put a tracked node at (col, row)
 * of a page.  Fails (0) when the placement check refuses it.  Otherwise the
 * "replaced same entry" word (+0x54) is set when the page slot already holds a
 * node with the same entry (+0x14); the node is registered (02060b58) and, if it
 * took and the page is the visible one (+0x18), the display cell (rows of 5,
 * 0xc8 per row at +0x10a0) is activated with state 0x1f and given the texture of
 * the entry found by the node's 1-based tag (+0x20); the page slot then points at
 * the node.  Returns the registration result.
 *
 * Codegen: the page slot base is NOT a local -- written as
 * pCtx->apPageSlot[nPage][nIndex] at each use it is the compiler's CSE
 * temp (sl) and the index variable takes sb; a pPage local swaps them.
 * The check's row parameter is u16 (the row loads fresh into r4 for it)
 * and the registration's is int (the reload r8 feeds both the index and
 * that call); u32 on either side re-colours the row temps.
 */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

#define PAGE_STRIDE 0xa0
#define PAGE_COLS   5
#define DISPLAY_CELL_ACTIVE_STATE 0x1f

typedef struct Ov008TrackedNode {
    u8  pad_00[0x14];
    int nEntry;               /* 0x14 */
    u8  pad_18[8];
    u16 nTag;                 /* 0x20 */
} Ov008TrackedNode;

typedef struct Ov008GridDisplayCell {
    int isActive;             /* 0x00 */
    int aTexture[6];          /* 0x04 */
    u8  pad_1c[2];
    u16 displayState;         /* 0x1e */
    u8  pad_20[8];
} Ov008GridDisplayCell;

typedef struct Ov008MenuContext {
    u8  pad_0000[0x18];
    u32 nVisiblePage;         /* 0x0018 */
    u8  pad_001c[0x54 - 0x1c];
    int bReplacedSame;        /* 0x0054 */
    u8  pad_0058[0x10a0 - 0x58];
    Ov008GridDisplayCell gridDisplayCells[8][5];  /* 0x10a0 */
    u8  pad_16e0[0x19c4 - 0x16e0];
    Ov008TrackedNode *apPageSlot[3][8 * PAGE_COLS]; /* 0x19c4: per page, row * 5 + col */
} Ov008MenuContext;

extern int  func_ov025_020925b8(Ov008MenuContext *pCtx, Ov008TrackedNode *pNode, u32 nPage, u32 nCol, u16 nRow, int nOne);
extern int  func_ov025_020930a8(Ov008MenuContext *pCtx, Ov008TrackedNode *pNode, u32 nPage, int nCol, int nRow);
extern int *func_ov025_0208ffc4(Ov008MenuContext *pCtx, u32 nTag);          /* Ov008_FindEntryBy1BasedTag */
extern void func_ov025_0208a5f8(int *pTexture, int *pParams);              /* Ov008_GetTextureParams */

int func_ov025_02093288(Ov008MenuContext *pCtx, Ov008TrackedNode *pNode, u32 nPage, u32 nCol, u16 nRow)
{
    int nResult;
    int nIndex;
    Ov008GridDisplayCell *pCell;

    if (func_ov025_020925b8(pCtx, pNode, nPage, nCol, nRow, 1) == 0) {
        return 0;
    }
    pCtx->bReplacedSame = 0;
    nIndex = nCol + nRow * PAGE_COLS;
    if (pCtx->apPageSlot[nPage][nIndex] != 0 && pNode->nEntry == pCtx->apPageSlot[nPage][nIndex]->nEntry) {
        pCtx->bReplacedSame = 1;
    }
    nResult = func_ov025_020930a8(pCtx, pNode, nPage, nCol, nRow);
    if (nResult != 0) {
        if (pCtx->nVisiblePage == nPage) {
            pCell = &pCtx->gridDisplayCells[nRow][nCol];
            pCell->isActive = 1;
            pCell->displayState = DISPLAY_CELL_ACTIVE_STATE;
            func_ov025_0208a5f8(pCell->aTexture, (int *)func_ov025_0208ffc4(pCtx, pNode->nTag)[1]);
        }
        pCtx->apPageSlot[nPage][nIndex] = pNode;
    }
    return nResult;
}
