/* func_ov008_020850c0 -- Ov008_SetupShopPage: build the shop panel for the
 * current tab (+0xc250).  The tab's tier page (0208500c: widget ids, tag
 * ids, list id and column) is shown, then eight row cells are created on
 * the slot manager (+0xbfb0) at x 0x30 (0xb6 on the reward tab) and y 2 +
 * row: the row's two icon cells (kinds 1 / 2, or 3 / 4 on the reward tab)
 * with mode bit 2 cleared, its text cell (kind 0 at the panel's row +0xe),
 * on the reward tab a kind-7 cell at x 0xc1 and a kind-0x17 cell at x 0xb6,
 * on the shop tab a kind-8 cell at x 0xb4, and off the reward tab a kind-0xb
 * cell at (0x25, y + 0.25).  Widgets 0x33 / 0x34 show at their blocks (one
 * column apart on the reward tab); off it widgets 0x28 .. 0x2f show at
 * their blocks too, pulled 0x18 columns left of widget 0x2c's block on the
 * recipe tab, which skips 0x2c / 0x2e.  The view's scroll argument (+0xf8),
 * +0xfc and ready flag (+0x100) reset; the reward tab counts the affordable
 * rewards (0208b6a8) into the buy dialog's funds (+0xc578, + 3 each).  With
 * bKeep the category (+0xc3c0) restarts at 0; categories are advanced until
 * a list builds (020846c0), wrapping at the tab's limit (5 / 2 / 8) with a
 * forced rebuild of category 0.  The rows are shown (02084ebc), the list
 * reset (020844cc) -- and scrolled to 0 without bKeep, or refreshed
 * (020869a4) on the recipe tab with rows -- and widget 1 goes to (0x28, or
 * 0x18 on the reward tab; 0x20 + 16 * (row - scroll)) and shows; the scroll
 * arrows update (02085a9c).  Codegen: the context pointer, the argument,
 * the limit and the buy dialog pointer are spilled; the locals are set in
 * the order view, buy dialog, state, slots, widgets (view / state / slots /
 * tab colour r5 .. r8); the x table is a two-entry local indexed by the
 * reward-tab test, its first entry reused for the text cell and, less 0xb
 * tiles, for the price cell (both hoisted and spilled); the row y is a
 * stepped local; the cells are stored straight into the view and re-read
 * for the mode-bit calls; the tab limit and the tier switch are switches;
 * the non-reward widget branch is written first; the block positions are
 * struct copies (adjusted after the copy), the anchor's x cached; the later
 * tab tests re-read the context.
 */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;
typedef signed short   s16;

#define TAB_SHOP    0
#define TAB_ITEMS   1
#define TAB_RECIPES 2
#define TAB_REWARDS 3
#define ROW_COUNT   8
#define ROW_Y_FIRST (2 << 16)
#define ROW_Y_STEP  (1 << 16)
#define WIDGET_CURSOR 1
#define WIDGET_LEFT   0x33
#define WIDGET_RIGHT  0x34
#define WIDGET_TAB_FIRST 0x28
#define WIDGET_TAB_LAST  0x2f
#define WIDGET_TAB_ANCHOR 0x2c
#define ROW_HEIGHT  16

typedef struct UiLayoutPos {
    int nX;
    int nY;
} UiLayoutPos;

typedef struct Ov008ParamRecord Ov008ParamRecord;

typedef struct Ov008ShopView {
    int nRow;                 /* 0x00 (ctx 0xc3c4) */
    int nScroll;              /* 0x04 */
    u32 nCount;               /* 0x08 */
    Ov008ParamRecord **apRows; /* 0x0c */
    u8  pad_10[8];
    int aCellText[ROW_COUNT]; /* 0x18: kind 0 */
    int aCellIconA[ROW_COUNT]; /* 0x38: kind 1 / 3 */
    int aCellIconB[ROW_COUNT]; /* 0x58: kind 2 / 4 */
    int aCellRewardA[ROW_COUNT]; /* 0x78: kind 7 */
    int aCellRewardB[ROW_COUNT]; /* 0x98: kind 0x17 */
    int aCellShop[ROW_COUNT]; /* 0xb8: kind 8 */
    int aCellPrice[ROW_COUNT]; /* 0xd8: kind 0xb */
    int nScrollArg;           /* 0xf8 (ctx 0xc4bc) */
    int nScrollPending;       /* 0xfc */
    int bListReady;           /* 0x100 (ctx 0xc4c4) */
} Ov008ShopView;

typedef struct Ov008ShopState {
    u8  pad_00[8];
    int nCategory;            /* 0x08 (ctx 0xc3c0) */
    Ov008ShopView view;       /* 0x0c (ctx 0xc3c4) */
} Ov008ShopState;

typedef struct Ov008BuyDialog {
    u8  pad_00[0x2c];
    u16 aFunds[2];            /* 0x2c (ctx 0xc578): per reward list */
} Ov008BuyDialog;

typedef struct Ov008PanelContext {
    u8   pad_0000[0xe];
    s16  nRow;                /* 0x000e */
    u8   pad_0010[0x2ab0 - 0x10];
    u8   widgets[0xbfb0 - 0x2ab0]; /* 0x2ab0: widget context */
    int  hSlots;              /* 0xbfb0 */
    u8   pad_bfb4[0xc250 - 0xbfb4];
    int  nTab;                /* 0xc250 */
    u8   pad_c254[0xc3b8 - 0xc254];
    Ov008ShopState shop;      /* 0xc3b8 */
    u8   pad_c4c8[0xc54c - 0xc4c8];
    Ov008BuyDialog buy;       /* 0xc54c */
} Ov008PanelContext;

extern Ov008PanelContext *data_ov008_02090fac;
extern void  func_ov008_0208500c(int nWidgetA, int nWidgetB, int nTag, int nList, int nText, int nColumn); /* Ov008_ShowTierPage */
extern int   func_ov008_02082ecc(int hSlots, int nKind, int nSlot, int nX, int nY); /* create a cell */
extern void  func_0203281c(int hSlots, int nCell, int bSet);           /* Slot_SetMode2Bit */
extern void *func_ov008_02054788(void *pWidgets, int nId);             /* FindEntryById */
extern void  func_ov008_02054ba4(void *pWidgets, void *pEntry, int bVisible); /* SetEntrySlotsVisible */
extern UiLayoutPos *func_ov008_0205489c(void *pWidgets, void *pEntry); /* Ov008_GetEntryBlock2c */
extern void  func_ov008_02054858(void *pWidgets, void *pEntry, UiLayoutPos *pPos); /* Ov008_SetEntryPos */
extern void  func_ov008_0208b6a8(u16 *aCount);                         /* Ov008_CountAffordableRecords */
extern int   func_ov008_020846c0(int bKeep, int bForce);               /* Ov008_RebuildShopList */
extern void  func_ov008_02084ebc(Ov008ParamRecord **apRows, u32 nCount, int nFirst); /* Ov008_ShowShopRows */
extern void  func_ov008_020869a4(void);                                /* refresh the recipe rows */
extern void  func_ov008_020844cc(u32 nCount);                          /* Ov008_ResetListTo */
extern void  func_ov008_0208459c(u32 nScroll, int nArg);               /* Ov008_ScrollListToRow */
extern void  func_ov008_02085a9c(void);                                /* Ov008_UpdateScrollArrows */

void func_ov008_020850c0(int bKeep)
{
    UiLayoutPos pos;
    UiLayoutPos anchor;
    int aX[2];
    Ov008PanelContext *ctx;
    Ov008ShopView *pView;
    Ov008ShopState *pShop;
    int hSlots;
    int nTab;
    Ov008BuyDialog *pBuy;
    u8 *pWidgets;
    int nLimit;
    int nX;
    int nY;
    int i;
    int nKind;
    void *pLeft;
    void *pRight;
    void *pEntry;
    UiLayoutPos *pBlock;
    int nId;
    int nPage;

    ctx = data_ov008_02090fac;
    nTab = ctx->nTab;
    pView = &ctx->shop.view;
    pBuy = &ctx->buy;
    pShop = &ctx->shop;
    hSlots = ctx->hSlots;
    pWidgets = ctx->widgets;
    switch (nTab) {
    case TAB_RECIPES:
        nLimit = 5;
        break;
    case TAB_REWARDS:
        nLimit = 2;
        break;
    default:
        nLimit = 8;
        break;
    }
    switch (ctx->nTab) {
    case TAB_SHOP:
        func_ov008_0208500c(0x6f, 0x79, 0x3ea, 100, 0x65, 3);
        break;
    case TAB_ITEMS:
        func_ov008_0208500c(0xd3, 0xdd, 0x3eb, 200, 0xc9, 5);
        break;
    case TAB_RECIPES:
        func_ov008_0208500c(0x137, 0x141, 0x3ec, 300, 0x12d, 7);
        break;
    case TAB_REWARDS:
        func_ov008_0208500c(0x19a, 0x1a5, 0x3ed, 400, 0x191, 10);
        break;
    }
    aX[0] = 0x30 << 12;
    aX[1] = 0xb6 << 12;
    nX = aX[nTab == TAB_REWARDS];
    nY = ROW_Y_FIRST;
    for (i = 0; i < ROW_COUNT; i++) {
        if (nTab == TAB_REWARDS) {
            nKind = 3;
        } else {
            nKind = 1;
        }
        pView->aCellIconA[i] = func_ov008_02082ecc(hSlots, nKind, 1, nX, nY);
        if (nTab == TAB_REWARDS) {
            nKind = 4;
        } else {
            nKind = 2;
        }
        pView->aCellIconB[i] = func_ov008_02082ecc(hSlots, nKind, 1, nX, nY);
        func_0203281c(hSlots, pView->aCellIconA[i], 0);
        func_0203281c(hSlots, pView->aCellIconB[i], 0);
        pView->aCellText[i] = func_ov008_02082ecc(hSlots, 0, ctx->nRow, aX[0], nY);
        if (nTab == TAB_REWARDS) {
            pView->aCellRewardA[i] = func_ov008_02082ecc(hSlots, 7, 1, 0xc1 << 12, nY);
            func_0203281c(hSlots, pView->aCellRewardA[i], 0);
            pView->aCellRewardB[i] = func_ov008_02082ecc(hSlots, 0x17, 0, 0xb6 << 12, nY);
            func_0203281c(hSlots, pView->aCellRewardB[i], 0);
        } else if (nTab == TAB_SHOP) {
            pView->aCellShop[i] = func_ov008_02082ecc(hSlots, 8, 1, 0xb4 << 12, nY);
            func_0203281c(hSlots, pView->aCellShop[i], 0);
        }
        if (nTab != TAB_REWARDS) {
            pView->aCellPrice[i] = func_ov008_02082ecc(hSlots, 0xb, 1, aX[0] - (0xb << 12), nY + 0x4000);
            func_0203281c(hSlots, pView->aCellPrice[i], 0);
        }
        nY += ROW_Y_STEP;
    }
    pLeft = func_ov008_02054788(pWidgets, WIDGET_LEFT);
    pRight = func_ov008_02054788(pWidgets, WIDGET_RIGHT);
    func_ov008_02054ba4(pWidgets, pLeft, 1);
    func_ov008_02054ba4(pWidgets, pRight, 1);
    if (nTab != TAB_REWARDS) {
        func_ov008_02054858(pWidgets, pLeft, func_ov008_0205489c(pWidgets, pLeft));
        func_ov008_02054858(pWidgets, pRight, func_ov008_0205489c(pWidgets, pRight));
        pEntry = func_ov008_02054788(pWidgets, WIDGET_TAB_ANCHOR);
        anchor = *func_ov008_0205489c(pWidgets, pEntry);
        for (nId = WIDGET_TAB_FIRST; nId <= WIDGET_TAB_LAST; nId++) {
            if (nTab == TAB_RECIPES && (nId == 0x2c || nId == 0x2e)) {
                continue;
            }
            func_ov008_02054ba4(pWidgets, func_ov008_02054788(pWidgets, nId), 1);
            pos = *func_ov008_0205489c(pWidgets, func_ov008_02054788(pWidgets, nId));
            if (nTab == TAB_RECIPES && pos.nX > anchor.nX) {
                pos.nX -= 0x18 << 12;
            }
            func_ov008_02054858(pWidgets, func_ov008_02054788(pWidgets, nId), &pos);
        }
    } else {
        pBlock = func_ov008_0205489c(pWidgets, pLeft);
        pos = *pBlock;
        pos.nX -= 1 << 16;
        func_ov008_02054858(pWidgets, pLeft, &pos);
        pBlock = func_ov008_0205489c(pWidgets, pRight);
        pos = *pBlock;
        pos.nX += 1 << 16;
        func_ov008_02054858(pWidgets, pRight, &pos);
    }
    pView->nScrollArg = 0;
    pView->nScrollPending = 0;
    pView->bListReady = 1;
    if (nTab == TAB_REWARDS) {
        func_ov008_0208b6a8(pBuy->aFunds);
        pBuy->aFunds[0] += 3;
        pBuy->aFunds[1] += 3;
    }
    if (bKeep != 0) {
        pShop->nCategory = 0;
    }
    if (func_ov008_020846c0(bKeep, 0) == 0) {
        do {
            nPage = ++pShop->nCategory;
            if (nPage >= nLimit) {
                pShop->nCategory = 0;
                break;
            }
        } while (func_ov008_020846c0(bKeep, 0) == 0);
        if (pShop->nCategory == 0) {
            func_ov008_020846c0(bKeep, 1);
        }
    }
    if (bKeep != 0) {
        func_ov008_02084ebc(pView->apRows, pView->nCount, pView->nScroll);
        if (ctx->nTab == TAB_RECIPES && pView->apRows != 0) {
            func_ov008_020869a4();
        }
        func_ov008_020844cc(pView->nCount);
    } else {
        func_ov008_02084ebc(pView->apRows, pView->nCount, pView->nScroll);
        func_ov008_020844cc(pView->nCount);
        func_ov008_0208459c(pView->nScroll, 0);
    }
    pEntry = func_ov008_02054788(pWidgets, WIDGET_CURSOR);
    if (ctx->nTab == TAB_REWARDS) {
        pos.nX = 0x18 << 12;
    } else {
        pos.nX = 0x28 << 12;
    }
    pos.nY = ((pView->nRow - pView->nScroll) * ROW_HEIGHT + 0x20) << 12;
    func_ov008_02054858(pWidgets, pEntry, &pos);
    func_ov008_02054ba4(pWidgets, pEntry, 1);
    func_ov008_02085a9c();
}
