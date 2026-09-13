/* func_ov025_02095cbc -- Ov008_BuildActionPage: build the page of the grid
 * menu's pending action nAction (+0xa4) on slot 9.  The slot is reset (02050c7c), rows 0xe .. 0x1e
 * of the 4-wide grid cleared and widgets 0x50 .. 0x5f disabled.  Action 0 (the
 * main menu) checks the three preset flags (0x3c67 ..) and whether any grid
 * page slot (+0x19c4, 3 x 40) is filled, then draws the five row surfaces
 * (+0x160, y = 4 + 3 * row, targets +0x298 stride 0x10): with the secondary panel (+0x4c) the
 * "presets" row 3 (text 6, colour 0xf3 when a preset exists, else 0xf5) and
 * the "grid" row 4 (text 4, likewise for a filled slot) get their captions,
 * otherwise rows 2 .. 4 take the texts of 0208f124 in colour 0xf5; caption
 * 7 is repainted on row 0 in colour 0xf3, widgets 0x50 .. 0x54 enabled, the
 * unavailable entries (0x53 / 0x54 with the secondary panel, 0x52 .. 0x54 otherwise)
 * pushed to subitem set 1, and widget 0x51 made the cursor row.  Action 1
 * resets the preset (+0x20) and builds the preset panel with all presets;
 * action 4 picks the first flagged preset and builds it restricted; actions
 * 2 / 5 / 7 build the grid (modes 2 / 4 / 0) and 3 / 6 / 8 the display (modes
 * 3 / 5 / 1) for the current preset.  Slot 9 is marked used.  Codegen: the
 * text triple is a struct copy from rodata; the widget loops end on their
 * inclusive bounds with the constant argument hoisted; action 0 zeroes the
 * action argument, the preset flag and the filled flag in that order and
 * reuses i for the page scan; the row loop walks a surface pointer with an
 * explicit y counter (spilled, initialised with i, stepped y / surface / i);
 * the caption colour is an if/else local (set case first); the row switch
 * has cases 3 and 4; case bodies are laid out 0, 1, 4, 2, 5, 7, 3, 6, 8.
 */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

#define PAGE_SLOT        9
#define ROW_COUNT        5
#define GRID_PAGES       3
#define GRID_CELLS       40
#define PRESET_COUNT     3
#define FLAG_PRESET_BASE 0x3c67
#define TEXT_FLAGS       0x412
#define COLOUR_ON        0xf3
#define COLOUR_OFF       0xf5
#define TEXT_PRESETS     6
#define TEXT_GRID        4
#define TEXT_TITLE       7

typedef struct TileSurface {
    u8 pad_00[0x3c];
} TileSurface;

typedef struct Ov008RowTargets {
    int hMain;                /* 0x00 */
    int hPreset;              /* 0x04 */
    u8  pad_08[8];
} Ov008RowTargets;

typedef struct Ov008TextTriple {
    int aText[3];
} Ov008TextTriple;

typedef struct Ov008MenuContext {
    u8  pad_0000[0x20];
    int nPreset;              /* 0x020 */
    u8  pad_0024[0x4c - 0x24];
    int bSecondaryPanel;      /* 0x04c */
    u8  pad_0050[0xa4 - 0x50];
    int nPendingAction;       /* 0x0a4 */
    int nActionArg;           /* 0x0a8 */
    u8  pad_00ac[0x160 - 0xac];
    TileSurface aRowSurface[ROW_COUNT]; /* 0x160 */
    u8  varRecords[0xc];      /* 0x28c */
    Ov008RowTargets aRowTarget[ROW_COUNT]; /* 0x298 */
    u8  pad_02e8[0x19c4 - 0x2e8];
    void *apPageSlot[GRID_PAGES][GRID_CELLS]; /* 0x19c4 */
} Ov008MenuContext;

extern const Ov008TextTriple data_ov025_020b3c84;
extern void *func_ov025_02084a7c(void);                                  /* Ov008_GetContext */
extern int   func_ov025_02084aa4(int nSlot);                             /* Ov008_ResetEntry: slot handle */
extern void  func_ov025_020849d8(int nSlot, int nX, int nY, int nW, int nH); /* Ov008_ClearGridRows */
extern void  func_ov025_0208ff84(void *pMenu, int nId, int bEnable);     /* Ov008_ResolveEntryAndConfigure */
extern int   func_02023588(int nFlag);                                   /* GameState_IsFlagSet */
extern void  func_0203034c(TileSurface *pSurface, int hLayer, int nX, int nY, int nPalette); /* Draw_ScaledValue */
extern void  func_02030094(TileSurface *pSurface, int nTarget, int nUpdate); /* TileSurface_SetCurrentItem */
extern void *func_ov025_02089894(void *pRecords, int nIndex);            /* GetVarRecordByIndex */
extern void  func_02030158(TileSurface *pSurface);                       /* Obj_InvokeInnerVtable4 */
extern void  func_020301c8(TileSurface *pSurface, int nX, int nY, int nColour, u32 nFlags, void *pRecord); /* Text_DrawDirectional */
extern void  func_020300f8(TileSurface *pSurface);                       /* EnqueueObjGfxCommand */
extern void  func_ov025_02091070(Ov008MenuContext *pCtx, int nRow, void *pText, int nColour); /* Ov008_RepaintTextRow */
extern void *func_ov025_0208843c(void *pMenu, int nId);                  /* FindEntryById */
extern void  func_ov025_020887c0(void *pMenu, void *pEntry, int nValue); /* Ov008_PushSubitemSet */
extern void  func_ov025_0208896c(void *pMenu, void *pEntry);             /* Ov008_SwapParamOverrides */
extern void  func_ov025_0208f144(void *pEntry);                          /* Ov008_SetTag3RowPos */
extern void  func_ov025_020958c0(Ov008MenuContext *pCtx, void *pMenu, int hLayer, int bAll); /* Ov008_SetupPresetPanel */
extern void  func_ov025_0208f37c(Ov008MenuContext *pCtx, int nPreset);   /* Ov008_DrawSavePage */
extern void  func_ov025_02095bc8(Ov008MenuContext *pCtx, void *pMenu, int hLayer, int nMode, int nPreset); /* Ov008_SetupMenuGrid */
extern void  func_ov025_02095af4(Ov008MenuContext *pCtx, void *pMenu, int hLayer, int nMode, int nPreset); /* Ov008_SetupMenuDisplay */
extern void  func_ov025_02084964(int nSlot);                             /* Ov008_MarkSlotUsed */

void func_ov025_02095cbc(Ov008MenuContext *pCtx, int nAction)
{
    Ov008TextTriple texts;
    int hLayer;
    int bPreset;
    int nY;
    void *pMenu;
    int i;
    int bFilled;
    int k;
    TileSurface *pSurface;
    void *pRecord;
    int nColour;

    texts = data_ov025_020b3c84;
    pCtx->nPendingAction = nAction;
    pMenu = func_ov025_02084a7c();
    hLayer = func_ov025_02084aa4(PAGE_SLOT);
    func_ov025_020849d8(PAGE_SLOT, 0xe, 4, 0x10, 0x13);
    for (i = 0x50; i <= 0x5f; i++) {
        func_ov025_0208ff84(pMenu, i, 0);
    }
    switch (nAction) {
    case 0:
        pCtx->nActionArg = 0;
        bPreset = 0;
        bFilled = 0;
        for (i = 0; i < PRESET_COUNT; i++) {
            if (func_02023588(FLAG_PRESET_BASE + i) != 0) {
                bPreset = 1;
            }
        }
        for (i = 0; i < GRID_PAGES; i++) {
            for (k = 0; k < GRID_CELLS; k++) {
                if (pCtx->apPageSlot[i][k] != 0) {
                    bFilled = 1;
                    break;
                }
            }
            if (bFilled) {
                break;
            }
        }
        pSurface = pCtx->aRowSurface;
        for (i = 0, nY = 4; i < ROW_COUNT; nY += 3, pSurface++, i++) {
            func_0203034c(pSurface, hLayer, nY, 0xf, 0);
            func_02030094(pSurface, pCtx->aRowTarget[i].hMain, 1);
            if (pCtx->bSecondaryPanel != 0) {
                switch (i) {
                case 3:
                    pRecord = func_ov025_02089894(pCtx->varRecords, TEXT_PRESETS);
                    if (bPreset != 0) {
                        nColour = COLOUR_ON;
                    } else {
                        nColour = COLOUR_OFF;
                    }
                    func_02030158(pSurface);
                    func_020301c8(pSurface, 0x39, 7, nColour - 1, TEXT_FLAGS, pRecord);
                    func_020301c8(pSurface, 0x38, 6, nColour, TEXT_FLAGS, pRecord);
                    func_020300f8(pSurface);
                    break;
                case 4:
                    pRecord = func_ov025_02089894(pCtx->varRecords, TEXT_GRID);
                    if (bFilled) {
                        nColour = COLOUR_ON;
                    } else {
                        nColour = COLOUR_OFF;
                    }
                    func_02030158(pSurface);
                    func_020301c8(pSurface, 0x39, 7, nColour - 1, TEXT_FLAGS, pRecord);
                    func_020301c8(pSurface, 0x38, 6, nColour, TEXT_FLAGS, pRecord);
                    func_020300f8(pSurface);
                    break;
                }
            } else if (i >= 2) {
                pRecord = func_ov025_02089894(pCtx->varRecords, texts.aText[i - 2]);
                func_02030158(pSurface);
                func_020301c8(pSurface, 0x39, 7, COLOUR_OFF - 1, TEXT_FLAGS, pRecord);
                func_020301c8(pSurface, 0x38, 6, COLOUR_OFF, TEXT_FLAGS, pRecord);
                func_020300f8(pSurface);
            }
        }
        func_ov025_02091070(pCtx, 0, func_ov025_02089894(pCtx->varRecords, TEXT_TITLE), COLOUR_ON);
        for (i = 0x50; i <= 0x54; i++) {
            func_ov025_0208ff84(pMenu, i, 1);
        }
        if (pCtx->bSecondaryPanel != 0) {
            if (bPreset == 0) {
                func_ov025_020887c0(pMenu, func_ov025_0208843c(pMenu, 0x53), 1);
            }
            if (!bFilled) {
                func_ov025_020887c0(pMenu, func_ov025_0208843c(pMenu, 0x54), 1);
            }
        } else {
            for (i = 0x52; i <= 0x54; i++) {
                func_ov025_020887c0(pMenu, func_ov025_0208843c(pMenu, i), 1);
            }
        }
        func_ov025_0208896c(pMenu, func_ov025_0208843c(pMenu, 0x51));
        func_ov025_0208f144(func_ov025_0208843c(pMenu, 0x51));
        break;
    case 1:
        pCtx->nPreset = 0;
        func_ov025_020958c0(pCtx, pMenu, hLayer, 1);
        func_ov025_0208f37c(pCtx, 0);
        break;
    case 4:
        pCtx->nPreset = 0;
        for (i = 0; i < PRESET_COUNT; i++) {
            if (func_02023588(FLAG_PRESET_BASE + i) != 0) {
                pCtx->nPreset = i;
                break;
            }
        }
        func_ov025_020958c0(pCtx, pMenu, hLayer, 0);
        func_ov025_0208f37c(pCtx, pCtx->nPreset);
        break;
    case 2:
        func_ov025_02095bc8(pCtx, pMenu, hLayer, 2, pCtx->nPreset);
        break;
    case 5:
        func_ov025_02095bc8(pCtx, pMenu, hLayer, 4, pCtx->nPreset);
        break;
    case 7:
        func_ov025_02095bc8(pCtx, pMenu, hLayer, 0, 0);
        break;
    case 3:
        func_ov025_02095af4(pCtx, pMenu, hLayer, 3, pCtx->nPreset);
        break;
    case 6:
        func_ov025_02095af4(pCtx, pMenu, hLayer, 5, pCtx->nPreset);
        break;
    case 8:
        func_ov025_02095af4(pCtx, pMenu, hLayer, 1, pCtx->nPreset);
        break;
    }
    func_ov025_02084964(PAGE_SLOT);
}
