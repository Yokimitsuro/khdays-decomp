/* func_ov008_02071618 -- Ov008_MissionListSelectRow: make row nRow the mission
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
typedef unsigned char  u8;
typedef unsigned short u16;

#define ROW_HEIGHT 32

typedef struct Ov008MissionListEntry {
    u8  pad_00[4];
    u16 nSlot;                /* 0x04 */
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

extern Ov008MissionListEntry *func_ov008_0205b670(int nIndex);
extern void func_ov008_0205b4ec(int nSlot, int bLocked);                  /* Ov008_MainMenu_UpdateSelectionText */
extern int  func_02020400(int nNum, int nDen);                            /* _s32_div_f */
extern void func_ov008_02071760(Ov008MissionList *pList, int nPos, int nTarget, int bNow); /* Ov008_ScrollListTo */
extern void func_ov008_02071468(Ov008MissionList *pList);                 /* Ov008_PositionListCursor */
extern void func_02033b78(int nKind, int nSound);                         /* PlaySound */
extern int  func_ov008_02051028(void);                                    /* page transition active */
extern int  func_ov008_02050ff8(void);                                    /* Ov008_GetCtxObject9630 */
extern void func_ov008_02070b44(Ov008MissionList *pList);                 /* Ov008_LayoutMissionDots */
extern void func_ov008_02070dd8(Ov008MissionList *pList);                 /* refresh the row texts */
extern void func_ov008_02071508(Ov008MissionList *pList);                 /* Ov008_UpdateListCursorCells */

void func_ov008_02071618(Ov008MissionList *pList, int nRow, int nSound)
{
    int bLocked;
    int nVisible;
    int nTarget;
    Ov008MissionListEntry *pEntry;

    if (nRow >= 0) {
        bLocked = 0;
        pEntry = func_ov008_0205b670(nRow);
        if (pList->bAnimating != 0) {
            bLocked = 1;
        }
        func_ov008_0205b4ec(pEntry->nSlot, bLocked);
    }
    pList->bCellsRefreshed = 1;
    pList->nWord1 = pList->nSelected;
    pList->nSelected = nRow;
    if (nRow >= 0 && pList->nScrollScale > 0) {
        nVisible = pList->nHeight / ROW_HEIGHT;
        if (nRow <= pList->nScroll / ROW_HEIGHT) {
            nTarget = nRow * ROW_HEIGHT;
            func_ov008_02071760(pList, func_02020400(pList->nTrackMax * nTarget, pList->nScrollScale), nTarget, 0);
        }
        if (nRow >= (pList->nScroll + nVisible * ROW_HEIGHT) / ROW_HEIGHT) {
            nTarget = (nRow - (nVisible - 1)) * ROW_HEIGHT;
            func_ov008_02071760(pList, func_02020400(pList->nTrackMax * nTarget, pList->nScrollScale), nTarget, 0);
        }
    }
    func_ov008_02071468(pList);
    if (nSound >= 0) {
        func_02033b78(0, nSound);
    }
    if (func_ov008_02051028() == 0) {
        if (func_ov008_02050ff8() == 0 && pList->bTouchEnabled == 0) {
            func_ov008_02070b44(pList);
        }
        func_ov008_02070dd8(pList);
    }
    func_ov008_02071508(pList);
}
