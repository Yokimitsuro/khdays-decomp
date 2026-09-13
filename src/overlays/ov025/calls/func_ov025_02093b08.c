/* func_ov025_02093b08 -- Ov008_ResetGridDrag: end a grid drag.  The drag
 * flag (+0x1820) and the nine drag cells (+0x184c, 0x28 each) are cleared.
 * With a lifted node (+0x19b4): when bRestore is set the node is put back at
 * its home cell (+0x68 page, +0x6c/+0x6e) through 02060d38, panel surface A
 * (+0xac) queued, and every lifted cell (+0x19b8 list: record, column / row
 * offset) put back beside it; the node is dropped, the tracked grid cells
 * cleared, widget 3's sub-item set 0 pushed, the current display cell
 * (+0x1848) put in state 0x1f and forgotten, row 0 repainted with the text
 * of the record under the cursor cell (0 when empty) in colour 0xf3, and
 * widgets 0xc9, 100 and 0x60 hidden.  The tween, pick-up and lifted words
 * (+0x28 / +0x2c / +0x50) are cleared.
 */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

#define DRAG_CELLS  9
#define GRID_PAGES  3
#define GRID_ROWS   8
#define GRID_COLS   5
#define WIDGET_DRAG 3
#define WIDGET_ICON 0xc9
#define WIDGET_INFO 100
#define WIDGET_HINT 0x60
#define CELL_STATE_IDLE 0x1f
#define COLOUR_ACTIVE 0xf3

typedef struct Ov008Message15Record {
    u8 pad[0x9c];
} Ov008Message15Record;

typedef struct Ov008LiftedCell {
    Ov008Message15Record *pRecord; /* 0x00 */
    int nColOffset;           /* 0x04 */
    int nRowOffset;           /* 0x08 */
} Ov008LiftedCell;

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
    u8  pad_001c[0x28 - 0x1c];
    int bTween;               /* 0x0028 */
    int bScroll;              /* 0x002c */
    u8  pad_0030[0x50 - 0x30];
    int bLifted;              /* 0x0050 */
    u8  pad_0054[0x64 - 0x54];
    u16 nColumn;              /* 0x0064 */
    u16 nRowSel;              /* 0x0066 */
    u32 nDragNode;            /* 0x0068: home page of the lifted node */
    u16 nHomeCol;             /* 0x006c */
    u16 nHomeRow;             /* 0x006e */
    u8  pad_0070[0xac - 0x70];
    u8  panelSurfaceA[0x3c];  /* 0x00ac */
    u8  pad_00e8[0x1820 - 0xe8];
    int bDragActive;          /* 0x1820 */
    u8  pad_1824[0x1848 - 0x1824];
    Ov008GridDisplayCell *pCurrentCell; /* 0x1848 */
    Ov008GridDisplayCell aDragCell[DRAG_CELLS]; /* 0x184c */
    u8  pad_19b4[0x19b4 - 0x19b4];
    Ov008Message15Record *pListNode;    /* 0x19b4 */
    u8  liftedList[12];       /* 0x19b8 */
    Ov008Message15Record *apPageSlot[GRID_PAGES][GRID_ROWS * GRID_COLS]; /* 0x19c4 */
    u8  pad_1ba4[0x1e68 - 0x1ba4];
    int textList[4];          /* 0x1e68 */
} Ov008MenuContext;

extern int  func_ov025_02093288(Ov008MenuContext *pCtx, Ov008Message15Record *pRecord, u32 nPage, u32 nCol, u16 nRow); /* place a record back */
extern void func_020300f8(void *pSurface);                                /* EnqueueObjGfxCommand */
extern Ov008LiftedCell *NNS_FndGetNextListObject(void *pList, void *pObject);
extern void func_ov025_0208f09c(Ov008MenuContext *pCtx);                  /* Ov008_ClearTrackedGridCells */
extern int  func_ov025_02084a7c(void);                                    /* Ov008_GetContext */
extern void *func_ov025_0208843c(int nCtx, int nId);                      /* FindEntryById */
extern void func_ov025_020887c0(int nCtx, void *pEntry, int nValue);      /* Ov008_PushSubitemSet */
extern void func_ov025_02091070(Ov008MenuContext *pCtx, int nRow, int nText, int nColour); /* Ov008_RepaintTextRow */
extern int  func_ov025_020b35d0(int *pList, Ov008Message15Record *pRecord); /* text index of a record */
extern void func_ov025_0208884c(int nCtx, void *pEntry, int bVisible);    /* SetEntrySlotsVisible */

void func_ov025_02093b08(Ov008MenuContext *pCtx, int bRestore)
{
    int i;
    Ov008LiftedCell *pCell;
    int nCtx;
    Ov008Message15Record *pRecord;

    pCtx->bDragActive = 0;
    for (i = 0; i < DRAG_CELLS; i++) {
        pCtx->aDragCell[i].isActive = 0;
    }
    if (pCtx->pListNode != 0) {
        if (bRestore != 0) {
            func_ov025_02093288(pCtx, pCtx->pListNode, pCtx->nDragNode, pCtx->nHomeCol, pCtx->nHomeRow);
            func_020300f8(pCtx->panelSurfaceA);
            for (pCell = NNS_FndGetNextListObject(pCtx->liftedList, 0); pCell != 0;
                 pCell = NNS_FndGetNextListObject(pCtx->liftedList, pCell)) {
                func_ov025_02093288(pCtx, pCell->pRecord, pCtx->nDragNode,
                                    (u16)(pCtx->nHomeCol + pCell->nColOffset), (u16)(pCtx->nHomeRow + pCell->nRowOffset));
            }
        }
        pCtx->pListNode = 0;
        func_ov025_0208f09c(pCtx);
        nCtx = func_ov025_02084a7c();
        func_ov025_020887c0(nCtx, func_ov025_0208843c(nCtx, WIDGET_DRAG), 0);
        if (pCtx->pCurrentCell != 0) {
            pCtx->pCurrentCell->displayState = CELL_STATE_IDLE;
            pCtx->pCurrentCell = 0;
        }
        pRecord = pCtx->apPageSlot[pCtx->nVisiblePage][pCtx->nRowSel * GRID_COLS + pCtx->nColumn];
        if (pRecord == 0) {
            func_ov025_02091070(pCtx, 0, 0, COLOUR_ACTIVE);
        } else {
            func_ov025_02091070(pCtx, 0, func_ov025_020b35d0(pCtx->textList, pRecord), COLOUR_ACTIVE);
        }
        func_ov025_0208884c(nCtx, func_ov025_0208843c(nCtx, WIDGET_ICON), 0);
        func_ov025_0208884c(nCtx, func_ov025_0208843c(nCtx, WIDGET_INFO), 0);
        func_ov025_0208884c(nCtx, func_ov025_0208843c(nCtx, WIDGET_HINT), 0);
    }
    pCtx->bTween = 0;
    pCtx->bScroll = 0;
    pCtx->bLifted = 0;
}
