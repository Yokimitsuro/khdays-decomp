/* func_ov008_02062d00 -- Ov008_ShowGridPage: make page nPage of the grid
 * menu visible.  With two or three pages (+0x1e78) the tab of the old page
 * (+0x18) and of the new one get their tracker callbacks invoked (tags from
 * 0208f13c for two pages, 0208f198 for three).  The current cell (+0x1848)
 * takes palette 0x10 on the drag page (+0x68), 0x1f elsewhere.  Every
 * display cell (+0x10a0, 8 x 5) is rebuilt from the page: grid id 0xff shows
 * texture tag 0xd1, an empty page slot (+0x19c4) deactivates the cell, a
 * record shows its tag (+0x20).  When the lifted node (+0x19b4) is placed
 * (+0x24), every lifted cell (+0x19b8) at the drag home (+0x6c / +0x6e) plus
 * its offset gets the drag / normal palette.  The page is recorded, the grid
 * hits rebuilt, the cursor re-placed in menu states below 2 and, with bSound
 * on a multi-page grid, sound 2 played.  Codegen: the cell index is a
 * statement at the top of the inner body; the palette is an int narrowed at
 * the store (hoisted); the page switch lists case 3 before case 2.
 */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;
typedef signed short   s16;

#define GRID_ROWS   8
#define GRID_COLS   5
#define GRID_ID_LOCKED 0xff
#define TAG_LOCKED  0xd1
#define PALETTE_DRAG 0x10
#define PALETTE_NORMAL 0x1f
#define SOUND_PAGE  2

typedef struct Ov008Message15Record {
    u8  pad_00[0x20];
    u16 nTag;                 /* 0x20: 1-based texture entry tag */
} Ov008Message15Record;

typedef struct Ov008TextureEntry {
    u8  pad_00[4];
    int *pTexture;            /* 0x04 */
} Ov008TextureEntry;

typedef struct Ov008LiftedCell {
    void *pRecord;            /* 0x00 */
    int nColOffset;           /* 0x04 */
    int nRowOffset;           /* 0x08 */
} Ov008LiftedCell;

typedef struct Ov008PlacedNode {
    u8  pad_00[0x24];
    int nPlacedSlot;          /* 0x24 */
} Ov008PlacedNode;

typedef struct Ov008GridDisplayCell {
    int isActive;             /* 0x00 */
    int aTexParams[2];        /* 0x04 */
    u8  pad_0c[0x1e - 0xc];
    s16 nPalette;             /* 0x1e */
    u8  pad_20[8];
} Ov008GridDisplayCell;

typedef struct Ov008PageTags2 {
    int aHide[2];             /* tag of each page's tab, hidden */
    int aShow[2];             /* tag of each page's tab, shown */
} Ov008PageTags2;

typedef struct Ov008PageTags3 {
    int aHide[3];
    int aShow[3];
} Ov008PageTags3;

typedef struct Ov008MenuContext {
    u8  pad_0000[0x10];
    u32 menuState;            /* 0x0010 */
    u8  pad_0014[4];
    int nVisiblePage;         /* 0x0018 */
    u8  pad_001c[0x64 - 0x1c];
    u16 nCursorCol;           /* 0x0064 */
    u16 nCursorRow;           /* 0x0066 */
    int nDragPage;            /* 0x0068 */
    u16 nHomeCol;             /* 0x006c */
    u16 nHomeRow;             /* 0x006e */
    u8  pad_0070[0x10a0 - 0x70];
    Ov008GridDisplayCell gridDisplayCells[GRID_ROWS][GRID_COLS]; /* 0x10a0 */
    u8  pad_16e0[0x1848 - 0x16e0];
    Ov008GridDisplayCell *pCurrentCell; /* 0x1848 */
    u8  pad_184c[0x19b4 - 0x184c];
    Ov008PlacedNode *pListNode; /* 0x19b4 */
    u8  liftedList[0xc];      /* 0x19b8 */
    Ov008Message15Record *apPageSlot[3][GRID_ROWS * GRID_COLS]; /* 0x19c4 */
    u8  pad_1ba4[0x1e78 - 0x1ba4];
    int nPageCount;           /* 0x1e78 */
    u8  pad_1e7c[0xc];
    u8  aGrid[3][GRID_ROWS][GRID_COLS]; /* 0x1e88 */
} Ov008MenuContext;

extern const Ov008PageTags3 data_ov008_0208f198;
extern const Ov008PageTags2 data_ov008_0208f13c;
extern int   func_ov008_02050c28(void);                                  /* Ov008_GetCtxBlock9500 */
extern void *func_ov008_02055808(int nTracker, u32 nTag);                /* ov008_FindEntryByTag */
extern void  func_ov008_0205589c(int nTracker, void *pCell);             /* Ov008_TagTracker_InvokeCallback */
extern Ov008TextureEntry *func_ov008_0205da50(Ov008MenuContext *pCtx, u32 nTag); /* Ov008_FindEntryBy1BasedTag */
extern void  func_ov008_02056988(int *pParams, int *pTexture);           /* Ov008_GetTextureParams */
extern Ov008LiftedCell *NNS_FndGetNextListObject(void *pList, void *pObject);
extern void  func_ov008_02060ae8(Ov008MenuContext *pCtx);                /* Ov008_RebuildGridHits */
extern int   func_ov008_0206245c(Ov008MenuContext *pCtx, int nColumn, int nRow, int nStep); /* move the cursor */
extern void  func_02033b78(int nKind, int nSound);                       /* PlaySound */

void func_ov008_02062d00(Ov008MenuContext *pCtx, int nPage, int bSound)
{
    Ov008PageTags3 tags3;
    Ov008PageTags2 tags2;
    int nTracker;
    int nRow;
    int nCol;
    int nCell;
    Ov008GridDisplayCell *pCell;
    int nPalette;
    Ov008LiftedCell *pLifted;

    tags3 = data_ov008_0208f198;
    tags2 = data_ov008_0208f13c;
    nTracker = func_ov008_02050c28();
    switch (pCtx->nPageCount) {
    case 1:
        break;
    case 3:
        func_ov008_0205589c(nTracker, func_ov008_02055808(nTracker, (u16)tags3.aHide[pCtx->nVisiblePage]));
        func_ov008_0205589c(nTracker, func_ov008_02055808(nTracker, (u16)tags3.aShow[nPage]));
        break;
    case 2:
        func_ov008_0205589c(nTracker, func_ov008_02055808(nTracker, (u16)tags2.aHide[pCtx->nVisiblePage]));
        func_ov008_0205589c(nTracker, func_ov008_02055808(nTracker, (u16)tags2.aShow[nPage]));
        break;
    }
    if (pCtx->pCurrentCell != 0) {
        pCtx->pCurrentCell->nPalette = pCtx->nDragPage == nPage ? PALETTE_DRAG : PALETTE_NORMAL;
    }
    for (nRow = 0; nRow < GRID_ROWS; nRow++) {
        for (nCol = 0; nCol < GRID_COLS; nCol++) {
            pCell = &pCtx->gridDisplayCells[nRow][nCol];
            nCell = nCol + nRow * GRID_COLS;
            if (pCtx->aGrid[nPage][nRow][nCol] == GRID_ID_LOCKED) {
                pCell->isActive = 1;
                func_ov008_02056988(pCell->aTexParams, func_ov008_0205da50(pCtx, TAG_LOCKED)->pTexture);
            } else if (pCtx->apPageSlot[nPage][nCell] == 0) {
                pCell->isActive = 0;
            } else {
                pCell->isActive = 1;
                func_ov008_02056988(pCell->aTexParams, func_ov008_0205da50(pCtx, pCtx->apPageSlot[nPage][nCell]->nTag)->pTexture);
            }
        }
    }
    if (pCtx->pListNode != 0 && pCtx->pListNode->nPlacedSlot >= 0) {
        nPalette = nPage == pCtx->nDragPage ? PALETTE_DRAG : PALETTE_NORMAL;
        for (pLifted = NNS_FndGetNextListObject(pCtx->liftedList, 0); pLifted != 0;
             pLifted = NNS_FndGetNextListObject(pCtx->liftedList, pLifted)) {
            pCtx->gridDisplayCells[pCtx->nHomeRow + pLifted->nRowOffset][pCtx->nHomeCol + pLifted->nColOffset].nPalette = nPalette;
        }
    }
    pCtx->nVisiblePage = nPage;
    func_ov008_02060ae8(pCtx);
    if (pCtx->menuState <= 1) {
        func_ov008_0206245c(pCtx, pCtx->nCursorCol, pCtx->nCursorRow, 1);
    }
    if (bSound != 0 && pCtx->nPageCount > 1) {
        func_02033b78(0, SOUND_PAGE);
    }
}
