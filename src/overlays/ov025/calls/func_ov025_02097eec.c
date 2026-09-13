/* func_ov025_02097eec -- Ov008_GridMenuInitStep: one step of the grid
 * menu's start-up (+0x0), returning 1 once done.  Step 0 initialises the
 * eight inventory lists (+0x304) and the lifted list (+0x19b8), enters menu
 * state 2, clears the current cell (+0x1848), parks both scroll sentinels
 * (+0x384 / +0x388), sets +0x1c to -1, sizes the grid from the owned copies
 * of item 1 (GameState 0x811 + 15, at most 0x78 cells, 40 per page ->
 * +0x1e74 / +0x1e78), sets the slide step (+0x38c) and the drag origin
 * (+0x60 / +0x62), installs the summary hooks (+0x2090), opens the resource
 * slot (+0x209c) and message dbs 0x15, 0x1b, 0x14, 0x16, 0x13 plus the slot's,
 * builds the record caches, the summary, the save page, the grid surfaces,
 * textures and page grid, clears the slide tween (+0x368) and allocates the
 * info window code node.  Steps 1 to 3 load the grid from the save, build
 * the inventory lists and draw the grid; step 4 hides the save page group,
 * invokes tags 1 / 2, shows page 0 in mode 0 with the page cursor (+0x70) at
 * 2 and redraws; step 5 requests cursor mode 0x14 (else transition 3),
 * refreshes, marks the active slot, enters state 2 or 0 by the secondary
 * panel (+0x4c) -- hiding widgets 0x37 / 0x38 without it -- and installs the
 * default handlers on the text loader (+0x1e68).  Codegen: the two scroll
 * sentinels are one chained assignment (the constant is formed before the
 * current-cell store).
 */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

#define LIST_COUNT   8
#define CELLS_PER_PAGE 40
#define CELL_MAX     0x78
#define CELL_EXTRA   0xf
#define SCROLL_SENTINEL 0x7fffffff
#define STATE_IDLE   2
#define CURSOR_MODE_DRAG 0x14

typedef struct Ov008HandlerPair {
    void *pFirst;
    void *pSecond;
} Ov008HandlerPair;

typedef struct Ov008MenuContext {
    int nInitStep;            /* 0x0000 */
    int bTransition;          /* 0x0004 */
    int menuMode;             /* 0x0008 */
    u8  pad_000c[4];
    int menuState;            /* 0x0010 */
    u8  pad_0014[4];
    int nVisiblePage;         /* 0x0018 */
    int bShown;               /* 0x001c */
    u8  pad_0020[0x4c - 0x20];
    int bSecondaryPanel;      /* 0x004c */
    u8  pad_0050[0x60 - 0x50];
    u16 nDragX;               /* 0x0060 */
    u16 nDragY;               /* 0x0062 */
    u8  pad_0064[0x70 - 0x64];
    int nPage;                /* 0x0070 */
    u8  pad_0074[0x304 - 0x74];
    u8  aInventoryList[LIST_COUNT][0xc]; /* 0x0304 */
    u8  pad_0364[4];
    u8  slideTween[0x1c];     /* 0x0368 */
    int nScrollTargetA;       /* 0x0384 */
    int nScrollTargetB;       /* 0x0388 */
    u16 nSlideStep;           /* 0x038c */
    u8  pad_038e[0x1848 - 0x38e];
    void *pCurrentCell;       /* 0x1848 */
    u8  pad_184c[0x19b8 - 0x184c];
    u8  liftedList[0xc];      /* 0x19b8 */
    u8  pad_19c4[0x1e68 - 0x19c4];
    u8  textLoader[0xc];      /* 0x1e68 */
    int nCellCount;           /* 0x1e74 */
    int nPageCount;           /* 0x1e78 */
    u8  pad_1e7c[0x1f78 - 0x1e7c];
    u8  summary[0x2090 - 0x1f78]; /* 0x1f78 */
    Ov008HandlerPair summaryHooks; /* 0x2090 */
    u8  pad_2098[4];
    int nResourceSlot;        /* 0x209c */
} Ov008MenuContext;

typedef struct GameState {
    u8 pad_0000[0x810];
    u8 aItemCount[0x8d0];     /* 0x810 */
} GameState;

extern GameState *data_0204be18;
extern int   func_ov025_02084a7c(void);                                  /* Ov008_GetContext */
extern void  NNS_FndInitList(void *pList, int nOffset);
extern void  func_ov025_0208eb14(int *pSlot, void *pArg);                /* open the resource slot */
extern int   func_ov025_02084ea4(int nDb);                               /* Ov008_AcquireMsgDb */
extern void  func_ov025_0208ed14(Ov008MenuContext *pCtx);                /* Ov008_InitMessageRecordCaches */
extern void  func_ov025_020871d4(void *pSummary, void *pHooks);          /* init a summary */
extern void  func_ov025_0208f898(void);                                  /* Ov008_InitializeSavePageGraphics */
extern void  func_ov025_0208fae0(Ov008MenuContext *pCtx);                /* Ov008_InitializeSavePageLayout */
extern void  func_ov025_02090140(Ov008MenuContext *pCtx);
extern void  func_ov025_02091c48(Ov008MenuContext *pCtx);                /* Ov008_InitGridMenuSurfaces */
extern void  func_ov025_02091edc(Ov008MenuContext *pCtx);                /* Ov008_InitGridMenuTextures */
extern void  func_ov025_02092114(Ov008MenuContext *pCtx);                /* Ov008_InitPageGrid */
extern void  func_02035f84(void *pTween);                                /* Tween_Clear */
extern void *func_ov025_02084b2c(void *pFn);                             /* Ov008_AllocCodeNode */
extern int   func_ov025_0208ec04(void);                                  /* Ov008_TickInfoWindowTransition */
extern void  func_ov025_020974e4(Ov008MenuContext *pCtx);                /* Ov008_LoadGridFromSave */
extern void  func_ov025_02090e44(Ov008MenuContext *pCtx);                /* Ov008_BuildInventoryLists */
extern void  func_ov025_020973e0(Ov008MenuContext *pCtx);                /* Ov008_DrawGridMenu */
extern void  func_ov025_02090000(Ov008MenuContext *pCtx, int nMode);     /* Ov008_SetSavePageGroupVisible */
extern int   func_ov025_02084a50(void);                                  /* Ov008_GetCtxBlock9500 */
extern void *func_ov025_020894b0(int nTracker, int nTag);                /* ov008_FindEntryByTag */
extern void  func_ov025_02089544(int nTracker, void *pCell);             /* Ov008_TagTracker_InvokeCallback */
extern void  func_ov025_0209522c(Ov008MenuContext *pCtx, int nPage, int bSound); /* Ov008_ShowGridPage */
extern int   func_ov025_02095544(Ov008MenuContext *pCtx, int nPage);     /* Ov008_Menu_ChangePage */
extern int   func_ov025_020a41f0(int nMode, int nA, int nB);             /* cursor mode request */
extern void  func_ov025_020a4970(void);                                  /* grid refresh */
extern void  func_ov025_02097ab0(Ov008MenuContext *pCtx);                /* Ov008_MarkAnyActiveSlot */
extern void  func_ov025_020956f8(Ov008MenuContext *pCtx, int nState);    /* Ov008_EnterMenuState */
extern void *func_ov025_0208843c(int nCtx, int nId);                     /* FindEntryById */
extern void  func_ov025_0208884c(int nCtx, void *pEntry, int bVisible);  /* SetEntrySlotsVisible */
extern void  func_ov025_020b3570(void *pLoader, Ov008HandlerPair *pHandlers); /* Ov008_InitWithDefaultHandlers */
extern void  func_ov025_0208ef44(void);                                  /* summary hook / default handler */
extern int   func_ov025_0208f020(int *pArg);                             /* summary hook / default handler */

int func_ov025_02097eec(Ov008MenuContext *pCtx)
{
    int bDone;
    int nCtx;
    int i;
    int nTracker;
    Ov008HandlerPair handlers;

    bDone = 0;
    nCtx = func_ov025_02084a7c();
    switch (pCtx->nInitStep) {
    case 0:
        for (i = 0; i < LIST_COUNT; i++) {
            NNS_FndInitList(pCtx->aInventoryList[i], 8);
        }
        NNS_FndInitList(pCtx->liftedList, 0xc);
        pCtx->menuState = STATE_IDLE;
        pCtx->pCurrentCell = 0;
        pCtx->nScrollTargetA = pCtx->nScrollTargetB = SCROLL_SENTINEL;
        pCtx->bShown = -1;
        pCtx->nCellCount = data_0204be18->aItemCount[1] + CELL_EXTRA;
        if (pCtx->nCellCount > CELL_MAX) {
            pCtx->nCellCount = CELL_MAX;
        }
        pCtx->nPageCount = (pCtx->nCellCount - 1) / CELLS_PER_PAGE + 1;
        pCtx->nSlideStep = 0x99;
        pCtx->nDragX = 0xffff;
        pCtx->nDragY = 0xffff;
        pCtx->summaryHooks.pFirst = func_ov025_0208ef44;
        pCtx->summaryHooks.pSecond = func_ov025_0208f020;
        func_ov025_0208eb14(&pCtx->nResourceSlot, 0);
        func_ov025_02084ea4(0x15);
        func_ov025_02084ea4(0x1b);
        func_ov025_02084ea4(0x14);
        func_ov025_02084ea4(0x16);
        func_ov025_02084ea4(0x13);
        func_ov025_02084ea4(pCtx->nResourceSlot);
        func_ov025_0208ed14(pCtx);
        func_ov025_020871d4(pCtx->summary, &pCtx->summaryHooks);
        func_ov025_0208f898();
        func_ov025_0208fae0(pCtx);
        func_ov025_02090140(pCtx);
        func_ov025_02091c48(pCtx);
        func_ov025_02091edc(pCtx);
        func_ov025_02092114(pCtx);
        func_02035f84(pCtx->slideTween);
        func_ov025_02084b2c(func_ov025_0208ec04);
        break;
    case 1:
        func_ov025_020974e4(pCtx);
        break;
    case 2:
        func_ov025_02090e44(pCtx);
        break;
    case 3:
        func_ov025_020973e0(pCtx);
        break;
    case 4:
        func_ov025_02090000(pCtx, 0);
        nTracker = func_ov025_02084a50();
        func_ov025_02089544(nTracker, func_ov025_020894b0(nTracker, 1));
        func_ov025_02089544(nTracker, func_ov025_020894b0(nTracker, 2));
        pCtx->menuMode = 0;
        pCtx->nVisiblePage = 2;
        func_ov025_0209522c(pCtx, 0, 0);
        pCtx->nPage = 2;
        func_ov025_02095544(pCtx, 0);
        func_ov025_020973e0(pCtx);
        break;
    case 5:
        if (func_ov025_020a41f0(CURSOR_MODE_DRAG, 0, 0) == 0) {
            pCtx->bTransition = 3;
        }
        func_ov025_020a4970();
        func_ov025_020973e0(pCtx);
        func_ov025_02097ab0(pCtx);
        func_ov025_020956f8(pCtx, pCtx->bSecondaryPanel != 0 ? 2 : 0);
        if (pCtx->bSecondaryPanel == 0) {
            for (i = 0x37; i <= 0x38; i++) {
                func_ov025_0208884c(nCtx, func_ov025_0208843c(nCtx, i), 0);
            }
        }
        handlers.pFirst = func_ov025_0208ef44;
        handlers.pSecond = func_ov025_0208f020;
        func_ov025_020b3570(pCtx->textLoader, &handlers);
        bDone = 1;
        break;
    }
    pCtx->nInitStep++;
    return bDone;
}
