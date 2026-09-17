/* func_ov025_020ae6f0 -- Ov025_ScrollList_Open: the opening steps of the day list (page B), one
 * per call of its state (+0); returns 1 once state 3 has run.  State 0 loads the row strings
 * (UI/cal/ttl_&.z; 0208985c), the display registers (020ae49c) and the rows
 * (Ov025_ScrollList_BuildRows 020ad918), zeroes the cursor (+0x2c8), makes cell 10 of the shared
 * tag tracker (02084a64) the 0xe0 x 0xa0 touch area at (16, 16) with Ov025_ScrollList_OnRowTouch
 * (020895d0 / 0208962c), loads the sub screen (020ae384) and the row surfaces (020ae28c), queues
 * transition 4 (0 from day 357 on; 0208da58) and registers the flush node (+0x2c; 02084b2c with
 * Ov025_ScrollList_Flush).  State 1 shows entries 1..0x13 of the 4a80 block (02084a8c), hides
 * 0x16..0x20, pushes sets 0 / 1 on entries 2 / 0x16 (020887c0), sizes the scroll bar
 * (Ov025_ScrollList_SetupScrollBar 020ae4f4) and puts the knob at its end (020adfb0).  State 2
 * selects the saved scroll row ((field 0x35d5 + 8) / 16 when set) and the saved cursor row
 * (field 0x35c5; Ov025_ScrollList_SelectRow 020adee0), draws the heading (0208e000) and the
 * arrows, knob bar, offset and markers (020adcbc / 020add28 / 020ade14 / 020ade68). */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

typedef struct Ov025ScrollList {
    int  nState;              /* 0x000: the opening state (this function) */
    void *pRows;              /* 0x004: the day rows */
    int  nCount;              /* 0x008 */
    int  bTouching;           /* 0x00c: the stylus holds the scroll bar */
    int  bPressed;            /* 0x010 */
    int  bRowsDirty;          /* 0x014: re-upload the row surfaces */
    int  bMarkersDirty;       /* 0x018: re-upload the marker screen */
    u8   strings[0x10];       /* 0x01c: the row name strings (UI/cal/ttl_&.z) */
    void *pNode;              /* 0x02c: the shared UI list node */
    u8   aSurface[11][0x3c];  /* 0x030: one text surface per row (TileSurface) */
    int  bDirty;              /* 0x2c4 */
    int  nCursor;             /* 0x2c8 */
    int  nField2cc;           /* 0x2cc */
    int  nScroll;             /* 0x2d0: in pixels, 16 per row */
    int  nPrevScroll;         /* 0x2d4 */
    int  nScrollMax;          /* 0x2d8 */
    int  nKnob;               /* 0x2dc */
    int  nKnobHeight;         /* 0x2e0 */
    int  nKnobMax;            /* 0x2e4 */
} Ov025ScrollList;            /* 0x2e8: the day list view of page B (Ov025_GetPageB) */

typedef void (*Ov008ItemCb)(void *pOwner, void *pEntry, void *pArg);

extern void  func_ov025_0208985c(void *pStrings, const char *pszPath); /* Ov008_StringSet_Load */
extern void  func_ov025_020ae49c(void);                             /* Ov025_ScrollList_InitDisplayRegs */
extern void  func_ov025_020ad918(Ov025ScrollList *pList);           /* Ov025_ScrollList_BuildRows */
extern int   func_ov025_02084a64(void);                             /* Ov025_GetCtxBlock954c: the tag tracker */
extern void *func_ov025_020894b0(int nTracker, int nTag);           /* Ov025_TagTracker_FindCell */
extern void  func_ov025_020895d0(int nTracker, void *pCell, int nX, int nY, int nW, int nH, int nMask, Ov008ItemCb pCallback); /* Ov008_InitAndAppendTracker */
extern void  func_ov025_0208962c(int nTracker, void *pCell, int bEnabled); /* SetField20Bit0 */
extern void  func_ov025_020aec58(void *pOwner, void *pEntry, void *pArg); /* Ov025_ScrollList_OnRowTouch */
extern void  func_ov025_020ae384(Ov025ScrollList *pList);           /* Ov025_ScrollList_LoadSubScreen: the argument is unused */
extern void  func_ov025_020ae28c(Ov025ScrollList *pList);           /* Ov025_ScrollList_SetupSurfaces */
extern u32   func_020235d0(int nField, int nBits);                  /* GameState_GetField */
extern void  func_ov025_0208da58(int nDir, int nArg);               /* Ov008_QueueTransition */
extern void *func_ov025_02084b2c(void *pfnFlush);                   /* Ov008_ListAppendNode */
extern int   func_ov025_020ae1b4(void);                             /* Ov025_ScrollList_Flush */
extern int   func_ov025_02084a8c(void);                             /* Ov008_GetCtxBlock4a80 */
extern void *func_ov025_0208843c(int nCtx, int nId);                /* FindEntryById */
extern void  func_ov025_0208884c(int nCtx, void *pEntry, int bVisible); /* SetEntrySlotsVisible */
extern void  func_ov025_020887c0(int nCtx, void *pEntry, int nSet); /* Ov008_PushSubitemSet */
extern void  func_ov025_020ae4f4(Ov025ScrollList *pList);           /* Ov025_ScrollList_SetupScrollBar */
extern void  func_ov025_020adfb0(Ov025ScrollList *pList, int nKnob, int nScroll, int bClampCursor); /* Ov025_ScrollList_SetKnob */
extern void  func_ov025_020adee0(Ov025ScrollList *pList, int nRow, int bSound); /* Ov025_ScrollList_SelectRow */
extern void  func_ov025_0208e000(int nHeadingMode);                 /* Ov008_DrawMissionSummaryHeading */
extern void  func_ov025_020adcbc(Ov025ScrollList *pList);           /* Ov025_ScrollList_RefreshArrows */
extern void  func_ov025_020add28(Ov025ScrollList *pList);           /* Ov025_ScrollList_PlaceKnobBar */
extern void  func_ov025_020ade14(Ov025ScrollList *pList);           /* Ov025_ScrollList_ApplyOffset */
extern void  func_ov025_020ade68(Ov025ScrollList *pList);           /* Ov025_ScrollList_PlaceMarkers */
extern const char data_ov025_020b54f8[];                            /* "UI/cal/ttl_&.z" */

int func_ov025_020ae6f0(Ov025ScrollList *pList)
{
    int bDone;
    int nTracker;
    int nCtx;
    int i;
    int bShow;
    int nDir;
    int nRow;
    int nScroll;

    bDone = 0;
    switch (pList->nState) {
    case 0:
        func_ov025_0208985c(pList->strings, data_ov025_020b54f8);
        func_ov025_020ae49c();
        func_ov025_020ad918(pList);
        pList->nCursor = 0;
        nTracker = func_ov025_02084a64();
        func_ov025_020895d0(nTracker, func_ov025_020894b0(nTracker, 10), 0x10, 0x10, 0xe0, 0xa0, 0xffff, func_ov025_020aec58);
        func_ov025_0208962c(nTracker, func_ov025_020894b0(nTracker, 10), 0);
        func_ov025_020ae384(pList);
        func_ov025_020ae28c(pList);
        nDir = 4;
        if (func_020235d0(0, 9) >= 357) {
            nDir = 0;
        }
        func_ov025_0208da58(nDir, 0);
        pList->pNode = func_ov025_02084b2c(func_ov025_020ae1b4);
        pList->nState++;
        break;
    case 1:
        nCtx = func_ov025_02084a8c();
        func_ov025_0208884c(nCtx, func_ov025_0208843c(nCtx, 1), 1);
        bShow = 1;
        for (i = 2; i <= 0x13; i++) {
            func_ov025_0208884c(nCtx, func_ov025_0208843c(nCtx, i), bShow);
        }
        bShow = 0;
        for (i = 0x16; i <= 0x20; i++) {
            func_ov025_0208884c(nCtx, func_ov025_0208843c(nCtx, i), bShow);
        }
        func_ov025_020887c0(nCtx, func_ov025_0208843c(nCtx, 2), 0);
        func_ov025_020887c0(nCtx, func_ov025_0208843c(nCtx, 0x16), 1);
        func_ov025_020ae4f4(pList);
        func_ov025_020adfb0(pList, pList->nKnobMax, 0x7fffffff, 0);
        pList->nState++;
        break;
    case 2:
        nRow = func_020235d0(0x35c5, 8);
        if (nRow < 0) {
            nRow = 0;
        }
        nScroll = func_020235d0(0x35d5, 10);
        if (nScroll >= 0) {
            func_ov025_020adee0(pList, (nScroll + 8) / 16, 0);
        }
        func_ov025_020adee0(pList, nRow, 0);
        func_ov025_0208e000(1);
        func_ov025_020adcbc(pList);
        func_ov025_020add28(pList);
        func_ov025_020ade14(pList);
        func_ov025_020ade68(pList);
        pList->nState++;
        break;
    case 3:
        pList->nState++;
        bDone = 1;
        break;
    }
    return bDone;
}
