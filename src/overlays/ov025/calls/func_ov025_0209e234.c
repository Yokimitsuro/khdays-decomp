/* func_ov025_0209e234 -- Ov025_Tutorial_UpdateScrollBar: show the up arrow (+0x2a4 of the page)
 * once the window (+0) has left the top and the down arrow (+0x2a8) while more than nine
 * topics (+4) remain below it (0208884c); the scroll knob (+0x2ac) keeps its x and is placed
 * (Ov008_GetEntryPos 02088544 / Ov008_SetEntryPos 02088500) one cell per row below its origin,
 * at the cursor's row (+2 less +0). */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;
typedef short          s16;

typedef struct UiLayoutPos {
    int  x;                   /* 0x00 */
    int  y;                   /* 0x04 */
} UiLayoutPos;

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
extern void  func_ov025_0208884c(int nCtx, void *pEntry, int bVisible); /* SetEntrySlotsVisible */
extern UiLayoutPos *func_ov025_02088544(int nCtx, void *pEntry);    /* Ov008_GetEntryPos */
extern void  func_ov025_02088500(int nCtx, void *pEntry, UiLayoutPos *pPos); /* Ov008_SetEntryPos */

void func_ov025_0209e234(void)
{
    Ov025TutorialPage *pPage;
    UiLayoutPos pos;

    pPage = func_ov025_02084afc();
    func_ov025_0208884c(pPage->nCtx, pPage->pUpArrow, pPage->nTop != 0);
    func_ov025_0208884c(pPage->nCtx, pPage->pDownArrow, pPage->nTop < pPage->nCount - 9);
    pos = *func_ov025_02088544(pPage->nCtx, pPage->pKnob);
    pos.y += (pPage->nCursor - pPage->nTop) << 16;
    func_ov025_02088500(pPage->nCtx, pPage->pKnob, &pos);
}
