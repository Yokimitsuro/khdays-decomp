/* func_ov026_02088820 -- Ov008_CanConfirmShopRow: whether the shop's selected
 * row (record list at ctx+0xc3d0, row index at ctx+0xc3c4) can be confirmed
 * on the current tab (ctx+0xc250).  Buy (tab 0): munny (GameState +0xc)
 * covers the price, the owned count of the item is below the record's cap and
 * the record's lock word (+0x28) is clear.  Sell (tab 1): the item is flagged
 * sellable (item def +0x8e == 1) and at least one copy is unequipped.  Redeem
 * (tab 2): the points total (GameState +0x8) covers the price, the record's
 * count plus the owned count fits under the cap, and the record's
 * requirements are met.  Returns 1 / 0.
 * NOTE: the row is read through the view pointer twice (apRows and nRow); mwcc
 * folds the nRow read onto the ctx+0xc000 partial and keeps the apRows one on
 * the materialised ctx+0xc3c4, which is the ROM's prologue.
 */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

#define TAB_BUY    0
#define TAB_SELL   1
#define TAB_REDEEM 2

typedef struct Ov008ItemDef {
    u8  pad_00[0x8e];
    u16 nSellable;            /* 0x8e */
} Ov008ItemDef;

typedef struct Ov008ParamRecord {
    u8            pad_00[0x8];
    u32           nPrice;       /* 0x08 */
    Ov008ItemDef *pItemDef;     /* 0x0c */
    u32           nCount;       /* 0x10 */
    u8            pad_14[0x28 - 0x14];
    int           bLocked;      /* 0x28 */
} Ov008ParamRecord;

typedef struct Ov008ShopView {
    int                nRow;      /* 0xc3c4 */
    u8                 pad_04[8];
    Ov008ParamRecord **apRows;    /* 0xc3d0 */
} Ov008ShopView;

typedef struct Ov008PanelContext {
    u8  pad_0000[0xc250];
    int nTab;                 /* 0xc250 */
    u8  pad_c254[0xc3c4 - 0xc254];
    int nRow;                 /* 0xc3c4 (= Ov008ShopView.nRow) */
} Ov008PanelContext;

typedef struct GameState {
    u8  pad_0000[0x8];
    u32 nPoints;              /* 0x008 */
    u32 nMunny;               /* 0x00c */
    u8  pad_0010[0x810 - 0x10];
    u8  aItemCount[0x8d0];    /* 0x810 */
} GameState;

extern Ov008PanelContext *data_ov026_02091368;
extern GameState *data_0204be18;
extern int func_ov026_0208df6c(Ov008ParamRecord *pRecord);              /* GetChildField14OrNeg1: item id */
extern int func_ov026_020850e4(Ov008ParamRecord *pRecord);              /* stock cap */
extern int func_ov026_0208df80(Ov008ParamRecord *pRecord);              /* Ov008_CountSpareItemsOfChild (u8) */
extern int func_ov026_02085f78(Ov008ParamRecord *pRecord);              /* Ov008_AreRequirementsMet */

int func_ov026_02088820(void)
{
    Ov008PanelContext *ctx;
    Ov008ShopView *pView;
    Ov008ParamRecord *pRecord;
    int nTab;
    int nItem;
    int nCap;

    ctx = data_ov026_02091368;
    pView = (Ov008ShopView *)((u8 *)ctx + 0xc3c4);
    nTab = ctx->nTab;
    pRecord = pView->apRows[pView->nRow];
    switch (nTab) {
    case TAB_BUY:
        if (data_0204be18->nMunny >= pRecord->nPrice) {
            nItem = func_ov026_0208df6c(pRecord);
            nCap = func_ov026_020850e4(pRecord);
            if (data_0204be18->aItemCount[nItem] < nCap && pRecord->bLocked == 0) {
                return 1;
            }
        }
        break;
    case TAB_SELL:
        if (pRecord->pItemDef->nSellable == 1 && func_ov026_0208df80(pRecord) > 0) {
            return 1;
        }
        break;
    case TAB_REDEEM:
        if (data_0204be18->nPoints >= pRecord->nPrice) {
            nItem = func_ov026_0208df6c(pRecord);
            nCap = func_ov026_020850e4(pRecord);
            if (pRecord->nCount + data_0204be18->aItemCount[nItem] <= (u32)nCap) {
                return func_ov026_02085f78(pRecord);
            }
        }
        break;
    }
    return 0;
}
