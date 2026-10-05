/* Ov008_GridMenuConfirm -- Ov008_GridMenuConfirm: the grid menu's confirm
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

#include "nitro/types.h"
#include "game/engine.h"

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
    u16 nValidity;            /* 0x06 */
} Ov008TouchRecord;   /* the NitroSDK's TPData: 8 bytes */

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

extern void Ov008_CopySourceBlock(void *pOut);                              /* touch record */
extern int  Ov008_PlaceDraggedNode(Ov008MenuContext *pCtx, int nArg);        /* drop the dragged node */
extern int  Ov008_MoveGridCursor(Ov008MenuContext *pCtx, int nColumn, int nRow, int nStep); /* move the cursor */
extern int  Ov008_PickUpGridNode(Ov008MenuContext *pCtx);                  /* Ov008_PickUpGridNode */
extern int Ov008_DrawPageBElement(int param_1, int param_2, ...); /* cursor mode request */
extern void Ov008_PageB_UploadSurface154(void);                                    /* grid refresh */
extern int  Ov008_DropLiftedNode(Ov008MenuContext *pCtx);                  /* drop the lifted node */
extern void Ov008_RebuildGridHits(Ov008MenuContext *pCtx);                  /* Ov008_RebuildGridHits */
extern Ov008InventoryItem *NNS_FndGetNthListObject(void *pList, int nIndex);        /* List_GetNthObject */
extern int  Ov008_PickUpListItem(Ov008MenuContext *pCtx, Ov008InventoryItem *pItem, u16 nSlot); /* Ov008_PickUpListItem */
extern void Ov008_EnterMenuState(Ov008MenuContext *pCtx, int nState);      /* Ov008_EnterMenuState */

void Ov008_GridMenuConfirm(Ov008MenuContext *pCtx)
{
    Ov008TouchRecord touch;

    Ov008_CopySourceBlock(&touch);
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
        if (Ov008_PlaceDraggedNode(pCtx, 1) != 0) {
            pCtx->nHoldCount = 1;
            if ((u32)pCtx->menuState <= STATE_GRID) {
                Ov008_MoveGridCursor(pCtx, pCtx->nColumn, pCtx->nRowSel, 0);
                pCtx->nBusyWord = 1;
            }
            PlaySound(0, SOUND_DROP);
        } else {
            PlaySound(0, SOUND_REFUSE);
        }
        break;
    case STATE_GRID:
        if (pCtx->pListNode == 0) {
            if (Ov008_PickUpGridNode(pCtx) != 0) {
                PlaySound(0, SOUND_OK);
                Ov008_DrawPageBElement(CURSOR_MODE_DRAG, 0, 2);
                Ov008_PageB_UploadSurface154();
            }
        } else if (Ov008_DropLiftedNode(pCtx) != 0) {
            Ov008_RebuildGridHits(pCtx);
            if (pCtx->nBusyWord != 0) {
                Ov008_DrawPageBElement(CURSOR_MODE_DRAG, 0, 2);
            } else {
                Ov008_MoveGridCursor(pCtx, pCtx->nColumn, pCtx->nRowSel, 1);
            }
            Ov008_PageB_UploadSurface154();
            PlaySound(0, SOUND_DROP);
        } else {
            PlaySound(0, SOUND_REFUSE);
        }
        break;
    case STATE_DRAG:
        if (pCtx->nBusy != 0) {
            return;
        }
        if (Ov008_PickUpListItem(pCtx, NNS_FndGetNthListObject(pCtx->pList, (u16)pCtx->nSelectedRow), PICK_SLOT) != 0) {
            Ov008_EnterMenuState(pCtx, STATE_LIST);
            PlaySound(0, SOUND_OK);
        } else {
            PlaySound(0, SOUND_REFUSE);
        }
        break;
    }
}
