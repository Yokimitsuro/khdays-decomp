/*
 * Ov008_WorldMap_SetupToolbar - load the world-map toolbar/entry resource blocks and set
 * which toolbar entries are visible, called from Ov008_WorldMap_StateTick (state 1).
 *
 * Binds two layout blocks (block 0x12 into the ctx-block at GetCtxBlock4a80, block 0x18 into
 * the main context) from templates data_ov008_0208edec / data_ov008_0208edfc, each with its
 * first word overwritten by a resource id. Then, depending on the menu mode flag obj[0x14e0]:
 *   - mode != 0, story flag 0x200d clear: show toolbar entry 2 and release its two slots;
 *   - mode != 0, context object present: show entry 10;
 *   - mode == 0, context object present: show entries 9 and 8, then display a 3-digit counter
 *     (from Ov008_CalcMissionCompletionPercent) across entries 0xf..0x11 - each digit shown unless it and the
 *     remaining higher digits are all zero (leading-zero suppression, but the ones place always
 *     shows).
 *
 * Notes: Ov008_LoadBlockProcessAndFree (load-block-process-and-free) takes 3 args (ctx, name, id) - the
 * 4th arg Ghidra shows is r3 left over from the 4-word template ldm. Ov008_CalcMissionCompletionPercent is
 * passed obj even though its body ignores it (the caller still loads r0). The digit split is a
 * signed divide-by-10 (val % 10 / val / 10), quotient kept to 16 bits.
 */

#include "nitro/types.h"
#include "game/engine.h"

typedef struct { u32 f0, f4, f8, fc; } Block4;

extern int  Ov008_GetCtxBlock4a80(void);
extern int  Ov008_PackHandleTagB(int a);
extern void Ov008_InitFromDescAndMark(int ctx, Block4 *blk);
extern int  Ov008_PackSlotTag(int tag);
extern void Ov008_LoadBlockProcessAndFree(int ctx, char *name, int id);
extern int  Ov008_GetContext(void);
extern void func_ov008_0205475c(int ctx, void *resName);
extern int  Ov008_FindEntryById(int ctx, int id);
extern void Ov008_SetEntrySlotsVisible(int ctx, int entry, int a);
extern void Ov008_ReleaseTwoSlots(int ctx, int entry);
extern int  Ov008_GetCtxObject9634(void);
extern unsigned short  Ov008_CalcMissionCompletionPercent(int obj);
extern void Ov008_ReleaseTwoSlotsEx(int ctx, int entry, int digit);
extern Block4 data_ov008_0208edec;
extern Block4 data_ov008_0208edfc;

void Ov008_WorldMap_SetupToolbar(int obj)
{
    int ctx;
    Block4 blk1;
    Block4 blk2;
    void *resName;
    int entry;
    int i;
    u32 val;
    u32 digit;

    ctx = Ov008_GetCtxBlock4a80();
    blk1 = data_ov008_0208edec;
    blk2 = data_ov008_0208edfc;
    blk1.f0 = Ov008_PackHandleTagB(9);
    Ov008_InitFromDescAndMark(ctx, &blk1);
    Ov008_LoadBlockProcessAndFree(ctx, (char *)Ov008_PackSlotTag(0x12), 0x2b);
    blk2.f0 = Ov008_PackSlotTag(0x17);
    ctx = Ov008_GetContext();
    Ov008_InitFromDescAndMark(ctx, &blk2);
    resName = (void *)Ov008_PackHandleTagB(8);
    if (resName != 0) {
        func_ov008_0205475c(ctx, resName);
    }
    Ov008_LoadBlockProcessAndFree(ctx, (char *)Ov008_PackSlotTag(0x18), 0x10);
    if (*(int *)(obj + 0x14e0) != 0 && GameState_IsFlagSet(0x200d) == 0) {
        entry = Ov008_FindEntryById(ctx, 2);
        Ov008_SetEntrySlotsVisible(ctx, entry, 1);
        Ov008_ReleaseTwoSlots(ctx, entry);
    }
    if (*(int *)(obj + 0x14e0) != 0 && Ov008_GetCtxObject9634() != 0) {
        entry = Ov008_FindEntryById(ctx, 10);
        Ov008_SetEntrySlotsVisible(ctx, entry, 1);
    }
    if (*(int *)(obj + 0x14e0) == 0 && Ov008_GetCtxObject9634() != 0) {
        val = Ov008_CalcMissionCompletionPercent(obj);
        entry = Ov008_FindEntryById(ctx, 9);
        Ov008_SetEntrySlotsVisible(ctx, entry, 1);
        entry = Ov008_FindEntryById(ctx, 8);
        Ov008_SetEntrySlotsVisible(ctx, entry, 1);
        i = 0;
        do {
            digit = (int)val % 10;
            val = (int)val / 10 & 0xffff;
            if (i == 0 || digit != 0 || val != 0) {
                entry = Ov008_FindEntryById(ctx, i + 0xf);
                Ov008_SetEntrySlotsVisible(ctx, entry, 1);
                Ov008_ReleaseTwoSlots(ctx, entry);
                Ov008_ReleaseTwoSlotsEx(ctx, entry, digit & 0xffff);
            }
            i = i + 1;
        } while (i < 3);
    }
}
