/* Ov025_PickUpListItem -- Ov008_PickUpListItem: start dragging one copy of an
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

#include "nitro/types.h"

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

extern void Ov025_ResetGridDrag(Ov008MenuContext *pCtx, int nArg);          /* drop the held node */
extern int  Ov025_GetContext(void);                                       /* Ov008_GetContext */
extern void *Ov025_FindEntryById(int nCtx, int nId);                         /* FindEntryById */
extern void Ov025_PushSubitemSet(int nCtx, void *pEntry, int nValue);         /* Ov008_PushSubitemSet */
extern Ov008TextureEntry *Ov025_FindEntryBy1BasedTag(Ov008MenuContext *pCtx, u32 nTag); /* Ov008_FindEntryBy1BasedTag */
extern void Ov025_ResolveTextureParams(int *pTexture, int *pParams);                /* Ov008_GetTextureParams */
extern void Ov025_ReleaseTwoSlotsEx_2(int nCtx, void *pEntry, int nFrame);         /* Ov008_ReleaseTwoSlotsEx */
extern void Ov025_SetEntrySlotsVisible(int nCtx, void *pEntry, int bVisible);       /* SetEntrySlotsVisible */
extern int Ov025_DrawPageBElement(int param_1, int param_2, ...); /* cursor mode request */
extern void Ov025_PageB_UploadSurface154(void);                                       /* grid refresh */

int Ov025_PickUpListItem(Ov008MenuContext *pCtx, Ov008InventoryItem *pItem, u16 nSlot)
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
        Ov025_ResetGridDrag(pCtx, pCtx->nPending);
    }
    nCtx = Ov025_GetContext();
    Ov025_PushSubitemSet(nCtx, Ov025_FindEntryById(nCtx, WIDGET_LIST), 1);
    pCtx->bDragActive = 1;
    pCtx->pListNode = pItem->pEntry;
    pDrag = &pCtx->drag;
    Ov025_ResolveTextureParams(pDrag->aTexture, Ov025_FindEntryBy1BasedTag(pCtx, pItem->pEntry->nTag)->pParams);
    pDrag->nSlot = nSlot;
    if (pItem->pEntry->nIconFrame >= 0) {
        Ov025_PushSubitemSet(nCtx, Ov025_FindEntryById(nCtx, WIDGET_ICON), 0);
        Ov025_ReleaseTwoSlotsEx_2(nCtx, Ov025_FindEntryById(nCtx, WIDGET_ICON), (u16)pItem->pEntry->nIconFrame);
        Ov025_SetEntrySlotsVisible(nCtx, Ov025_FindEntryById(nCtx, WIDGET_ICON), 1);
    }
    Ov025_DrawPageBElement(CURSOR_MODE_DRAG, 0, 2);
    Ov025_PageB_UploadSurface154();
    pCtx->nPending = 0;
    return 1;
}
