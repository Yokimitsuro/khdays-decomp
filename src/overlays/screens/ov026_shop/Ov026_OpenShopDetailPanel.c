/* Ov026_OpenShopDetailPanel -- Ov008_OpenShopDetailPanel: open the shop's detail
 * panel (+0xc4f4) for its record.  The selection (+0xc534) starts at 0 when
 * the record's entry is visible, else 2; tag 0x135 of the tracker (+0x10) is
 * invoked; for the two choice boxes of 0208fe74 (x, y, w, h bytes) a pair of
 * cells (kinds 1 / 2, +0xc5e0) is created at the box centre; widget 1 is
 * moved to x 8.0 (keeping the last centre's y) and shown only on selection
 * 0; the five texts (+0xc520.., var records 0x14, 0x15, 0x13, 0x16, 0x23)
 * are cached; the title width (+0xc548) measured on the detail surface
 * (+0xc160) centres the title cell (+0xc550, kind 0, slot +0xe) on 0x87 at
 * y 4.0 and the icon cell (+0xc54c, kind 0xb) 11 px left and 4 px lower.
 * With an icon id (item def +0x20) the title cell shows, the icon cell shows
 * when the owned count (GameState 0x810 + item id) differs from the spare
 * copies, and the title cell is forwarded to frame id - 1.  The confirmation
 * (+0xc538) is cleared and the choice (+0xc53c) set to 1.  Codegen: the
 * selection as a ternary (predicated), the choice cells as a [2][2] array.
 */

#include "nitro/types.h"

#define TAG_DETAIL_OPEN 0x135
#define WIDGET_CURSOR   1
#define CHOICE_BOXES    2

typedef struct UiLayoutPos {
    int nX;
    int nY;
} UiLayoutPos;

typedef struct Ov008ChoiceBox {
    u8 nX;
    u8 nY;
    u8 nW;
    u8 nH;
} Ov008ChoiceBox;

typedef struct Ov008ItemDef {
    u8    pad_00[0xc];
    void *pName;              /* 0x0c */
    u8    pad_10[4];
    int   nItemId;            /* 0x14 */
    u8    pad_18[8];
    u16   nIconId;            /* 0x20: 1-based */
} Ov008ItemDef;

typedef struct Ov008ParamRecord {
    u8            pad_00[0xc];
    Ov008ItemDef *pItemDef;   /* 0x0c */
} Ov008ParamRecord;

typedef struct Ov008ShopDetailPanel {
    Ov008ParamRecord *pRecord; /* 0x00 */
    u8    pad_04[0x2c - 4];
    void *pTextLeft;          /* 0x2c */
    void *pTextRight;         /* 0x30 */
    void *apLabel[3];         /* 0x34 */
    int   nSelection : 16;    /* 0x40 */
    int   pad_40 : 16;
    u16   bConfirmed;         /* 0x44 */
    u8    pad_46[2];
    int   nChoice;            /* 0x48 */
    int   hIconCell;          /* 0x4c */
    int   hTitleCell;         /* 0x50 */
    int   nTitleWidth;        /* 0x54 */
} Ov008ShopDetailPanel;

typedef struct Ov008PanelContext {
    u8  pad_0000[0xe];
    s16 nCell;                /* 0x000e */
    u8  tracker[0x2ab0 - 0x10]; /* 0x0010 */
    u8  widgets[0xbfb0 - 0x2ab0]; /* 0x2ab0 */
    int hSlots;               /* 0xbfb0 */
    u8  pad_bfb4[0xc130 - 0xbfb4];
    u8  textLoader[0xc];      /* 0xc130 */
    u8  pad_c13c[0xc160 - 0xc13c];
    u8  detailSurface[0x3c];  /* 0xc160 */
    u8  pad_c19c[0xc4f4 - 0xc19c];
    Ov008ShopDetailPanel detail; /* 0xc4f4 */
    u8  pad_c54c[0xc5e0 - 0xc54c];
    int aChoiceCell[CHOICE_BOXES][2]; /* 0xc5e0: per box, kinds 1 / 2 */
} Ov008PanelContext;

typedef struct GameState {
    u8 pad_0000[0x810];
    u8 aItemCount[0x8d0];     /* 0x810 */
} GameState;

extern Ov008PanelContext *data_ov026_02091368;
extern GameState *gGameState;
extern Ov008ChoiceBox data_ov026_020910cc[];
extern int   Ov026_IsEntryVisible(Ov008ParamRecord *pRecord);               /* Ov008_IsEntryVisible */
extern void *Ov026_FindEntryByTag(void *pTracker, int nTag);                 /* ov008_FindEntryByTag */
extern void  Ov026_TagTracker_InvokeCallback(void *pTracker, void *pCell);              /* Ov008_TagTracker_InvokeCallback */
extern int Ov026_CreateMissionCell(int *mgr, unsigned int res, int slot, int xform, ...); /* create a cell */
extern void *Ov026_FindEntryById(void *pWidgets, int nId);                  /* FindEntryById */
extern void  Ov026_ReleaseTwoSlotsEx(void *pWidgets, void *pEntry, UiLayoutPos *pPos); /* Ov008_SetEntryPos */
extern void  Ov026_SetEntrySlotsVisible(void *pWidgets, void *pEntry, int bVisible); /* SetEntrySlotsVisible */
extern void *Ov026_GetVarRecordByIndex(void *pRecords, int nIndex);               /* GetVarRecordByIndex */
extern int   TextWindow_GetTextWidth(void *pSurface, void *pText);                    /* text width */
extern void  Slot_SetVisible(int hSlots, int nCell, int bVisible);            /* Slot_SetVisible */
extern u8    Ov026_CountSpareItemsOfChild(Ov008ParamRecord *pRecord);                /* Ov008_CountSpareItemsOfChild */
extern void  Slot_ForwardToEntry(int hSlots, int nCell, u32 nFrame);              /* Slot_ForwardToEntry */

void Ov026_OpenShopDetailPanel(void)
{
    Ov008PanelContext *ctx;
    Ov008ShopDetailPanel *pPanel;
    u8 *pWidgets;
    int hSlots;
    int i;
    UiLayoutPos pos;

    ctx = data_ov026_02091368;
    pPanel = &ctx->detail;
    pWidgets = ctx->widgets;
    hSlots = ctx->hSlots;
    pPanel->nSelection = Ov026_IsEntryVisible(ctx->detail.pRecord) != 0 ? 0 : 2;
    Ov026_TagTracker_InvokeCallback(ctx->tracker, Ov026_FindEntryByTag(ctx->tracker, TAG_DETAIL_OPEN));
    for (i = 0; i < CHOICE_BOXES; i++) {
        pos.nX = (data_ov026_020910cc[i].nX + (data_ov026_020910cc[i].nW >> 1)) << 12;
        pos.nY = (data_ov026_020910cc[i].nY + (data_ov026_020910cc[i].nH >> 1)) << 12;
        ctx->aChoiceCell[i][0] = Ov026_CreateMissionCell((int *)hSlots, 1, 0, pos.nX, pos.nY);
        ctx->aChoiceCell[i][1] = Ov026_CreateMissionCell((int *)hSlots, 2, 0, pos.nX, pos.nY);
    }
    pos.nX = 0x80000;
    Ov026_ReleaseTwoSlotsEx(pWidgets, Ov026_FindEntryById(pWidgets, WIDGET_CURSOR), &pos);
    Ov026_SetEntrySlotsVisible(pWidgets, Ov026_FindEntryById(pWidgets, WIDGET_CURSOR), pPanel->nSelection == 0);
    pPanel->pTextLeft = Ov026_GetVarRecordByIndex(ctx->textLoader, 0x14);
    pPanel->pTextRight = Ov026_GetVarRecordByIndex(ctx->textLoader, 0x15);
    pPanel->apLabel[0] = Ov026_GetVarRecordByIndex(ctx->textLoader, 0x13);
    pPanel->apLabel[1] = Ov026_GetVarRecordByIndex(ctx->textLoader, 0x16);
    pPanel->apLabel[2] = Ov026_GetVarRecordByIndex(ctx->textLoader, 0x23);
    pPanel->nTitleWidth = TextWindow_GetTextWidth(ctx->detailSurface, pPanel->pRecord->pItemDef->pName);
    pos.nY = 0x40000;
    pos.nX = (0x87 - ((pPanel->nTitleWidth + 0x10) >> 1)) << 12;
    pPanel->hTitleCell = Ov026_CreateMissionCell((int *)hSlots, 0, ctx->nCell, pos.nX, pos.nY);
    pPanel->hIconCell = Ov026_CreateMissionCell((int *)hSlots, 0xb, 1, pos.nX - 0xb000, pos.nY + 0x4000);
    if (pPanel->pRecord->pItemDef->nIconId != 0) {
        Slot_SetVisible(hSlots, pPanel->hTitleCell, 1);
        Slot_SetVisible(hSlots, pPanel->hIconCell, gGameState->aItemCount[pPanel->pRecord->pItemDef->nItemId] != Ov026_CountSpareItemsOfChild(pPanel->pRecord));
        Slot_ForwardToEntry(hSlots, pPanel->hTitleCell, (u16)(pPanel->pRecord->pItemDef->nIconId - 1));
    }
    pPanel->bConfirmed = 0;
    pPanel->nChoice = 1;
}
