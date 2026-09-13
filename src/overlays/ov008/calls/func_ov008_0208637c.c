/* func_ov008_0208637c -- Ov008_DrawSellDialog: redraw the shop's quantity
 * dialog (+0xc4c8) on the dialog surface (+0xc160, frame 0x28, 0x38, 0xb0 x
 * 0x60).  The total is the record's price (+0x8) times the count (+0xc):
 * on tab 0 (+0xc250) it is subtracted through the column panel's right base
 * (+0xc320) under variable text 1, on other tabs added to the left base
 * (+0xc31c) under text 0.  The item name (def +0xc) goes at (0x44, 0x48)
 * and the price at x 0xb0; with font +0xc148 the label is drawn at (0xb2,
 * 0x4a) and (0xb2, 0x5e); back on font +0xc13c texts 2 / 4 go at (0x34,
 * 0x5c) / (0x61, 0x5c), the count at x 0x78 and the total at x 0xb0.  The
 * four choice cells (+0xc5e0) show "selection (+0x1c) set and choice
 * (+0x1f) 0 / not 0 / 1 / not 1".  Selection 0 with a pending flag (+0x1e
 * low nibble, a bitfield) hides widget 1 and shows / reruns widget 6 (manager +0x2ab0);
 * selection 1 does the opposite and draws the two texts (+0x20 / +0x24) at
 * (0x50, 0x77) / (0xb0, 0x77), then, like selection 2, moves widget 1 to
 * x = (0x20 or 0x80 by the choice) << 12 keeping its y; selection 2 then
 * resets to 0 and returns.  Otherwise the pending nibble is cleared.
 * Codegen: locals assigned in the order pDialog, hSlots, pSurface,
 * pWidgets; the label pointer and the total are locals chosen in the tab
 * if/else; the "== 0" cell tests are if/else, the "!= 0" ones inline bools;
 * the pending nibble is a 4-bit bitfield; case 1 falls into case 2.
 */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;
typedef signed short   s16;

#define TEXT_STYLE   4
#define LABEL_STYLE  2
#define WIDGET_QTY   1
#define WIDGET_CONFIRM 6

typedef struct UiLayoutPos {
    int nX;
    int nY;
} UiLayoutPos;

typedef struct Ov008ItemDef {
    u8    pad_00[0xc];
    void *pName;              /* 0x0c */
} Ov008ItemDef;

typedef struct Ov008ParamRecord {
    u8            pad_00[8];
    u32           nPrice;     /* 0x08 */
    Ov008ItemDef *pItemDef;   /* 0x0c */
} Ov008ParamRecord;

typedef struct Ov008SellDialog {
    Ov008ParamRecord *pRecord; /* 0x00 (0xc4c8) */
    u8    pad_04[8];
    int   nCount;             /* 0x0c (0xc4d4) */
    u8    pad_10[0xc];
    s16   nSelection;         /* 0x1c (0xc4e4) */
    u8    nPending : 4;       /* 0x1e: widgets pending */
    u8    nHigh : 4;
    u8    nChoice;            /* 0x1f */
    void *pTextLeft;          /* 0x20 */
    void *pTextRight;         /* 0x24 */
} Ov008SellDialog;

typedef struct Ov008RenderSurface {
    u8    pad_00[0x20];
    void *pFont;              /* 0x20 */
    u8    pad_24[0x3c - 0x24];
} Ov008RenderSurface;

typedef struct Ov008ColumnPanel {
    int  aCell[6][8];         /* 0x00 */
    int  nLeftSelected;       /* 0xc0 */
    int  nRightSelected;      /* 0xc4 */
    int  nLeftBase;           /* 0xc8 */
    int  nRightBase;          /* 0xcc */
} Ov008ColumnPanel;

typedef struct Ov008PanelContext {
    u8   pad_0000[0x2ab0];
    u8   widgets[0xbfb0 - 0x2ab0]; /* 0x2ab0: widget context */
    int  hSlots;              /* 0xbfb0 */
    u8   pad_bfb4[0xc13c - 0xbfb4];
    u8   fontA[0xc];          /* 0xc13c */
    u8   fontB[0xc];          /* 0xc148 */
    u8   fontC[0xc];          /* 0xc154 */
    Ov008RenderSurface dialogSurface; /* 0xc160 */
    u8   pad_c19c[0xc250 - 0xc19c];
    int  nTab;                /* 0xc250 */
    Ov008ColumnPanel columns; /* 0xc254 */
    u8   pad_c324[0xc4c8 - 0xc324];
    Ov008SellDialog sell;     /* 0xc4c8 */
    u8   pad_c4f0[0xc5c8 - 0xc4f0];
    void *apVarText[5];       /* 0xc5c8 */
    u8   pad_c5dc[4];
    int  aChoiceCell[4];      /* 0xc5e0 */
} Ov008PanelContext;

extern Ov008PanelContext *data_ov008_02090fac;
extern void  func_0203011c(void *pSurface, int nX, int nY, int nW, int nH);            /* Obj_InvokeInnerVtable8 */
extern void  func_ov008_02082d44(void *pSurface, void *pText, int nX, int nY, int nStyle, int nShadow); /* Ov008_DrawStringShadowed */
extern void  func_ov008_02082d98(void *pSurface, u32 nValue, int nX, int nY, int nStyle); /* draw a number */
extern void  func_02032710(int hSlots, int nCell, int bVisible);                        /* Slot_SetVisible */
extern void *func_ov008_02054788(void *pWidgets, int nId);                              /* FindEntryById */
extern void  func_ov008_02054ba4(void *pWidgets, void *pEntry, int bVisible);           /* SetEntrySlotsVisible */
extern void  func_ov008_02054c80(void *pWidgets, void *pEntry, int nFrame);             /* Ov008_ReleaseTwoSlotsEx */
extern UiLayoutPos *func_ov008_02054820(void *pWidgets, void *pEntry);                  /* Ov008_GetEntryPos */
extern void  func_ov008_02054858(void *pWidgets, void *pEntry, UiLayoutPos *pPos);      /* Ov008_SetEntryPos */

void func_ov008_0208637c(void)
{
    Ov008PanelContext *ctx;
    Ov008SellDialog *pDialog;
    int hSlots;
    Ov008RenderSurface *pSurface;
    u8 *pWidgets;
    u32 nPrice;
    u32 nTotal;
    void *pLabel;
    int bShow;
    UiLayoutPos pos;

    ctx = data_ov008_02090fac;
    pDialog = &ctx->sell;
    hSlots = ctx->hSlots;
    pSurface = &ctx->dialogSurface;
    pWidgets = ctx->widgets;
    nPrice = pDialog->pRecord->nPrice;
    func_0203011c(pSurface, 0x28, 0x38, 0xb0, 0x60);
    nTotal = nPrice * pDialog->nCount;
    if (ctx->nTab == 0) {
        pLabel = data_ov008_02090fac->apVarText[1];
        ctx->columns.nRightBase = -nTotal;
    } else {
        pLabel = data_ov008_02090fac->apVarText[0];
        ctx->columns.nLeftBase = nTotal;
    }
    func_ov008_02082d44(pSurface, pDialog->pRecord->pItemDef->pName, 0x44, 0x48, TEXT_STYLE, 8);
    func_ov008_02082d98(pSurface, nPrice, 0xb0, 0x48, TEXT_STYLE);
    pSurface->pFont = ctx->fontB;
    func_ov008_02082d44(pSurface, pLabel, 0xb2, 0x4a, LABEL_STYLE, 8);
    func_ov008_02082d44(pSurface, pLabel, 0xb2, 0x5e, LABEL_STYLE, 8);
    pSurface->pFont = ctx->fontA;
    func_ov008_02082d44(pSurface, data_ov008_02090fac->apVarText[2], 0x34, 0x5c, TEXT_STYLE, 8);
    func_ov008_02082d44(pSurface, data_ov008_02090fac->apVarText[4], 0x61, 0x5c, TEXT_STYLE, 8);
    func_ov008_02082d98(pSurface, pDialog->nCount, 0x78, 0x5c, TEXT_STYLE);
    func_ov008_02082d98(pSurface, nTotal, 0xb0, 0x5c, TEXT_STYLE);
    if (pDialog->nSelection != 0 && pDialog->nChoice == 0) {
        bShow = 1;
    } else {
        bShow = 0;
    }
    func_02032710(hSlots, ctx->aChoiceCell[0], bShow);
    func_02032710(hSlots, ctx->aChoiceCell[1], pDialog->nSelection != 0 && pDialog->nChoice != 0);
    if (pDialog->nSelection != 0 && pDialog->nChoice == 1) {
        bShow = 1;
    } else {
        bShow = 0;
    }
    func_02032710(hSlots, ctx->aChoiceCell[2], bShow);
    func_02032710(hSlots, ctx->aChoiceCell[3], pDialog->nSelection != 0 && pDialog->nChoice != 1);
    switch (pDialog->nSelection) {
    case 0:
        if (pDialog->nPending != 0) {
            func_ov008_02054ba4(pWidgets, func_ov008_02054788(pWidgets, WIDGET_QTY), 0);
            func_ov008_02054ba4(pWidgets, func_ov008_02054788(pWidgets, WIDGET_CONFIRM), 1);
            func_ov008_02054c80(pWidgets, func_ov008_02054788(pWidgets, WIDGET_CONFIRM), 0);
        }
        break;
    case 1:
        if (pDialog->nPending != 0) {
            func_ov008_02054ba4(pWidgets, func_ov008_02054788(pWidgets, WIDGET_CONFIRM), 0);
            func_ov008_02054ba4(pWidgets, func_ov008_02054788(pWidgets, WIDGET_QTY), 1);
        }
        func_ov008_02082d44(pSurface, pDialog->pTextLeft, 0x50, 0x77, TEXT_STYLE, 0x10);
        func_ov008_02082d44(pSurface, pDialog->pTextRight, 0xb0, 0x77, TEXT_STYLE, 0x10);
    case 2:
        pos.nX = ((pDialog->nChoice == 0 ? 0 : 0x60) + 0x20) << 12;
        pos.nY = func_ov008_02054820(pWidgets, func_ov008_02054788(pWidgets, WIDGET_QTY))->nY;
        func_ov008_02054858(pWidgets, func_ov008_02054788(pWidgets, WIDGET_QTY), &pos);
        if (pDialog->nSelection == 2) {
            pDialog->nSelection = 0;
            return;
        }
        break;
    }
    pDialog->nPending = 0;
}
