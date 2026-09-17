/* func_ov025_020a6e68 -- Ov025_MissionList_SetupScrollBar: size the mission list's scroll bar
 * for the current slot's entries (0208dc74).  The pixel scroll (+0xc) and track position
 * (+0x20) start at 0; the bar is 0x80 high from y 0x30 (+0x18 / +0x14; 0xa0 from 0x10 during a
 * page transition, 02084e38); the scroll range (+0x1c) is 32 an entry beyond the bar, the knob
 * (+0x24) the bar's own height, or height * height / (32 * entries) when the entries overflow
 * it (the 64-bit divide 02020400), at least 0x20, and the track range (+0x28) the bar less the
 * knob.  Of the bar entries 4..0x13 of the 4a80 block (02084a8c) those within the knob less 16
 * are shown (0208884c), the caps 2 and 3 shown, the second pair of every entry 2..0x13 released
 * (020888b0), and the bar laid out (020a685c) with its arrows (020a67dc). */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

typedef struct Ov008MissionList {
    int  nSelected;           /* 0x000 */
    int  nPrevSelected;       /* 0x004 */
    int  nCursorRow;          /* 0x008 */
    int  nScroll;             /* 0x00c: in pixels, 32 a row */
    int  nPrevScroll;         /* 0x010 */
    int  nTop;                /* 0x014: the bar top, 0x30 (0x10 during a page transition) */
    int  nHeight;             /* 0x018: the bar height, 0x80 (0xa0 during a page transition) */
    int  nScrollScale;        /* 0x01c: the pixel scroll range */
    int  nTrackPos;           /* 0x020 */
    int  nKnobLength;         /* 0x024 */
    int  nTrackMax;           /* 0x028 */
} Ov008MissionList;

extern u16   func_ov025_0208dc74(void);                             /* Ov025_MissionSlotEntryCount */
extern int   func_ov025_02084e38(void);                             /* Ov025_GetCtxObject9634: page transition */
extern int   func_02020400(int nNum, int nDen);                     /* _s32_div_f */
extern int   func_ov025_02084a8c(void);                             /* Ov008_GetCtxBlock4a80 */
extern void *func_ov025_0208843c(int nCtx, int nId);                /* FindEntryById */
extern void  func_ov025_0208884c(int nCtx, void *pEntry, int bVisible); /* SetEntrySlotsVisible */
extern void  func_ov025_020888b0(int nCtx, void *pEntry);           /* Ov025_ReleaseTwoSlots */
extern void  func_ov025_020a685c(Ov008MissionList *pList);          /* Ov008_LayoutMenuRows: the knob bar */
extern void  func_ov025_020a67dc(Ov008MissionList *pList);          /* Ov008_UpdateScrollArrows */

void func_ov025_020a6e68(Ov008MissionList *pList)
{
    int nCount;
    int nCtx;
    int i;
    int nHidden;
    int nShown;

    nCount = func_ov025_0208dc74();
    pList->nScroll = 0;
    pList->nTrackPos = 0;
    pList->nHeight = 0x80;
    pList->nTop = 0x30;
    if (func_ov025_02084e38() != 0) {
        pList->nHeight += 0x20;
        pList->nTop -= 0x20;
    }
    pList->nScrollScale = nCount * 32 - pList->nHeight;
    if (pList->nScrollScale < 0) {
        pList->nScrollScale = 0;
    }
    pList->nKnobLength = pList->nHeight;
    if (nCount * 32 > pList->nHeight) {
        pList->nKnobLength = func_02020400(pList->nHeight * pList->nHeight, nCount * 32);
    }
    if (pList->nKnobLength < 0x20) {
        pList->nKnobLength = 0x20;
    }
    pList->nTrackMax = pList->nHeight - pList->nKnobLength;
    nCtx = func_ov025_02084a8c();
    nHidden = 0;
    nShown = 1;
    for (i = 4; i <= 0x13; i++) {
        if ((i - 3) * 8 < pList->nKnobLength - 0x10) {
            func_ov025_0208884c(nCtx, func_ov025_0208843c(nCtx, i), nShown);
        } else {
            func_ov025_0208884c(nCtx, func_ov025_0208843c(nCtx, i), nHidden);
        }
    }
    func_ov025_0208884c(nCtx, func_ov025_0208843c(nCtx, 2), 1);
    func_ov025_0208884c(nCtx, func_ov025_0208843c(nCtx, 3), 1);
    for (i = 2; i <= 0x13; i++) {
        func_ov025_020888b0(nCtx, func_ov025_0208843c(nCtx, i));
    }
    func_ov025_020a685c(pList);
    func_ov025_020a67dc(pList);
}
