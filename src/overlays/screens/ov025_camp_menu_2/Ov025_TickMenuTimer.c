/* Ov025_TickMenuTimer -- Ov008_TickMenuTimer (180 B, 8 relocs).
 * Per-frame tick for a timed menu element. Once (guarded by flag14dc), when the 64-bit tick
 * counter has advanced past the stored deadline (stored + 0x7fd88 < OS_GetTick()), it marks
 * the flag and fires the one-shot Ov025_WorldMap_UpdateSelectionText(field14e8, field14e4). It always ticks the
 * sub-object at +4 (Ov025_DrawMenuPanels). Then, if field14e0 is set and GameState_IsFlagSet(0x200d)
 * returns 0, it refreshes widget id 2 with the (u16) value from Ov105_WM_GetLinkLevel via
 * Ov025_ReleaseTwoSlotsEx_2. */

#include "nitro/types.h"
#include "game/engine.h"

typedef struct Ov008TimerState {
    u8  pad_0000[4];
    u8  sub_0004[0x14d4 - 4];   /* 0x4: sub-object ticked by Ov025_DrawMenuPanels */
    u64 stored;                 /* 0x14d4: 64-bit deadline base */
    int flag14dc;               /* 0x14dc: one-shot fired flag */
    int field14e0;              /* 0x14e0 */
    int field14e4;              /* 0x14e4 */
    int field14e8;              /* 0x14e8 */
} Ov008TimerState;

extern u64   OS_GetTick(void);
extern void  Ov025_WorldMap_UpdateSelectionText(int a, int b);
extern void  Ov025_DrawMenuPanels(void *sub);
extern void *Ov025_GetContext(void);
extern void *Ov025_FindEntryById(void *ctx, int id);
extern int   Ov105_WM_GetLinkLevel(void);
extern void  Ov025_ReleaseTwoSlotsEx_2(void *ctx, void *widget, int value);

void Ov025_TickMenuTimer(Ov008TimerState *param_1)
{
    void *ctx;
    void *widget;

    if (param_1->flag14dc == 0) {
        u64 now = OS_GetTick();
        if (param_1->stored + 0x7fd88 < now) {
            param_1->flag14dc = 1;
            Ov025_WorldMap_UpdateSelectionText(param_1->field14e8, param_1->field14e4);
        }
    }
    Ov025_DrawMenuPanels(&param_1->sub_0004);
    if (param_1->field14e0 == 0) {
        return;
    }
    if (GameState_IsFlagSet(0x200d) != 0) {
        return;
    }
    ctx = Ov025_GetContext();
    widget = Ov025_FindEntryById(ctx, 2);
    Ov025_ReleaseTwoSlotsEx_2(ctx, widget, (u16)Ov105_WM_GetLinkLevel());
}
