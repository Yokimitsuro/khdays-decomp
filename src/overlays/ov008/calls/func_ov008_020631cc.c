/* func_ov008_020631cc -- Ov008_EnterMenuState: put the grid menu into state
 * nState (+0x10, the previous state kept at +0x14 for state 1).  State 0
 * (list): widget 3 goes to (9.0, 32.0) fx32 and the cursor is moved to the
 * cursor cell (+0x64/+0x66) with step 1.  State 1 (grid): the same unless the
 * previous state was 0 or 1, in which case the grid is only reset; widget 3's
 * sub-item set 0 is pushed and the grid refreshed.  State 2 (drag), only with
 * a secondary panel (+0x4c): widget 3 goes to (104.0, 32.0); a lifted node
 * (+0x19b4 with +0x50) is removed from its home cell (+0x68, +0x6c/+0x6e);
 * the grid is reset and, in menu mode 0 (+0x8), the selected page (+0x9c) is
 * switched to -- on failure row 0 is highlighted and the selection cleared --
 * and cursor mode 0x14 with 0 requested; then the grid is refreshed.
 */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

#define STATE_LIST   0
#define STATE_GRID   1
#define STATE_DRAG   2
#define WIDGET_DRAG  3
#define CURSOR_MODE_DRAG 0x14
#define POS_LIST_X   0x9000
#define POS_DRAG_X   0x68000
#define POS_Y        0x20000

typedef struct UiLayoutPos {
    int nX;
    int nY;
} UiLayoutPos;

typedef struct Ov008MenuContext {
    u8  pad_0000[0x8];
    int menuMode;             /* 0x0008 */
    u8  pad_000c[4];
    int menuState;            /* 0x0010 */
    int prevMenuState;        /* 0x0014 */
    u8  pad_0018[0x4c - 0x18];
    int bSecondaryPanel;      /* 0x004c */
    int bLifted;              /* 0x0050 */
    u8  pad_0054[0x64 - 0x54];
    u16 nColumn;              /* 0x0064 */
    u16 nRowSel;              /* 0x0066 */
    u32 nDragNode;            /* 0x0068: home page of the lifted node */
    u16 nHomeCol;             /* 0x006c */
    u16 nHomeRow;             /* 0x006e */
    u8  pad_0070[0x9c - 0x70];
    int nSelectedRow;         /* 0x009c */
    u8  pad_00a0[0x19b4 - 0xa0];
    void *pListNode;          /* 0x19b4 */
} Ov008MenuContext;

extern int  func_ov008_02050c54(void);                                    /* Ov008_GetContext */
extern void *func_ov008_02054788(int nCtx, int nId);                      /* FindEntryById */
extern void func_ov008_020548a4(int nCtx, void *pEntry, UiLayoutPos *pPos); /* set the base position */
extern int  func_ov008_0206245c(Ov008MenuContext *pCtx, int nColumn, int nRow, int nStep); /* move the cursor */
extern void func_ov008_020615dc(Ov008MenuContext *pCtx, int nArg);        /* grid reset */
extern void func_ov008_02054b18(int nCtx, void *pEntry, int nValue);      /* Ov008_PushSubitemSet */
extern void func_ov008_0206f384(void);                                    /* grid refresh */
extern int  func_ov008_02061f40(Ov008MenuContext *pCtx, u32 nPage, u32 nCol, u32 nRow, int bSilent); /* Ov008_RemoveGridNode */
extern int  func_ov008_02062288(Ov008MenuContext *pCtx, int nPage);       /* switch page */
extern void func_ov008_0205f084(Ov008MenuContext *pCtx, int nRow);        /* highlight a visible row */
extern int  func_ov008_0206eb64(int nMode, int nA, int nB);               /* cursor mode request */

void func_ov008_020631cc(Ov008MenuContext *pCtx, int nState)
{
    UiLayoutPos pos = { 0, 0 };
    int nCtx;
    void *pEntry;
    int nPrev;

    nCtx = func_ov008_02050c54();
    pEntry = func_ov008_02054788(nCtx, WIDGET_DRAG);
    nPrev = pCtx->menuState;
    pCtx->menuState = nState;
    switch (nState) {
    case STATE_LIST:
        pos.nX = POS_LIST_X;
        pos.nY = POS_Y;
        func_ov008_020548a4(nCtx, pEntry, &pos);
        func_ov008_0206245c(pCtx, pCtx->nColumn, pCtx->nRowSel, 1);
        break;
    case STATE_GRID:
        if (nPrev != STATE_LIST && nPrev != STATE_GRID) {
            pos.nX = POS_LIST_X;
            pos.nY = POS_Y;
            func_ov008_020548a4(nCtx, pEntry, &pos);
            func_ov008_0206245c(pCtx, pCtx->nColumn, pCtx->nRowSel, 1);
        } else {
            func_ov008_020615dc(pCtx, 0);
        }
        func_ov008_02054b18(nCtx, pEntry, 0);
        pCtx->prevMenuState = nPrev;
        func_ov008_0206f384();
        break;
    case STATE_DRAG:
        if (pCtx->bSecondaryPanel == 0) {
            return;
        }
        pos.nX = POS_DRAG_X;
        pos.nY = POS_Y;
        func_ov008_020548a4(nCtx, pEntry, &pos);
        if (pCtx->pListNode != 0 && pCtx->bLifted != 0) {
            func_ov008_02061f40(pCtx, pCtx->nDragNode, pCtx->nHomeCol, pCtx->nHomeRow, 0);
        }
        func_ov008_020615dc(pCtx, 0);
        if (pCtx->menuMode == 0) {
            if (func_ov008_02062288(pCtx, pCtx->nSelectedRow) == 0) {
                func_ov008_0205f084(pCtx, 0);
                pCtx->nSelectedRow = 0;
            }
            func_ov008_0206eb64(CURSOR_MODE_DRAG, 0, 0);
        }
        func_ov008_0206f384();
        break;
    }
}
