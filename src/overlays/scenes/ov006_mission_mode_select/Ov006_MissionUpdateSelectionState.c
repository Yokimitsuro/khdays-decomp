#include "nitro/types.h"
#include "nitro/os_types.h"

#include "game/ov006_mission_mode_select.h"
#include "game/engine.h"

/* Mission selection state: while the scene is waiting, copies the local profile name into the
 * selection block, takes the peers' uploaded selections and, once they have started, moves to the
 * confirmation state; sends the local selection when the transition is done. */

#define MISSION_CONTEXT (data_ov006_020565e4.pContext)

extern void OS_GetOwnerInfo(OSOwnerInfo *info);
extern void StrCopy16(void *selection_block, void *payload);
extern int Ov006_GetPeerTileUploadPending(int value);
extern void Ov006_UploadSlotTiles(int mode, void *send_block, u32 size);
extern void Ov006_MissionUpdateInputTransition(void);
extern int Ov006_MissionIsTransitionDone(void);
extern int Ov006_SendNetworkPacket(const void *payload, u32 payload_size);
extern void Ov006_UpdateSelectionConfirmationState(void);
extern void Ov006_UpdateAndGetIdleHandler(void);

void *Ov006_MissionUpdateSelectionState(void) {
    OSOwnerInfo owner;
    void *next = 0;

    switch (Game_PollSceneAlive()) {
    case 3:
        break;
    case 4:
        OS_GetOwnerInfo(&owner);
        StrCopy16(MISSION_CONTEXT->selectionBlock, owner.nickName);
        if (Ov006_GetPeerTileUploadPending(0) != 0) {
            Ov006_UploadSlotTiles(0, &MISSION_CONTEXT->message.selection.flags, 0x68);
            if (MISSION_CONTEXT->message.selection.flags.bits.sendStarted != 0) {
                Ov006_MissionUpdateInputTransition();
                GameSession_SetSyncEnabled(0);
                next = (void *)Ov006_UpdateSelectionConfirmationState;
                break;
            }
        }
        if (Ov006_MissionIsTransitionDone() != 0) {
            Ov006_SendNetworkPacket(MISSION_CONTEXT->selectionBlock, 0x18);
        }
        break;
    default:
        MISSION_CONTEXT->sendBusy = 0;
        next = (void *)Ov006_UpdateAndGetIdleHandler;
        break;
    }

    return next;
}
