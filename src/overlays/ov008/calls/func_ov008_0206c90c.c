/* func_ov008_0206c90c -- Ov008_ScrollMenuMoveTo: move the scrolling menu
 * to row nRow (wrapped over the entry count of the list at +0x1cc) and
 * redraw it; returns 1 when the list has more than one entry.  The scroll
 * top is the scroll (+0x3c) / 16, reset to 0 with the target (+0x40) for
 * short lists (up to 8 entries) that had scrolled; then the window is
 * clamped: past the end (8 or more entries, top + 7 beyond the count) the
 * top becomes count - 8 with the cursor offset (row - top) rows; a row
 * beyond top + 7 sets the target to (row - 7) rows with the cursor on row
 * 7; a row at or above the top makes it the target with the cursor at 0;
 * otherwise the target stays and the cursor sits (row - top) rows less the
 * scroll remainder.  Widgets 0x29 / 0x51 are placed at their bases (+0x20c
 * / +0x214) plus the cursor offset, the list window drawn (0206c690) and
 * the gauge knob laid out at (0x80 - +0x4c) * (target % 16 + top * 16) /
 * (16 * (visible - 8)); with more than 8 visible rows widgets 3 / 4 show
 * while the knob is above 0 / below the range, else both hide.  When bDraw
 * is set the row's entry text is pushed (0206eb64) by kind (+0x8): 0 =
 * record 0x15 of the id (or record 0x13 of its +0x34), 1 / 5 = record 0x13
 * of the id, 2 = variable text id, 3 = text id - 0x3b, 4 = texts 0x84 /
 * 0x83 for ids 0xff / 0xfe else the record of db 0206b6e4; the surface
 * (+0x64) is queued.  The row is stored (+0x50).  Codegen: the entry count
 * is the first zero (shared with the {0, 0} initialisers); the row
 * parameter is reused for the wrapped row; the top and the widget context
 * live in a block (top declared first) so they colour after the cursor
 * entry; the arrow flags are if/else assignments held across the lookup;
 * the kind-0 text is a ternary on the two record fields (one shared load);
 * the division helper is called explicitly (remainder from the high word).
 */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

#define ROW_HEIGHT     16
#define WINDOW_ROWS    8
#define GAUGE_RANGE    0x80
#define WIDGET_CURSOR_A 0x29
#define WIDGET_CURSOR_B 0x51
#define WIDGET_ARROW_UP 3
#define WIDGET_ARROW_DOWN 4
#define DB_MESSAGE_15  0x15
#define DB_MESSAGE_13  0x13
#define DB_SLOT        0xe

typedef struct UiLayoutPos {
    int nX;
    int nY;
} UiLayoutPos;

typedef struct Ov008ListNode {
    int nId;                  /* 0x00 */
    u8  pad_04[4];
    int nKind;                /* 0x08 */
} Ov008ListNode;

/* header shared by the 0x15 and 0x13 message records */
typedef struct Ov008TextRecord {
    u8  pad_00[0x10];
    u32 nText;                /* 0x10: entry text */
    u8  pad_14[0x20];
    u32 nLinkedId;            /* 0x34: linked record 0x13 id (0x15 records) */
} Ov008TextRecord;

typedef struct Ov008ScrollMenu {
    u8  pad_000[0x3c];
    int nScrollPos;           /* 0x03c: current scroll, row * 16 */
    int nScrollTarget;        /* 0x040: target scroll, row * 16 */
    u8  pad_044[8];
    int nGaugeScale;          /* 0x04c */
    int nSelectedRow;         /* 0x050 */
    u8  pad_054[4];
    u8  textRecords[0xc];     /* 0x058: variable text records */
    u8  objSurface[0x1cc - 0x64]; /* 0x064 */
    u8  list[0xc];            /* 0x1cc */
    u8  pad_1d8[0x20c - 0x1d8];
    UiLayoutPos cursorBaseA;  /* 0x20c: base of widget 0x29 */
    UiLayoutPos cursorBaseB;  /* 0x214: base of widget 0x51 */
} Ov008ScrollMenu;

extern int   func_ov008_02050c64(void);                                  /* Ov008_GetCtxBlock4a80 */
extern long long func_02020400(int nNum, int nDen);                      /* _s32_div_f: quotient, remainder in the high word */
extern void *NNS_FndGetNextListObject(void *pList, void *pObject);
extern void *func_ov008_02054788(int nCtx, int nId);                     /* FindEntryById */
extern void  func_ov008_020548a4(int nCtx, void *pEntry, UiLayoutPos *pPos); /* set the base position */
extern void  func_ov008_02054858(int nCtx, void *pEntry, UiLayoutPos *pPos); /* Ov008_SetEntryPos */
extern int   func_ov008_0206c690(Ov008ScrollMenu *pMenu, int nTop, int bFinal, int nArg); /* Ov008_DrawListWindow */
extern void  func_ov008_0206c7a0(Ov008ScrollMenu *pMenu, int nPos);      /* Ov008_LayoutScrollGauge */
extern void  func_ov008_02054ba4(int nCtx, void *pEntry, int bVisible);  /* SetEntrySlotsVisible */
extern Ov008ListNode *func_02010154(void *pList, int nIndex);          /* List_GetNthObject */
extern void  func_020342e8(Ov008TextRecord **ppRecord, int nDb, u32 nIndex, int nSlot); /* MsgDb_FetchRecord */
extern void  func_020343cc(Ov008TextRecord **ppRecord);                  /* release a raw db record */
extern int   func_ov008_0206eb64(int nMode, int nA, u32 nText);          /* cursor mode / text request */
extern void *func_ov008_02055c84(void *pRecords, int nIndex);            /* GetVarRecordByIndex */
extern u16   func_ov008_0206b6e4(void);                                  /* text db of the page */
extern int   func_020300f8(void *pSurface);                              /* EnqueueObjGfxCommand */

int func_ov008_0206c90c(Ov008ScrollMenu *pMenu, int nRow, int bDraw, int nArg)
{
    UiLayoutPos offset = {0, 0};
    UiLayoutPos pos = {0, 0};
    Ov008TextRecord *pRecA;
    Ov008TextRecord *pRecB;
    Ov008TextRecord *pRecC;
    int nCount;
    void *pEntry;
    void *pNode;
    int nVisible;
    int nRange;
    int nKnob;
    Ov008ListNode *pItem;
    int nId;
    int bUp;
    int bDown;

    nCount = 0;
    pRecA = 0;
    pRecB = 0;
    pRecC = 0;
    {
        int nTop;
        int nCtx;

        nCtx = func_ov008_02050c64();
        for (pNode = NNS_FndGetNextListObject(pMenu->list, 0); pNode != 0; pNode = NNS_FndGetNextListObject(pMenu->list, pNode)) {
            nCount++;
        }
        nRow = (int)(func_02020400(nRow + nCount, nCount) >> 32);
        nTop = pMenu->nScrollPos / ROW_HEIGHT;
        if (nCount <= WINDOW_ROWS && pMenu->nScrollPos > 0) {
            nTop = 0;
            pMenu->nScrollTarget = 0;
        }
        if (nCount >= WINDOW_ROWS && nTop + 7 >= nCount) {
            nTop = nCount - WINDOW_ROWS;
            pMenu->nScrollTarget = nTop * ROW_HEIGHT;
            offset.nY = (nRow - nTop) << 16;
        } else if (nRow > nTop + 7) {
            pMenu->nScrollTarget = (nRow - 7) * ROW_HEIGHT;
            offset.nY = 7 << 16;
            nTop = pMenu->nScrollTarget / ROW_HEIGHT;
        } else if (nRow <= nTop) {
            pMenu->nScrollTarget = nRow * ROW_HEIGHT;
            offset.nY = 0;
            nTop = pMenu->nScrollTarget / ROW_HEIGHT;
        } else {
            offset.nY = ((nRow - nTop) * ROW_HEIGHT - pMenu->nScrollPos % ROW_HEIGHT) << 12;
        }
        pEntry = func_ov008_02054788(nCtx, WIDGET_CURSOR_A);
        pos.nX = pMenu->cursorBaseA.nX + offset.nX;
        pos.nY = pMenu->cursorBaseA.nY + offset.nY;
        func_ov008_020548a4(nCtx, pEntry, &pos);
        func_ov008_02054858(nCtx, pEntry, &pos);
        pEntry = func_ov008_02054788(nCtx, WIDGET_CURSOR_B);
        pos.nX = pMenu->cursorBaseB.nX + offset.nX;
        pos.nY = pMenu->cursorBaseB.nY + offset.nY;
        func_ov008_020548a4(nCtx, pEntry, &pos);
        func_ov008_02054858(nCtx, pEntry, &pos);
        nVisible = func_ov008_0206c690(pMenu, nTop, 1, nArg);
        nRange = GAUGE_RANGE - pMenu->nGaugeScale;
        nKnob = (int)func_02020400(nRange * (pMenu->nScrollTarget % ROW_HEIGHT + nTop * ROW_HEIGHT), (nVisible - WINDOW_ROWS) * ROW_HEIGHT);
        func_ov008_0206c7a0(pMenu, nKnob);
        if (nVisible > WINDOW_ROWS) {
            if (nKnob > 0) {
                bUp = 1;
            } else {
                bUp = 0;
            }
            func_ov008_02054ba4(nCtx, func_ov008_02054788(nCtx, WIDGET_ARROW_UP), bUp);
            if (nKnob < nRange) {
                bDown = 1;
            } else {
                bDown = 0;
            }
            func_ov008_02054ba4(nCtx, func_ov008_02054788(nCtx, WIDGET_ARROW_DOWN), bDown);
        } else {
            func_ov008_02054ba4(nCtx, func_ov008_02054788(nCtx, WIDGET_ARROW_UP), 0);
            func_ov008_02054ba4(nCtx, func_ov008_02054788(nCtx, WIDGET_ARROW_DOWN), 0);
        }
    }
    if (bDraw != 0) {
        pItem = func_02010154(pMenu->list, (u16)nRow);
        switch (pItem->nKind) {
        case 1:
        case 5:
            func_020342e8(&pRecB, DB_MESSAGE_13, pItem->nId, DB_SLOT);
            func_ov008_0206eb64(0, 0, pRecB->nText);
            func_020343cc(&pRecB);
            break;
        case 0:
            func_020342e8(&pRecA, DB_MESSAGE_15, pItem->nId, DB_SLOT);
            if (pRecA->nLinkedId != 0) {
                func_020342e8(&pRecB, DB_MESSAGE_13, pRecA->nLinkedId, DB_SLOT);
            }
            func_ov008_0206eb64(0, 0, pRecB != 0 ? pRecB->nText : pRecA->nText);
            if (pRecB != 0) {
                func_020343cc(&pRecB);
            }
            func_020343cc(&pRecA);
            break;
        case 4:
            nId = pItem->nId;
            if (nId == 0xff) {
                func_ov008_0206eb64(0, 0, (u32)func_ov008_02055c84(pMenu->textRecords, 0x84));
            } else if (nId == 0xfe) {
                func_ov008_0206eb64(0, 0, (u32)func_ov008_02055c84(pMenu->textRecords, 0x83));
            } else {
                func_020342e8(&pRecC, func_ov008_0206b6e4(), nId, DB_SLOT);
                func_ov008_0206eb64(0, 0, pRecC->nText);
                func_020343cc(&pRecC);
            }
            break;
        case 3:
            func_ov008_0206eb64(0, 0, (u32)func_ov008_02055c84(pMenu->textRecords, pItem->nId - 0x3b));
            break;
        case 2:
            func_ov008_0206eb64(0, 0, (u32)func_ov008_02055c84(pMenu->textRecords, pItem->nId));
            break;
        }
        func_020300f8(pMenu->objSurface);
    }
    pMenu->nSelectedRow = nRow;
    return nCount > 1;
}
