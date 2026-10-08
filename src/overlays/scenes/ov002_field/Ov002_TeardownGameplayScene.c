/*
 * Ov002_TeardownGameplayScene - gameplay scene teardown handler (returned by
 * Ov002_TickGameplayState). Tears the gameplay slice down and returns the next scene handler.
 *
 * No-op (NULL) while the global busy byte data_0204be04 is set, or until Ov002_StepTeardownHandshake
 * and Ov002_ClosePause (Ov002_ClosePause) both report ready. For local player 0 with a
 * non-negative flag at heap+0x8d78 it refreshes the active mask from the slot table. It then
 * notifies Ov002_AddMissionTally for each set bit of the heap+0x8c8a mask (and clears it), destroys
 * the party object, the pause object and the pause menu, releases resources, and issues the
 * deferred-draw release (StoreGlobalByteAt0(-1) returns the u64 fed straight into DeferredDraw_Release).
 * If an overlay class is loaded (heap+0x8b4c != -1) it calls its +0x38 method, unloads the
 * overlay (heap+0x8b50) and marks it gone; frees the heap+0x8dbc buffer if any. Finally, when
 * heap+0x8bb4 is -1 it runs Ov002_ClearRosterRow/EntityManager_ReleaseViews and hands off to
 * Ov002_FinishSaveStep, otherwise it enqueues command 0x14 and hands off to Ov002_PickNextPhase.
 *
 * THUMB, void(void): the caller's r0-r3 are not used (the deferred-draw call takes only the u64
 * from StoreGlobalByteAt0, whose arg is -1 via mvn, not 0xff). rec=heap+0x8ba8 is spilled to the
 * stack for the final heap+0x8bb4 test; the final branch is written else-first so the -1 arm is
 * the branch target.
 */

#include "nitro/types.h"

typedef void (*CodeFn)(void);

extern int  NNSi_FndGetCurrentRootHeap(void);
extern int  Ov002_StepTeardownHandshake(void);
extern int  Ov002_ClosePause(void);
extern int  Session_GetLocalPlayerIndex(void);
extern int  Ov022_GetEntryField66(int a);
extern int  Ov002_GetSlotTableByte(int a);
extern void Ov002_SetActiveMaskBit(int a);
extern void Ov002_AddMissionTally(int a, int b, int c);
extern void Ov002_DestroyPartyObject(void);
extern void Ov002_DestroyPauseObject(void);
extern void Ov002_DestroyPauseMenu(void);
extern void Ov002_ReleaseResources(void);
extern long long StoreGlobalByteAt0(int a);
extern void DeferredDraw_Release(int a, int b);
extern void UnloadOverlaySync(int a, int b);
extern void NNSi_FndFreeFromDefaultHeap(int p);
extern void RequestQueue_SetOrPushKind3(int a);
extern void Ov002_ClearRosterRow(void);
extern void EntityManager_ReleaseViews(void);
extern void Ov002_PickNextPhase(void);
extern void Ov002_FinishSaveStep(void);
extern u8   data_0204be04;

void *Ov002_TeardownGameplayScene(void)
{
    int base = NNSi_FndGetCurrentRootHeap();
    int rec = base + 0x8ba8;
    void *result;
    u32 i;

    if (data_0204be04 != 0) return 0;
    if (Ov002_StepTeardownHandshake() == 0) return 0;
    if (Ov002_ClosePause() == 0) return 0;
    if (Session_GetLocalPlayerIndex() == 0 && *(char *)(base + 0x8d78) >= 0) {
        int x = Ov022_GetEntryField66(0);
        u32 b = Ov002_GetSlotTableByte(x);
        Ov002_SetActiveMaskBit(b & 0xffff);
    }
    i = 0;
    do {
        if (*(u8 *)(base + 0x8c8a) & (1 << i)) {
            Ov002_AddMissionTally(i, 1, 1);
        }
        i++;
    } while ((int)i < 4);
    *(u8 *)(base + 0x8c8a) = 0;
    Ov002_DestroyPartyObject();
    Ov002_DestroyPauseObject();
    Ov002_DestroyPauseMenu();
    Ov002_ReleaseResources();
    {
        long long v = StoreGlobalByteAt0(-1);
        DeferredDraw_Release((int)v, (int)((unsigned long long)v >> 0x20));
    }
    if (*(int *)(base + 0x8b4c) != -1) {
        (**(CodeFn *)(base + 0x8b84))();
        UnloadOverlaySync(0, *(int *)(base + 0x8b50));
        *(int *)(base + 0x8b4c) = -1;
    }
    if (*(int *)(base + 0x8dbc) != 0) {
        NNSi_FndFreeFromDefaultHeap(*(int *)(base + 0x8dbc));
        *(int *)(base + 0x8dbc) = 0;
    }
    if (*(int *)(rec + 0xc) != -1) {
        RequestQueue_SetOrPushKind3(0x14);
        result = (void *)Ov002_PickNextPhase;
    } else {
        Ov002_ClearRosterRow();
        result = (void *)Ov002_FinishSaveStep;
        EntityManager_ReleaseViews();
    }
    return result;
}
