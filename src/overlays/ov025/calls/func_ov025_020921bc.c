/* func_ov025_020921bc -- Ov008_PickUpListItem: start dragging one copy of an
 * inventory list item onto the grid.  Refused (0) when every copy is already
 * placed (nPlaced >= nCount) or the item's entry is of kind 2.  Otherwise a
 * node still held by the drag cell is dropped back (020615dc with the pending
 * word +0x40), the context's widget 3 gets its sub-item set pushed, the drag
 * cell (+0x1820) is armed with the entry's texture parameters and the slot id
 * (+0x183e), and the list node (+0x19b4) points at the entry.  An entry with an
 * icon frame (+0x24 >= 0) shows widget 0xc9 with that frame.  Then the cursor
 * mode 0x14 is requested, the grid refreshed and the pending word cleared.
 * Returns 1.
 */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

#define ENTRY_KIND_FIXED 2
#define WIDGET_LIST      3
#define WIDGET_ICON      0xc9
#define CURSOR_MODE_DRAG 0x14

typedef struct Ov008ShapeEntry {
    u8  pad_00[0x18];
    int nKind;                /* 0x18 */
    u8  pad_1c[4];
    u16 nTag;                 /* 0x20: 1-based texture entry tag */
    u8  pad_22[2];
    int nIconFrame;           /* 0x24: -1 = none */
} Ov008ShapeEntry;

typedef struct Ov008InventoryItem {
    Ov008ShapeEntry *pEntry;  /* 0x00 */
    u8  nCount;               /* 0x04: copies owned */
    u8  nPlaced;              /* 0x05: copies on the grid */
} Ov008InventoryItem;

typedef struct Ov008DragTexture {
    int aTexture[6];          /* 0x00 */
    u8  pad_18[2];
    u16 nSlot;                /* 0x1a */
} Ov008DragTexture;

typedef struct Ov008TextureEntry {
    u8    pad_00[4];
    int  *pParams;            /* 0x04 */
} Ov008TextureEntry;

typedef struct Ov008MenuContext {
    u8  pad_0000[0x40];
    int nPending;             /* 0x0040 */
    u8  pad_0044[0x1820 - 0x44];
    int bDragActive;                 /* 0x1820 */
    Ov008DragTexture drag;           /* 0x1824 */
    u8  pad_1840[0x19b4 - 0x1840];
    Ov008ShapeEntry *pListNode;      /* 0x19b4 */
} Ov008MenuContext;

extern void func_ov025_02093b08(Ov008MenuContext *pCtx, int nArg);          /* drop the held node */
extern int  func_ov025_02084a7c(void);                                       /* Ov008_GetContext */
extern void *func_ov025_0208843c(int nCtx, int nId);                         /* FindEntryById */
extern void func_ov025_020887c0(int nCtx, void *pEntry, int nValue);         /* Ov008_PushSubitemSet */
extern Ov008TextureEntry *func_ov025_0208ffc4(Ov008MenuContext *pCtx, u32 nTag); /* Ov008_FindEntryBy1BasedTag */
extern void func_ov025_0208a5f8(int *pTexture, int *pParams);                /* Ov008_GetTextureParams */
extern void func_ov025_02088928(int nCtx, void *pEntry, int nFrame);         /* Ov008_ReleaseTwoSlotsEx */
extern void func_ov025_0208884c(int nCtx, void *pEntry, int bVisible);       /* SetEntrySlotsVisible */
extern int  func_ov025_020a41f0(int nMode, int nA, int nB);                  /* cursor mode request */
extern void func_ov025_020a4970(void);                                       /* grid refresh */

int func_ov025_020921bc(Ov008MenuContext *pCtx, Ov008InventoryItem *pItem, u16 nSlot)
{
    int nCtx;
    Ov008DragTexture *pDrag;

    if (pItem->nPlaced >= pItem->nCount) {
        return 0;
    }
    if (pItem->pEntry->nKind == ENTRY_KIND_FIXED) {
        return 0;
    }
    if (pCtx->pListNode != 0) {
        func_ov025_02093b08(pCtx, pCtx->nPending);
    }
    nCtx = func_ov025_02084a7c();
    func_ov025_020887c0(nCtx, func_ov025_0208843c(nCtx, WIDGET_LIST), 1);
    pCtx->bDragActive = 1;
    pCtx->pListNode = pItem->pEntry;
    pDrag = &pCtx->drag;
    func_ov025_0208a5f8(pDrag->aTexture, func_ov025_0208ffc4(pCtx, pItem->pEntry->nTag)->pParams);
    pDrag->nSlot = nSlot;
    if (pItem->pEntry->nIconFrame >= 0) {
        func_ov025_020887c0(nCtx, func_ov025_0208843c(nCtx, WIDGET_ICON), 0);
        func_ov025_02088928(nCtx, func_ov025_0208843c(nCtx, WIDGET_ICON), (u16)pItem->pEntry->nIconFrame);
        func_ov025_0208884c(nCtx, func_ov025_0208843c(nCtx, WIDGET_ICON), 1);
    }
    func_ov025_020a41f0(CURSOR_MODE_DRAG, 0, 2);
    func_ov025_020a4970();
    pCtx->nPending = 0;
    return 1;
}
