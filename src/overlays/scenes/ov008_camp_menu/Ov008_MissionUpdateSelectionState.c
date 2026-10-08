#include "nitro/types.h"
#include "nitro/os_types.h"

#include "game/ov008_camp_menu.h"
#include "game/engine.h"
#define MISSION_CONTEXT (data_ov008_02090f24.pContext)

extern void OS_GetOwnerInfo(OSOwnerInfo *info);
extern void StrCopy16(void *selection_block, void *payload);
extern int Ov008_GetPeerTileUploadPending(int value);
extern void Ov008_UploadSlotTiles(int mode, void *send_block, u32 size);
extern void Ov008_MissionUpdateInputTransition(void);
extern int Ov008_MissionIsTransitionDone(void);
extern int Ov008_SendPacket(const void *payload, u32 payload_size);
extern void Ov008_UpdateSelectionConfirmationState(void);
extern void Ov008_MissionIdleStateNoOp(void);

void *Ov008_MissionUpdateSelectionState(void) {
    OSOwnerInfo owner;
    void *next = 0;

    switch (Game_PollSceneAlive()) {
    case 3:
        break;
    case 4:
        OS_GetOwnerInfo(&owner);
        StrCopy16(MISSION_CONTEXT->selectionBlock, owner.nickName);
        if (Ov008_GetPeerTileUploadPending(0) != 0) {
            Ov008_UploadSlotTiles(0, &MISSION_CONTEXT->message.selection.flags, 0x68);
            if (MISSION_CONTEXT->message.selection.flags.bits.sendStarted != 0) {
                Ov008_MissionUpdateInputTransition();
                GameSession_SetSyncEnabled(0);
                next = (void *)Ov008_UpdateSelectionConfirmationState;
                break;
            }
        }
        if (Ov008_MissionIsTransitionDone() != 0) {
            Ov008_SendPacket(MISSION_CONTEXT->selectionBlock, 0x18);
        }
        break;
    default:
        MISSION_CONTEXT->sendBusy = 0;
        next = (void *)Ov008_MissionIdleStateNoOp;
        break;
    }

    return next;
}
