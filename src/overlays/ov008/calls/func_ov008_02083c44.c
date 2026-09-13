/* func_ov008_02083c44 -- Ov008_DrawCounterPanel: redraw the shop's counter
 * panel (+0xc324) for record pRecord (0 = none) and quantity nCount.  A
 * special item (0208b7a8 on the item id) shows no owned count.  On its
 * first draw (+0x0) the tag callback 0x3f3 (tracker +0x5c) runs and the
 * counter surface (+0xc1d8) is cleared (0xb0 x 0x30); widgets 0x14 .. 0x1a
 * (manager +0x7530) are hidden and, with a record, the widget of its
 * category (0208ff20, entry 3 for a special item) shown.  The surface is
 * cleared again and the item name (def +0xc) drawn at (0xd, 0xb).  The nine
 * digit cells are hidden; with a record the extra cell (+0x38) follows the
 * special flag and the owned count (GameState 0x810) goes to the first
 * counter.  For a non-special record whose owned count differs from nCount
 * (nCount not negative) widget 1 hides and 9 shows, widget 7 (owned below
 * nCount) or 8 shows and reruns its slots when its flag bit 1 (+0x84) is
 * clear while the other hides, and nCount goes to the second counter (the
 * third on tab 1, +0xc250); otherwise 7, 8 and 9 hide and widget 1 shows
 * only on tabs 0 / 2 when the counts match.  Codegen: the widget table is a
 * 28-byte struct copy; the special flag, owned count, surface and widget 9
 * are locals; the digit rows are a 3 x 3 array and the quantity row is
 * picked as (&aDigit[1])[tab != 1]; the tab test is an int bool.
 */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

#define DIGIT_COUNT   3
#define TAG_COUNTER   0x3f3
#define WIDGET_FIRST  0x14
#define WIDGET_LAST   0x1a
#define WIDGET_QTY    1
#define WIDGET_DOWN   7
#define WIDGET_UP     8
#define WIDGET_MARK   9

typedef struct Ov008ItemDef {
    u8   pad_00[0xc];
    void *pName;              /* 0x0c */
    u8   pad_10[4];
    int  nItemId;             /* 0x14 */
    int  nCategory;           /* 0x18 */
} Ov008ItemDef;

typedef struct Ov008ParamRecord {
    u8   pad_00[0xc];
    Ov008ItemDef *pItemDef;   /* 0x0c */
} Ov008ParamRecord;

typedef struct Ov008MenuEntry {
    u8   pad_00[0x84];
    u32  bUseAlt : 1;         /* 0x84 bit 0 */
    u32  bLocked : 1;         /* 0x84 bit 1 */
} Ov008MenuEntry;

typedef struct Ov008CounterPanel {
    int bReady;               /* 0x00 */
    int bVisible;             /* 0x04 */
    int aDigit[3][DIGIT_COUNT]; /* 0x08: owned / quantity / quantity on tab 1 */
    u8  pad_2c[0x38 - 0x2c];
    int hExtra;               /* 0x38 */
} Ov008CounterPanel;

typedef struct Ov008WidgetTable {
    int aWidget[7];           /* widget id per item category (3 = special) */
} Ov008WidgetTable;

typedef struct Ov008PanelContext {
    u8   pad_0000[0x5c];
    u8   tagTracker[0x7530 - 0x5c];   /* 0x005c */
    u8   widgets[0xbfb4 - 0x7530];    /* 0x7530: widget manager */
    int  hSlotsB;                     /* 0xbfb4 */
    u8   pad_bfb8[0xc1d8 - 0xbfb8];
    u8   counterSurface[0x3c];        /* 0xc1d8 */
    u8   pad_c214[0xc250 - 0xc214];
    int  nTab;                        /* 0xc250 */
    u8   pad_c254[0xc324 - 0xc254];
    Ov008CounterPanel counter;        /* 0xc324 */
} Ov008PanelContext;

typedef struct GameState {
    u8 pad_0000[0x810];
    u8 aItemCount[0x8d0];     /* 0x810 */
} GameState;

extern Ov008PanelContext *data_ov008_02090fac;
extern GameState *data_0204be18;
extern const Ov008WidgetTable data_ov008_0208ff20;
extern int   func_ov008_0208b7a8(int nItemId);                           /* special item? */
extern void *func_ov008_02055808(void *pTracker, int nTag);              /* ov008_FindEntryByTag */
extern void  func_ov008_0205589c(void *pTracker, void *pEntry);          /* Ov008_TagTracker_InvokeCallback */
extern void  func_0203011c(void *pSurface, int nX, int nY, int nW, int nH); /* Obj_InvokeInnerVtable8: clear */
extern Ov008MenuEntry *func_ov008_02054788(void *pManager, int nId);     /* FindEntryById */
extern void  func_ov008_02054ba4(void *pManager, Ov008MenuEntry *pEntry, int bVisible); /* SetEntrySlotsVisible */
extern void  func_ov008_02054c80(void *pManager, Ov008MenuEntry *pEntry, int nFrame); /* Ov008_ReleaseTwoSlotsEx */
extern void  func_ov008_02082d44(void *pSurface, void *pText, int nX, int nY, int nStyle, int nShadow); /* Ov008_DrawStringShadowed */
extern void  func_02032710(int hSlots, int nCell, int bVisible);         /* Slot_SetVisible */
extern void  func_ov008_020838c8(u32 nValue, int *pCells);               /* Ov008_DrawThreeDigitCounter */

void func_ov008_02083c44(Ov008ParamRecord *pRecord, int nCount)
{
    Ov008WidgetTable table;
    void *pSurface;
    Ov008MenuEntry *pMark;
    int bSpecial;
    Ov008PanelContext *ctx;
    Ov008CounterPanel *pPanel;
    int hSlots;
    void *pWidgets;
    int nOwned;
    int i;
    Ov008MenuEntry *pUp;
    Ov008MenuEntry *pDown;
    Ov008MenuEntry *pQty;
    int bShow;
    int bTab;

    ctx = data_ov008_02090fac;
    hSlots = ctx->hSlotsB;
    table = data_ov008_0208ff20;
    pSurface = ctx->counterSurface;
    pPanel = &ctx->counter;
    pWidgets = ctx->widgets;
    if (pRecord == 0) {
        bSpecial = 0;
    } else {
        bSpecial = func_ov008_0208b7a8(pRecord->pItemDef->nItemId);
    }
    if (pRecord == 0) {
        nOwned = 0;
    } else {
        nOwned = data_0204be18->aItemCount[pRecord->pItemDef->nItemId];
    }
    if (pPanel->bReady == 0) {
        func_ov008_0205589c(ctx->tagTracker, func_ov008_02055808(ctx->tagTracker, TAG_COUNTER));
        func_0203011c(pSurface, 0, 0, 0xb0, 0x30);
        pPanel->bReady = 1;
    }
    for (i = WIDGET_FIRST; i <= WIDGET_LAST; i++) {
        func_ov008_02054ba4(pWidgets, func_ov008_02054788(pWidgets, i), 0);
    }
    if (pRecord != 0) {
        func_ov008_02054ba4(pWidgets, func_ov008_02054788(pWidgets, table.aWidget[bSpecial != 0 ? 3 : pRecord->pItemDef->nCategory]), 1);
    }
    func_0203011c(pSurface, 0, 0, 0xb0, 0x30);
    if (pRecord != 0) {
        func_ov008_02082d44(pSurface, pRecord->pItemDef->pName, 0xd, 0xb, 4, 8);
    }
    for (i = 0; i < DIGIT_COUNT; i++) {
        func_02032710(hSlots, pPanel->aDigit[0][i], 0);
        func_02032710(hSlots, pPanel->aDigit[1][i], 0);
        func_02032710(hSlots, pPanel->aDigit[2][i], 0);
    }
    if (pRecord != 0) {
        func_02032710(hSlots, pPanel->hExtra, bSpecial);
        if (bSpecial == 0) {
            func_ov008_020838c8(nOwned, pPanel->aDigit[0]);
        }
    }
    pMark = func_ov008_02054788(pWidgets, WIDGET_MARK);
    pUp = func_ov008_02054788(pWidgets, WIDGET_UP);
    pDown = func_ov008_02054788(pWidgets, WIDGET_DOWN);
    pQty = func_ov008_02054788(pWidgets, WIDGET_QTY);
    if (bSpecial == 0 && nOwned != nCount && nCount >= 0) {
        func_ov008_02054ba4(pWidgets, pQty, 0);
        func_ov008_02054ba4(pWidgets, pMark, 1);
        if (nOwned < nCount) {
            if (!pDown->bLocked) {
                func_ov008_02054ba4(pWidgets, pDown, 1);
                func_ov008_02054c80(pWidgets, pDown, 0);
            }
            func_ov008_02054ba4(pWidgets, pUp, 0);
        } else {
            if (!pUp->bLocked) {
                func_ov008_02054ba4(pWidgets, pUp, 1);
                func_ov008_02054c80(pWidgets, pUp, 0);
            }
            func_ov008_02054ba4(pWidgets, pDown, 0);
        }
        func_ov008_020838c8(nCount, (&pPanel->aDigit[1])[ctx->nTab != 1]);
    } else {
        func_ov008_02054ba4(pWidgets, pUp, 0);
        func_ov008_02054ba4(pWidgets, pDown, 0);
        func_ov008_02054ba4(pWidgets, pMark, 0);
        bShow = 0;
        bTab = ctx->nTab == 0 || ctx->nTab == 2;
        if (bTab && nOwned == nCount) {
            bShow = 1;
        }
        func_ov008_02054ba4(pWidgets, pQty, bShow);
    }
}
