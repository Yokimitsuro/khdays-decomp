/* func_ov025_02098ad4 -- Ov008_GridMenuBack: the grid menu's back button in ov025's copy of the
 * grid menu. Same as ov008's 020665a8 except that the grid flag toggle (states 1 and 2/mode 0)
 * is replaced by clearing the target slot (0, -1) with sound 3. By state (+0x10), ignored while a
 * key is held, the busy word (+0x30) or a transition word (+0x24 .. +0x2c) is set. State 0 (list)
 * without a lifted node (+0x19b4) clears the target slot with sound 3; with one the drag is reset,
 * the grid hits rebuilt, state 1 entered, cursor mode 0x14 requested (arg 1 when 020967d4 fills
 * the cell), the cursor moved, the row block disabled and the equip panel refreshed with sound
 * 0x37. State 1 (grid) with a node removes it from its home cell (+0x68, +0x6c / +0x6e), resets
 * the drag, refreshes the panel and moves the cursor with sound 0x37. State 2 (drag) in menu mode
 * 1 acts on the pending action (+0xa4): 0 clears the param overrides, begins the switch back to
 * the previous mode (+0xc), enters state 0 without a secondary panel (+0x4c), installs the grid
 * list hooks (data_ov025_020b4d4c: done 020988c0, select 020984ac, cancel 020985b8) with sound
 * 0x38; 2 / 5 enter grid menu mode 1 / 4 and the other sub modes up to 8 mode 0, with sound 3. */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

#define STATE_LIST   0
#define STATE_GRID   1
#define STATE_DRAG   2
#define SOUND_CANCEL 3
#define SOUND_REMOVE 0x37
#define SOUND_BACK   0x38
#define CURSOR_MODE_DRAG 0x14

typedef struct Ov000_Input {
    u16 x;
    u16 y;
    u16 keys;
    u16 pad;
} Ov000_Input;

typedef struct Ov008ListHooks {
    u8   pad_00[0x14];
    void (*pfnSelect)(void); /* 0x14 */
    void (*pfnCancel)(void); /* 0x18 */
    u8   pad_1c[8];
    void (*pfnDone)(void);   /* 0x24 */
} Ov008ListHooks;

typedef struct Ov008MenuContext {
    u8  pad_0000[8];
    int menuMode;             /* 0x0008 */
    int prevMenuMode;         /* 0x000c */
    int menuState;            /* 0x0010 */
    u8  pad_0014[0x24 - 0x14];
    int bDrag;                /* 0x0024 */
    int bTween;               /* 0x0028 */
    int bScroll;              /* 0x002c */
    int nBusyWord;            /* 0x0030 */
    u8  pad_0034[0x4c - 0x34];
    int bSecondaryPanel;      /* 0x004c */
    u8  pad_0050[0x64 - 0x50];
    u16 nCursorCol;           /* 0x0064 */
    u16 nCursorRow;           /* 0x0066 */
    u32 nDragPage;            /* 0x0068 */
    u16 nHomeCol;             /* 0x006c */
    u16 nHomeRow;             /* 0x006e */
    u8  pad_0070[0xa4 - 0x70];
    int nPendingAction;       /* 0x00a4 */
    u8  pad_00a8[0x19b4 - 0xa8];
    void *pListNode;          /* 0x19b4 */
    u8  pad_19b8[0x1f78 - 0x19b8];
    u8  summary[0x100];       /* 0x1f78: Ov008GridSummary */
} Ov008MenuContext;

extern Ov008ListHooks data_ov025_020b4d4c;
extern int   func_ov025_020899dc(Ov000_Input *pIn);                         /* sample the input */
extern void  func_ov025_02084798(int nEntry, int nTarget);                  /* Ov008_SetTargetSlot */
extern void  func_02033b78(int nKind, int nSound);                          /* PlaySound */
extern void  func_ov025_02093b08(Ov008MenuContext *pCtx, int bRestore);     /* Ov008_ResetGridDrag */
extern void  func_ov025_02093038(Ov008MenuContext *pCtx);                   /* Ov008_RebuildGridHits */
extern void  func_ov025_020956f8(Ov008MenuContext *pCtx, int nState);       /* Ov008_EnterMenuState */
extern int   func_ov025_020967d4(Ov008MenuContext *pCtx);                   /* fill the cursor cell */
extern int   func_ov025_020a41f0(int nMode, int nA, int nB);                /* cursor mode request */
extern int   func_ov025_02094988(Ov008MenuContext *pCtx, int nColumn, int nRow, int nStep); /* move the cursor */
extern void  func_ov025_020a4264(void);                                     /* Ov008_DisableRowBlock */
extern void  func_ov025_020a4408(void *pSummary);                           /* Ov008_RefreshEquipPanel */
extern int   func_ov025_0209446c(Ov008MenuContext *pCtx, u32 nPage, u32 nCol, u32 nRow, int bSilent); /* Ov008_RemoveGridNode */
extern int   func_ov025_02084a7c(void);                                     /* Ov008_GetContext */
extern void  func_ov025_0208896c(int nCtx, void *pEntry);                   /* Ov008_SwapParamOverrides */
extern void  func_ov025_02095070(Ov008MenuContext *pCtx, int nMode);        /* Ov008_BeginMenuModeSwitch */
extern void  func_ov025_02095cbc(Ov008MenuContext *pCtx, int nMode);        /* enter a grid menu mode */
extern void  func_ov025_020988c0(void);                                     /* Ov008_GridMenuConfirm */
extern void  func_ov025_020984ac(void);                                     /* list select hook */
extern void  func_ov025_020985b8(void);                                     /* list cancel hook */

void func_ov025_02098ad4(Ov008MenuContext *pCtx)
{
    Ov000_Input in;

    func_ov025_020899dc(&in);
    if (in.keys != 0 || pCtx->nBusyWord != 0) {
        return;
    }
    if (pCtx->bDrag != 0 || pCtx->bTween != 0 || pCtx->bScroll != 0) {
        return;
    }
    switch (pCtx->menuState) {
    case STATE_LIST:
        if (pCtx->pListNode == 0) {
            func_ov025_02084798(0, -1);
            func_02033b78(0, SOUND_CANCEL);
        } else {
            func_ov025_02093b08(pCtx, 0);
            func_ov025_02093038(pCtx);
            func_ov025_020956f8(pCtx, STATE_GRID);
            if (func_ov025_020967d4(pCtx) != 0) {
                func_ov025_020a41f0(CURSOR_MODE_DRAG, 0, 1);
            } else {
                func_ov025_020a41f0(CURSOR_MODE_DRAG, 0, 0);
            }
            func_ov025_02094988(pCtx, pCtx->nCursorCol, pCtx->nCursorRow, 0);
            func_ov025_020a4264();
            func_ov025_020a4408(pCtx->summary);
            func_02033b78(0, SOUND_REMOVE);
        }
        break;
    case STATE_GRID:
        if (pCtx->pListNode == 0) {
            func_ov025_02084798(0, -1);
            func_02033b78(0, SOUND_CANCEL);
        } else {
            func_ov025_0209446c(pCtx, pCtx->nDragPage, pCtx->nHomeCol, pCtx->nHomeRow, 0);
            func_ov025_02093b08(pCtx, 0);
            func_ov025_020a4264();
            func_ov025_020a4408(pCtx->summary);
            func_ov025_02094988(pCtx, pCtx->nCursorCol, pCtx->nCursorRow, 0);
            func_02033b78(0, SOUND_REMOVE);
        }
        break;
    case STATE_DRAG:
        switch (pCtx->menuMode) {
        case 0:
            func_ov025_02084798(0, -1);
            func_02033b78(0, SOUND_CANCEL);
            break;
        case 1:
            switch (pCtx->nPendingAction) {
            case 0:
                func_ov025_0208896c(func_ov025_02084a7c(), 0);
                func_ov025_02095070(pCtx, pCtx->prevMenuMode);
                if (pCtx->bSecondaryPanel == 0) {
                    func_ov025_020956f8(pCtx, STATE_LIST);
                }
                data_ov025_020b4d4c.pfnDone = func_ov025_020988c0;
                data_ov025_020b4d4c.pfnSelect = func_ov025_020984ac;
                data_ov025_020b4d4c.pfnCancel = func_ov025_020985b8;
                func_02033b78(0, SOUND_BACK);
                break;
            case 1:
            case 3:
            case 4:
            case 6:
            case 7:
            case 8:
                func_ov025_02095cbc(pCtx, 0);
                func_02033b78(0, SOUND_CANCEL);
                break;
            case 2:
                func_ov025_02095cbc(pCtx, 1);
                func_02033b78(0, SOUND_CANCEL);
                break;
            case 5:
                func_ov025_02095cbc(pCtx, 4);
                func_02033b78(0, SOUND_CANCEL);
                break;
            }
            break;
        }
        break;
    }
}
