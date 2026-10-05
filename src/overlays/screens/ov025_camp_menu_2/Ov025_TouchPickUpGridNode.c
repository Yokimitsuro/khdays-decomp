/* Ov025_TouchPickUpGridNode -- Ov008_TouchPickUpGridNode: stylus pick-up of a grid
 * node.  Nothing while the menu is busy (+0x30), the pen is up, or a drag or
 * tween (+0x24 / +0x28) is running, or the pen is off the grid.  The touch
 * becomes the drag position (+0x60/+0x62) and the cell the cursor cell
 * (+0x64/+0x66); the previous cursor cell is restored when the pick-up
 * (Ov008_PickUpGridNode, result kept in +0x2c) fails.  On success widget 100
 * is hidden, menu button 5 refreshed, widget 0x4a shown with the node's icon
 * frame (+0x24, or hidden when the node has none), cursor mode 0x14 requested
 * with 5, the grid refreshed, and the node's text row repainted (0205eafc,
 * row 0, colour 0xf3, index from 0208e66c on +0x1e68) with the pick sound.
 */

#include "nitro/types.h"
#include "game/engine.h"

#define WIDGET_INFO  100
#define WIDGET_ICON  0x4a
#define CURSOR_MODE_DRAG 0x14
#define SOUND_PICK   1
#define COLOUR_ACTIVE 0xf3

typedef struct Ov008ShapeEntry {
    u8  pad_00[0x24];
    int nIconFrame;           /* 0x24: -1 = none */
} Ov008ShapeEntry;

typedef struct Ov008TouchRecord {
    u16 nX;                   /* 0x00 */
    u16 nY;                   /* 0x02 */
    u16 nTouching;            /* 0x04 */
    u16 nValidity;            /* 0x06 */
} Ov008TouchRecord;   /* the NitroSDK's TPData: 8 bytes */

typedef struct Ov008MenuContext {
    u8  pad_0000[0x24];
    int bDrag;                /* 0x0024 */
    int bTween;               /* 0x0028 */
    int bScroll;              /* 0x002c: pick-up result */
    int nBusy;                /* 0x0030 */
    u8  pad_0034[0x60 - 0x34];
    u16 nDragX;               /* 0x0060 */
    u16 nDragY;               /* 0x0062 */
    u16 nColumn;              /* 0x0064 */
    u16 nRowSel;              /* 0x0066 */
    u8  pad_0068[0x19b4 - 0x68];
    Ov008ShapeEntry *pListNode;  /* 0x19b4 */
    u8  pad_19b8[0x1e68 - 0x19b8];
    int textList[4];          /* 0x1e68 */
} Ov008MenuContext;

extern Ov008MenuContext *Ov025_GetPageA(void);                       /* Ov008_GetMenuContext */
extern void Ov025_CopySourceBlock(void *pOut);                              /* touch record */
extern int  Ov025_GetContext(void);                                    /* Ov008_GetContext */
extern int  Ov025_PixelToTileCell(u16 *pCol, u16 *pRow, unsigned int nX, unsigned int nY);    /* Ov008_PixelToTileCell */
extern int  Ov025_PickUpGridNode(Ov008MenuContext *pCtx);                  /* Ov008_PickUpGridNode */
extern void *Ov025_FindEntryById(int nCtx, int nId);                      /* FindEntryById */
extern void Ov025_SetEntrySlotsVisible(int nCtx, void *pEntry, int bVisible);    /* SetEntrySlotsVisible */
extern void Ov025_UpdateMenuButton5(int nArg);                                /* Ov008_UpdateMenuButton5 */
extern void Ov025_ReleaseTwoSlotsEx_2(int nCtx, void *pEntry, int nFrame);      /* Ov008_ReleaseTwoSlotsEx */
extern int Ov025_DrawPageBElement(int param_1, int param_2, ...); /* cursor mode request */
extern void Ov025_PageB_UploadSurface154(void);                                    /* grid refresh */
extern int  Ov025_GetItemDescriptionForMember(int *pList, Ov008ShapeEntry *pNode);      /* text index of a node */
extern void Ov025_RepaintTextRow(Ov008MenuContext *pCtx, int nRow, int nText, int nColour); /* Ov008_RepaintTextRow */

void Ov025_TouchPickUpGridNode(void)
{
    Ov008MenuContext *pCtx;
    Ov008TouchRecord touch;
    u16 nCol;
    u16 nRow;
    int nCtx;
    u16 nOldCol;
    u16 nOldRow;
    void *pIcon;

    pCtx = Ov025_GetPageA();
    if (pCtx->nBusy != 0) {
        return;
    }
    Ov025_CopySourceBlock(&touch);
    nCtx = Ov025_GetContext();
    if (touch.nTouching == 0) {
        return;
    }
    if (pCtx->bDrag != 0 || pCtx->bTween != 0) {
        return;
    }
    if (Ov025_PixelToTileCell(&nCol, &nRow, touch.nX, touch.nY) == 0) {
        return;
    }
    nOldCol = pCtx->nColumn;
    nOldRow = pCtx->nRowSel;
    pCtx->nDragX = touch.nX;
    pCtx->nDragY = touch.nY;
    pCtx->nColumn = nCol;
    pCtx->nRowSel = nRow;
    pCtx->bScroll = Ov025_PickUpGridNode(pCtx);
    if (pCtx->bScroll == 0) {
        pCtx->nColumn = nOldCol;
        pCtx->nRowSel = nOldRow;
        return;
    }
    Ov025_SetEntrySlotsVisible(nCtx, Ov025_FindEntryById(nCtx, WIDGET_INFO), 0);
    Ov025_UpdateMenuButton5(0);
    pIcon = Ov025_FindEntryById(nCtx, WIDGET_ICON);
    if (pCtx->pListNode->nIconFrame >= 0) {
        Ov025_SetEntrySlotsVisible(nCtx, pIcon, 1);
        Ov025_ReleaseTwoSlotsEx_2(nCtx, pIcon, (u16)pCtx->pListNode->nIconFrame);
    } else {
        Ov025_SetEntrySlotsVisible(nCtx, pIcon, 0);
    }
    Ov025_DrawPageBElement(CURSOR_MODE_DRAG, 0, 5);
    Ov025_PageB_UploadSurface154();
    Ov025_RepaintTextRow(pCtx, 0, Ov025_GetItemDescriptionForMember(pCtx->textList, pCtx->pListNode), COLOUR_ACTIVE);
    PlaySound(0, SOUND_PICK);
}
