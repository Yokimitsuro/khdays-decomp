#include "nitro/types.h"
#include "nitro/os_types.h"

#include "game/ov006_mission_mode_select.h"
#include "game/engine.h"

#pragma opt_dead_assignments off
/* Ov006_MissionPeerSyncState -- synchronize Mission Mode peer names and
 * presence latches while the scene connection state advances. */

typedef void (*MissionCallback)(void);

#define MISSION_CONTEXT (data_ov006_020565e4.pContext)
extern u16 data_ov006_02056600[];

extern void Ov105_WH_SetGgid(u32 value);
extern void OS_GetOwnerInfo(OSOwnerInfo *info);
extern u16 *StrCopy16(u16 *dst, const u16 *src);
extern void MI_CpuCopy8(const void *src, void *dst, u32 size);
extern void Ov105_WH_StartMeasureChannel(void);
extern void Ov006_MissionStartTransition(void);
extern unsigned short WH_GetBitmap(void);
extern int Ov006_GetPeerTileUploadPending(int peerIndex);
extern void Ov006_UploadSlotTiles(int peerIndex, u16 *name, u32 size);
extern void MI_CpuFill8(void *dst, int value, u32 size);
extern void Ov006_RefreshSelectionSendBlock(void);
extern int Ov006_MissionIsTransitionDone(void);
extern int Ov006_SendNetworkPacket(const void *payload, u32 payloadSize);
extern void Ov006_UpdateAndGetIdleHandler(void);

MissionCallback Ov006_MissionPeerSyncState(void) {
    OSOwnerInfo localProfile;
    MissionCallback nextState = 0;

    switch (Game_PollSceneAlive()) {
    case 1: {
        MissionContext *context;

        Ov105_WH_SetGgid(0x800356);
        context = MISSION_CONTEXT;
        OS_GetOwnerInfo(&localProfile);
        StrCopy16(context->active.roster.records.split.local.name,
                      localProfile.nickName);
        *(u16 *)&context->active.roster.records.split.local.status = 1;
        MISSION_CONTEXT->active.roster.remotePeerCapacity = 3;
        MI_CpuCopy8(&MISSION_CONTEXT->active.roster.records.split.local,
                    data_ov006_02056600, sizeof(MissionPeerRecord));
        Ov105_WH_StartMeasureChannel();
        break;
    }
    case 3:
        break;
    case 7:
        Ov006_MissionStartTransition();
        break;
    case 4: {
        u16 sessionMask;
        u8 *remotePeerActive;
        u32 peerIndex;
        int remoteIndex;

        peerIndex = 0;
        remotePeerActive = 0;
        remotePeerActive = MISSION_CONTEXT->active.roster.remotePeerActive;
        sessionMask = WH_GetBitmap();

        peerIndex = 1;
        goto check_peer;
    process_peer:
        {
            if (Ov006_GetPeerTileUploadPending(peerIndex) != 0) {
                Ov006_UploadSlotTiles(
                    peerIndex,
                    MISSION_CONTEXT->active.roster.records.split.remote[peerIndex - 1].name,
                    sizeof(MissionPeerRecord));
                remoteIndex = peerIndex - 1;
                remotePeerActive[remoteIndex] = 1;
                MISSION_CONTEXT->transitionRequested = 1;
                MISSION_CONTEXT->sendBusy = 0;
            } else {
                remoteIndex = peerIndex - 1;
                if (remotePeerActive[remoteIndex] != 0 &&
                    (sessionMask & (1 << peerIndex)) == 0) {
                    remotePeerActive[remoteIndex] = 0;
                MISSION_CONTEXT->message.selection.peerStatus[peerIndex] = 0;
                MI_CpuFill8(
                    MISSION_CONTEXT->message.selection.playerNames[peerIndex],
                    0, sizeof(MISSION_CONTEXT->message.selection.playerNames[0]));
                MI_CpuFill8(
                    &MISSION_CONTEXT->active.roster.records.split.remote[peerIndex - 1], 0,
                    sizeof(MissionPeerRecord));
                    MISSION_CONTEXT->refreshRequested = 1;
                }
            }
            peerIndex = (u8)(peerIndex + 1);
        }
    check_peer:
        if (peerIndex < 4) {
            goto process_peer;
        }

        Ov006_RefreshSelectionSendBlock();
        if (Ov006_MissionIsTransitionDone() != 0) {
            Ov006_SendNetworkPacket(
                &MISSION_CONTEXT->message.selection,
                sizeof(MissionSelectionSendBlock));
        }
        break;
    }
    default:
        MISSION_CONTEXT->sendBusy = 0;
        nextState = Ov006_UpdateAndGetIdleHandler;
        break;
    }

    return nextState;
}