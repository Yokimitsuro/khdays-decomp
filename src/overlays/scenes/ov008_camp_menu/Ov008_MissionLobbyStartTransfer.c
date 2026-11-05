#include "nitro/types.h"

#include "game/ov008_camp_menu.h"
#include "game/engine.h"
/* Ov008_MissionLobbyStartTransfer -- Ov008_MissionLobbyStartTransfer: start the mission
 * lobby's transfer; returns the poll handler (0207a758, after setting
 * +0x4fc and field 28 of the global block to 2) once a transfer started, or
 * 0.  While the transfer is busy (+0x4e8), or with the session ready, the
 * group message (+0x4a8: header word + four join packets) is built once
 * (+0x4f8): cleared, every occupied slot's member kind resolved to the
 * packet's target, every packet marked pending and joined by the bit of the
 * lobby mask (01fff974); the message is then copied to +0x4c4 and, with the
 * session, sent on gate 0xd.  Otherwise, with the list header (+0x4a0) at 1,
 * the local player's packet becomes the join packet (+0x4e0) and the header
 * is cleared without a transfer; else the header is cleared, the join packet
 * is marked pending while no retry (+0x4f2) happened, given the local player
 * with no target and sent on gate 0xd.  Codegen: the message build is a
 * static inline helper (two copies) taking the packets through a local
 * pointer; the u8 loop counter walks a byte index.
 */

#define GATE_LOBBY   0xd
#define SLOT_COUNT   4

typedef struct SessionSlotInfo {
    int bOccupied;            /* 0x00 */
    int nMemberKind;          /* 0x04 */
} SessionSlotInfo;

#define MISSION_CONTEXT (data_ov008_02090f24.pContext)
extern void  MI_CpuFill8(void *pDst, int nValue, u32 nSize);
extern SessionSlotInfo *Slot4_GetIfOccupied(int nSlot);                 /* Slot4_GetIfOccupied */
extern int   Ov008_CharacterToSelectPlace(int nMemberKind);                /* member kind -> packet target */
extern void *Ov008_MissionLobbyPoll(void);                           /* Ov008_MissionLobbyPoll */

static inline void Ov008_BuildGroupMessage(MissionContext *pCtx)
{
    MissionEntry *pPacket;
    u16 nMask;
    u8 i;
    SessionSlotInfo *pInfo;

    pPacket = pCtx->liveEntries.entries;
    nMask = GetGlobalU16At6();
    if (MISSION_CONTEXT->groupBuilt == 0) {
        MI_CpuFill8(&MISSION_CONTEXT->liveEntries, 0, sizeof(MissionEntryBlock));
        for (i = 0; i < SLOT_COUNT; i++) {
            pInfo = Slot4_GetIfOccupied(i);
            if (pInfo != 0) {
                pPacket[i].characterId = Ov008_CharacterToSelectPlace(pInfo->nMemberKind);
            }
            pPacket[i].flags.request = 1;
            pPacket[i].flags.selectable = (nMask & (1 << i)) != 0;
        }
        MISSION_CONTEXT->groupBuilt = 1;
    }
}

void *Ov008_MissionLobbyStartTransfer(void)
{
    int bStarted;
    void *pNext;
    MissionContext *pCtx;
    u16 nPlayer;

    bStarted = 0;
    pNext = 0;
    pCtx = MISSION_CONTEXT;
    if (pCtx->localMode != 0) {
        Ov008_BuildGroupMessage(pCtx);
        bStarted = 1;
        pCtx = MISSION_CONTEXT;
        pCtx->sentEntries = pCtx->liveEntries;
    } else if (Session_IsReady() != 0) {
        pCtx = MISSION_CONTEXT;
        Ov008_BuildGroupMessage(pCtx);
        pCtx = MISSION_CONTEXT;
        pCtx->sentEntries = pCtx->liveEntries;
        MsgQueue_SendGate(GATE_LOBBY, &pCtx->liveEntries, sizeof(MissionEntryBlock));
        bStarted = 1;
    } else if (MISSION_CONTEXT->entryUpdateMask == 1) {
        nPlayer = Session_GetLocalPlayerIndex();
        pCtx = MISSION_CONTEXT;
        pCtx->localEntry = pCtx->liveEntries.entries[nPlayer];
        bStarted = 1;
        pCtx->localEntry.playerIndex = nPlayer;
        MISSION_CONTEXT->entryUpdateMask = 0;
    } else {
        MISSION_CONTEXT->entryUpdateMask = 0;
        pCtx = MISSION_CONTEXT;
        pCtx->localEntry.flags.request = pCtx->retryCount == 0;
        MISSION_CONTEXT->localEntry.playerIndex = Session_GetLocalPlayerIndex();
        MISSION_CONTEXT->localEntry.characterId = -1;
        MISSION_CONTEXT->localEntry.missionId = 0;
        MsgQueue_SendGate(GATE_LOBBY, &MISSION_CONTEXT->localEntry, sizeof(MissionEntry));
    }
    if (bStarted != 0) {
        MISSION_CONTEXT->transferB = 1;
        StoreToGlobalPtr4Field28(2);
        pNext = Ov008_MissionLobbyPoll;
    }
    return pNext;
}
