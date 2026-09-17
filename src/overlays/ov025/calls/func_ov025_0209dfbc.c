/* func_ov025_0209dfbc -- Ov025_Tutorial_PageUp: scroll the tutorial list up a page.  Ignored
 * while up / down are held (bits 6-7 of data_0204c18c), something is busy (020afd18), the
 * stylus is down (bits 2-3 of +0xc) or the window (+0) is already at the top; otherwise the
 * window and the cursor (+2) move up nine topics, or up to the top when fewer remain.  The
 * row base (+0x64) resets, the phase bits (0-1 of +0xc) become 1, the cursor sound plays
 * (02033b78 0 / 0) and the rows are refreshed (0209e3f8). */
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
    int  bDragging;           /* 0x58: the scroll knob follows the stylus */
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
    s16  nShown;              /* 0x008: the topic open in the text viewer */
    s16  nField0a;            /* 0x00a */
    int  nPhase : 2;          /* 0x00c bits 0-1: 1 = cursor moved, redraw */
    int  nTouch : 2;          /* 0x00c bits 2-3: the stylus state */
    int  nActive : 4;         /* 0x00c bits 4-7 */
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
extern u16   data_0204c18c;                                         /* held keys */

void func_ov025_0209dfbc(void)
{
    Ov025TutorialPage *pPage;
    s16 nTop;

    pPage = func_ov025_02084afc();
    if (data_0204c18c & 0xc0) {
        return;
    }
    if (func_ov025_020afd18() != 0) {
        return;
    }
    if (pPage->nTouch != 0) {
        return;
    }
    nTop = pPage->nTop;
    if (nTop <= 0) {
        return;
    }
    if (nTop >= 9) {
        pPage->nTop = nTop - 9;
        pPage->nCursor -= 9;
    } else {
        pPage->nCursor -= nTop;
        pPage->nTop = 0;
    }
    pPage->list.nRowBase = 0;
    pPage->nPhase = 1;
    func_02033b78(0, 0);
    func_ov025_0209e3f8();
}
