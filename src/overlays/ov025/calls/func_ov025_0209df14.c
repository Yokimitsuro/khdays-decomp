/* func_ov025_0209df14 -- Ov025_Tutorial_CursorDown: move the tutorial cursor (+2 of the page)
 * down one topic while nothing is busy (020afd18) and no page scroll is in flight (bits 2-3 of
 * +0xc).  With at least two topics the cursor advances; past the ninth row the window (+0)
 * follows it, past the last topic both wrap to the top; either scroll resets the row base
 * (+0x64).  The phase bits (0-1 of +0xc) become 1, the cursor sound plays (02033b78 0 / 0) and
 * the rows are refreshed (0209e3f8). */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;
typedef short          s16;

typedef struct Ov025TutorialList {
    void *pHeader;            /* 0x00 */
    void *pFooter;            /* 0x04 */
    void *apRow[15];          /* 0x08 */
    int  nVisible;            /* 0x44: rows placed by Ov025_Tutorial_PlaceRows */
    int  nTotal;              /* 0x48 */
    int  nScroll;             /* 0x4c: the row requested by Ov025_Tutorial_ScrollTo */
    int  nRows;               /* 0x50: 4..18 */
    int  nRowBase;            /* 0x54: the row offset the entries are placed from */
    int  nField58;            /* 0x58 */
} Ov025TutorialList;          /* 0x5c */

typedef struct Ov025TutorialTopic {
    const u16 *pName;         /* 0x00 */
    int  nId;                 /* 0x04 */
} Ov025TutorialTopic;

typedef struct Ov025TutorialPage {
    s16  nTop;                /* 0x000: the first visible topic */
    s16  nCursor;             /* 0x002 */
    s16  nCount;              /* 0x004 */
    s16  nField06;            /* 0x006 */
    int  nField08;            /* 0x008 */
    u32  nPhase : 2;          /* 0x00c bits 0-1: 1 = cursor moved, redraw */
    int  nScrollDir : 2;      /* 0x00c bits 2-3: a page scroll in flight */
    Ov025TutorialList list;   /* 0x010 */
    u8   textTitle[0xc];      /* 0x06c: "UI/cm/str/ttl_&.s.z" */
    u8   textTopics[0xc];     /* 0x078: "UI/tutorial/root_&.s.z" */
    u8   surface[0x3c];       /* 0x084: the text surface */
    int  nField0c0;           /* 0x0c0 */
    int  nTracker;            /* 0x0c4: the tag tracker (markers) */
    int  nCtx;                /* 0x0c8: the entry context (rows, arrows, knob) */
    Ov025TutorialTopic aTopic[58]; /* 0x0cc: the unlocked topics in display order */
    void *pMarkerCell;        /* 0x29c */
    void *pMarkerLitCell;     /* 0x2a0 */
    void *pUpArrow;           /* 0x2a4 */
    void *pDownArrow;         /* 0x2a8 */
    void *pKnob;              /* 0x2ac */
} Ov025TutorialPage;          /* 0x2b0: a view of page A (Ov008_GetPageA) */

extern Ov025TutorialPage *func_ov025_02084afc(void);                /* Ov008_GetPageA */
extern int   func_ov025_020afd18(void);                             /* Ov025_IsPageBBusy */
extern void  func_02033b78(int nKind, int nSound);                  /* PlaySound */
extern void  func_ov025_0209e3f8(void);                             /* Ov025_Tutorial_RefreshRows */

void func_ov025_0209df14(void)
{
    Ov025TutorialPage *pPage;

    pPage = func_ov025_02084afc();
    if (func_ov025_020afd18() != 0) {
        return;
    }
    if (pPage->nScrollDir != 0) {
        return;
    }
    if (pPage->nCount <= 1) {
        return;
    }
    pPage->nCursor++;
    if (pPage->nCursor >= pPage->nCount) {
        pPage->nCursor = 0;
        pPage->nTop = 0;
        pPage->list.nRowBase = 0;
    } else if (pPage->nTop + 9 <= pPage->nCursor) {
        pPage->nTop++;
        pPage->list.nRowBase = 0;
    }
    pPage->nPhase = 1;
    func_02033b78(0, 0);
    func_ov025_0209e3f8();
}
