/* func_ov008_02062288 -- Ov008_SelectListRow: make list row nRow the selected
 * row (+0x9c) of the inventory list.  The row is first brought into the
 * eight-row window (Ov008_ScrollMenuRowsTo over the scroll row +0x74 with
 * the page count +0x78, track 0x7f); a row outside the list answers 0.  The
 * row's item id is flagged in the bitset.  When the window did not move the
 * eight visible rows' widgets are refreshed: row widget 400 + i shows the
 * item with its bitset state as frame (hidden while game flag 0x37c9 + id is
 * set) and widget 500 + i follows the item's placed-copies byte (+5);
 * otherwise the rows are rebuilt from the new first row (0205e2e0).  Finally
 * the row is highlighted relative to the scroll row.  Returns 1.
 */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

#define VISIBLE_ROWS  8
#define TRACK_END     0x7f
#define ROW_WIDGET_A  400
#define ROW_WIDGET_B  500
#define FLAG_ITEM_HIDDEN 0x37c9

typedef struct Ov008Message15Record {
    u8  pad_00[0x14];
    int nItemId;              /* 0x14 */
} Ov008Message15Record;

typedef struct Ov008InventoryItem {
    Ov008Message15Record *pRecord;  /* 0x00 */
    u8  nCount;               /* 0x04: copies owned */
    u8  nPlaced;              /* 0x05: copies on the grid */
} Ov008InventoryItem;

typedef struct Ov008MenuContext {
    u8  pad_0000[0x70];
    int nRowBase;             /* 0x0070 */
    int nScrollRow;           /* 0x0074 */
    int nPageCount;           /* 0x0078 */
    u8  pad_007c[0x9c - 0x7c];
    int nSelectedRow;         /* 0x009c */
    u8  pad_00a0[0x300 - 0xa0];
    void *pList;              /* 0x0300: current inventory list */
} Ov008MenuContext;

extern int  func_ov008_02050c54(void);                                    /* Ov008_GetContext */
extern int  func_ov008_0206215c(Ov008MenuContext *pCtx, int nRow, int nFirst, int nTotal, int nTrackEnd, int nVisible); /* Ov008_ScrollMenuRowsTo */
extern Ov008InventoryItem *func_02010154(void *pList, int nIndex);        /* List_GetNthObject */
extern void func_ov008_0205e7ec(Ov008MenuContext *pCtx, int nItemId);     /* Ov008_SetBitInBitset */
extern void func_ov008_0205e2e0(Ov008MenuContext *pCtx, int nRowBase, int nFirst); /* rebuild the visible rows */
extern int  func_02023588(int nFlag);                                     /* GameState_IsFlagSet */
extern void *func_ov008_02054788(int nCtx, int nId);                      /* FindEntryById */
extern void func_ov008_02054ba4(int nCtx, void *pEntry, int bVisible);    /* SetEntrySlotsVisible */
extern int  func_ov008_0205db98(Ov008MenuContext *pCtx, int nItemId);     /* TestBitInBitset */
extern void func_ov008_02054c80(int nCtx, void *pEntry, int nFrame);      /* Ov008_ReleaseTwoSlotsEx */
extern Ov008InventoryItem *NNS_FndGetNextListObject(void *pList, void *pObject);
extern void func_ov008_0205f084(Ov008MenuContext *pCtx, int nRow);        /* highlight a visible row */

int func_ov008_02062288(Ov008MenuContext *pCtx, int nRow)
{
    int i;
    int nCtx;
    int nFirst;
    Ov008InventoryItem *pItem;

    i = 0;
    nCtx = func_ov008_02050c54();
    nFirst = func_ov008_0206215c(pCtx, nRow, pCtx->nScrollRow, pCtx->nPageCount, TRACK_END, VISIBLE_ROWS);
    if (nFirst < 0) {
        return 0;
    }
    pCtx->nSelectedRow = nRow;
    pItem = func_02010154(pCtx->pList, (u16)nRow);
    if (pItem != 0) {
        func_ov008_0205e7ec(pCtx, pItem->pRecord->nItemId);
    }
    if (pCtx->nScrollRow != nFirst) {
        func_ov008_0205e2e0(pCtx, pCtx->nRowBase, nFirst);
    } else {
        pItem = func_02010154(pCtx->pList, (u16)nFirst);
        while (pItem != 0) {
            if (func_02023588(pItem->pRecord->nItemId + FLAG_ITEM_HIDDEN) != 0) {
                func_ov008_02054ba4(nCtx, func_ov008_02054788(nCtx, i + ROW_WIDGET_A), 0);
            } else {
                func_ov008_02054c80(nCtx, func_ov008_02054788(nCtx, i + ROW_WIDGET_A), (u16)(func_ov008_0205db98(pCtx, pItem->pRecord->nItemId) != 0));
                func_ov008_02054ba4(nCtx, func_ov008_02054788(nCtx, i + ROW_WIDGET_A), 1);
            }
            if (pItem->nPlaced != 0) {
                func_ov008_02054ba4(nCtx, func_ov008_02054788(nCtx, i + ROW_WIDGET_B), 1);
            } else {
                func_ov008_02054ba4(nCtx, func_ov008_02054788(nCtx, i + ROW_WIDGET_B), 0);
            }
            i++;
            if (i >= VISIBLE_ROWS) {
                break;
            }
            pItem = NNS_FndGetNextListObject(pCtx->pList, pItem);
        }
    }
    func_ov008_0205f084(pCtx, nRow - pCtx->nScrollRow);
    return 1;
}
