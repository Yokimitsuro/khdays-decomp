/* NOT MATCHING -- 1394 of 1448 bytes, 352 of 362 instructions aligned.
 *
 * Exact size, exact instruction count and exact relocations. Two residues:
 * the `moveq r1, #0 ; movne r1, #1` pair for the left-column selection is
 * emitted the other way round (build 139 always puts the != arm first for a
 * variable; direct stores in both branches give the ROM's order but recompute
 * the shared column address), and in the tab-0 buy test the owned count is
 * consumed by the delta subtraction right after its load in the ROM (scratch
 * r2, count in sb, the recipe flag in sl) while build 139 schedules the
 * subtraction after the recipe tests and colours count / owned / flag as
 * sl / sb / fp.
 *
 * Swept: ~2900 prologue / declaration / recipe-shape variants in earlier
 * sessions, the 13/09 volatile reads and flag-init orders that fixed the flag
 * registers, condition polarity and boolean spellings for the pair (24),
 * switch / goto / block forms, bShow types and reuse, flag placements (16),
 * block-scoped subsets of the buy-test locals (127), compound and plain
 * subtractions, free narrowing casts on the byte count, joint callee return
 * types (240), a u32 type mask (1024), 49 pragmas, the C++ lane. Left for
 * decomp.me.
 */
/* func_ov008_02085dd4 -- Ov008_OpenSellDialog: open the shop's quantity
 * dialog (+0xc4c8) for the selected record of the item list (+0xc3c4:
 * index, +0xc3d0: records) and return the id of its caption text.  The
 * tab's tag (0x6d on tab 0, 0xd1 otherwise) is invoked on the tracker
 * (+0x10); the four choice cells (+0xc5e0, kinds 1 / 2) are created at the
 * centres of the two 0208fe84 rectangles; widget 1 goes to x 0x80 hidden;
 * the dialog texts (+0x20 / +0x24) come from records 0x1f / 0x20 of +0xc130.
 * The record's stock (def +0x20) and the owned count (+0x10, from the item
 * counts of 0204be18) are read; on tab 0 widget 6 of the secondary context
 * (+0x7530) is shown 0x12 rows below its block and the right column takes
 * selection 2 with the negated price, otherwise widget 5 is shown while
 * the points (+0x8) are below 999999, which also selects the left column,
 * whose base takes the price.  The dialog's step (+0x14) and mark (+0x18)
 * reset; its two counter cells (+0x4 kind 0 at the panel's row +0xe, +0x8
 * kind 0xb) are created, and with stock the first shows, the second shows
 * while the owned count differs from the spare count (0208b0d0), and the
 * first is forwarded to stock - 1.  The pending nibble (+0x1e) then holds,
 * on tab 0, whether the item can still be bought (a recipe record with its
 * three fields set, or a level requirement (+0x20) exactly one above the
 * level table (0204be18 +0x1168 by +0x4), or an owned count one below the
 * cap (02082234) less the delta, or munny (+0xc) below twice the price) --
 * caption 0x21 / 0xe -- and on tab 1 whether exactly one spare item exists
 * -- caption 0x22 / 0x11.  Widget 6 shows while nothing is pending; the
 * selection (+0x1c) mirrors the nibble, which is then set to 1 with the
 * choice (+0x1f); the two counters at +0x28 / +0x2a clear.  Codegen: the
 * tag is a u16 local; the list pointer is spilled; the caption is a spilled
 * local assigned in each branch; the buy test is a chain of flag locals
 * (bRecipe as a && chain, then bOk, bLast, bAfford defaulting to 1).
 */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;
typedef signed short   s16;

#define MUNNY_MAX      999999
#define TAG_TAB0       0x6d
#define TAG_TAB1       0xd1
#define WIDGET_QTY     1
#define WIDGET_CONFIRM 6
#define WIDGET_SELL    6
#define WIDGET_BUY     5
#define TEXT_LEFT      0x1f
#define TEXT_RIGHT     0x20
#define CAPTION_BUY_OK 0x21
#define CAPTION_BUY_NO 0xe
#define CAPTION_SELL_OK 0x22
#define CAPTION_SELL_NO 0x11

typedef struct UiLayoutPos {
    int nX;
    int nY;
} UiLayoutPos;

typedef struct Ov008CellRect {
    u8 nX;
    u8 nY;
    u8 nW;
    u8 nH;
} Ov008CellRect;

typedef struct Ov008ItemDef {
    u8    pad_00[0x20];
    u16   nStock;             /* 0x20 */
} Ov008ItemDef;

typedef struct Ov008ParamRecord {
    u8    pad_00[4];
    int   nLevelIndex;        /* 0x04 */
    u32   nPrice;             /* 0x08 */
    Ov008ItemDef *pItemDef;   /* 0x0c */
    u8    pad_10[4];
    int   nRecipeA;           /* 0x14 */
    int   nRecipeB;           /* 0x18 */
    u8    pad_1c[4];
    int   nLevelReq;          /* 0x20 */
    u8    pad_24[2];
    u8    nRecipeC;           /* 0x26 */
} Ov008ParamRecord;

typedef struct Ov008SellDialog {
    Ov008ParamRecord *pRecord; /* 0x00 (0xc4c8) */
    int   hCounterA;          /* 0x04 */
    int   hCounterB;          /* 0x08 */
    int   nCount;             /* 0x0c (0xc4d4) */
    int   nOwned;             /* 0x10 */
    int   nStep;              /* 0x14 */
    int   nMark;              /* 0x18 */
    s16   nSelection;         /* 0x1c (0xc4e4) */
    u8    nState : 4;         /* 0x1e: dialog state */
    u8    bCanBuy : 4;        /* 0x1e: the item can still be bought / sold */
    u8    nChoice;            /* 0x1f */
    void *pTextLeft;          /* 0x20 */
    void *pTextRight;         /* 0x24 */
    u16   nCounterA;          /* 0x28 */
    u16   nCounterB;          /* 0x2a */
} Ov008SellDialog;

typedef struct Ov008ItemList {
    int   nIndex;             /* 0x00 (0xc3c4) */
    u8    pad_04[8];
    Ov008ParamRecord **ppRecord; /* 0x0c (0xc3d0) */
} Ov008ItemList;

typedef struct Ov008ColumnPanel {
    int  aCell[6][8];         /* 0x00 */
    int  nLeftSelected;       /* 0xc0 */
    int  nRightSelected;      /* 0xc4 */
    int  nLeftBase;           /* 0xc8 */
    int  nRightBase;          /* 0xcc */
} Ov008ColumnPanel;

typedef struct Ov008ChoiceCells {
    int  hA;                  /* kind 1 */
    int  hB;                  /* kind 2 */
} Ov008ChoiceCells;

typedef struct Ov008PanelContext {
    u8   pad_0000[0xe];
    s16  nRow;                /* 0x000e */
    u8   tagTracker[0x2ab0 - 0x10]; /* 0x0010 */
    u8   widgets[0x7530 - 0x2ab0]; /* 0x2ab0: widget context */
    u8   widgetsB[0xbfb0 - 0x7530]; /* 0x7530: secondary widget context */
    int  hSlots;              /* 0xbfb0 */
    u8   pad_bfb4[0xc130 - 0xbfb4];
    u8   textRecords[0xc];    /* 0xc130 */
    u8   pad_c13c[0xc250 - 0xc13c];
    int  nTab;                /* 0xc250 */
    Ov008ColumnPanel columns; /* 0xc254 */
    u8   pad_c324[0xc3c4 - 0xc324];
    Ov008ItemList itemList;   /* 0xc3c4 */
    u8   pad_c3d4[0xc4c8 - 0xc3d4];
    Ov008SellDialog sell;     /* 0xc4c8 */
    u8   pad_c4f4[0xc5e0 - 0xc4f4];
    Ov008ChoiceCells aChoice[2]; /* 0xc5e0 */
} Ov008PanelContext;

typedef struct GameState {
    u8  pad_0000[8];
    u32 nPoints;              /* 0x008 */
    u32 nMunny;               /* 0x00c */
    u8  pad_0010[0x810 - 0x10];
    u8  aItemCount[0x1168 - 0x810]; /* 0x810 */
    u16 aLevel[1];            /* 0x1168 */
} GameState;

extern Ov008PanelContext *data_ov008_02090fac;
extern const Ov008CellRect data_ov008_0208fe84[2];
extern GameState *volatile data_0204be18;                                       /* g_pTallySource */
extern void *func_ov008_02055808(void *pTracker, u16 nTag);            /* ov008_FindEntryByTag */
extern void  func_ov008_0205589c(void *pTracker, void *pCell);         /* Ov008_TagTracker_InvokeCallback */
extern int   func_ov008_02082ecc(int hSlots, int nKind, int nSlot, int nX, int nY); /* create a cell */
extern void *func_ov008_02054788(void *pWidgets, int nId);             /* FindEntryById */
extern void  func_ov008_02054858(void *pWidgets, void *pEntry, UiLayoutPos *pPos); /* Ov008_SetEntryPos */
extern void  func_ov008_02054ba4(void *pWidgets, void *pEntry, int bVisible); /* SetEntrySlotsVisible */
extern void *func_ov008_02055c84(void *pRecords, int nIndex);          /* GetVarRecordByIndex */
extern int   func_ov008_0208b0bc(Ov008ParamRecord *pRecord);           /* GetChildField14OrNeg1: item id */
extern UiLayoutPos *func_ov008_0205489c(void *pWidgets, void *pEntry); /* Ov008_GetEntryBlock2c */
extern void  func_ov008_02054c80(void *pWidgets, void *pEntry, int nFrame); /* Ov008_ReleaseTwoSlotsEx */
extern void  func_02032710(int hSlots, int nCell, int bVisible);       /* Slot_SetVisible */
extern u8    func_ov008_0208b0d0(Ov008ParamRecord *pRecord);           /* Ov008_CountSpareItemsOfChild */
extern void  func_020325ec(int hSlots, int nCell, int nValue);         /* Slot_ForwardToEntry */
extern int   func_ov008_02082234(Ov008ParamRecord *pRecord);           /* stock cap */

int func_ov008_02085dd4(void)
{
    UiLayoutPos pos;
    Ov008PanelContext *ctx;
    u8 *pWidgetsB;
    Ov008SellDialog *pDialog;
    int nTag;
    int hSlots;
    Ov008ItemList *pList;
    int nCaption;
    int nTab;
    u8 *pWidgets;
    int i;
    void *pEntry;
    UiLayoutPos *pBlock;
    int nStock;
    int nItem;
    int nCap;
    int bAB;
    int bLast;
    int bAfford;
    int bOk;
    int bRecipe;
    Ov008ParamRecord *pRecord;
    int nDelta;
    int nVal;
    int bShow;

    ctx = data_ov008_02090fac;
    nTab = ctx->nTab;
    pList = &ctx->itemList;
    pDialog = &ctx->sell;
    if (nTab == 0) {
        nTag = TAG_TAB0;
    } else {
        nTag = TAG_TAB1;
    }
    pWidgets = ctx->widgets;
    pWidgetsB = ctx->widgetsB;
    hSlots = ctx->hSlots;
    func_ov008_0205589c(ctx->tagTracker, func_ov008_02055808(ctx->tagTracker, nTag));
    for (i = 0; i < 2; i++) {
        pos.nX = (data_ov008_0208fe84[i].nX + (data_ov008_0208fe84[i].nW >> 1)) << 12;
        pos.nY = (data_ov008_0208fe84[i].nY + (data_ov008_0208fe84[i].nH >> 1)) << 12;
        ctx->aChoice[i].hA = func_ov008_02082ecc(hSlots, 1, 0, pos.nX, pos.nY);
        ctx->aChoice[i].hB = func_ov008_02082ecc(hSlots, 2, 0, pos.nX, pos.nY);
    }
    pos.nX = 0x80 << 12;
    func_ov008_02054858(pWidgets, func_ov008_02054788(pWidgets, WIDGET_QTY), &pos);
    func_ov008_02054ba4(pWidgets, func_ov008_02054788(pWidgets, WIDGET_QTY), 0);
    pDialog->pTextLeft = func_ov008_02055c84(ctx->textRecords, TEXT_LEFT);
    pDialog->pTextRight = func_ov008_02055c84(ctx->textRecords, TEXT_RIGHT);
    pDialog->pRecord = pList->ppRecord[pList->nIndex];
    nStock = pDialog->pRecord->pItemDef->nStock;
    pDialog->nCount = 1;
    if (nTab == 0) {
        ((volatile Ov008SellDialog *)pDialog)->nOwned = data_0204be18->aItemCount[func_ov008_0208b0bc(pDialog->pRecord)];
        pEntry = func_ov008_02054788(pWidgetsB, WIDGET_SELL);
        pBlock = func_ov008_0205489c(pWidgetsB, pEntry);
        pos = *pBlock;
        pos.nY += 0x12 << 12;
        func_ov008_02054ba4(pWidgetsB, pEntry, 1);
        func_ov008_02054858(pWidgetsB, pEntry, &pos);
        func_ov008_02054c80(pWidgetsB, pEntry, 0);
        ctx->columns.nRightSelected = 2;
        ctx->columns.nRightBase = -pDialog->pRecord->nPrice;
    } else {
        ((volatile Ov008SellDialog *)pDialog)->nOwned = data_0204be18->aItemCount[func_ov008_0208b0bc(pDialog->pRecord)];
        pEntry = func_ov008_02054788(pWidgetsB, WIDGET_BUY);
        pBlock = func_ov008_0205489c(pWidgetsB, pEntry);
        pos = *pBlock;
        func_ov008_02054ba4(pWidgetsB, pEntry, data_0204be18->nPoints != MUNNY_MAX);
        func_ov008_02054858(pWidgetsB, pEntry, &pos);
        func_ov008_02054c80(pWidgetsB, pEntry, 0);
        if (data_0204be18->nPoints == MUNNY_MAX) {
            bShow = 0;
        } else {
            bShow = 1;
        }
        ctx->columns.nLeftSelected = bShow;
        ctx->columns.nLeftBase = pDialog->pRecord->nPrice;
    }
    pDialog->nStep = 0;
    pDialog->nMark = -1;
    pDialog->hCounterA = func_ov008_02082ecc(hSlots, 0, ctx->nRow, 0x3b << 12, 0x4d << 12);
    pDialog->hCounterB = func_ov008_02082ecc(hSlots, 0xb, 1, 0x30 << 12, 0x51 << 12);
    if (nStock > 0) {
        func_02032710(hSlots, pDialog->hCounterA, 1);
        nItem = func_ov008_0208b0bc(pDialog->pRecord);
        func_02032710(hSlots, pDialog->hCounterB, data_0204be18->aItemCount[nItem] != func_ov008_0208b0d0(pDialog->pRecord));
        func_020325ec(hSlots, pDialog->hCounterA, (u16)(nStock - 1));
    }
    switch (nTab) {
    case 0:
        nCap = func_ov008_02082234(pDialog->pRecord);
        nItem = func_ov008_0208b0bc(pDialog->pRecord);
        pRecord = pDialog->pRecord;
        bRecipe = 0;
        bOk = bLast = bAfford = 1;
        nDelta = data_0204be18->aItemCount[nItem];
        bAB = 0;
        nDelta -= ((volatile Ov008SellDialog *)pDialog)->nOwned;
        if (pRecord->nRecipeA != 0 && pRecord->nRecipeC != 0) {
            bAB = 1;
        }
        if (bAB != 0 && pRecord->nRecipeB != 0) {
            bRecipe = 1;
        }
        nCap -= nDelta;
        if (!bRecipe) {
            if (pRecord->nLevelReq - data_0204be18->aLevel[pRecord->nLevelIndex] != 1) {
                bOk = 0;
            }
        }
        if (!bOk) {
            if (((volatile Ov008SellDialog *)pDialog)->nOwned != nCap - 1) {
                bLast = 0;
            }
        }
        if (!bLast) {
            if (data_0204be18->nMunny >= pRecord->nPrice << 1) {
                bAfford = 0;
            }
        }
        pDialog->bCanBuy = bAfford ? 1 : 0;
        if (pDialog->bCanBuy != 0) {
            nCaption = CAPTION_BUY_OK;
        } else {
            nCaption = CAPTION_BUY_NO;
        }
        break;
    case 1:
        pDialog->bCanBuy = func_ov008_0208b0d0(pDialog->pRecord) == 1 ? 1 : 0;
        if (pDialog->bCanBuy != 0) {
            nCaption = CAPTION_SELL_OK;
        } else {
            nCaption = CAPTION_SELL_NO;
        }
        break;
    }
    func_ov008_02054ba4(pWidgets, func_ov008_02054788(pWidgets, WIDGET_CONFIRM), pDialog->bCanBuy == 0);
    func_ov008_02054c80(pWidgets, func_ov008_02054788(pWidgets, WIDGET_CONFIRM), 0);
    pDialog->nSelection = pDialog->bCanBuy != 0;
    pDialog->nState = 1;
    pDialog->nChoice = 1;
    pDialog->nCounterA = 0;
    pDialog->nCounterB = 0;
    return nCaption;
}
