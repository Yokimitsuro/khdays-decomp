/* func_ov025_0209e5e8 -- Ov025_Tutorial_HandleTouch: the tutorial page's stylus input.  Nothing
 * happens while the page is inactive (bits 4-7 of +0xc); a pending cursor move (bits 0-1) with no
 * touch held (bits 2-3) and no direction key (data_0204c18c bits 4-7) clears the phase and
 * cancels the viewer (020afcdc), and a pending phase otherwise ends the frame.  With the stylus
 * up, or the text viewer idle (020afcf0), the touch state (bits 2-3) copies the stylus, the
 * viewer is cancelled, the topic under the cursor (+0xcc table, +2) is opened when it is not
 * the one shown (+8; 020afd4c) and a knob drag (+0x68) ends.  While the stylus is held with the
 * touch state already set the knob keeps following it (Ov025_Tutorial_DragKnob 0209e520);
 * on the first touch (state becomes 1) a press inside the scroll bar box (data_ov025_020b41a0;
 * 0209d6c4) starts the drag, otherwise a press on one of the nine visible rows (x 16..0xd7, 16
 * pixels each from y 0x30) moves the cursor there, plays the cursor sound, opens the topic,
 * cancels the viewer and refreshes the rows (0209e3f8). */
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

typedef struct Ov025TouchInput {
    u16  wX;                  /* 0x00 */
    u16  wY;                  /* 0x02 */
    u16  wHeld;               /* 0x04 */
    u16  wPad;                /* 0x06 */
} Ov025TouchInput;

extern Ov025TutorialPage *func_ov025_02084afc(void);                /* Ov008_GetPageA */
extern void  func_ov025_020afcdc(void);                             /* Ov025_Viewer_Cancel */
extern void  func_ov025_020899dc(Ov025TouchInput *pTouch);          /* Ov008_ReadTouch */
extern int   func_ov025_020afcf0(void);                             /* Ov025_Viewer_IsIdle */
extern void  func_ov025_020afd4c(int nTopic);                       /* Ov025_Viewer_Open */
extern int   func_ov025_020afd18(void);                             /* Ov025_Viewer_IsBusy */
extern int   func_ov025_0209d6c4(const u16 *pPos, const u8 *pBox);  /* Ov025_PointInBox */
extern void  func_ov025_0209e520(const Ov025TouchInput *pTouch);    /* Ov025_Tutorial_DragKnob */
extern void  func_02033b78(int nKind, int nSound);                  /* PlaySound */
extern void  func_ov025_0209e3f8(void);                             /* Ov025_Tutorial_RefreshRows */
extern u16   data_0204c18c;                                         /* held keys */
extern const u8 data_ov025_020b41a0[];                              /* the scroll bar box */

void func_ov025_0209e5e8(void)
{
    Ov025TutorialPage *pPage;
    Ov025TouchInput touch;
    int nY;
    int nRow;
    int nTopic;

    pPage = func_ov025_02084afc();
    if (pPage->nActive == 0) {
        return;
    }
    if (pPage->nTouch == 0 && pPage->nPhase != 0 && !(data_0204c18c & 0xf0)) {
        pPage->nPhase = 0;
        func_ov025_020afcdc();
    }
    if (pPage->nPhase != 0) {
        return;
    }
    func_ov025_020899dc(&touch);
    if (touch.wHeld != 0 && func_ov025_020afcf0() == 0) {
        if (pPage->nTouch == 0) {
            pPage->nTouch = 1;
            if (pPage->list.bDragging == 0 && func_ov025_020afd18() == 0 && func_ov025_0209d6c4(&touch.wX, data_ov025_020b41a0) != 0) {
                pPage->list.bDragging = 1;
                func_ov025_0209e520(&touch);
                return;
            }
            if (touch.wX < 0x10) {
                return;
            }
            if (touch.wX >= 0xd8) {
                return;
            }
            if (touch.wY < 0x20) {
                return;
            }
            nY = 0x30;
            for (nRow = 0; nRow < 9; nRow++, nY += 0x10) {
                if (pPage->nTop + nRow >= pPage->nCount) {
                    return;
                }
                if (touch.wY < nY) {
                    nTopic = pPage->nTop + nRow;
                    if (pPage->nCursor == nTopic) {
                        return;
                    }
                    pPage->nCursor = nTopic;
                    func_02033b78(0, 0);
                    func_ov025_020afd4c(pPage->aTopic[pPage->nCursor].nId);
                    pPage->nShown = pPage->nCursor;
                    func_ov025_020afcdc();
                    func_ov025_0209e3f8();
                    return;
                }
            }
        } else if (pPage->list.bDragging != 0) {
            func_ov025_0209e520(&touch);
            func_ov025_020afcdc();
        }
    } else {
        pPage->nTouch = touch.wHeld != 0;
        func_ov025_020afcdc();
        if (pPage->nCursor != pPage->nShown) {
            func_ov025_020afd4c(pPage->aTopic[pPage->nCursor].nId);
            pPage->nShown = pPage->nCursor;
        }
        if (pPage->list.bDragging != 0) {
            pPage->list.bDragging = 0;
        }
    }
}
