#pragma opt_common_subs off

/*
 * Ov002_ShutDownMissionScene - tear the whole mission scene down.
 *
 * The scene's own exit hook runs first and its overlay - plus overlay 0x45 when
 * this was scene kind 7 - is unloaded, then every subsystem the scene brought
 * up is closed in the reverse order it was opened: link session, party object,
 * pause buffers, slot table, deferred draws, link state and scene context. The
 * saved global slots are cleared, the two heap buffers the scene owns are
 * freed, and the scene pointer is dropped.
 *
 * The boot-mode flag bit 2 marks a run that never claimed those globals, so it
 * skips the two frees that go with them.
 *
 * THUMB.
 */

#include "nitro/types.h"

typedef u32 FSOverlayID;

extern u32 OVERLAY_69_ID[1];
#define FS_OVERLAY_ID_ov069 ((FSOverlayID)(u32) & (OVERLAY_69_ID))

extern int data_ov002_0207fa00;
extern unsigned char data_0204c240;

extern char *NNSi_FndGetCurrentRootHeap(void);
extern void NNSi_FndFreeFromDefaultHeap(int pBlock);
extern void UnloadOverlaySync(int nProcessor, FSOverlayID nOverlay);
extern void DeferredDraw_Release(void);
extern void FSi_BindCardTransfer(int nArg);
extern int EntityManager_ReleaseViews(void);
extern void PartyState_ReleaseNodes(void);
extern void PartyState_FreeRecord(void);
extern void StoreGlobalArrayEntry(int nIndex, int nValue);
extern void StoreGlobalByteAt0(int nValue);
extern void ZeroHalfThenFree(int pBlock);

extern void func_ov002_0206fb74(void);
extern void Ov002_DestroyPartyObject(void);
extern void Ov002_FreePauseBuffers(void);
extern void Ov002_DestroySlotTable(void);
extern void Ov002_ResetSubsystem(void);
extern void Ov002_DestroyPauseMenu(void);
extern void Ov002_DropLinkSession(void);
extern void Ov002_FreeRootBuffer0x8d14(void);
extern void Ov002_World_ClearTarget(void);
extern void Ov002_World_ResetMarker(void);
extern void Ov002_ResetLinkState(void);
extern void Ov002_Roster_Release(void);
extern void Ov002_Link_ReleaseService(void);
extern void Ov002_DestroySubsystem(void);
extern void Ov002_DestroyLinkContext(void);
extern void Ov002_FreeWorkBuffer(void);
extern void Ov002_DestroySceneContext(void);
extern void Ov002_ResetFrmVramStates(void);
extern void Ov002_ClearRosterRow(void);
extern void Ov002_SetRootWord8a28(int nIndex, int nValue);
extern void Ov002_ReleaseObjectService(void);

void Ov002_ShutDownMissionScene(void)
{
    char *ctx;

    ctx = NNSi_FndGetCurrentRootHeap();
    func_ov002_0206fb74();
    if (*(int *)(ctx + 0x8b4c) != -1) {
        (*(void (**)(void))(ctx + 0x8b84))();
        UnloadOverlaySync(0, *(FSOverlayID *)(ctx + 0x8b50));
        if (*(int *)(ctx + 0x8b58) == 7) {
            UnloadOverlaySync(0, FS_OVERLAY_ID_ov069);
        }
        *(int *)(ctx + 0x8b4c) = -1;
    }
    if ((data_0204c240 & 4) == 0) {
        PartyState_FreeRecord();
    }
    FSi_BindCardTransfer(0);
    PartyState_ReleaseNodes();
    Ov002_DestroyPartyObject();
    Ov002_FreePauseBuffers();
    Ov002_DestroySlotTable();
    Ov002_ResetSubsystem();
    Ov002_DestroyPauseMenu();
    Ov002_DropLinkSession();
    Ov002_FreeRootBuffer0x8d14();
    Ov002_World_ClearTarget();
    Ov002_World_ResetMarker();
    DeferredDraw_Release();
    EntityManager_ReleaseViews();
    Ov002_ResetLinkState();
    Ov002_Roster_Release();
    Ov002_Link_ReleaseService();
    Ov002_DestroySubsystem();
    Ov002_DestroyLinkContext();
    Ov002_FreeWorkBuffer();
    Ov002_DestroySceneContext();
    StoreGlobalByteAt0(-1);
    Ov002_ResetFrmVramStates();
    Ov002_ClearRosterRow();
    ZeroHalfThenFree(*(int *)(ctx + 4));
    Ov002_SetRootWord8a28(0, 0);
    Ov002_SetRootWord8a28(1, 0);
    Ov002_SetRootWord8a28(2, 0);
    Ov002_SetRootWord8a28(3, 0);
    StoreGlobalArrayEntry(2, 0);
    StoreGlobalArrayEntry(1, 0);
    StoreGlobalArrayEntry(0x13, 0);
    if ((data_0204c240 & 4) == 0) {
        NNSi_FndFreeFromDefaultHeap(*(int *)(ctx + 0x8dac));
        *(int *)(ctx + 0x8dac) = 0;
    }
    Ov002_ReleaseObjectService();
    if (*(int *)(ctx + 0x8dbc) != 0) {
        NNSi_FndFreeFromDefaultHeap(*(int *)(ctx + 0x8dbc));
        *(int *)(ctx + 0x8dbc) = 0;
    }
    data_ov002_0207fa00 = 0;
}
