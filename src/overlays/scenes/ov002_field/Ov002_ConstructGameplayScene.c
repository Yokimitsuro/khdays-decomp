/*
 * Ov002_ConstructGameplayScene - master constructor for the ov002 gameplay scene. Builds the
 * gameplay session on the root heap (published to data_ov002_0207fa00), brings up every
 * subsystem, seeds the per-mission scene-transition entry, and returns the initial state handler.
 *
 * Flow:
 *  - grabs the root heap and records it; enables the lazy class unless either archive
 *    (GameState_IsFlagSet 0x18bd / 0x18c9) is already resident;
 *  - initialises the session header fields at heap+0x8b4c..heap+0x8dc2 (handles/flags/-1
 *    sentinels), the card-present flag at heap+0x8b54, and the local-player bit at heap+0x8dc2;
 *  - clears the big work area at heap+0x859c (0x5a4 bytes) and copies the mission descriptor
 *    from `params` (or the default data_0204c240 when null) into the session record at heap+0x8ba8;
 *  - if hard mode is active it scales the three reward figures at data_0204c254+0x10 by 100;
 *  - formats the mission id string (OS_SPrintf) and loads its archive, then runs the whole init
 *    chain (party/enemy/HUD/camera/panel/etc. - the func_ov002_* calls) and the sub-object
 *    allocators (Ov002_AllocSceneState, Ov002_EnsureSceneManager(0x792b), ...);
 *  - allocates the 0x40-entry u16 table at heap+0x8dac from GameState_GetField (unless flag 4 is set);
 *  - when the global mode byte data_0204c240 is 0, maps the mission id to the next-scene id in
 *    data_0204c23c (the scene-transition table);
 *  - returns Ov002_UpdatePendingRequest when a link session is active (Session_IsActive), else
 *    Ov002_TickGameplayState - the scene's first tick handler.
 *
 * THUMB, returns the handler pointer. Notes on matching the original codegen: the card flag is a
 * merged store (one int temp, not a store per branch); the hard-mode reward loop keeps the
 * data_0204c254 base pointer live from its +0xe test through the +0x10 scale (counter declared
 * before the pointer so it lands in the low scratch register); and the transition switch emits its
 * case bodies in source order, so the cases are listed 5,6,4,0x6c,0x6f,0x514,0x72,0x515 to match.
 */

#include "nitro/types.h"

extern int   data_ov002_0207fa00;
extern short data_0204c23c;
extern u8    data_0204c240;
extern u8    data_0204c248;
extern u8    data_0204c254;
extern int   data_0204c4d8;
extern char gOv002MiMiPathFmt[];
extern int   gOv002SName;
extern int   gOv002IName;
extern int   data_ov002_0207f134;

extern int  NNSi_FndGetCurrentRootHeap(void);
extern int  GameState_IsFlagSet(int archiveId);
extern void Ov002_SetLazyClassEnabled(int enabled);
extern int  Obj_GetCurrent(void);
extern void StoreGlobalArrayEntry(int a, void *b);
extern int  Session_IsActive(void);
extern int  Session_GetSetup(void);
extern int  Session_GetLocalPlayerIndex(void);
extern void Ov002_InitPlayRecord(void);
extern void MI_CpuFill8(void *dest, int data, int size);
extern void Game_ApplyModeFlags(void);
extern void GameState_SetField(int a, int b, int c);
extern int OS_SPrintf(char *dst, const char *fmt, ...);
extern int  Msg_OpenContainerAndReadHeader(char *buf, int a);
extern void Ov002_ResetGlobalTracks(int a);
extern void Ov002_ClearRosterRow(void);
extern void Ov002_InitHandleRecord(void);
extern void Ov002_InitContextRecord(void);
extern void Ov002_InitStateRecord(void);
extern void Ov002_World_ClearByte8C98(void);
extern void Ov002_World_ClearPair8D7C(void);
extern void Ov002_World_ClearPending(void);
extern void Ov002_DropLinkSession(void);
extern void Ov002_World_ClearTarget(void);
extern void Ov002_World_ResetMarker(void);
extern void Ov002_ForceMasterBrightnessToLimit(void);
extern void Ov002_AllocSceneState(void);
extern void Ov002_CreateSlotContext(int a);
extern void EntityManager_ResetSingleton(void);
extern void Ov002_ResetNineSlots(void);
extern void Ov002_Roster_Create(void);
extern void Ov002_CreateRootObject(int a);
extern void Ov002_Link_InstallPacketHandler(void);
extern void Ov002_ScheduleRetry(void);
extern void Ov002_CreateSeededObjectOnce(void);
extern void Ov002_RefreshSlotOccupancy(void);
extern void Ov002_CreateSceneRegistry(void);
extern void Ov002_SetSceneObjectsActive(int active);
extern int  Ov002_EnsureSceneManager(int sceneId);
extern void Ov002_StreamFormattedLine(void *a, void *b);
extern void Ov002_SetRootWord8a28(int a, int b);
extern int  GetFrameRateMode(void);
extern void Ov002_SetStateRecordStage(void);
extern void PartyState_AllocRecord(void);
extern int  NNSi_FndAllocFromDefaultExpHeap(int size);
extern short GameState_GetField(int a, int b);
extern void Ov002_SelectTableEntry(void);
extern void *Ov002_UpdatePendingRequest(void);
extern void *Ov002_TickGameplayState(void);

void *Ov002_ConstructGameplayScene(void *param_1)
{
    char *heap;
    char *rec;
    char *src;
    char buf[0x14];
    int i;

    heap = (char *)NNSi_FndGetCurrentRootHeap();
    rec = heap + 0x8ba8;
    data_ov002_0207fa00 = (int)heap;
    if (GameState_IsFlagSet(0x18bd) == 0 && GameState_IsFlagSet(0x18c9) == 0) {
        Ov002_SetLazyClassEnabled(1);
    }
    *(int *)heap = Obj_GetCurrent();
    StoreGlobalArrayEntry(2, &data_ov002_0207f134);
    *(int *)(heap + 0x8b58) = -1;
    *(int *)(heap + 0x8b4c) = -1;
    *(u16 *)(heap + 0x8da0) = 0;
    if (Session_IsActive() != 0 && *(int *)(Session_GetSetup() + 4) >= 3) {
        i = 1;
    } else {
        i = 0;
    }
    *(int *)(heap + 0x8b54) = i;
    *(int *)(heap + 0x8b60) = -1;
    *(int *)(heap + 0x8b64) = 0;
    *(u8 *)(heap + 0x8b68) = 0;
    *(u8 *)(heap + 0x8dc2) = 1 << Session_GetLocalPlayerIndex();
    *(u16 *)(heap + 0x8dc0) = 0xffff;
    *(u8 *)(heap + 0x8d9c) = 0;
    *(u8 *)(heap + 0x8da4) = 0;
    Ov002_InitPlayRecord();
    MI_CpuFill8(heap + 0x859c, 0, 0x5a4);
    src = param_1 ? (char *)param_1 : (char *)&data_0204c240;
    *(u16 *)rec = *(u16 *)(src + 2);
    *(u16 *)(rec + 2) = *(u16 *)(src + 4);
    Game_ApplyModeFlags();
    GameState_SetField(0x82 << 6, 5, 0);
    *(int *)(rec + 0x14) = *(u8 *)(src + 1);
    if ((data_0204c240 & 2) != 0 && (data_0204c240 & 4) == 0) {
        int k;
        char *q = (char *)&data_0204c254;
        if (*(u16 *)(q + 0xe) == 0) {
            for (k = 0; k < 3; k++) {
                *(int *)(q + 0x10) = *(int *)(q + 0x10) * 0x64;
                q += 4;
            }
        }
    }
    OS_SPrintf(buf, gOv002MiMiPathFmt, *(short *)rec);
    *(int *)(heap + 4) = Msg_OpenContainerAndReadHeader(buf, 2);
    Ov002_ResetGlobalTracks(*(int *)(rec + 0x14));
    Ov002_ClearRosterRow();
    Ov002_InitHandleRecord();
    Ov002_InitContextRecord();
    Ov002_InitStateRecord();
    Ov002_World_ClearByte8C98();
    Ov002_World_ClearPair8D7C();
    Ov002_World_ClearPending();
    Ov002_DropLinkSession();
    Ov002_World_ClearTarget();
    Ov002_World_ResetMarker();
    Ov002_ForceMasterBrightnessToLimit();
    Ov002_AllocSceneState();
    Ov002_CreateSlotContext(*(short *)rec);
    EntityManager_ResetSingleton();
    Ov002_ResetNineSlots();
    Ov002_Roster_Create();
    Ov002_CreateRootObject(*(int *)((char *)&data_0204c4d8 + 0x14));
    Ov002_Link_InstallPacketHandler();
    Ov002_ScheduleRetry();
    Ov002_CreateSeededObjectOnce();
    Ov002_RefreshSlotOccupancy();
    Ov002_CreateSceneRegistry();
    Ov002_SetSceneObjectsActive(1);
    Ov002_EnsureSceneManager(0x792b);
    Ov002_StreamFormattedLine(&gOv002SName, &gOv002IName);
    Ov002_SetRootWord8a28(0, *(int *)(heap + 4));
    MI_CpuFill8(heap + 0x8d84, 0, 0x18);
    if ((data_0204c240 & 0xc) == 4 && *(u8 *)((char *)&data_0204c248 + 2) != 0) {
        int v = (GetFrameRateMode() == 1) ? 0x14 : 0x1e;
        *(short *)(heap + 0x8d98) = (short)((v << 0xc) >> 0xc);
    } else {
        *(short *)(heap + 0x8d98) = -1;
    }
    *(u8 *)(heap + 0x8b40) = 0;
    *(int *)(heap + 0x8b44) = 0;
    *(int *)(heap + 0x8b48) = 0;
    *(u8 *)(heap + 0x8b41) = 0xff;
    *(u16 *)(heap + 0x8b6a) = 0;
    *(int *)(heap + 0x8b78) = 0;
    *(u16 *)(heap + 0x8b6c) = 0;
    *(u16 *)(heap + 0x8b6e) = 0;
    *(u16 *)(heap + 0x8b70) = 0;
    *(u16 *)(heap + 0x8b72) = 0;
    *(u16 *)(heap + 0x8b74) = 0;
    *(int *)(heap + 0x8db0) = 0;
    *(u16 *)(heap + 0x8db4) = 0xffff;
    *(u8 *)(heap + 0x8db6) = 0;
    *(int *)(heap + 0x8dbc) = 0;
    MI_CpuFill8(heap + 0x8db7, 0, 4);
    *(u8 *)(heap + 0x8d9e) = 0;
    Ov002_SetStateRecordStage();
    if ((data_0204c240 & 4) == 0) {
        PartyState_AllocRecord();
    }
    if ((data_0204c240 & 4) == 0) {
        *(int *)(heap + 0x8dac) = NNSi_FndAllocFromDefaultExpHeap(0x80);
        for (i = 0; i < 0x40; i++) {
            *(short *)(*(int *)(heap + 0x8dac) + i * 2) = GameState_GetField(0x1400 + i * 0x10, 0x10);
        }
    } else {
        *(int *)(heap + 0x8dac) = 0;
    }
    Ov002_SelectTableEntry();
    GameState_SetField(0x20dd, 3, 0xffff);
    if (data_0204c240 == 0) {
        short sv = *(short *)rec;
        switch (sv) {
        case 5:     data_0204c23c = 4;    break;
        case 6:     data_0204c23c = 5;    break;
        case 4:     data_0204c23c = 6;    break;
        case 0x6c:  data_0204c23c = 0x25; break;
        case 0x6f:  data_0204c23c = 0x4a; break;
        case 0x514: data_0204c23c = 0x5b; break;
        case 0x72:  data_0204c23c = 0x5c; break;
        case 0x515: data_0204c23c = 0x5d; break;
        default:
            if (sv >= 1 && sv <= 6) data_0204c23c = sv;
            break;
        }
    }
    if (Session_IsActive() != 0) {
        return (void *)Ov002_UpdatePendingRequest;
    }
    return (void *)Ov002_TickGameplayState;
}
