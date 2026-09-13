/* func_ov008_020665a8 -- Ov008_GridMenuBack: the grid menu's back button,
 * by state (+0x10), ignored while a key is held (input sample), the busy
 * word (+0x30) or any of the three transition words (+0x24 .. +0x2c) is
 * set.  State 0 (list) without a lifted node (+0x19b4) clears the target
 * slot with sound 3; with one the drag is reset, the grid hits rebuilt,
 * state 1 entered, cursor mode 0x14 requested (arg 1 when 020642a8 fills
 * the cell), the cursor moved to the cursor cell, the row block disabled
 * and the equip panel refreshed with sound 0x37.  State 1 (grid) with a
 * node removes it from its home cell (+0x68, +0x6c / +0x6e), resets the
 * drag, refreshes the panel and moves the cursor with sound 0x37; without
 * one the grid flag 0x2010 is toggled (target slot 0 / -1 by the flag and
 * the +0x1fa4 word) with sound 3.  State 2 (drag) in menu mode 0 (+0x8)
 * toggles the flag likewise; mode 1 acts on the pending action (+0xa4): 0 clears
 * the param overrides, begins the switch back to the previous mode (+0xc),
 * enters state 0 without a secondary panel (+0x4c), installs the grid
 * list hooks (02090380: done 02066394, select 02065f80, cancel 0206608c)
 * with sound 0x38; 2 / 5 enter grid menu mode 1 / 4 and the other sub
 * modes up to 8 mode 0, each with sound 3.  Codegen: the flag toggle is a
 * static inline helper (three copies; the "+0x1fa4 set" branch first).
 */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

#define STATE_LIST   0
#define STATE_GRID   1
#define STATE_DRAG   2
#define FLAG_GRID    0x2010
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
    u8  summary[0x1fa4 - 0x1f78]; /* 0x1f78: Ov008GridSummary (0x100) */
    int bOptionReverse;       /* 0x1fa4 */
} Ov008MenuContext;

extern Ov008ListHooks data_ov008_02090380;
extern int   func_ov008_02055dcc(Ov000_Input *pIn);                         /* sample the input */
extern void  func_ov008_02050970(int nEntry, int nTarget);                  /* Ov008_SetTargetSlot */
extern void  func_02033b78(int nKind, int nSound);                          /* PlaySound */
extern void  func_ov008_020615dc(Ov008MenuContext *pCtx, int bRestore);     /* Ov008_ResetGridDrag */
extern void  func_ov008_02060ae8(Ov008MenuContext *pCtx);                   /* Ov008_RebuildGridHits */
extern void  func_ov008_020631cc(Ov008MenuContext *pCtx, int nState);       /* Ov008_EnterMenuState */
extern int   func_ov008_020642a8(Ov008MenuContext *pCtx);                   /* fill the cursor cell */
extern int   func_ov008_0206eb64(int nMode, int nA, int nB);                /* cursor mode request */
extern int   func_ov008_0206245c(Ov008MenuContext *pCtx, int nColumn, int nRow, int nStep); /* move the cursor */
extern void  func_ov008_0206ebd8(void);                                     /* Ov008_DisableRowBlock */
extern void  func_ov008_0206ed7c(void *pSummary);                           /* Ov008_RefreshEquipPanel */
extern int   func_02023588(int nFlag);                                      /* GameState_IsFlagSet */
extern void  func_020235a8(int nFlag);                                      /* GameState_SetFlag */
extern void  func_020235bc(int nFlag);                                      /* GameState_ClearFlag */
extern int   func_ov008_02061f40(Ov008MenuContext *pCtx, u32 nPage, u32 nCol, u32 nRow, int bSilent); /* Ov008_RemoveGridNode */
extern int   func_ov008_02050c54(void);                                     /* Ov008_GetContext */
extern void  func_ov008_02054cc4(int nCtx, void *pEntry);                   /* Ov008_SwapParamOverrides */
extern void  func_ov008_02062b44(Ov008MenuContext *pCtx, int nMode);        /* Ov008_BeginMenuModeSwitch */
extern void  func_ov008_02063790(Ov008MenuContext *pCtx, int nMode);        /* enter a grid menu mode */
extern void  func_ov008_02066394(void);                                     /* Ov008_GridMenuConfirm */
extern void  func_ov008_02065f80(void);                                     /* list select hook */
extern void  func_ov008_0206608c(void);                                     /* list cancel hook */

static inline void Ov008_ToggleGridFlag(Ov008MenuContext *pCtx)
{
    if (pCtx->bOptionReverse != 0) {
        if (func_02023588(FLAG_GRID) == 0) {
            func_ov008_02050970(-1, -1);
        } else {
            func_ov008_02050970(0, -1);
        }
        func_020235a8(FLAG_GRID);
    } else {
        if (func_02023588(FLAG_GRID) != 0) {
            func_ov008_02050970(-1, -1);
        } else {
            func_ov008_02050970(0, -1);
        }
        func_020235bc(FLAG_GRID);
    }
}

void func_ov008_020665a8(Ov008MenuContext *pCtx)
{
    Ov000_Input in;

    func_ov008_02055dcc(&in);
    if (in.keys != 0 || pCtx->nBusyWord != 0) {
        return;
    }
    if (pCtx->bDrag != 0 || pCtx->bTween != 0 || pCtx->bScroll != 0) {
        return;
    }
    switch (pCtx->menuState) {
    case STATE_LIST:
        if (pCtx->pListNode == 0) {
            func_ov008_02050970(0, -1);
            func_02033b78(0, SOUND_CANCEL);
        } else {
            func_ov008_020615dc(pCtx, 0);
            func_ov008_02060ae8(pCtx);
            func_ov008_020631cc(pCtx, STATE_GRID);
            if (func_ov008_020642a8(pCtx) != 0) {
                func_ov008_0206eb64(CURSOR_MODE_DRAG, 0, 1);
            } else {
                func_ov008_0206eb64(CURSOR_MODE_DRAG, 0, 0);
            }
            func_ov008_0206245c(pCtx, pCtx->nCursorCol, pCtx->nCursorRow, 0);
            func_ov008_0206ebd8();
            func_ov008_0206ed7c(pCtx->summary);
            func_02033b78(0, SOUND_REMOVE);
        }
        break;
    case STATE_GRID:
        if (pCtx->pListNode == 0) {
            Ov008_ToggleGridFlag(pCtx);
            func_02033b78(0, SOUND_CANCEL);
        } else {
            func_ov008_02061f40(pCtx, pCtx->nDragPage, pCtx->nHomeCol, pCtx->nHomeRow, 0);
            func_ov008_020615dc(pCtx, 0);
            func_ov008_0206ebd8();
            func_ov008_0206ed7c(pCtx->summary);
            func_ov008_0206245c(pCtx, pCtx->nCursorCol, pCtx->nCursorRow, 0);
            func_02033b78(0, SOUND_REMOVE);
        }
        break;
    case STATE_DRAG:
        switch (pCtx->menuMode) {
        case 0:
            Ov008_ToggleGridFlag(pCtx);
            func_02033b78(0, SOUND_CANCEL);
            break;
        case 1:
            switch (pCtx->nPendingAction) {
            case 0:
                func_ov008_02054cc4(func_ov008_02050c54(), 0);
                func_ov008_02062b44(pCtx, pCtx->prevMenuMode);
                if (pCtx->bSecondaryPanel == 0) {
                    func_ov008_020631cc(pCtx, STATE_LIST);
                }
                data_ov008_02090380.pfnDone = func_ov008_02066394;
                data_ov008_02090380.pfnSelect = func_ov008_02065f80;
                data_ov008_02090380.pfnCancel = func_ov008_0206608c;
                func_02033b78(0, SOUND_BACK);
                break;
            case 1:
            case 3:
            case 4:
            case 6:
            case 7:
            case 8:
                func_ov008_02063790(pCtx, 0);
                func_02033b78(0, SOUND_CANCEL);
                break;
            case 2:
                func_ov008_02063790(pCtx, 1);
                func_02033b78(0, SOUND_CANCEL);
                break;
            case 5:
                func_ov008_02063790(pCtx, 4);
                func_02033b78(0, SOUND_CANCEL);
                break;
            }
            break;
        }
        break;
    }
}
