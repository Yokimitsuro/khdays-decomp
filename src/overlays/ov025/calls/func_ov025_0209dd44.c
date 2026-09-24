/* func_ov025_0209dd44 -- Ov025_Tutorial_BuildTopicList: collect the unlocked tutorial topics.
 * Topics 1..57 whose flag is set (0209dd2c) are appended to the page's table (+0xcc: the
 * topic's string from the text at +0x78, GetVarRecordByIndex 02089894, and its id) and the
 * count (+4) stored; the table is then bubble-sorted by the display order of each id
 * (data_ov025_020b41dc), lowest first. */
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
extern int   func_ov025_0209dd2c(int nTopic);                       /* Ov025_Tutorial_IsTopicUnlocked */
extern const u16 *func_ov025_02089894(void *pRecords, int nIndex);  /* GetVarRecordByIndex */
extern const u8 data_ov025_020b41dc[];                              /* display order per topic id */

void func_ov025_0209dd44(void)
{
    Ov025TutorialPage *pPage;
    u16 i;
    u16 n;
    int nIndex;
    int nId;
    Ov025TutorialTopic *pTopic;
    u16 j;
    Ov025TutorialTopic tmp;

    pPage = func_ov025_02084afc();
    i = 0;
    n = 0;
    for (; i < 0x3a; i++) {
        nId = i + 1;
        if (func_ov025_0209dd2c(nId) != 0) {
            nIndex = n;
            n++;
            pTopic = &pPage->aTopic[nIndex];
            pTopic->pName = func_ov025_02089894(pPage->textTopics, nId);
            pTopic->nId = nId;
        }
    }
    pPage->nCount = n;
    for (i = 0; i < pPage->nCount - 1; i++) {
        for (j = pPage->nCount - 1; i < j; j--) {
            if (data_ov025_020b41dc[pPage->aTopic[j - 1].nId] > data_ov025_020b41dc[pPage->aTopic[j].nId]) {
                tmp = pPage->aTopic[j];
                pPage->aTopic[j] = pPage->aTopic[j - 1];
                pPage->aTopic[j - 1] = tmp;
            }
        }
    }
}
