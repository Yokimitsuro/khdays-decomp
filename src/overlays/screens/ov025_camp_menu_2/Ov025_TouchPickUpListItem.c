/* Ov025_TouchPickUpListItem -- Ov008_TouchPickUpListItem: stylus pick-up of an
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

#include "nitro/types.h"
#include "game/engine.h"

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
    u16 nValidity;            /* 0x06 */
} Ov008TouchRecord;   /* the NitroSDK's TPData: 8 bytes */

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

extern Ov008MenuContext *Ov025_GetPageA(void);                       /* Ov008_GetMenuContext */
extern int  Ov025_GetContext(void);                                    /* Ov008_GetContext */
extern void Ov025_CopySourceBlock(void *pOut);                              /* touch record */
extern Ov008InventoryItem *NNS_FndGetNthListObject(void *pList, int nIndex);        /* List_GetNthObject */
extern int  Ov025_PickUpListItem(Ov008MenuContext *pCtx, Ov008InventoryItem *pItem, u16 nSlot); /* Ov008_PickUpListItem */
extern void Ov025_SetBitInBitset(Ov008MenuContext *pCtx, int nItemId);     /* Ov008_SetBitInBitset */
extern void Ov025_UpdateMenuButton5(int nArg);                                /* Ov008_UpdateMenuButton5 */
extern int  Ov025_GetItemDescriptionForMember(int *pList, void *pNode);                 /* text index of a node */
extern void Ov025_RepaintTextRow(Ov008MenuContext *pCtx, int nRow, int nText, int nColour); /* Ov008_RepaintTextRow */
extern int Ov025_DrawPageBElement(int param_1, int param_2, ...); /* cursor mode request */
extern void Ov025_PageB_UploadSurface154(void);                                    /* grid refresh */
extern void *Ov025_FindEntryById(int nCtx, int nId);                      /* FindEntryById */
extern void Ov025_SetEntrySlotsVisible(int nCtx, void *pEntry, int bVisible);    /* SetEntrySlotsVisible */
extern void Ov025_ReleaseTwoSlotsEx_2(int nCtx, void *pEntry, int nFrame);      /* Ov008_ReleaseTwoSlotsEx */
extern void Ov025_ClearTagRange(void);                                    /* Ov008_DisableRowBlock */
extern void Ov025_RefreshStatusPage(Ov008GridSummary *pSummary);              /* Ov008_RefreshEquipPanel */
extern void Ov025_RebuildGridHits(Ov008MenuContext *pCtx);                  /* Ov008_RebuildGridHits */
extern void Ov025_HighlightListRow(Ov008MenuContext *pCtx, int nRow);        /* highlight a visible row */

void Ov025_TouchPickUpListItem(void)
{
    Ov008MenuContext *pCtx;
    int nCtx;
    Ov008TouchRecord touch;
    int nRow;
    u32 nIndex;
    Ov008InventoryItem *pItem;
    void *pIcon;

    pCtx = Ov025_GetPageA();
    nCtx = Ov025_GetContext();
    if (pCtx->nBusy != 0) {
        return;
    }
    Ov025_CopySourceBlock(&touch);
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
    pItem = NNS_FndGetNthListObject(pCtx->pList, (u16)nIndex);
    if (pItem == 0) {
        return;
    }
    if (Ov025_PickUpListItem(pCtx, pItem, PICK_SLOT) != 0) {
        pCtx->bTween = 1;
        Ov025_SetBitInBitset(pCtx, pItem->pRecord->nItemId);
        Ov025_UpdateMenuButton5(0);
        Ov025_RepaintTextRow(pCtx, 0, Ov025_GetItemDescriptionForMember(pCtx->textList, pCtx->pListNode), COLOUR_ACTIVE);
        Ov025_DrawPageBElement(CURSOR_MODE_DRAG, 0, 5);
        Ov025_PageB_UploadSurface154();
        pIcon = Ov025_FindEntryById(nCtx, WIDGET_ICON);
        if (pItem->pRecord->nPlacedSlot >= 0) {
            Ov025_SetEntrySlotsVisible(nCtx, pIcon, 1);
            Ov025_ReleaseTwoSlotsEx_2(nCtx, pIcon, (u16)pItem->pRecord->nPlacedSlot);
        } else {
            Ov025_SetEntrySlotsVisible(nCtx, pIcon, 0);
        }
        Ov025_ClearTagRange();
        Ov025_RefreshStatusPage(&pCtx->summary);
        Ov025_RebuildGridHits(pCtx);
        PlaySound(0, SOUND_PICK);
    } else {
        PlaySound(0, SOUND_REFUSE);
    }
    Ov025_HighlightListRow(pCtx, nRow);
    pCtx->nSelectedRow = nIndex;
}
