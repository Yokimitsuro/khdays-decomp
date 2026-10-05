/* Ov008_OpenBuyDialog -- Ov008_OpenBuyDialog: open the shop's buy dialog
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

#include "nitro/types.h"

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
extern GameState *gGameState;
extern void *Ov008_FindEntryByTag(void *pTracker, int nTag);                 /* ov008_FindEntryByTag */
extern void  Ov008_TagTracker_InvokeCallback(void *pTracker, void *pCell);              /* Ov008_TagTracker_InvokeCallback */
extern void *Ov008_FindEntryById(void *pWidgets, int nId);                  /* FindEntryById */
extern void  Ov008_SetEntrySlotsVisible(void *pWidgets, void *pEntry, int bVisible); /* SetEntrySlotsVisible */
extern void  Ov008_DrawTitleBar(int nCaption);                             /* set the dialog caption */
extern int Ov008_CreateMissionCell(int *mgr, unsigned int res, int slot, int xform, ...); /* create a cell */
extern void  Ov008_ShowCounterPanel(void);                                     /* Ov008_ShowCounterPanel */
extern void  Ov008_UpdateCounterPanel(void);                                     /* refresh the totals */
extern void  Obj_InvokeInnerVtable8(void *pSurface, int nX, int nY, int nW, int nH); /* Obj_InvokeInnerVtable8 */
extern void  Ov008_DrawStringShadowed(void *pSurface, void *pText, int nX, int nY, int nStyle, int nShadow); /* Ov008_DrawStringShadowed */
extern void *Ov008_GetVarRecordByIndex(void *pRecords, int nIndex);               /* GetVarRecordByIndex */
extern void  Slot_SetVisible(int hSlots, int nCell, int bVisible);            /* Slot_SetVisible */
extern void  Ov008_DrawDescriptionText(u16 *pText, u32 nIcon);                    /* Ov008_DrawDescriptionText */
extern u16  *Ov008_GetItemDescriptionForMember(int *pList, Ov008ItemDef *pItemDef);       /* text of an item def */
extern void  Ov008_ShowThreeDigitCells(int hSlots, u32 nValue, int *aCell);       /* Ov008_ShowThreeDigitCells */
extern void  PlaySound(int nKind, int nSound);                          /* PlaySound */

void Ov008_OpenBuyDialog(void)
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
        pDialog->aFunds[0] = gGameState->otherRewardTotal;
        pDialog->aFunds[1] = gGameState->mode8RewardTotal;
        Ov008_TagTracker_InvokeCallback(ctx->trackerB, Ov008_FindEntryByTag(ctx->trackerB, TAG_BUY_SECONDARY));
        Ov008_TagTracker_InvokeCallback(ctx->tracker, Ov008_FindEntryByTag(ctx->tracker, TAG_BUY_PRIMARY));
        Ov008_SetEntrySlotsVisible(pWidgets, Ov008_FindEntryById(pWidgets, 1), 0);
        Ov008_SetEntrySlotsVisible(pWidgets, Ov008_FindEntryById(pWidgets, 9), 1);
        Ov008_SetEntrySlotsVisible(pWidgets, Ov008_FindEntryById(pWidgets, 7), 1);
        Ov008_DrawTitleBar(0x17);
        for (i = 0; i < DIGIT_CELLS; i++) {
            pDialog->aDigitCell[i] = Ov008_CreateMissionCell((int *)hSlots, 0x15, 0, (0xc0 + i * 8) << 12, 0x52000);
        }
        pDialog->aCategoryCell[0] = Ov008_CreateMissionCell((int *)hSlots, 0x13, 0, 0xb0000, 0x50000);
        pDialog->aCategoryCell[1] = Ov008_CreateMissionCell((int *)hSlots, 0x14, 0, 0xb0000, 0x50000);
        Ov008_ShowCounterPanel();
        Ov008_UpdateCounterPanel();
        pDialog->bFirstOpen = 0;
    }
    Obj_InvokeInnerVtable8(pSurface, 0x20, 0x30, 0xc0, 0x60);
    Ov008_DrawStringShadowed(pSurface, pRecord->pName, 0x80, 0x3b, TEXT_STYLE, 0x10);
    Ov008_DrawStringShadowed(pSurface, Ov008_GetVarRecordByIndex(ctx->textLoader, 0x19), 0x28, 0x4c, TEXT_STYLE, 8);
    Slot_SetVisible(hSlots, pDialog->aCategoryCell[0], 0);
    Slot_SetVisible(hSlots, pDialog->aCategoryCell[1], 0);
    if (pRecord->pItemDef == 0) {
        Ov008_DrawDescriptionText(pRecord->pRecipeText, ICON_NONE);
    } else {
        pText = Ov008_GetItemDescriptionForMember(ctx->textList, pRecord->pItemDef);
        Ov008_DrawDescriptionText(pText, pRecord->pItemDef->nIcon);
    }
    Ov008_ShowThreeDigitCells(hSlots, pRecord->nPrice, pDialog->aDigitCell);
    Slot_SetVisible(hSlots, pDialog->aCategoryCell[pRecord->nCategory], 1);
    PlaySound(0, SOUND_OPEN);
}
