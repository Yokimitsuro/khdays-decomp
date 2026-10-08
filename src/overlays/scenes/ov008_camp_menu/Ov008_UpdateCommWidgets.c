/* Ov008_UpdateCommWidgets -- Ov008_UpdateCommWidgets (184 B, 12 relocs).
 * Reflects a wireless/comm status value into the two menu widgets (ids 2 and 1) on the menu's
 * widget context. Bails out early if the context is unavailable or either gate check
 * (Session_Exists / Session_IsActive) is false. Reads a signed 8-bit value from the WM query: when
 * it is valid (>= 0) both widgets are set to that value via Ov008_ReleaseTwoSlotsEx; when it is
 * unavailable (< 0) both widgets are disabled via Ov008_SetEntrySlotsVisible(..., 0). */

#include "nitro/types.h"
#include "game/engine.h"

extern void *Ov008_GetCtxBlock4a80(void);
extern int   Ov105_WH_GetLinkLevel(void);
extern void *Ov008_FindEntryById(void *ctx, int id);
extern void  Ov008_ReleaseTwoSlotsEx(void *ctx, void *widget, int value);
extern void  Ov008_SetEntrySlotsVisible(void *ctx, void *widget, int flag);

void Ov008_UpdateCommWidgets(void)
{
    void *ctx = Ov008_GetCtxBlock4a80();
    if (ctx == 0) return;
    if (Session_Exists() == 0) return;
    if (Session_IsActive() == 0) return;
    {
        int v = (signed char)Ov105_WH_GetLinkLevel();
        if (v >= 0) {
            Ov008_ReleaseTwoSlotsEx(ctx, Ov008_FindEntryById(ctx, 2), (u16)v);
            Ov008_ReleaseTwoSlotsEx(ctx, Ov008_FindEntryById(ctx, 1), (u16)v);
        } else {
            Ov008_SetEntrySlotsVisible(ctx, Ov008_FindEntryById(ctx, 2), 0);
            Ov008_SetEntrySlotsVisible(ctx, Ov008_FindEntryById(ctx, 1), 0);
        }
    }
}
