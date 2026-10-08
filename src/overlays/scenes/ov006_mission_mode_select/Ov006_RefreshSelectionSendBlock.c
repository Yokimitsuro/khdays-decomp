#include "nitro/types.h"

#include "game/ov006_mission_mode_select.h"

#pragma opt_dead_assignments off
/* Ov006_RefreshSelectionSendBlock -- rebuild the Mission Mode selection-send
 * message from the current session mask and four player records. The four dead
 * initial assignments emit no code under this pragma and reproduce the retail
 * register allocation. */

#define MISSION_CONTEXT (data_ov006_020565e4.pContext)
extern const u16 data_ov006_020563d4[];
extern unsigned short WH_GetBitmap(void);
extern void MI_CpuFill8(void *dst, int value, u32 size);
extern u32 VBlank_GetCount(void);
extern void StrCopy16(u16 *dst, const u16 *src);
extern u32 Ov006_IsMissionMenuBusy(void);

void Ov006_RefreshSelectionSendBlock(void) {
    MissionContext *context;
    MissionSelectionSendBlock *sendBlock;
    u16 sessionMask;
    const u16 *placeholderName;
    const u16 *name;
    u8 status;
    u8 playerIndex;
    int changed;

    sendBlock = 0;
    sessionMask = 0;
    placeholderName = 0;
    name = 0;

    sendBlock = &MISSION_CONTEXT->message.selection;
    sessionMask = WH_GetBitmap();

    MISSION_CONTEXT->refreshTimer--;
    if (MISSION_CONTEXT->refreshTimer < 0) {
        MISSION_CONTEXT->refreshTimer = 0;
    }

    MI_CpuFill8(&MISSION_CONTEXT->message.selection, 0,
                sizeof(MissionSelectionSendBlock));
    MISSION_CONTEXT->message.selection.sessionValue = VBlank_GetCount();
    MISSION_CONTEXT->message.selection.sessionMask = sessionMask;

    placeholderName = data_ov006_020563d4;

    for (playerIndex = 0; playerIndex < 4; playerIndex++) {
        StrCopy16(sendBlock->playerNames[playerIndex], placeholderName);
    }

    context = MISSION_CONTEXT;
    changed = 0;
    for (playerIndex = 1; playerIndex < 4; playerIndex++) {
        if (context->active.roster.records.all[playerIndex].status == 1) {
            changed = 1;
        }
    }

    if (context->refreshRequested != 0) {
        context->refreshRequested = 0;
        changed = 1;
    }
    MISSION_CONTEXT->message.selection.flags.bits.changed = changed;
    if (changed != 0) {
        MISSION_CONTEXT->refreshTimer = 30;
    }

    for (playerIndex = 0; playerIndex < 4; playerIndex++) {
        name = data_ov006_020563d4;
        status = 0;

        if ((sessionMask & (1 << playerIndex)) != 0) {
            if (playerIndex == 0) {
                name = MISSION_CONTEXT->active.roster.records.split.local.name;
            } else {
                if (Ov006_IsMissionMenuBusy() == 0) {
                    name = MISSION_CONTEXT->active.roster.records.split.remote[playerIndex - 1].name;
                }
                status = MISSION_CONTEXT->active.roster.records.all[playerIndex].status;
                if (MISSION_CONTEXT->message.selection.flags.bits.sendStarted) {
                    status = 0;
                }
            }
        }

        if (name != 0) {
            StrCopy16(sendBlock->playerNames[playerIndex], name);
        }
        sendBlock->peerStatus[playerIndex] = status;
    }
}

