/* Ov025_MissionListSelectRow -- Ov008_MissionListSelectRow: make row nRow the mission
 * list's selection.  With a real row its entry's text slot is shown (locked
 * while the list is animating); the cell refresh is requested, the previous
 * selection remembered and the new one stored.  While the list has a scroll
 * scale, the view scrolls (Ov008_ScrollListTo, track position = track max *
 * target / scale) so the row is in view: up to row * 32 when the row sits at
 * or above the scroll, down to (row - visible rows + 1) * 32 when it sits at
 * or below the last visible row.  Then the cursor is positioned, the sound
 * (when >= 0) played, and outside a page transition the mission dots (when no
 * modal object and touch is off) and row texts are refreshed; finally the
 * cursor cells are updated.
 */

#include "nitro/types.h"
#include "game/engine.h"

#define ROW_HEIGHT 32

typedef struct Ov008MissionListEntry {
    u8  pad_00[4];
    u16 nCategory;                /* 0x04 */
} Ov008MissionListEntry;

typedef struct Ov008MissionList {
    int nSelected;            /* 0x000 */
    int nWord1;               /* 0x004: previous selection */
    u8  pad_008[4];
    int nScroll;              /* 0x00c */
    u8  pad_010[8];
    int nHeight;              /* 0x018 */
    int nScrollScale;         /* 0x01c */
    u8  pad_020[8];
    int nTrackMax;            /* 0x028 */
    u8  pad_02c[0x38 - 0x2c];
    int bTouchEnabled;        /* 0x038 */
    u8  pad_03c[0x4c - 0x3c];
    int bCellsRefreshed;      /* 0x04c */
    u8  pad_050[0x68 - 0x50];
    int bAnimating;           /* 0x068 */
} Ov008MissionList;

extern Ov008MissionListEntry *Ov025_GetNextMissionEntry_2(int nIndex);
extern void Ov025_WorldMap_UpdateSelectionText(int nSlot, int bLocked);                  /* Ov008_WorldMap_UpdateSelectionText */
extern int  func_02020400(int nNum, int nDen);                            /* _s32_div_f */
extern void Ov025_ScrollListTo(Ov008MissionList *pList, int nPos, int nTarget, int bNow); /* Ov008_ScrollListTo */
extern void Ov025_MissionList_PlaceCursor(Ov008MissionList *pList);                 /* Ov008_PositionListCursor */
extern int  Ov025_GetCtxObject9634(void);                                    /* page transition active */
extern int  Ov025_GetCtxObject9630(void);                                    /* Ov008_GetCtxObject9630 */
extern void Ov025_LayoutMissionDots(Ov008MissionList *pList);                 /* Ov008_LayoutMissionDots */
extern void Ov025_LayoutMissionTiles(Ov008MissionList *pList);                 /* refresh the row texts */
extern void Ov025_UpdateListCursorCells(Ov008MissionList *pList);                 /* Ov008_UpdateListCursorCells */

void Ov025_MissionListSelectRow(Ov008MissionList *pList, int nRow, int nSound)
{
    int bLocked;
    int nVisible;
    int nTarget;
    Ov008MissionListEntry *pEntry;

    if (nRow >= 0) {
        bLocked = 0;
        pEntry = Ov025_GetNextMissionEntry_2(nRow);
        if (pList->bAnimating != 0) {
            bLocked = 1;
        }
        Ov025_WorldMap_UpdateSelectionText(pEntry->nCategory, bLocked);
    }
    pList->bCellsRefreshed = 1;
    pList->nWord1 = pList->nSelected;
    pList->nSelected = nRow;
    if (nRow >= 0 && pList->nScrollScale > 0) {
        nVisible = pList->nHeight / ROW_HEIGHT;
        if (nRow <= pList->nScroll / ROW_HEIGHT) {
            nTarget = nRow * ROW_HEIGHT;
            Ov025_ScrollListTo(pList, func_02020400(pList->nTrackMax * nTarget, pList->nScrollScale), nTarget, 0);
        }
        if (nRow >= (pList->nScroll + nVisible * ROW_HEIGHT) / ROW_HEIGHT) {
            nTarget = (nRow - (nVisible - 1)) * ROW_HEIGHT;
            Ov025_ScrollListTo(pList, func_02020400(pList->nTrackMax * nTarget, pList->nScrollScale), nTarget, 0);
        }
    }
    Ov025_MissionList_PlaceCursor(pList);
    if (nSound >= 0) {
        PlaySound(0, nSound);
    }
    if (Ov025_GetCtxObject9634() == 0) {
        if (Ov025_GetCtxObject9630() == 0 && pList->bTouchEnabled == 0) {
            Ov025_LayoutMissionDots(pList);
        }
        Ov025_LayoutMissionTiles(pList);
    }
    Ov025_UpdateListCursorCells(pList);
}
