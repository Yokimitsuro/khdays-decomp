/* func_ov025_0209d974 -- Ov025_Tutorial_SetupEntries: bind the tutorial page's sprites.  The
 * tag tracker (+0xc4 of the page) loads archive member 0x42 (Ov008_PackSlotTag 02084d18;
 * 020891dc), its cell 0 is invoked (Ov008_TagTracker_InvokeCallback 02089544) and cells 1 / 2
 * become the plain and lit row markers (+0x29c / +0x2a0; 020894b0).  The entry context (+0xc8)
 * takes the layout template data_ov025_020b41a4 with member 0x44 as its resource (020883f8),
 * loads the 0x14 entries of member 0x45 (Ov008_LoadBlockProcessAndFree 0208832c) and releases
 * the list slots in mode 2 (02088a7c); entries 2, 3 and 1 become the up arrow, the down arrow
 * and the scroll knob (+0x2a4 / +0x2a8 / +0x2ac; FindEntryById 0208843c) and the knob is shown
 * (SetEntrySlotsVisible 0208884c). */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;
typedef short          s16;

typedef struct Ov008LayoutTemplate {
    u32  words[4];
} Ov008LayoutTemplate;

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
extern u32   func_ov025_02084d18(int nMember);                      /* Ov008_PackSlotTag */
extern void  func_ov025_020891dc(int nTracker, u32 nTag);           /* Ov008_TagTracker_Load */
extern void *func_ov025_020894b0(int nTracker, int nTag);           /* Ov008_TagTracker_FindCell */
extern void  func_ov025_02089544(int nTracker, void *pCell);        /* Ov008_TagTracker_InvokeCallback */
extern void  func_ov025_020883f8(int nCtx, Ov008LayoutTemplate *pLayout); /* Ov008_SetLayout */
extern void  func_ov025_0208832c(int nCtx, u32 nTag, int nCount);   /* Ov008_LoadBlockProcessAndFree */
extern void  func_ov025_02088a7c(int nCtx, int nMode);              /* Ov008_ForEachListNode */
extern void *func_ov025_0208843c(int nCtx, int nId);                /* FindEntryById */
extern void  func_ov025_0208884c(int nCtx, void *pEntry, int bVisible); /* SetEntrySlotsVisible */
extern Ov008LayoutTemplate data_ov025_020b41a4;

void func_ov025_0209d974(void)
{
    Ov008LayoutTemplate layout;
    Ov025TutorialPage *pPage;

    layout = data_ov025_020b41a4;
    pPage = func_ov025_02084afc();
    func_ov025_020891dc(pPage->nTracker, func_ov025_02084d18(0x42));
    func_ov025_02089544(pPage->nTracker, func_ov025_020894b0(pPage->nTracker, 0));
    pPage->pMarkerCell = func_ov025_020894b0(pPage->nTracker, 1);
    pPage->pMarkerLitCell = func_ov025_020894b0(pPage->nTracker, 2);
    layout.words[0] = func_ov025_02084d18(0x44);
    func_ov025_020883f8(pPage->nCtx, &layout);
    func_ov025_0208832c(pPage->nCtx, func_ov025_02084d18(0x45), 0x14);
    func_ov025_02088a7c(pPage->nCtx, 2);
    pPage->pUpArrow = func_ov025_0208843c(pPage->nCtx, 2);
    pPage->pDownArrow = func_ov025_0208843c(pPage->nCtx, 3);
    pPage->pKnob = func_ov025_0208843c(pPage->nCtx, 1);
    func_ov025_0208884c(pPage->nCtx, func_ov025_0208843c(pPage->nCtx, 1), 1);
}
