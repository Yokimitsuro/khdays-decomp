/* func_ov008_02066c30 -- Ov008_TouchPickUpListItem: stylus pick-up of an
 * inventory list row.  Nothing while the menu is busy (+0x30), the pen is up,
 * or a drag / pick-up (+0x24 / +0x2c) is running.  The pen's y (minus the
 * 0x18 header, 16 px per row, at most row 7) plus the scroll row (+0x74)
 * selects the item in the current list (+0x300); a missing item ends here.
 * A successful pick-up (Ov008_PickUpListItem, slot 0x16) starts the tween
 * (+0x28), flags the item's id, refreshes menu button 5, repaints the node's
 * text row (row 0, colour 0xf3), requests cursor mode 0x14 with 5, refreshes
 * the grid, shows widget 0x4a with the record's placed slot (+0x24, hidden
 * when none), disables the row block, refreshes the equip panel from the
 * summary (+0x1f78), rebuilds the grid hits and plays sound 1; a refused
 * pick-up plays sound 4.  Either way the row is highlighted (0205f084) and
 * becomes the selected row (+0x9c).
 */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

#define LIST_TOP      0x18
#define ROW_HEIGHT    16
#define LAST_ROW      7
#define PICK_SLOT     0x16
#define WIDGET_ICON   0x4a
#define CURSOR_MODE_DRAG 0x14
#define COLOUR_ACTIVE 0xf3
#define SOUND_PICK    1
#define SOUND_REFUSE  4

typedef struct Ov008Message15Record {
    u8  pad_00[0x14];
    int nItemId;              /* 0x14 */
    u8  pad_18[0xc];
    int nPlacedSlot;          /* 0x24: -1 = not placed */
} Ov008Message15Record;

typedef struct Ov008InventoryItem {
    Ov008Message15Record *pRecord;  /* 0x00 */
} Ov008InventoryItem;

typedef struct Ov008TouchRecord {
    u16 nX;                   /* 0x00 */
    u16 nY;                   /* 0x02 */
    u16 nTouching;            /* 0x04 */
} Ov008TouchRecord;

typedef struct Ov008GridSummary {
    u8 pad[0x100];
} Ov008GridSummary;

typedef struct Ov008MenuContext {
    u8  pad_0000[0x24];
    int bDrag;                /* 0x0024 */
    int bTween;               /* 0x0028 */
    int bScroll;              /* 0x002c: pick-up result */
    int nBusy;                /* 0x0030 */
    u8  pad_0034[0x74 - 0x34];
    int nScrollRow;           /* 0x0074 */
    u8  pad_0078[0x9c - 0x78];
    int nSelectedRow;         /* 0x009c */
    u8  pad_00a0[0x300 - 0xa0];
    void *pList;              /* 0x0300: current inventory list */
    u8  pad_0304[0x19b4 - 0x304];
    void *pListNode;          /* 0x19b4 */
    u8  pad_19b8[0x1e68 - 0x19b8];
    int textList[4];          /* 0x1e68 */
    u8  pad_1e78[0x1f78 - 0x1e78];
    Ov008GridSummary summary; /* 0x1f78 */
} Ov008MenuContext;

extern Ov008MenuContext *func_ov008_02050cd4(void);                       /* Ov008_GetMenuContext */
extern int  func_ov008_02050c54(void);                                    /* Ov008_GetContext */
extern void func_ov008_02055dcc(void *pOut);                              /* touch record */
extern Ov008InventoryItem *func_02010154(void *pList, int nIndex);        /* List_GetNthObject */
extern int  func_ov008_0205fc6c(Ov008MenuContext *pCtx, Ov008InventoryItem *pItem, u16 nSlot); /* Ov008_PickUpListItem */
extern void func_ov008_0205e7ec(Ov008MenuContext *pCtx, int nItemId);     /* Ov008_SetBitInBitset */
extern void func_ov008_0206f7b0(int nArg);                                /* Ov008_UpdateMenuButton5 */
extern int  func_ov008_0208e66c(int *pList, void *pNode);                 /* text index of a node */
extern void func_ov008_0205eafc(Ov008MenuContext *pCtx, int nRow, int nText, int nColour); /* Ov008_RepaintTextRow */
extern int  func_ov008_0206eb64(int nMode, int nA, int nB);               /* cursor mode request */
extern void func_ov008_0206f384(void);                                    /* grid refresh */
extern void *func_ov008_02054788(int nCtx, int nId);                      /* FindEntryById */
extern void func_ov008_02054ba4(int nCtx, void *pEntry, int bVisible);    /* SetEntrySlotsVisible */
extern void func_ov008_02054c80(int nCtx, void *pEntry, int nFrame);      /* Ov008_ReleaseTwoSlotsEx */
extern void func_ov008_0206ebd8(void);                                    /* Ov008_DisableRowBlock */
extern void func_ov008_0206ed7c(Ov008GridSummary *pSummary);              /* Ov008_RefreshEquipPanel */
extern void func_ov008_02060ae8(Ov008MenuContext *pCtx);                  /* Ov008_RebuildGridHits */
extern void func_02033b78(int nKind, int nSound);                         /* PlaySound */
extern void func_ov008_0205f084(Ov008MenuContext *pCtx, int nRow);        /* highlight a visible row */

void func_ov008_02066c30(void)
{
    Ov008MenuContext *pCtx;
    int nCtx;
    Ov008TouchRecord touch;
    int nRow;
    u32 nIndex;
    Ov008InventoryItem *pItem;
    void *pIcon;

    pCtx = func_ov008_02050cd4();
    nCtx = func_ov008_02050c54();
    if (pCtx->nBusy != 0) {
        return;
    }
    func_ov008_02055dcc(&touch);
    if (touch.nTouching == 0) {
        return;
    }
    if (pCtx->bDrag != 0 || pCtx->bScroll != 0) {
        return;
    }
    nRow = (touch.nY - LIST_TOP) / ROW_HEIGHT;
    if (nRow > LAST_ROW) {
        nRow = LAST_ROW;
    }
    nIndex = pCtx->nScrollRow + nRow;
    pItem = func_02010154(pCtx->pList, (u16)nIndex);
    if (pItem == 0) {
        return;
    }
    if (func_ov008_0205fc6c(pCtx, pItem, PICK_SLOT) != 0) {
        pCtx->bTween = 1;
        func_ov008_0205e7ec(pCtx, pItem->pRecord->nItemId);
        func_ov008_0206f7b0(0);
        func_ov008_0205eafc(pCtx, 0, func_ov008_0208e66c(pCtx->textList, pCtx->pListNode), COLOUR_ACTIVE);
        func_ov008_0206eb64(CURSOR_MODE_DRAG, 0, 5);
        func_ov008_0206f384();
        pIcon = func_ov008_02054788(nCtx, WIDGET_ICON);
        if (pItem->pRecord->nPlacedSlot >= 0) {
            func_ov008_02054ba4(nCtx, pIcon, 1);
            func_ov008_02054c80(nCtx, pIcon, (u16)pItem->pRecord->nPlacedSlot);
        } else {
            func_ov008_02054ba4(nCtx, pIcon, 0);
        }
        func_ov008_0206ebd8();
        func_ov008_0206ed7c(&pCtx->summary);
        func_ov008_02060ae8(pCtx);
        func_02033b78(0, SOUND_PICK);
    } else {
        func_02033b78(0, SOUND_REFUSE);
    }
    func_ov008_0205f084(pCtx, nRow);
    pCtx->nSelectedRow = nIndex;
}
