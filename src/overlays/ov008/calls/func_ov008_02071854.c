/* func_ov008_02071854 -- Ov008_MissionListPage: move the mission list's
 * selection by a page (nHeight / 32 rows) down (nDir > 0, clamped to the last
 * entry) or up (clamped to 0).  When the selection changes: the cursor cells
 * are flagged for refresh, the previous selection kept (+4), the new one
 * stored; the selection text is updated (locked when animating); outside a page
 * transition the dots are relaid (no modal object, touch disabled) and the row
 * texts refreshed; then the list scrolls so the selection keeps its screen
 * position (new pixel scroll clamped to [0, nScrollScale], track position
 * scale * max / trackMax) and the cursor cue plays.
 */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

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

#define ROW_HEIGHT 32
#define NO_TARGET  0x7fffffff

extern u16  func_ov008_0205b708(void);                                    /* mission entry count */
extern Ov008MissionListEntry *func_ov008_0205b670(int nIndex);
extern void func_ov008_0205b4ec(int nSlot, int bLocked);                  /* Ov008_MainMenu_UpdateSelectionText */
extern int  func_ov008_02051028(void);                                    /* page transition active */
extern int  func_ov008_02050ff8(void);                                    /* Ov008_GetCtxObject9630 */
extern void func_ov008_02070b44(Ov008MissionList *pList);                 /* Ov008_LayoutMissionDots */
extern void func_ov008_02070dd8(Ov008MissionList *pList);                 /* refresh the row texts */
extern int  func_02020400(int nNum, int nDen);                            /* _s32_div_f */
extern void func_ov008_02071760(Ov008MissionList *pList, int nPos, int nTarget, int bNow); /* Ov008_ScrollListTo */
extern void func_02033b78(int nKind, int nSound);                         /* PlaySound */

void func_ov008_02071854(Ov008MissionList *pList, int nDir)
{
    int nNext;
    int nCurrent;
    int nScroll;
    int bLocked;

    nCurrent = pList->nSelected;
    if (nCurrent < 0) {
        return;
    }
    if (nDir > 0) {
        int nCount = func_ov008_0205b708();
        nCurrent = pList->nSelected;
        nNext = nCurrent + pList->nHeight / ROW_HEIGHT;
        if (nNext >= nCount) {
            nNext = nCount - 1;
        }
    } else {
        nNext = nCurrent - pList->nHeight / ROW_HEIGHT;
        if (nNext < 0) {
            nNext = 0;
        }
    }
    if (nNext == nCurrent) {
        return;
    }
    nScroll = pList->nScroll + (nNext - nCurrent) * ROW_HEIGHT;
    pList->bCellsRefreshed = 1;
    pList->nWord1 = pList->nSelected;
    pList->nSelected = nNext;
    if (nNext >= 0) {
        Ov008MissionListEntry *pEntry;
        bLocked = 0;
        pEntry = func_ov008_0205b670(nNext);
        if (pList->bAnimating != 0) {
            bLocked = 1;
        }
        func_ov008_0205b4ec(pEntry->nSlot, bLocked);
    }
    if (func_ov008_02051028() == 0) {
        if (func_ov008_02050ff8() == 0 && pList->bTouchEnabled == 0) {
            func_ov008_02070b44(pList);
        }
        func_ov008_02070dd8(pList);
    }
    if (nScroll < 0) {
        nScroll = 0;
    }
    if (nScroll > pList->nScrollScale) {
        nScroll = pList->nScrollScale;
    }
    func_ov008_02071760(pList, func_02020400(pList->nTrackMax * nScroll, pList->nScrollScale), nScroll, 0);
    func_02033b78(0, 0);
}
