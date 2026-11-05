#include "nitro/types.h"

#include "game/ov006_mission_mode_select.h"
#include "game/engine.h"

/* Synchronises the chosen mission members with the peers: writes the chosen characters to the slot
 * table (resolving duplicates), sends and confirms the entries, then moves on. */

typedef void (*MissionCallback)(void);

typedef struct {
    u32 active;
    int resourceSlot;
} MissionResourceSlot;

extern void MI_CpuFill8(void *dst, int value, u32 size);
extern int Ov006_SelectPlaceToCharacter(int characterId);
extern int Ov006_CanAdvancePastIntro(void);
extern void Ov006_MissionResolveDuplicateIds(void);
extern void Ov006_GetIdleHandlerGated(void);
extern void Ov006_UpdateAndGetIdleHandler(void);

MissionCallback Ov006_UpdateMissionEntrySynchronization(void) {
    MissionCallback result = 0;
    MissionContext *context = data_ov006_020565e4.pContext;

    if (context->localMode != 0) {
        if (context->liveEntries.header.bits.locked) {
            MissionEntry *entries = context->liveEntries.entries;
            MissionResourceSlot slot;
            u8 outputIndex;
            u8 entryIndex;

            MI_CpuFill8(&slot, 0, sizeof(slot));
            for (entryIndex = 0; entryIndex < 4; entryIndex++) {
                CopyToSlotTable8(&slot, entryIndex);
            }

            outputIndex = 0;
            for (entryIndex = 0; entryIndex < 4; entryIndex++) {
                MI_CpuFill8(&slot, 0, sizeof(slot));
                if (entries[entryIndex].flags.selectable) {
                    slot.active = 1;
                    slot.resourceSlot = Ov006_SelectPlaceToCharacter(
                        entries[entryIndex].characterId);
                    CopyToSlotTable8(&slot, outputIndex);
                    outputIndex = (outputIndex + 1) & 0xff;
                }
            }
            result = Ov006_GetIdleHandlerGated;
        }
    } else {
        Session_GetLocalPlayerIndex();
        if (Ov006_CanAdvancePastIntro() != 0) {
            return Ov006_UpdateAndGetIdleHandler;
        }

        if (Session_IsReady() != 0) {
            if (data_ov006_020565e4.pContext->entryUpdateMask != 0) {
                u16 sessionMask;
                u8 entryIndex;

                data_ov006_020565e4.pContext->entryUpdateMask = 0;
                Ov006_MissionResolveDuplicateIds();
                MsgQueue_SendGate(0xd,
                    (u16 *)&data_ov006_020565e4.pContext->liveEntries,
                    sizeof(MissionEntryBlock));

                if (data_ov006_020565e4.pContext->liveEntries.header.bits.locked) {
                    MissionResourceSlot slot;
                    MissionEntry *entries;
                    int peerIndex;
                    u8 *peerFlags;
                    u8 *peerFlagsBase;
                    u8 outputIndex;

                    sessionMask = GetGlobalU16At6();
                    context = data_ov006_020565e4.pContext;
                    peerIndex = 1;
                    peerFlagsBase = (u8 *)&context->liveEntries.entries[0].flags;
                    peerFlags = peerFlagsBase + sizeof(MissionEntry);
                    do {
                        if ((sessionMask & (1 << peerIndex)) != 0 &&
                            !((MissionEntryFlags *)peerFlags)->acknowledged) {
                            return 0;
                        }
                        peerIndex++;
                        peerFlags += sizeof(MissionEntry);
                    } while (peerIndex < 4);

                    entries = context->liveEntries.entries;
                    MI_CpuFill8(&slot, 0, sizeof(slot));
                    for (entryIndex = 0; entryIndex < 4; entryIndex++) {
                        CopyToSlotTable8(&slot, entryIndex);
                    }

                    outputIndex = 0;
                    for (entryIndex = 0; entryIndex < 4; entryIndex++) {
                        MI_CpuFill8(&slot, 0, sizeof(slot));
                        if (entries[entryIndex].flags.selectable) {
                            slot.active = 1;
                            slot.resourceSlot = Ov006_SelectPlaceToCharacter(
                                entries[entryIndex].characterId);
                            CopyToSlotTable8(&slot, outputIndex);
                            outputIndex = (outputIndex + 1) & 0xff;
                        }
                    }
                    result = Ov006_GetIdleHandlerGated;
                }
            }
        } else {
            context = data_ov006_020565e4.pContext;
            if (context->liveEntries.header.bits.locked) {
                if (context->messageHandle == 0xffff) {
                    u16 messageHandle;

                    context->localEntry.flags.acknowledged = 1;
                    messageHandle = MsgQueue_Post(
                        0xd, &data_ov006_020565e4.pContext->localEntry,
                        sizeof(MissionEntry));
                    data_ov006_020565e4.pContext->messageHandle = messageHandle;
                    return 0;
                }

                if (MsgQueue_Contains(context->messageHandle) == 0) {
                    MissionResourceSlot slot;
                    MissionEntry *entries;
                    u8 outputIndex;
                    u8 entryIndex;

                    data_ov006_020565e4.pContext->messageHandle = 0xffff;
                    context = data_ov006_020565e4.pContext;
                    entries = context->liveEntries.entries;
                    MI_CpuFill8(&slot, 0, sizeof(slot));
                    for (entryIndex = 0; entryIndex < 4; entryIndex++) {
                        CopyToSlotTable8(&slot, entryIndex);
                    }

                    outputIndex = 0;
                    for (entryIndex = 0; entryIndex < 4; entryIndex++) {
                        MI_CpuFill8(&slot, 0, sizeof(slot));
                        if (entries[entryIndex].flags.selectable) {
                            slot.active = 1;
                            slot.resourceSlot = Ov006_SelectPlaceToCharacter(
                                entries[entryIndex].characterId);
                            CopyToSlotTable8(&slot, outputIndex);
                            outputIndex = (outputIndex + 1) & 0xff;
                        }
                    }
                    result = Ov006_GetIdleHandlerGated;
                }
            } else {
                MsgQueue_SendGate(0xd, (u16 *)&context->localEntry,
                              sizeof(MissionEntry));
            }
        }
    }

    if (result == Ov006_GetIdleHandlerGated) {
        GameSession_SetSyncEnabled(1);
        StoreToGlobalPtr4Field28(3);
    }
    return result;
}
