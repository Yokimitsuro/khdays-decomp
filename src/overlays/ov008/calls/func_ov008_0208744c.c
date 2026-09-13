/* func_ov008_0208744c -- Ov008_OpenBuyDialog: open the shop's buy dialog
 * (+0xc54c) for its record (+0x24).  On the first open (+0x1c) the two fund
 * counters (+0x28 / +0x2a) are copied from the save header (0x196a /
 * 0x1968), tag 0x3ed of the secondary tracker (+0x5c) and tag 0x199 of the
 * primary one (+0x10) are invoked, widget 1 hidden and 9 / 7 shown, caption
 * 0x17 set, the three digit cells (+0x10, kind 0x15 at y 0xc0 + 8 i, x
 * 0x52) and the two category cells (+0x8, kinds 0x13 / 0x14 at (0xb0, 0x50))
 * created, the counter panel shown and the totals refreshed.  Then the
 * dialog surface (+0xc160) is framed (0x20, 0x30, 0xc0 x 0x60), the record's
 * name (+0x18) drawn at (0x80, 0x3b) and var record 0x19 at (0x28, 0x4c),
 * both category cells hidden, the description drawn (the record's own text
 * +0x1c with icon -1 without an item def, else the def's text and icon
 * +0x24), the price (+0x8) shown on the digit cells, the record's category
 * cell (+0x6) shown and sound 0x11 played.  Codegen: digit cell y written
 * as (0xc0 + i * 8) << 12; the description call split so the item def is
 * re-read after the text lookup; hSlots declared before pDialog.
 */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

#define DIGIT_CELLS   3
#define TAG_BUY_SECONDARY 0x3ed
#define TAG_BUY_PRIMARY   0x199
#define TEXT_STYLE    4
#define ICON_NONE     (-1)
#define SOUND_OPEN    0x11

typedef struct Ov008ItemDef {
    u8  pad_00[0x24];
    u32 nIcon;                /* 0x24 */
} Ov008ItemDef;

typedef struct Ov008ParamRecord {
    u8  pad_00[6];
    u16 nCategory;            /* 0x06: fund category */
    u32 nPrice;               /* 0x08 */
    Ov008ItemDef *pItemDef;   /* 0x0c */
    u8  pad_10[8];
    void *pName;              /* 0x18: recipe view */
    u16 *pRecipeText;         /* 0x1c: recipe view (no item def) */
} Ov008ParamRecord;

typedef struct Ov008BuyDialog {
    u8  pad_00[8];
    int aCategoryCell[2];     /* 0x08 (0xc554) */
    int aDigitCell[DIGIT_CELLS]; /* 0x10 (0xc55c) */
    int bFirstOpen;           /* 0x1c (0xc568) */
    u8  pad_20[4];
    Ov008ParamRecord *pRecord; /* 0x24 (0xc570) */
    u16 aFunds[2];            /* 0x28 (0xc574): per category */
} Ov008BuyDialog;

typedef struct Ov008PanelContext {
    u8  pad_0000[0x10];
    u8  tracker[0x5c - 0x10]; /* 0x0010: primary tag tracker */
    u8  trackerB[0x2ab0 - 0x5c]; /* 0x005c: secondary tag tracker */
    u8  widgets[0xbfb0 - 0x2ab0]; /* 0x2ab0 */
    int hSlots;               /* 0xbfb0 */
    u8  pad_bfb4[0xc130 - 0xbfb4];
    u8  textLoader[0xc];      /* 0xc130: var text records */
    u8  pad_c13c[0xc160 - 0xc13c];
    u8  dialogSurface[0x3c];  /* 0xc160 */
    u8  pad_c19c[0xc54c - 0xc19c];
    Ov008BuyDialog buy;       /* 0xc54c */
    u8  pad_c578[0xc5fc - 0xc578];
    int textList[3];          /* 0xc5fc */
} Ov008PanelContext;

typedef struct GameState {
    u8  pad_0000[0x1968];
    u16 mode8RewardTotal;     /* 0x1968 */
    u16 otherRewardTotal;     /* 0x196a */
} GameState;

extern Ov008PanelContext *data_ov008_02090fac;
extern GameState *data_0204be18;
extern void *func_ov008_02055808(void *pTracker, int nTag);                 /* ov008_FindEntryByTag */
extern void  func_ov008_0205589c(void *pTracker, void *pCell);              /* Ov008_TagTracker_InvokeCallback */
extern void *func_ov008_02054788(void *pWidgets, int nId);                  /* FindEntryById */
extern void  func_ov008_02054ba4(void *pWidgets, void *pEntry, int bVisible); /* SetEntrySlotsVisible */
extern void  func_ov008_02082f2c(int nCaption);                             /* set the dialog caption */
extern int   func_ov008_02082ecc(int hSlots, int nKind, int nSlot, int nY, int nX); /* create a cell */
extern void  func_ov008_02083a60(void);                                     /* Ov008_ShowCounterPanel */
extern void  func_ov008_0208400c(void);                                     /* refresh the totals */
extern void  func_0203011c(void *pSurface, int nX, int nY, int nW, int nH); /* Obj_InvokeInnerVtable8 */
extern void  func_ov008_02082d44(void *pSurface, void *pText, int nX, int nY, int nStyle, int nShadow); /* Ov008_DrawStringShadowed */
extern void *func_ov008_02055c84(void *pRecords, int nIndex);               /* GetVarRecordByIndex */
extern void  func_02032710(int hSlots, int nCell, int bVisible);            /* Slot_SetVisible */
extern void  func_ov008_02082fa8(u16 *pText, u32 nIcon);                    /* Ov008_DrawDescriptionText */
extern u16  *func_ov008_0208e66c(int *pList, Ov008ItemDef *pItemDef);       /* text of an item def */
extern void  func_ov008_02083970(int hSlots, u32 nValue, int *aCell);       /* Ov008_ShowThreeDigitCells */
extern void  func_02033b78(int nKind, int nSound);                          /* PlaySound */

void func_ov008_0208744c(void)
{
    Ov008PanelContext *ctx;
    int hSlots;
    Ov008BuyDialog *pDialog;
    u8 *pSurface;
    u8 *pWidgets;
    Ov008ParamRecord *pRecord;
    int i;
    u16 *pText;

    ctx = data_ov008_02090fac;
    pDialog = &ctx->buy;
    hSlots = ctx->hSlots;
    pRecord = pDialog->pRecord;
    pSurface = ctx->dialogSurface;
    pWidgets = ctx->widgets;
    if (pDialog->bFirstOpen != 0) {
        pDialog->aFunds[0] = data_0204be18->otherRewardTotal;
        pDialog->aFunds[1] = data_0204be18->mode8RewardTotal;
        func_ov008_0205589c(ctx->trackerB, func_ov008_02055808(ctx->trackerB, TAG_BUY_SECONDARY));
        func_ov008_0205589c(ctx->tracker, func_ov008_02055808(ctx->tracker, TAG_BUY_PRIMARY));
        func_ov008_02054ba4(pWidgets, func_ov008_02054788(pWidgets, 1), 0);
        func_ov008_02054ba4(pWidgets, func_ov008_02054788(pWidgets, 9), 1);
        func_ov008_02054ba4(pWidgets, func_ov008_02054788(pWidgets, 7), 1);
        func_ov008_02082f2c(0x17);
        for (i = 0; i < DIGIT_CELLS; i++) {
            pDialog->aDigitCell[i] = func_ov008_02082ecc(hSlots, 0x15, 0, (0xc0 + i * 8) << 12, 0x52000);
        }
        pDialog->aCategoryCell[0] = func_ov008_02082ecc(hSlots, 0x13, 0, 0xb0000, 0x50000);
        pDialog->aCategoryCell[1] = func_ov008_02082ecc(hSlots, 0x14, 0, 0xb0000, 0x50000);
        func_ov008_02083a60();
        func_ov008_0208400c();
        pDialog->bFirstOpen = 0;
    }
    func_0203011c(pSurface, 0x20, 0x30, 0xc0, 0x60);
    func_ov008_02082d44(pSurface, pRecord->pName, 0x80, 0x3b, TEXT_STYLE, 0x10);
    func_ov008_02082d44(pSurface, func_ov008_02055c84(ctx->textLoader, 0x19), 0x28, 0x4c, TEXT_STYLE, 8);
    func_02032710(hSlots, pDialog->aCategoryCell[0], 0);
    func_02032710(hSlots, pDialog->aCategoryCell[1], 0);
    if (pRecord->pItemDef == 0) {
        func_ov008_02082fa8(pRecord->pRecipeText, ICON_NONE);
    } else {
        pText = func_ov008_0208e66c(ctx->textList, pRecord->pItemDef);
        func_ov008_02082fa8(pText, pRecord->pItemDef->nIcon);
    }
    func_ov008_02083970(hSlots, pRecord->nPrice, pDialog->aDigitCell);
    func_02032710(hSlots, pDialog->aCategoryCell[pRecord->nCategory], 1);
    func_02033b78(0, SOUND_OPEN);
}
