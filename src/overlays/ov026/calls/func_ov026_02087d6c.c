/* func_ov026_02087d6c -- Ov008_ShowShopRows: lay the shop list region out
 * (ctx+0xc160: 0x20, 0x18, 0xc0, 0x80) and hide the eight rows' cells of the
 * shop view (ctx+0xc3c4: seven arrays of eight cells from +0x18): on tab 3 the
 * +0x98 and +0x78 cells, on tab 0 the +0xb8 cells, and always the +0x18, +0x38,
 * +0x58 and +0xd8 cells.  Then, given a record pointer list, draws up to eight
 * rows from apRows[nFirst + i] while that index is below nCount (row text via
 * 020848e8, row icon via 02084b10).
 */
typedef unsigned char u8;
typedef unsigned int  u32;

#define ROW_COUNT 8
#define TAB_BUY   0
#define TAB_NONE  3

typedef struct Ov008ShopView {
    u8  pad_00[0x18];
    int aCellA[ROW_COUNT];    /* 0x18 */
    int aCellB[ROW_COUNT];    /* 0x38 */
    int aCellC[ROW_COUNT];    /* 0x58 */
    int aCellD[ROW_COUNT];    /* 0x78 */
    int aCellE[ROW_COUNT];    /* 0x98 */
    int aCellF[ROW_COUNT];    /* 0xb8 */
    int aCellG[ROW_COUNT];    /* 0xd8 */
} Ov008ShopView;

typedef struct Ov008PanelContext {
    u8  pad_0000[0xbfb0];
    int hSlots;               /* 0xbfb0 */
    u8  pad_bfb4[0xc160 - 0xbfb4];
    u8  textSurface[0xc250 - 0xc160]; /* 0xc160 */
    int nTab;                 /* 0xc250 */
} Ov008PanelContext;

extern Ov008PanelContext *data_ov026_02091368;
extern void func_0203011c(void *pRegion, int nX, int nY, int nW, int nH);
extern void func_02032710(int hSlots, int nCell, int bVisible);          /* Slot_SetVisible */
extern void func_ov026_02087798(int nRow, void *pRecord);                /* draw the row text */
extern void func_ov026_020879c0(int nRow, void *pRecord);                /* draw the row icon */

void func_ov026_02087d6c(void **apRows, u32 nCount, int nFirst)
{
    Ov008PanelContext *ctx;
    int hSlots;
    Ov008ShopView *pView;
    int i;
    u32 nIndex;

    ctx = data_ov026_02091368;
    hSlots = ctx->hSlots;
    pView = (Ov008ShopView *)((u8 *)ctx + 0xc3c4);
    func_0203011c(ctx->textSurface, 0x20, 0x18, 0xc0, 0x80);
    for (i = 0; i < ROW_COUNT; i++) {
        if (data_ov026_02091368->nTab == TAB_NONE) {
            func_02032710(hSlots, pView->aCellE[i], 0);
            func_02032710(hSlots, pView->aCellD[i], 0);
        } else if (data_ov026_02091368->nTab == TAB_BUY) {
            func_02032710(hSlots, pView->aCellF[i], 0);
        }
        func_02032710(hSlots, pView->aCellA[i], 0);
        func_02032710(hSlots, pView->aCellB[i], 0);
        func_02032710(hSlots, pView->aCellC[i], 0);
        func_02032710(hSlots, pView->aCellG[i], 0);
    }
    if (apRows == 0) {
        return;
    }
    for (i = 0; i < ROW_COUNT; i++) {
        nIndex = nFirst + i;
        if (nIndex >= nCount) {
            return;
        }
        func_ov026_02087798(i, apRows[nIndex]);
        func_ov026_020879c0(i, apRows[nIndex]);
    }
}
