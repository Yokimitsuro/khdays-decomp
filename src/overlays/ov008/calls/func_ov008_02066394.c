/* func_ov008_02066394 -- Ov008_GridMenuConfirm: the grid menu's confirm
 * button.  Nothing while the pen is down or a drag, tween or pick-up
 * (+0x24 / +0x28 / +0x2c) is running.  State 0 (list): unless busy (+0x8)
 * the dragged node is dropped (020617e0 1; refusal plays 4); on success the
 * +0x44 word is set, the cursor moved to the cursor cell with step 0 and the
 * +0x30 busy word set while the state is still below 2, and sound 0x36
 * plays.  State 1 (grid): with a lifted node it is dropped (02062848,
 * refusal 4), the grid hits rebuilt, the cursor moved to the cursor cell
 * (step 1) or cursor mode 0x14 / 2 requested while busy, the grid refreshed
 * and 0x36 played; otherwise the node under the cursor is picked up (sound 1,
 * cursor mode 0x14 / 2, grid refresh; refusal 4).  State 2 (drag): unless
 * busy the selected list item (+0x9c) is picked up into slot 0x16 (refusal
 * 4), state 0 entered and sound 1 played.
 */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

#define STATE_LIST   0
#define STATE_GRID   1
#define STATE_DRAG   2
#define PICK_SLOT    0x16
#define CURSOR_MODE_DRAG 0x14
#define SOUND_OK     1
#define SOUND_REFUSE 4
#define SOUND_DROP   0x36

typedef struct Ov008TouchRecord {
    u16 nX;                   /* 0x00 */
    u16 nY;                   /* 0x02 */
    u16 nTouching;            /* 0x04 */
} Ov008TouchRecord;

typedef struct Ov008InventoryItem {
    u8 pad[0x14];
} Ov008InventoryItem;

typedef struct Ov008MenuContext {
    u8  pad_0000[0x8];
    int nBusy;                /* 0x0008 */
    u8  pad_000c[4];
    int menuState;            /* 0x0010 */
    u8  pad_0014[0x24 - 0x14];
    int bDrag;                /* 0x0024 */
    int bTween;               /* 0x0028 */
    int bScroll;              /* 0x002c */
    int nBusyWord;            /* 0x0030 */
    u8  pad_0034[0x44 - 0x34];
    int nHoldCount;           /* 0x0044 */
    u8  pad_0048[0x64 - 0x48];
    u16 nColumn;              /* 0x0064 */
    u16 nRowSel;              /* 0x0066 */
    u8  pad_0068[0x9c - 0x68];
    int nSelectedRow;         /* 0x009c */
    u8  pad_00a0[0x300 - 0xa0];
    void *pList;              /* 0x0300 */
    u8  pad_0304[0x19b4 - 0x304];
    void *pListNode;          /* 0x19b4 */
} Ov008MenuContext;

extern void func_ov008_02055dcc(void *pOut);                              /* touch record */
extern int  func_ov008_020617e0(Ov008MenuContext *pCtx, int nArg);        /* drop the dragged node */
extern int  func_ov008_0206245c(Ov008MenuContext *pCtx, int nColumn, int nRow, int nStep); /* move the cursor */
extern void func_02033b78(int nKind, int nSound);                         /* PlaySound */
extern int  func_ov008_02061ce4(Ov008MenuContext *pCtx);                  /* Ov008_PickUpGridNode */
extern int  func_ov008_0206eb64(int nMode, int nA, int nB);               /* cursor mode request */
extern void func_ov008_0206f384(void);                                    /* grid refresh */
extern int  func_ov008_02062848(Ov008MenuContext *pCtx);                  /* drop the lifted node */
extern void func_ov008_02060ae8(Ov008MenuContext *pCtx);                  /* Ov008_RebuildGridHits */
extern Ov008InventoryItem *func_02010154(void *pList, int nIndex);        /* List_GetNthObject */
extern int  func_ov008_0205fc6c(Ov008MenuContext *pCtx, Ov008InventoryItem *pItem, u16 nSlot); /* Ov008_PickUpListItem */
extern void func_ov008_020631cc(Ov008MenuContext *pCtx, int nState);      /* Ov008_EnterMenuState */

void func_ov008_02066394(Ov008MenuContext *pCtx)
{
    Ov008TouchRecord touch;

    func_ov008_02055dcc(&touch);
    if (touch.nTouching != 0) {
        return;
    }
    if (pCtx->bDrag != 0 || pCtx->bTween != 0 || pCtx->bScroll != 0) {
        return;
    }
    switch (pCtx->menuState) {
    case STATE_LIST:
        if (pCtx->nBusy != 0) {
            return;
        }
        if (func_ov008_020617e0(pCtx, 1) != 0) {
            pCtx->nHoldCount = 1;
            if ((u32)pCtx->menuState <= STATE_GRID) {
                func_ov008_0206245c(pCtx, pCtx->nColumn, pCtx->nRowSel, 0);
                pCtx->nBusyWord = 1;
            }
            func_02033b78(0, SOUND_DROP);
        } else {
            func_02033b78(0, SOUND_REFUSE);
        }
        break;
    case STATE_GRID:
        if (pCtx->pListNode == 0) {
            if (func_ov008_02061ce4(pCtx) != 0) {
                func_02033b78(0, SOUND_OK);
                func_ov008_0206eb64(CURSOR_MODE_DRAG, 0, 2);
                func_ov008_0206f384();
            }
        } else if (func_ov008_02062848(pCtx) != 0) {
            func_ov008_02060ae8(pCtx);
            if (pCtx->nBusyWord != 0) {
                func_ov008_0206eb64(CURSOR_MODE_DRAG, 0, 2);
            } else {
                func_ov008_0206245c(pCtx, pCtx->nColumn, pCtx->nRowSel, 1);
            }
            func_ov008_0206f384();
            func_02033b78(0, SOUND_DROP);
        } else {
            func_02033b78(0, SOUND_REFUSE);
        }
        break;
    case STATE_DRAG:
        if (pCtx->nBusy != 0) {
            return;
        }
        if (func_ov008_0205fc6c(pCtx, func_02010154(pCtx->pList, (u16)pCtx->nSelectedRow), PICK_SLOT) != 0) {
            func_ov008_020631cc(pCtx, STATE_LIST);
            func_02033b78(0, SOUND_OK);
        } else {
            func_02033b78(0, SOUND_REFUSE);
        }
        break;
    }
}
