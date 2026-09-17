/* func_ov025_0209dc10 -- Ov025_Tutorial_SetupList: size the tutorial topic list (+0x10 of the
 * page) for nTotal topics.  All 15 row entries are hidden (0208884c), the total kept, the
 * scroll and the +0x58 word cleared; the visible row count (+0x50) is 18 for up to 9 topics,
 * otherwise 0x90 / nTotal clamped to 4..18 (the 64-bit divide 02020400), and the loop bound
 * (+0x44) is that count less four.  The header and footer entries are shown and the rows are
 * placed from the top (Ov025_Tutorial_PlaceRows 0209db50 with row 0). */
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
extern void  func_ov025_0208884c(int nCtx, void *pEntry, int bVisible); /* SetEntrySlotsVisible */
extern int   func_02020400(int nNum, int nDen);                     /* _s32_div_f */
extern void  func_ov025_0209db50(int nRow);                         /* Ov025_Tutorial_PlaceRows */

void func_ov025_0209dc10(int nTotal)
{
    Ov025TutorialPage *pPage;
    Ov025TutorialList *pList;
    int i;

    pPage = func_ov025_02084afc();
    pList = &pPage->list;
    for (i = 0; i < 15; i++) {
        func_ov025_0208884c(pPage->nCtx, pList->apRow[i], 0);
    }
    pList->nTotal = nTotal;
    pList->nScroll = 0;
    pList->nField58 = 0;
    if (nTotal <= 9) {
        pList->nRows = 0x12;
    } else {
        pList->nRows = func_02020400(0x90, nTotal);
        if (pList->nRows < 4) {
            pList->nRows = 4;
        }
        if (pList->nRows > 0x12) {
            pList->nRows = 0x12;
        }
    }
    pList->nVisible = pList->nRows - 4;
    func_ov025_0208884c(pPage->nCtx, pList->pHeader, 1);
    func_ov025_0208884c(pPage->nCtx, pList->pFooter, 1);
    func_ov025_0209db50(0);
}
