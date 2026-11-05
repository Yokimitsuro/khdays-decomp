/* Ov008_RaiseSelectedItemWidget -- Ov008_RaiseSelectedItemWidget: lift the highlighted
 * item's widget.  Resolves the widget of the highlighted item's current column
 * (id from the table row `sel`, column = the item's count) into a pick, swaps
 * its parameter overrides and either releases its two slots (item available)
 * or pushes its sub-item set; when the highlight differs from the backed-up
 * one (+0x80) and that item is both available and enabled, its widget is resolved
 * too and reset.  Then the pick is re-resolved with id 1 and the widget moved
 * to its layout position raised by 8 px (fx32 0x8000).
 */

#include "nitro/types.h"

typedef struct UiLayoutPos {
    int nX;
    int nY;
} UiLayoutPos;

typedef struct Ov008WidgetPick {
    s16   nId;                /* 0x00 */
    u8    pad_02[2];
    void *pEntry;             /* 0x04 */
    UiLayoutPos pos;          /* 0x08 */
} Ov008WidgetPick;

typedef struct Ov008SelCtx {
    u8  pad_0000[0x4c];
    s16 sel;                  /* 0x4c: highlighted item */
    s16 counts[0x19];         /* 0x4e */
    s16 selBackup;            /* 0x80: backed-up highlight */
    s16 countsBackup[0x19];   /* 0x82 */
} Ov008SelCtx;

#define ITEM_STRIDE 0x14
#define RAISE_FX32  0x8000

typedef struct Ov008ConfigValue {
    s16 nId;                  /* 0x00 */
    u8  nText;                /* 0x02: its name, a cfg_&.s record */
    u8  nHelpText;            /* 0x03: its help, a cfg_&.s record */
} Ov008ConfigValue;

typedef struct Ov008ConfigSetting {
    s16 nId;                  /* 0x00 */
    u8  nText;                /* 0x02: its name, a cfg_&.s record */
    u8  nHelpText;            /* 0x03: its help, a cfg_&.s record */
    u8  nAnchor;              /* 0x04 */
    u8  nState;               /* 0x05: lock state */
    u8  bEnabled;             /* 0x06: 0 shows it as "?" */
    u8  nSubCount;            /* 0x07: its values; 0 for a heading */
    Ov008ConfigValue aSub[3]; /* 0x08 */
} Ov008ConfigSetting;

extern Ov008ConfigSetting gOv008ConfigSettings[];

extern Ov008SelCtx *Ov008_GetMenuContext(void);                     /* Ov008_GetMenuContext */
extern int  Ov008_GetContext(void);                             /* Ov008_GetContext */
extern void Ov008_DispatchFrom2DTable(Ov008WidgetPick *pPick, int nItem, int nColumn); /* Ov008_DispatchFrom2DTable */
extern void Ov008_SwapParamOverrides(int nCtx, void *pEntry);           /* Ov008_SwapParamOverrides */
extern void Ov008_ReleaseTwoSlots_2(int nCtx, void *pEntry);           /* Ov008_ReleaseTwoSlots */
extern void Ov008_PushSubitemSet(int nCtx, void *pEntry, int nValue); /* Ov008_PushSubitemSet */
extern void Ov008_WidgetRef_Hide(Ov008WidgetPick *pPick);           /* Ov008_Set_9c68 */
extern void Ov008_WidgetRef_Init(Ov008WidgetPick *pPick, s16 nId);  /* Ov008_Set_9bec */
extern void Ov008_SetEntryPos(int nCtx, void *pEntry, UiLayoutPos *pPos); /* Ov008_SetEntryPos */

void Ov008_RaiseSelectedItemWidget(void)
{
    Ov008SelCtx *ctx = Ov008_GetMenuContext();
    int nCtx;
    s16 *p = &ctx->sel;
    s16 *pBackup = &ctx->selBackup;
    UiLayoutPos pos;
    Ov008WidgetPick pick;
    int nBackup;

    nCtx = Ov008_GetContext();
    Ov008_DispatchFrom2DTable(&pick, ctx->sel, (p + 1)[ctx->sel]);
    pos = pick.pos;
    Ov008_SwapParamOverrides(nCtx, pick.pEntry);
    if (gOv008ConfigSettings[ctx->sel].bEnabled != 0) {
        Ov008_ReleaseTwoSlots_2(nCtx, pick.pEntry);
    } else {
        Ov008_PushSubitemSet(nCtx, pick.pEntry, 0);
    }
    nBackup = *pBackup;
    if (*p != nBackup) {
        if (gOv008ConfigSettings[nBackup].bEnabled != 0 && gOv008ConfigSettings[nBackup].nSubCount != 0) {
            Ov008_DispatchFrom2DTable(&pick, *pBackup, (pBackup + 1)[nBackup]);
            Ov008_WidgetRef_Hide(&pick);
        }
    }
    Ov008_WidgetRef_Init(&pick, 1);
    pos.nY += RAISE_FX32;
    Ov008_SetEntryPos(nCtx, pick.pEntry, &pos);
}
