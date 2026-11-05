/* Ov025_ScrollList_Open -- Ov025_ScrollList_Open: the opening steps of the day list (page B), one
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

#include "nitro/types.h"

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

extern void  Ov025_InitResourceRecord(void *pStrings, const char *pszPath); /* Ov008_StringSet_Load */
extern void  Ov025_InitDisplayRegs(void);                             /* Ov025_ScrollList_InitDisplayRegs */
extern void  Ov025_ScrollList_BuildRows(Ov025ScrollList *pList);           /* Ov025_ScrollList_BuildRows */
extern int   Ov025_GetCtxBlock954c(void);                             /* Ov025_GetCtxBlock954c: the tag tracker */
extern void *Ov025_FindEntryByTag(int nTracker, int nTag);           /* Ov025_TagTracker_FindCell */
extern void  Ov025_InitAndAppendTracker(int nTracker, void *pCell, int nX, int nY, int nW, int nH, int nMask, Ov008ItemCb pCallback); /* Ov008_InitAndAppendTracker */
extern void  Ov025_SetField20Bit0(int nTracker, void *pCell, int bEnabled); /* SetField20Bit0 */
extern void  Ov025_ScrollList_HandleTouch(void *pOwner, void *pEntry, void *pArg); /* Ov025_ScrollList_OnRowTouch */
extern void  Ov025_ScrollList_LoadSubScreen(Ov025ScrollList *pList);           /* Ov025_ScrollList_LoadSubScreen: the argument is unused */
extern void  Ov025_ScrollList_SetupSurfaces(Ov025ScrollList *pList);           /* Ov025_ScrollList_SetupSurfaces */
extern u32   GameState_GetField(int nField, int nBits);                  /* GameState_GetField */
extern void  Ov025_WorldMap_UpdateSelectionText(int nDir, int nArg);               /* Ov008_QueueTransition */
extern void *Ov025_AllocAndRegisterEntry(void *pfnFlush);                   /* Ov008_ListAppendNode */
extern int   Ov025_ScrollList_Flush(void);                             /* Ov025_ScrollList_Flush */
extern int   Ov025_GetBlock4a80(void);                             /* Ov008_GetCtxBlock4a80 */
extern void *Ov025_FindEntryById(int nCtx, int nId);                /* FindEntryById */
extern void  Ov025_SetEntrySlotsVisible(int nCtx, void *pEntry, int bVisible); /* SetEntrySlotsVisible */
extern void  Ov025_PushSubitemSet(int nCtx, void *pEntry, int nSet); /* Ov008_PushSubitemSet */
extern void  Ov025_ScrollList_SetupScrollBar(Ov025ScrollList *pList);           /* Ov025_ScrollList_SetupScrollBar */
extern void  Ov025_ScrollList_SetKnob(Ov025ScrollList *pList, int nKnob, int nScroll, int bClampCursor); /* Ov025_ScrollList_SetKnob */
extern void  Ov025_ScrollList_SelectRow(Ov025ScrollList *pList, int nRow, int bSound); /* Ov025_ScrollList_SelectRow */
extern void  Ov025_DrawMissionSummaryHeading(int nHeadingMode);                 /* Ov008_DrawMissionSummaryHeading */
extern void  Ov025_RefreshScrollArrows(Ov025ScrollList *pList);           /* Ov025_ScrollList_RefreshArrows */
extern void  Ov025_ScrollList_PlaceKnobBar(Ov025ScrollList *pList);           /* Ov025_ScrollList_PlaceKnobBar */
extern void  Ov025_ApplyComputedOffset(Ov025ScrollList *pList);           /* Ov025_ScrollList_ApplyOffset */
extern void  Ov025_ScrollList_PlaceMarkers(Ov025ScrollList *pList);           /* Ov025_ScrollList_PlaceMarkers */
extern const char gOv025UiCalTtlPath[];                            /* "UI/cal/ttl_&.z" */

int Ov025_ScrollList_Open(Ov025ScrollList *pList)
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
        Ov025_InitResourceRecord(pList->strings, gOv025UiCalTtlPath);
        Ov025_InitDisplayRegs();
        Ov025_ScrollList_BuildRows(pList);
        pList->nCursor = 0;
        nTracker = Ov025_GetCtxBlock954c();
        Ov025_InitAndAppendTracker(nTracker, Ov025_FindEntryByTag(nTracker, 10), 0x10, 0x10, 0xe0, 0xa0, 0xffff, Ov025_ScrollList_HandleTouch);
        Ov025_SetField20Bit0(nTracker, Ov025_FindEntryByTag(nTracker, 10), 0);
        Ov025_ScrollList_LoadSubScreen(pList);
        Ov025_ScrollList_SetupSurfaces(pList);
        nDir = 4;
        if (GameState_GetField(0, 9) >= 357) {
            nDir = 0;
        }
        Ov025_WorldMap_UpdateSelectionText(nDir, 0);
        pList->pNode = Ov025_AllocAndRegisterEntry(Ov025_ScrollList_Flush);
        pList->nState++;
        break;
    case 1:
        nCtx = Ov025_GetBlock4a80();
        Ov025_SetEntrySlotsVisible(nCtx, Ov025_FindEntryById(nCtx, 1), 1);
        bShow = 1;
        for (i = 2; i <= 0x13; i++) {
            Ov025_SetEntrySlotsVisible(nCtx, Ov025_FindEntryById(nCtx, i), bShow);
        }
        bShow = 0;
        for (i = 0x16; i <= 0x20; i++) {
            Ov025_SetEntrySlotsVisible(nCtx, Ov025_FindEntryById(nCtx, i), bShow);
        }
        Ov025_PushSubitemSet(nCtx, Ov025_FindEntryById(nCtx, 2), 0);
        Ov025_PushSubitemSet(nCtx, Ov025_FindEntryById(nCtx, 0x16), 1);
        Ov025_ScrollList_SetupScrollBar(pList);
        Ov025_ScrollList_SetKnob(pList, pList->nKnobMax, 0x7fffffff, 0);
        pList->nState++;
        break;
    case 2:
        nRow = GameState_GetField(0x35c5, 8);
        if (nRow < 0) {
            nRow = 0;
        }
        nScroll = GameState_GetField(0x35d5, 10);
        if (nScroll >= 0) {
            Ov025_ScrollList_SelectRow(pList, (nScroll + 8) / 16, 0);
        }
        Ov025_ScrollList_SelectRow(pList, nRow, 0);
        Ov025_DrawMissionSummaryHeading(1);
        Ov025_RefreshScrollArrows(pList);
        Ov025_ScrollList_PlaceKnobBar(pList);
        Ov025_ApplyComputedOffset(pList);
        Ov025_ScrollList_PlaceMarkers(pList);
        pList->nState++;
        break;
    case 3:
        pList->nState++;
        bDone = 1;
        break;
    }
    return bDone;
}
