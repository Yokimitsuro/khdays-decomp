/* func_ov008_02071760 -- Ov008_ScrollListTo: set a scroll list's position.
 * nPos is clamped to [0, nMax] and stored; the pixel scroll is either the given
 * nTarget or, with NO_TARGET, derived from the position (scale * pos / max).
 * When asked to settle now and the list is not animating, the selection is
 * pulled into the visible window [first row, first row + rows - 1].  Then the
 * rows are refilled, laid out, the cursor placed, the list ticked and the scroll
 * arrows refreshed.
 */
typedef unsigned char u8;
typedef unsigned int  u32;

#define NO_TARGET  0x7fffffff
#define ROW_HEIGHT 32

typedef struct Ov008MissionList {                /* the page-B list object */
    int nSelected;            /* 0x00 */
    u8  pad_04[8];
    int nScroll;              /* 0x0c: pixels */
    u8  pad_10[8];
    int nHeight;              /* 0x18: pixels */
    int nScrollScale;         /* 0x1c: pixels per track unit x max */
    int nTrackPos;            /* 0x20 */
    u8  pad_24[4];
    int nTrackMax;            /* 0x28 */
    u8  pad_2c[0x68 - 0x2c];
    int bAnimating;           /* 0x68 */
} Ov008MissionList;

extern int func_02020400(int nNum, int nDen);                            /* _s32_div_f */
extern void func_ov008_02071618(Ov008MissionList *pList, u32 nWord, int nTarget);
extern void func_ov008_0207126c(Ov008MissionList *pList);                 /* Ov008_RefillListRows */
extern void func_ov008_02071378(Ov008MissionList *pList);                 /* Ov008_LayoutMenuRows */
extern void func_ov008_02071468(Ov008MissionList *pList);                 /* Ov008_PositionListCursor */
extern void func_ov008_02071508(Ov008MissionList *pList);
extern void func_ov008_020712f8(Ov008MissionList *pList);                 /* Ov008_UpdateScrollArrows */

void func_ov008_02071760(Ov008MissionList *pList, int nPos, int nTarget, int bNow)
{
    int nFirst;
    int nRows;

    if (nPos < 0) {
        nPos = 0;
    }
    if (nPos > pList->nTrackMax) {
        nPos = pList->nTrackMax;
    }
    pList->nTrackPos = nPos;
    if (nTarget != NO_TARGET) {
        pList->nScroll = nTarget;
    }
    if (nTarget == NO_TARGET) {
        pList->nScroll = func_02020400(pList->nScrollScale * pList->nTrackPos, pList->nTrackMax);
    }
    nFirst = (pList->nScroll + ROW_HEIGHT / 2) / ROW_HEIGHT;
    if (bNow != 0 && pList->bAnimating == 0) {
        nRows = pList->nHeight / ROW_HEIGHT;
        if (pList->nSelected < nFirst) {
            func_ov008_02071618(pList, nFirst, -1);
        }
        if (pList->nSelected > nFirst + (nRows - 1)) {
            func_ov008_02071618(pList, nFirst + (nRows - 1), -1);
        }
    }
    func_ov008_0207126c(pList);
    func_ov008_02071378(pList);
    func_ov008_02071468(pList);
    func_ov008_02071508(pList);
    func_ov008_020712f8(pList);
}
