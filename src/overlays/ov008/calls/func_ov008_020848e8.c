/* func_ov008_020848e8 -- Ov008_DrawShopRowMarks: show the marker cells of
 * shop row nRow for record pRecord.  The record's unlock state (0 / 1 /
 * other) comes from Ov008_QueryRecordUnlock over the sorted array (+0xc3d0)
 * at scroll (+0xc3c8) + row.  On tabs other than 3 (+0xc250): an item icon
 * id (item def +0x20) shows cell A[row] on that frame (id - 1); tabs other
 * than 1 show cell B / C[row] for unlock 0 / 1; tab 0 shows cell F[row]
 * when the level is reached (+0x28); cell G[row] shows when the owned count
 * (GameState 0x810 + item id) differs from the spare copies.  On tab 3 a
 * record with a level requirement (+0x20) shows cell E[row]; otherwise cell
 * D[row] follows "price (+0x8) within the category cap (+0xc574 + 2 * tab)
 * and story field 0x44e (3 bits) at least the record's u16 at +0x10", and
 * when that fails, past the category's free count (+0xc578 + 2 * tab) with
 * the record's byte +0x12 clear nothing more shows, else cell B / C[row].
 */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

#define ROW_COUNT   8
#define TAB_RECIPES 3
#define FIELD_STORY 0x44e

typedef struct Ov008ItemDef {
    u8  pad_00[0x20];
    u16 nIconId;              /* 0x20: 1-based */
} Ov008ItemDef;

typedef struct Ov008ParamRecord {   /* tab-3 (recipe) view: +0x10 overlays the shop record's u32 nBasePrice */
    u8  pad_00[8];
    u32 nPrice;               /* 0x08 */
    Ov008ItemDef *pItemDef;   /* 0x0c */
    u16 nStoryReq;            /* 0x10: story field 0x44e must reach this */
    u8  nFlag12;              /* 0x12: set = still listed past the free count */
    u8  pad_13[0x20 - 0x13];
    int nLevelReq;            /* 0x20 */
    u8  pad_24[4];
    int bLevelReached;        /* 0x28 */
} Ov008ParamRecord;

typedef struct Ov008ShopView {
    int nRow;                 /* 0x00 */
    int nScroll;              /* 0x04 */
    int nCount;               /* 0x08 */
    Ov008ParamRecord **apRows; /* 0x0c */
    u8  pad_10[8];
    int aCellA[ROW_COUNT];    /* 0x18 */
    int aCellBC[2][ROW_COUNT]; /* 0x38 / 0x58: per unlock state */
    int aCellD[ROW_COUNT];    /* 0x78 */
    int aCellE[ROW_COUNT];    /* 0x98 */
    int aCellF[ROW_COUNT];    /* 0xb8 */
    int aCellG[ROW_COUNT];    /* 0xd8 */
} Ov008ShopView;

typedef struct Ov008PanelContext {
    u8  pad_0000[0xbfb0];
    int hSlots;               /* 0xbfb0 */
    u8  pad_bfb4[0xc250 - 0xbfb4];
    int nTab;                 /* 0xc250 */
    u8  pad_c254[0xc3c0 - 0xc254];
    int nCategory;            /* 0xc3c0 */
    Ov008ShopView view;       /* 0xc3c4 */
    u8  pad_c4bc[0xc574 - 0xc4bc];
    u16 aPriceCap[2];         /* 0xc574: per category */
    u16 aFreeCount[2];        /* 0xc578: per category */
} Ov008PanelContext;

typedef struct GameState {
    u8 pad_0000[0x810];
    u8 aItemCount[0x8d0];     /* 0x810 */
} GameState;

extern Ov008PanelContext *data_ov008_02090fac;
extern GameState *data_0204be18;
extern u32  func_ov008_0208b368(Ov008ParamRecord **apRecords, u32 nIndex, int nArg); /* Ov008_QueryRecordUnlock */
extern void func_02032710(int hSlots, int nCell, int bVisible);          /* Slot_SetVisible */
extern void func_020325ec(int hSlots, int nCell, u32 nFrame);            /* Slot_ForwardToEntry */
extern int  func_ov008_0208b0bc(Ov008ParamRecord *pRecord);              /* GetChildField14OrNeg1: item id */
extern u8   func_ov008_0208b0d0(Ov008ParamRecord *pRecord);              /* Ov008_CountSpareItemsOfChild */
extern u32  func_020235d0(int nField, int nBits);                        /* GameState_GetField */

void func_ov008_020848e8(int nRow, Ov008ParamRecord *pRecord)
{
    Ov008PanelContext *ctx;
    Ov008ShopView *pView;
    u32 nUnlock;
    u32 nIndex;
    int nIconId;
    int bVisible;
    int nItemId;

    ctx = data_ov008_02090fac;
    pView = &ctx->view;
    nIndex = pView->nScroll + nRow;
    nUnlock = func_ov008_0208b368(pView->apRows, nIndex, 0);
    if (ctx->nTab != TAB_RECIPES) {
        nIconId = pRecord->pItemDef->nIconId;
        if (nIconId > 0) {
            func_02032710(ctx->hSlots, pView->aCellA[nRow], 1);
            func_020325ec(ctx->hSlots, pView->aCellA[nRow], (u16)(nIconId - 1));
        }
        if (ctx->nTab != 1 && nUnlock < 2) {
            func_02032710(ctx->hSlots, pView->aCellBC[nUnlock][nRow], 1);
        }
        if (ctx->nTab == 0 && pRecord->bLevelReached != 0) {
            func_02032710(ctx->hSlots, pView->aCellF[nRow], 1);
        }
        nItemId = func_ov008_0208b0bc(pRecord);
        func_02032710(ctx->hSlots, pView->aCellG[nRow], data_0204be18->aItemCount[nItemId] != func_ov008_0208b0d0(pRecord));
        return;
    }
    if (pRecord->nLevelReq != 0) {
        func_02032710(ctx->hSlots, pView->aCellE[nRow], 1);
        return;
    }
    bVisible = pRecord->nPrice <= ctx->aPriceCap[ctx->nCategory] && func_020235d0(FIELD_STORY, 3) >= pRecord->nStoryReq;
    func_02032710(ctx->hSlots, pView->aCellD[nRow], bVisible);
    if (bVisible != 0) {
        return;
    }
    if (nIndex >= ctx->aFreeCount[ctx->nCategory] && pView->apRows[nIndex]->nFlag12 == 0) {
        return;
    }
    if (nUnlock < 2) {
        func_02032710(ctx->hSlots, pView->aCellBC[nUnlock][nRow], 1);
    }
}
