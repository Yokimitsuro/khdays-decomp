/* func_ov008_0208571c -- Ov008_ShopRefreshSelection: redraw the shop list
 * after the cursor moved.  The visible rows are shown from the scroll
 * (+0xc3c8); the record under the cursor (+0xc3c4) gets its description
 * drawn (a recipe -- kind 3 -- without an item def draws its own text, +0x1c,
 * with icon 0x3f; any other record the text of its item def with the def's
 * icon, +0x24) unless it is a recipe with a level requirement (+0x20) or one
 * past the category's free count (+0xc578) whose byte +0x12 is clear, in
 * which case the description box (+0xc160, 0 / 0xa0, 0x100 x 0x20) is
 * cleared and widget 0x3f hidden.  Widget 1 (the cursor) is moved to row
 * (cursor - scroll) * 16 + 32, the list scrolled to the scroll row, and the
 * eight row tags of the current tab (+0xc250: 0x65 / 0xc9 / 0x12d / 0x191 +
 * i) stamped with the tab's selected / normal mode.  Codegen: the free-count
 * compare reads ctx->view.nRow (a second address path, so the earlier load
 * is not reused); declarations i, nOffset, tab constants, pRecord.
 */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

#define KIND_RECIPE  3
#define ICON_RECIPE  0x3f
#define ROW_COUNT    8
#define WIDGET_DESC  0x3f
#define WIDGET_CURSOR 1

typedef struct UiLayoutPos {
    int nX;
    int nY;
} UiLayoutPos;

typedef struct Ov008ItemDef {
    u8  pad_00[0x24];
    u32 nIcon;                /* 0x24 */
} Ov008ItemDef;

typedef struct Ov008ParamRecord {
    int nKind;                /* 0x00: 3 = recipe */
    u8  pad_04[8];
    Ov008ItemDef *pItemDef;   /* 0x0c */
    u8  pad_10[2];
    u8  nFlag12;              /* 0x12: recipe view */
    u8  pad_13[0x1c - 0x13];
    u16 *pRecipeText;         /* 0x1c: recipe view (no item def) */
    int nLevelReq;            /* 0x20 */
} Ov008ParamRecord;

typedef struct Ov008ShopView {
    int nRow;                 /* 0x00 */
    int nScroll;              /* 0x04 */
    u32 nCount;               /* 0x08 */
    Ov008ParamRecord **apRows; /* 0x0c */
    u8  pad_10[0xf8 - 0x10];
    int nScrollArg;           /* 0xf8 (ctx 0xc4bc) */
} Ov008ShopView;

typedef struct Ov008PanelContext {
    u8  pad_0000[0x10];
    u8  tracker[0x2ab0 - 0x10]; /* 0x0010: tag tracker */
    u8  widgets[0xc160 - 0x2ab0]; /* 0x2ab0: widget context */
    u8  descSurface[0x3c];    /* 0xc160 */
    u8  pad_c19c[0xc250 - 0xc19c];
    int nTab;                 /* 0xc250 */
    u8  pad_c254[0xc3c0 - 0xc254];
    int nCategory;            /* 0xc3c0 */
    Ov008ShopView view;       /* 0xc3c4 */
    u8  pad_c4c0[0xc578 - 0xc4c0];
    u16 aFreeCount[2];        /* 0xc578 */
    u8  pad_c57c[0xc5fc - 0xc57c];
    int textList[3];          /* 0xc5fc */
} Ov008PanelContext;

extern Ov008PanelContext *data_ov008_02090fac;
extern void  func_ov008_02084ebc(Ov008ParamRecord **apRows, u32 nCount, int nFirst); /* Ov008_ShowShopRows */
extern u16  *func_ov008_0208e66c(int *pList, Ov008ItemDef *pItemDef);       /* text of an item def */
extern void  func_ov008_02082fa8(u16 *pText, u32 nIcon);                    /* Ov008_DrawDescriptionText */
extern void  func_0203011c(void *pSurface, int nX, int nY, int nW, int nH); /* Obj_InvokeInnerVtable8 */
extern void *func_ov008_02054788(void *pWidgets, int nId);                  /* FindEntryById */
extern void  func_ov008_02054ba4(void *pWidgets, void *pEntry, int bVisible); /* SetEntrySlotsVisible */
extern UiLayoutPos *func_ov008_02054820(void *pWidgets, void *pEntry);      /* Ov008_GetEntryPos */
extern void  func_ov008_02054858(void *pWidgets, void *pEntry, UiLayoutPos *pPos); /* Ov008_SetEntryPos */
extern void  func_ov008_0208459c(u32 nScroll, int nArg);                    /* Ov008_ScrollListToRow */
extern void *func_ov008_02055808(void *pTracker, u16 nTag);                 /* ov008_FindEntryByTag */
extern void  func_ov008_02055910(void *pTracker, void *pCell, u8 nMode);    /* Ov008_StampTileMode */
extern void  func_ov008_0205589c(void *pTracker, void *pCell);              /* Ov008_TagTracker_InvokeCallback */

void func_ov008_0208571c(void)
{
    Ov008PanelContext *ctx;
    Ov008ShopView *pView;
    u8 *pWidgets;
    int i;
    int nOffset;
    int nTagBase;
    u32 nModeSel;
    u32 nMode;
    Ov008ParamRecord *pRecord;
    u16 *pText;
    u32 nIcon;
    UiLayoutPos pos;
    void *pCell;

    ctx = data_ov008_02090fac;
    pView = &ctx->view;
    pWidgets = ctx->widgets;
    func_ov008_02084ebc(pView->apRows, pView->nCount, pView->nScroll);
    if (pView->apRows != 0) {
        pRecord = pView->apRows[pView->nRow];
        if (pRecord->nKind != KIND_RECIPE
            || (pRecord->nLevelReq == 0 && (ctx->view.nRow < ctx->aFreeCount[ctx->nCategory] || pRecord->nFlag12 != 0))) {
            if (pRecord->nKind == KIND_RECIPE && pRecord->pItemDef == 0) {
                pText = pRecord->pRecipeText;
                nIcon = ICON_RECIPE;
            } else {
                pText = func_ov008_0208e66c(ctx->textList, pRecord->pItemDef);
                nIcon = pRecord->pItemDef->nIcon;
            }
            func_ov008_02082fa8(pText, nIcon);
            goto placed;
        }
    }
    func_0203011c(data_ov008_02090fac->descSurface, 0, 0xa0, 0x100, 0x20);
    func_ov008_02054ba4(data_ov008_02090fac->widgets, func_ov008_02054788(data_ov008_02090fac->widgets, WIDGET_DESC), 0);
placed:
    pos = *func_ov008_02054820(pWidgets, func_ov008_02054788(pWidgets, WIDGET_CURSOR));
    pos.nY = ((pView->nRow - pView->nScroll) * 16 + 0x20) << 12;
    func_ov008_02054858(pWidgets, func_ov008_02054788(pWidgets, WIDGET_CURSOR), &pos);
    func_ov008_0208459c(pView->nScroll, pView->nScrollArg);
    nOffset = pView->nRow - pView->nScroll;
    switch (ctx->nTab) {
    case 0:
        nTagBase = 0x65;
        nModeSel = 4;
        nMode = 3;
        break;
    case 1:
        nTagBase = 0xc9;
        nModeSel = 6;
        nMode = 5;
        break;
    case 2:
        nTagBase = 0x12d;
        nModeSel = 8;
        nMode = 7;
        break;
    case 3:
        nTagBase = 0x191;
        nModeSel = 0xb;
        nMode = 0xa;
        break;
    }
    for (i = 0; i < ROW_COUNT; i++) {
        pCell = func_ov008_02055808(ctx->tracker, (u16)(nTagBase + i));
        func_ov008_02055910(ctx->tracker, pCell, (u8)(i == nOffset ? nModeSel : nMode));
        func_ov008_0205589c(ctx->tracker, pCell);
    }
}
