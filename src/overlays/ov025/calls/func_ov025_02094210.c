/* func_ov025_02094210 -- Ov008_PickUpGridNode: lift the node under the cursor
 * cell (+0x64/+0x66) of the visible page (+0x18) off the grid for dragging.
 * Nothing (0) when the page slot is empty.  Otherwise the grid is reset, the
 * node's home (page +0x68, cell +0x6c/+0x6e) and the list node (+0x19b4) are
 * recorded, the cursor's display cell (+0x1848) is pointed at the grid cell
 * and put into state 0x10, the drag texture (+0x1824) is taken from the
 * node's 1-based tag, widget 3's sub-item set pushed; a node with an icon
 * frame (+0x24) re-finds its grid hit (unlinked through 02061b18, its sub-item
 * set pushed on widget 0xc9) and shows widget 0xc9 with that frame.  Then the
 * grid is rebuilt (02060e3c) and the pending, drag-active and +0x50 words are
 * set.  Returns 1.
 */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

#define PAGE_COLS   5
#define WIDGET_DRAG 3
#define WIDGET_ICON 0xc9
#define CELL_STATE_LIFTED 0x10

typedef struct Ov008ShapeEntry {
    u8  pad_00[0x20];
    u16 nTag;                 /* 0x20: 1-based texture entry tag */
    u8  pad_22[2];
    int nIconFrame;           /* 0x24: -1 = none */
} Ov008ShapeEntry;

typedef struct Ov008GridDisplayCell {
    int isActive;             /* 0x00 */
    int aTexture[6];          /* 0x04 */
    u8  pad_1c[2];
    u16 displayState;         /* 0x1e */
    u8  pad_20[8];
} Ov008GridDisplayCell;

typedef struct Ov008GridHit {
    u8  pad_00[4];
    int nSubitem;             /* 0x04 */
} Ov008GridHit;

typedef struct Ov008TextureEntry {
    u8    pad_00[4];
    int  *pParams;            /* 0x04 */
} Ov008TextureEntry;

typedef struct Ov008DragTexture {
    int aTexture[6];          /* 0x00 */
    u8  pad_18[2];
    u16 nSlot;                /* 0x1a */
} Ov008DragTexture;

typedef struct Ov008MenuContext {
    u8  pad_0000[0x18];
    u32 nVisiblePage;         /* 0x0018 */
    u8  pad_001c[0x40 - 0x1c];
    int nPending;             /* 0x0040 */
    u8  pad_0044[0xc];
    int bLifted;              /* 0x0050 */
    u8  pad_0054[0x64 - 0x54];
    u16 nColumn;              /* 0x0064 */
    u16 nRowSel;              /* 0x0066 */
    u32 nDragNode;            /* 0x0068 */
    u16 nHomeCol;             /* 0x006c */
    u16 nHomeRow;             /* 0x006e */
    u8  pad_0070[0x10a0 - 0x70];
    Ov008GridDisplayCell gridDisplayCells[8][PAGE_COLS]; /* 0x10a0 */
    u8  pad_16e0[0x1820 - 0x16e0];
    int bDragActive;          /* 0x1820 */
    Ov008DragTexture drag;    /* 0x1824 */
    u8  pad_1840[8];
    Ov008GridDisplayCell *pCurrentCell; /* 0x1848 */
    u8  pad_184c[0x19b4 - 0x184c];
    Ov008ShapeEntry *pListNode;         /* 0x19b4 */
    u8  pad_19b8[0xc];
    Ov008ShapeEntry *apPageSlot[3][8 * PAGE_COLS]; /* 0x19c4: per page, row * 5 + col */
} Ov008MenuContext;

extern void func_ov025_02093b08(Ov008MenuContext *pCtx, int nArg);          /* grid reset */
extern Ov008TextureEntry *func_ov025_0208ffc4(Ov008MenuContext *pCtx, u32 nTag); /* Ov008_FindEntryBy1BasedTag */
extern void func_ov025_0208a5f8(int *pTexture, int *pParams);                /* Ov008_GetTextureParams */
extern int  func_ov025_02084a7c(void);                                       /* Ov008_GetContext */
extern void *func_ov025_0208843c(int nCtx, int nId);                         /* FindEntryById */
extern void func_ov025_020887c0(int nCtx, void *pEntry, int nValue);         /* Ov008_PushSubitemSet */
extern Ov008GridHit *func_ov025_020922fc(Ov008MenuContext *pCtx, u32 nPage, u32 nCol, u32 nRow); /* Ov008_FindGridHit */
extern void func_ov025_02094044(Ov008MenuContext *pCtx, Ov008GridHit *pHit); /* unlink the hit */
extern void func_ov025_02088928(int nCtx, void *pEntry, int nFrame);         /* Ov008_ReleaseTwoSlotsEx */
extern void func_ov025_0208884c(int nCtx, void *pEntry, int bVisible);       /* SetEntrySlotsVisible */
extern void func_ov025_0209338c(Ov008MenuContext *pCtx);                     /* rebuild the grid */

int func_ov025_02094210(Ov008MenuContext *pCtx)
{
    Ov008ShapeEntry *pNode;
    Ov008GridDisplayCell *pCell;
    int nCtx;
    void *pIcon;
    Ov008GridHit *pHit;
    int nResult;

    nResult = 0;
    pNode = pCtx->apPageSlot[pCtx->nVisiblePage][pCtx->nRowSel * PAGE_COLS + pCtx->nColumn];
    if (pNode != 0) {
        func_ov025_02093b08(pCtx, 0);
        pCtx->nDragNode = pCtx->nVisiblePage;
        pCtx->nHomeCol = pCtx->nColumn;
        pCtx->nHomeRow = pCtx->nRowSel;
        pCtx->pListNode = pNode;
        pCell = &pCtx->gridDisplayCells[pCtx->nRowSel][pCtx->nColumn];
        pCtx->pCurrentCell = pCell;
        pCell->displayState = CELL_STATE_LIFTED;
        func_ov025_0208a5f8(pCtx->drag.aTexture, func_ov025_0208ffc4(pCtx, pCtx->pListNode->nTag)->pParams);
        nCtx = func_ov025_02084a7c();
        func_ov025_020887c0(nCtx, func_ov025_0208843c(nCtx, WIDGET_DRAG), 1);
        pIcon = func_ov025_0208843c(nCtx, WIDGET_ICON);
        if (pNode->nIconFrame >= 0) {
            func_ov025_02094044(pCtx, func_ov025_020922fc(pCtx, pCtx->nDragNode, pCtx->nHomeCol, pCtx->nHomeRow));
            pHit = func_ov025_020922fc(pCtx, pCtx->nDragNode, pCtx->nHomeCol, pCtx->nHomeRow);
            if (pHit != 0) {
                func_ov025_020887c0(nCtx, pIcon, pHit->nSubitem);
            }
            func_ov025_02088928(nCtx, pIcon, (u16)pNode->nIconFrame);
            func_ov025_0208884c(nCtx, pIcon, 1);
        }
        func_ov025_0209338c(pCtx);
        nResult = 1;
        pCtx->nPending = 1;
        pCtx->bDragActive = 1;
        pCtx->bLifted = 1;
    }
    return nResult;
}
