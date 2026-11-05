/*
 * Ov008_WorldMap_UpdateSelectionText - update the selected menu entry and redraw its caption.
 * Before the delayed refresh is armed, or when the same entry remains selected, it only caches
 * the pending entry and transition mode. Otherwise it starts the selection transition, chooses
 * the locked fallback text or the entry-specific record, remeasures it, draws it, and flushes
 * the tile-text surface.
 */

#include "nitro/types.h"

extern u8 *Ov025_GetPageA(void);
extern void Ov025_StartSelectionTransition(void *state, u32 entryId, int fastTransition);
extern void Obj_InvokeInnerVtable4(void *surface);
extern int GameState_IsFlagSet(int flagId);
extern void *Ov025_GetVarRecordByIndex(void *records, int index);
extern void Ov025_UpdateThresholdSlot(void *surface, void *text);
extern void *func_ov025_0208a26c(void *list, u32 entryId);
extern void Text_DrawWithShadow(void *surface, int x, int y, int mode,
                          void *text, int shadow);
extern void EnqueueObjGfxCommand(void *surface);

void Ov025_WorldMap_UpdateSelectionText(u32 entryId, int fastTransition)
{
    u8 *menuContext = Ov025_GetPageA();
    int isEntryUnlocked;
    void *textRecord;

    if (*(int *)(menuContext + 0x14dc) == 0 ||
        *(u32 *)(menuContext + 0x14ec) == entryId) {
        goto cache_only;
    }

    Ov025_StartSelectionTransition(menuContext + 4, entryId, fastTransition);
    *(u32 *)(menuContext + 0x14ec) = entryId;
    Obj_InvokeInnerVtable4(menuContext + 0x145c);

    isEntryUnlocked = GameState_IsFlagSet(entryId + 0x3bc9);
    if (entryId == 0) {
        isEntryUnlocked = 1;
    }
    if (entryId == 4) {
        isEntryUnlocked = 1;
    }

    if (isEntryUnlocked == 0) {
        textRecord = Ov025_GetVarRecordByIndex(menuContext + 0x14f4, 4);
        Ov025_UpdateThresholdSlot(menuContext + 0x145c, textRecord);
    }
    if (isEntryUnlocked == 0) {
        textRecord = Ov025_GetVarRecordByIndex(menuContext + 0x14f4, 4);
        Text_DrawWithShadow(menuContext + 0x145c, 2, 3, 1, textRecord, 0);
    }
    if (isEntryUnlocked != 0) {
        textRecord = func_ov025_0208a26c(menuContext + 0x13fc, entryId);
        Ov025_UpdateThresholdSlot(menuContext + 0x145c, textRecord);
    }
    if (isEntryUnlocked != 0) {
        textRecord = func_ov025_0208a26c(menuContext + 0x13fc, entryId);
        Text_DrawWithShadow(menuContext + 0x145c, 2, 3, 1, textRecord, 0);
    }
    EnqueueObjGfxCommand(menuContext + 0x145c);
    return;

cache_only:
    *(u32 *)(menuContext + 0x14e8) = entryId;
    *(int *)(menuContext + 0x14e4) = fastTransition;
}
