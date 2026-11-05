/*
 * Ov008_WorldMap_StateTick - per-frame state machine for the holo-missions' world map (the camp's
 * screen 1, scene 0x13), invoked through the scene's state-handler table (no direct caller).
 *
 * State 0 (first-time setup): records whether the menu context object is type 2 at
 * obj[0x538], primes the sub-object (Ov008_WorldMap_SetupDisplay), fills the object-list init
 * params (copied from the data_ov008_0208edd4 template, then slotCount=8 and listSize
 * 7 or 3 depending on Ov008_AnyEntryFlagged), builds the object list either directly
 * (ov008_InitObjectWithList) or via Ov008_WorldMap_InitObjectListRetry when Ov008_GetCtxField967c is
 * set, loads the scene 0x13 layout resource, and picks a variant (4, or 0 once the
 * story counter GameState_GetField(0,9) reaches 0x165) stored at obj[0x53b]; then
 * advances the state.
 * State 1: runs the second-phase setup (Ov008_WorldMap_SetupToolbar, Ov008_SetupMenuBgCellsAlt,
 * Ov008_WorldMap_SetupTextSurfaces), advances the state, stamps the 64-bit entry tick at obj[0x535],
 * and returns 1 to signal the transition happened this frame.
 * Every frame ends by drawing the menu panels (Ov008_DrawMenuPanels).
 *
 * Codegen: the outer state test is a switch (forward-jump dispatch). The a84c and
 * GetCtxField967c tests are written with `!=` and swapped bodies so mwcc lays out the
 * "else" block inline (fall-through) and jumps to the "then" block, matching the ROM;
 * the natural `== 0` spelling emits the opposite layout. Many callee args Ghidra shows
 * are leftover-register phantoms; only the registers set here are real.
 */

/* Object-list init parameters: a 3-word template copied from data_ov008_0208edd4, with
 * the last two words overwritten for the world-map list geometry in state 0. */

#include "nitro/types.h"
#include "game/engine.h"

typedef struct {
    int f0;
    int slotCount;
    int listSize;
} Ov008ObjListInitParams;

extern int  Ov008_GetCtxObject95c0(void);
extern void Ov008_WorldMap_SetupDisplay(void);
extern int  Ov008_AnyEntryFlagged(void);
extern int  Ov008_GetCtxField967c(void);
extern void Ov008_InitMissionList(u32 *list, Ov008ObjListInitParams *p);
extern void Ov008_WorldMap_InitObjectListRetry(int obj, Ov008ObjListInitParams *p);
extern void Ov008_SortListByKey(int obj);
extern int  Ov008_GetCtxBlock954c(void);
extern int  Ov008_PackSlotTag(int tag);
extern void Ov008_LoadLayoutResource(int block, int ref);
extern void Ov008_WorldMap_InitPanelContext(u32 *node, int a);
extern void Ov008_MenuCursor_MoveToSlotNoAnim(int *node, int v);
extern void Ov008_WorldMap_SetupToolbar(int obj);
extern void Ov008_SetupMenuBgCellsAlt(int *obj);
extern void Ov008_WorldMap_SetupTextSurfaces(int obj);
extern u64  OS_GetTick(void);
extern void Ov008_DrawMenuPanels(int *node);
extern Ov008ObjListInitParams data_ov008_0208edd4;

int Ov008_WorldMap_StateTick(int *obj)
{
    Ov008ObjListInitParams p;
    int iVar1;
    int ref;
    u32 counter;
    u64 tick;
    int ret;

    p = data_ov008_0208edd4;
    ret = 0;
    switch (*obj) {
    case 0:
        iVar1 = Ov008_GetCtxObject95c0();
        obj[0x538] = (iVar1 == 2);
        Ov008_WorldMap_SetupDisplay();
        if (Ov008_AnyEntryFlagged() != 0) {
            p.listSize = 3;
            p.slotCount = 8;
        } else {
            p.listSize = 7;
            p.slotCount = 8;
        }
        if (Ov008_GetCtxField967c() != 0) {
            Ov008_WorldMap_InitObjectListRetry((int)obj, &p);
        } else {
            Ov008_InitMissionList((u32 *)(obj + 0x4ff), &p);
        }
        Ov008_SortListByKey((int)obj);
        iVar1 = Ov008_GetCtxBlock954c();
        ref = Ov008_PackSlotTag(0x13);
        Ov008_LoadLayoutResource(iVar1, ref);
        iVar1 = 4;
        counter = GameState_GetField(0, 9);
        if (0x165 <= counter) iVar1 = 0;
        Ov008_WorldMap_InitPanelContext((u32 *)(obj + 1), 0);
        Ov008_MenuCursor_MoveToSlotNoAnim(obj + 1, iVar1);
        obj[0x53b] = iVar1;
        *obj = *obj + 1;
        break;
    case 1:
        Ov008_WorldMap_SetupToolbar((int)obj);
        Ov008_SetupMenuBgCellsAlt(obj);
        Ov008_WorldMap_SetupTextSurfaces((int)obj);
        *obj = *obj + 1;
        tick = OS_GetTick();
        *(u64 *)(obj + 0x535) = tick;
        ret = 1;
        break;
    }
    Ov008_DrawMenuPanels(obj + 1);
    return ret;
}
