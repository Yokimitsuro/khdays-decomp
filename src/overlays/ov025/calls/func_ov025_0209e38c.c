/* func_ov025_0209e38c -- Ov025_Tutorial_PlaceMarkers: place the nine row markers of the tutorial
 * list down the left column.  The marker under the cursor (row = cursor +2 - top +0 of the page)
 * uses the lit cell (+0x2a0), the others the plain cell (+0x29c); each is put at column 2, row
 * 4 + 2 * i in the page's tag tracker (+0xc4; 0208951c) and its callback invoked
 * (Ov008_TagTracker_InvokeCallback 02089544). */
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
extern void  func_ov025_0208951c(int nTracker, void *pCell, s16 nX, s16 nY); /* Ov008_TagTracker_SetCellPos */
extern void  func_ov025_02089544(int nTracker, void *pCell);        /* Ov008_TagTracker_InvokeCallback */

void func_ov025_0209e38c(void)
{
    Ov025TutorialPage *pPage;
    int i;
    int nRow;
    s16 nY;
    void *pCell;

    pPage = func_ov025_02084afc();
    nRow = pPage->nCursor - pPage->nTop;
    nY = 4;
    for (i = 0; i < 9; i++) {
        if (nRow == i) {
            pCell = pPage->pMarkerLitCell;
        } else {
            pCell = pPage->pMarkerCell;
        }
        func_ov025_0208951c(pPage->nTracker, pCell, 2, nY);
        func_ov025_02089544(pPage->nTracker, pCell);
        nY += 2;
    }
}
