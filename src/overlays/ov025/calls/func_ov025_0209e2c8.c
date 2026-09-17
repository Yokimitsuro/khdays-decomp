/* func_ov025_0209e2c8 -- Ov025_Tutorial_DrawTitles: redraw the tutorial page's text surface
 * (+0x84 of the page).  The page title (string 0 of the title text at +0x6c; 02089894) is drawn
 * at column 0xf9, row 2, width 2 in style 0x821 with a shadow (Ov025_Tutorial_DrawText
 * 0209e1c0), then the names of the nine visible topics (records of 8 bytes at +0xcc, from the
 * window +0 while below the count +4) at column 0x1c, 16 rows apart from row 0x23, in style
 * 0x209; the surface is flushed (020300f8) and VRAM slot 9 marked used (02084964). */
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
extern void  func_02030158(void *pSurface);                         /* Obj_InvokeInnerVtable4 */
extern const u16 *func_ov025_02089894(void *pText, int nIndex);     /* Ov008_GetString */
extern void  func_ov025_0209e1c0(const u16 *pString, int nX, int nY, int nWidth, u32 nStyle, int bShadow); /* Ov025_Tutorial_DrawText */
extern void  func_020300f8(void *pSurface);                         /* EnqueueObjGfxCommand */
extern void  func_ov025_02084964(int nSlot);                        /* Ov008_MarkSlotUsed */

void func_ov025_0209e2c8(void)
{
    Ov025TutorialPage *pPage;
    u16 i;
    int nRow;

    pPage = func_ov025_02084afc();
    func_02030158(pPage->surface);
    func_ov025_0209e1c0(func_ov025_02089894(pPage->textTitle, 0), 0xf9, 2, 2, 0x821, 1);
    for (i = 0; i < 9; i++) {
        nRow = pPage->nTop + i;
        if (nRow >= pPage->nCount) {
            break;
        }
        func_ov025_0209e1c0(pPage->aTopic[nRow].pName, 0x1c, i * 16 + 0x23, 2, 0x209, 1);
    }
    func_020300f8(pPage->surface);
    func_ov025_02084964(9);
}
