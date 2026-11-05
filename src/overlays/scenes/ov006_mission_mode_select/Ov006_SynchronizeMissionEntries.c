#include "nitro/types.h"

#include "game/ov006_mission_mode_select.h"
#include "game/engine.h"

/* Builds the mission member entries from the session's connected players (or the forced default)
 * and exchanges them with the peers before the entry sync. */

typedef void (*MissionCallback)(void);

extern void MI_CpuFill8(void *dst, int value, u32 size);
extern int Ov006_CharacterToSelectPlace(int entry);
extern int Ov006_CanAdvancePastIntro(void);
extern void Ov006_UpdateAndGetIdleHandler(void);
extern void Ov006_UpdateMissionEntrySynchronization(void);

MissionCallback Ov006_SynchronizeMissionEntries(void) {
    int ready = 0;
    MissionCallback next = 0;

    if (data_ov006_020565e4.pContext->localMode != 0) {
        MissionEntry *entries = data_ov006_020565e4.pContext->liveEntries.entries;
        u16 mask = GetGlobalU16At6();
        u8 i;

        MI_CpuFill8(&data_ov006_020565e4.pContext->liveEntries, 0,
                    sizeof(MissionEntryBlock));
        for (i = 0; i < 4; i++) {
            entries[i].characterId = i;
            entries[i].flags.selectable = (mask & (1 << i)) != 0;
        }
        if (data_ov006_020565e4.pContext->localMode != 0) {
            entries[0].characterId = Ov006_CharacterToSelectPlace(0);
        }
        data_ov006_020565e4.pContext->sentEntries =
            data_ov006_020565e4.pContext->liveEntries;
        ready = 1;
    } else {
        if (Ov006_CanAdvancePastIntro() != 0) {
            return Ov006_UpdateAndGetIdleHandler;
        }

        if (Session_IsReady() != 0) {
            MissionEntry *entries = data_ov006_020565e4.pContext->liveEntries.entries;
            u16 mask = GetGlobalU16At6();
            u8 i;

            MI_CpuFill8(&data_ov006_020565e4.pContext->liveEntries, 0,
                        sizeof(MissionEntryBlock));
            for (i = 0; i < 4; i++) {
                entries[i].characterId = i;
                entries[i].flags.selectable = (mask & (1 << i)) != 0;
            }
            if (data_ov006_020565e4.pContext->localMode != 0) {
                entries[0].characterId = Ov006_CharacterToSelectPlace(0);
            }
            data_ov006_020565e4.pContext->sentEntries =
                data_ov006_020565e4.pContext->liveEntries;
            MsgQueue_SendGate(0xd,
                          (u16 *)&data_ov006_020565e4.pContext->liveEntries,
                          sizeof(MissionEntryBlock));
            ready = 1;
        } else if (data_ov006_020565e4.pContext->entryUpdateMask == 1) {
            u16 localPlayer = Session_GetLocalPlayerIndex();
            MissionContext *context = data_ov006_020565e4.pContext;

            context->localEntry = context->liveEntries.entries[localPlayer];
            context->localEntry.playerIndex = localPlayer;
            data_ov006_020565e4.pContext->entryUpdateMask = 0;
            ready = 1;
        } else {
            data_ov006_020565e4.pContext->entryUpdateMask = 0;
            data_ov006_020565e4.pContext->localEntry.flags.request = 0;
            data_ov006_020565e4.pContext->localEntry.playerIndex = Session_GetLocalPlayerIndex();
            data_ov006_020565e4.pContext->localEntry.characterId = -1;
            data_ov006_020565e4.pContext->localEntry.missionId = 0;
            MsgQueue_SendGate(0xd,
                          (u16 *)&data_ov006_020565e4.pContext->localEntry,
                          sizeof(MissionEntry));
        }
    }

    if (ready != 0) {
        StoreToGlobalPtr4Field28(2);
        next = Ov006_UpdateMissionEntrySynchronization;
    }
    return next;
}
