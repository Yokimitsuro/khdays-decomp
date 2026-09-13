/* func_ov008_02085b10 -- Ov008_HideShopList: tear the shop list display
 * down before a tab switch.  Widgets 0x28..0x2f are hidden, the description
 * box (+0xc160) framed at (0x20, 0x18, 0xc0 x 0x80), the two pixel buffers
 * (+0x18a8, 0x600 bytes and +0x1ea8, 0x500 bytes) cleared and bits 4 / 5 of
 * the flag word (+0x2aac) raised.  For each of the eight rows the row tag
 * (0x191 + i on the recipe tab, else 0x65 + i) gets its callback invoked and
 * the row's cells unlinked: B, C and A always, D and E on the recipe tab, F
 * on tab 0 and G on every other tab.  Widget 0x3f is hidden; on tab 2 with a
 * pending handler (+0xc3d8) other than 02089410 the description box is
 * cleared (0, 0xa0, 0x100 x 0x20), widget 0x3f hidden again and the menu
 * screen set up, while the recipe tab runs 02087884.  Finally widgets 1,
 * 0x33, 0x34, 4 and 5 are hidden and the list cells hidden.
 */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

#define ROW_COUNT   8
#define TAB_RECIPES 3
#define ROW_TAG_BASE        0x65
#define ROW_TAG_BASE_RECIPE 0x191
#define WIDGET_ROW_FIRST 0x28
#define WIDGET_ROW_LAST  0x2f
#define WIDGET_DESC 0x3f
#define FLAGS_LIST_HIDDEN 0x30

typedef struct Ov008ShopView {
    u8  pad_00[0x14];
    void *pfnPending;         /* 0x14 (ctx 0xc3d8) */
    int aCellA[ROW_COUNT];    /* 0x18 */
    int aCellBC[2][ROW_COUNT]; /* 0x38 / 0x58 */
    int aCellD[ROW_COUNT];    /* 0x78 */
    int aCellE[ROW_COUNT];    /* 0x98 */
    int aCellF[ROW_COUNT];    /* 0xb8 */
    int aCellG[ROW_COUNT];    /* 0xd8 */
} Ov008ShopView;

typedef struct Ov008PanelContext {
    u8  pad_0000[0x10];
    u8  tracker[0x18a8 - 0x10]; /* 0x0010: primary tag tracker */
    u8  pixelsA[0x600];       /* 0x18a8 */
    u8  pixelsB[0x500];       /* 0x1ea8 */
    u8  pad_23a8[0x2aac - 0x23a8];
    u32 nFlags;               /* 0x2aac */
    u8  widgets[0xbfb0 - 0x2ab0]; /* 0x2ab0 */
    int hSlots;               /* 0xbfb0 */
    u8  pad_bfb4[0xc160 - 0xbfb4];
    u8  descSurface[0x3c];    /* 0xc160 */
    u8  pad_c19c[0xc250 - 0xc19c];
    int nTab;                 /* 0xc250 */
    u8  pad_c254[0xc3c4 - 0xc254];
    Ov008ShopView view;       /* 0xc3c4 */
} Ov008PanelContext;

extern Ov008PanelContext *data_ov008_02090fac;
extern void *func_ov008_02054788(void *pWidgets, int nId);                  /* FindEntryById */
extern void  func_ov008_02054ba4(void *pWidgets, void *pEntry, int bVisible); /* SetEntrySlotsVisible */
extern void  func_0203011c(void *pSurface, int nX, int nY, int nW, int nH); /* Obj_InvokeInnerVtable8 */
extern void  INITi_CpuClear32_0x01ff86fc(int nValue, void *pDst, u32 nSize);
extern void *func_ov008_02055808(void *pTracker, u16 nTag);                 /* ov008_FindEntryByTag */
extern void  func_ov008_020558f4(void *pTracker, void *pCell);              /* ov008_InvokeCallback40 */
extern void  func_02032450(int hSlots, int nCell);                          /* Slot_UnlinkIfLinked */
extern void  func_ov008_02086da4(void);                                     /* Ov008_SetupMenuScreen */
extern void  func_ov008_02087884(void);                                     /* Ov008_Set_7884 */
extern void  func_ov008_02084384(void);                                     /* Ov008_HideListCells */
extern void *func_ov008_02089410(void);                                     /* detail confirm entry */

void func_ov008_02085b10(void)
{
    Ov008PanelContext *ctx;
    int i;
    Ov008ShopView *pView;
    int hSlots;
    int nTab;
    u8 *pWidgets;
    u8 *pSurface;
    void *pCell;

    ctx = data_ov008_02090fac;
    pView = &ctx->view;
    hSlots = ctx->hSlots;
    nTab = ctx->nTab;
    pWidgets = ctx->widgets;
    pSurface = ctx->descSurface;
    for (i = WIDGET_ROW_FIRST; i <= WIDGET_ROW_LAST; i++) {
        func_ov008_02054ba4(pWidgets, func_ov008_02054788(pWidgets, i), 0);
    }
    func_0203011c(pSurface, 0x20, 0x18, 0xc0, 0x80);
    INITi_CpuClear32_0x01ff86fc(0, ctx->pixelsA, 0x600);
    INITi_CpuClear32_0x01ff86fc(0, ctx->pixelsB, 0x500);
    ctx->nFlags |= FLAGS_LIST_HIDDEN;
    for (i = 0; i < ROW_COUNT; i++) {
        pCell = func_ov008_02055808(ctx->tracker, (u16)(i + (nTab == TAB_RECIPES ? ROW_TAG_BASE_RECIPE : ROW_TAG_BASE)));
        func_ov008_020558f4(ctx->tracker, pCell);
        func_02032450(hSlots, pView->aCellBC[0][i]);
        func_02032450(hSlots, pView->aCellBC[1][i]);
        func_02032450(hSlots, pView->aCellA[i]);
        if (nTab == TAB_RECIPES) {
            func_02032450(hSlots, pView->aCellD[i]);
            func_02032450(hSlots, pView->aCellE[i]);
        } else if (nTab == 0) {
            func_02032450(hSlots, pView->aCellF[i]);
        }
        if (nTab != TAB_RECIPES) {
            func_02032450(hSlots, pView->aCellG[i]);
        }
    }
    func_ov008_02054ba4(pWidgets, func_ov008_02054788(pWidgets, WIDGET_DESC), 0);
    if (nTab == 2 && pView->pfnPending != func_ov008_02089410) {
        func_0203011c(data_ov008_02090fac->descSurface, 0, 0xa0, 0x100, 0x20);
        func_ov008_02054ba4(data_ov008_02090fac->widgets, func_ov008_02054788(data_ov008_02090fac->widgets, WIDGET_DESC), 0);
        func_ov008_02086da4();
    } else if (nTab == TAB_RECIPES) {
        func_ov008_02087884();
    }
    func_ov008_02054ba4(pWidgets, func_ov008_02054788(pWidgets, 1), 0);
    func_ov008_02054ba4(pWidgets, func_ov008_02054788(pWidgets, 0x33), 0);
    func_ov008_02054ba4(pWidgets, func_ov008_02054788(pWidgets, 0x34), 0);
    func_ov008_02054ba4(pWidgets, func_ov008_02054788(pWidgets, 4), 0);
    func_ov008_02054ba4(pWidgets, func_ov008_02054788(pWidgets, 5), 0);
    func_ov008_02084384();
}
