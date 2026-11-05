#include "nitro/types.h"

#include "game/ov008_camp_menu.h"
#include "game/engine.h"
/* Ov008_MissionLobbyPoll -- Ov008_MissionLobbyPoll: one poll of the mission
 * lobby's transfer state; returns the next state handler (0207aa40 once a
 * transfer (+0x4f4) is pending, after which field 28 of the global block is
 * set to 3) or 0.  While the transfer is busy (+0x4e8) only the pending
 * transfer is forwarded; otherwise, with the session ready, the transfer is
 * forwarded, the lobby refreshed (02079ae4) and the group header (+0x4a8,
 * 0x1c bytes) sent on gate 0xd, and without a session the join packet
 * (+0x4e0, 6 bytes) is sent instead.  Forwarding a transfer clears the four
 * slot infos (02031618) and then re-registers every joined packet (+0x4ac,
 * 6 each, bit 0 of +0x1) as kind 1 with its menu entry's slot.  Codegen: the
 * forwarding block is a static inline helper (three copies, each with its own
 * stack info); the packet array is taken through a local pointer.
 */

#define GATE_LOBBY   0xd
#define SLOT_COUNT   4
#define INFO_KIND_JOINED 1

typedef struct Ov008SlotInfo {
    u32 nKind;                /* 0x00 */
    int nSlot;                /* 0x04 */
} Ov008SlotInfo;

#define MISSION_CONTEXT (data_ov008_02090f24.pContext)
extern void  MI_CpuFill8(void *pDst, int nValue, u32 nSize);
extern int   Ov008_SelectPlaceToCharacter(int nEntry);                     /* Ov008_SelectPlaceToCharacter */
extern void  Ov008_MissionResolveDuplicateIds(void);                           /* lobby refresh */
extern void *Ov008_RefreshListView(void);                           /* next lobby state */

static inline void Ov008_ForwardJoinedSlots(MissionContext *pCtx)
{
    Ov008SlotInfo info;
    u8 i;
    u8 nSlot;
    MissionEntry *pPacket;

    pPacket = pCtx->liveEntries.entries;
    MI_CpuFill8(&info, 0, sizeof(info));
    for (i = 0; i < SLOT_COUNT; i++) {
        CopyToSlotTable8(&info, i);
    }
    nSlot = 0;
    for (i = 0; i < SLOT_COUNT; i++) {
        MI_CpuFill8(&info, 0, sizeof(info));
        if (pPacket[i].flags.selectable) {
            info.nKind = INFO_KIND_JOINED;
            info.nSlot = Ov008_SelectPlaceToCharacter(pPacket[i].characterId);
            CopyToSlotTable8(&info, nSlot);
            nSlot++;
        }
    }
}

void *Ov008_MissionLobbyPoll(void)
{
    void *pNext;
    MissionContext *pCtx;

    pNext = 0;
    pCtx = MISSION_CONTEXT;
    if (pCtx->localMode != 0) {
        if (pCtx->transferA != 0) {
            Ov008_ForwardJoinedSlots(pCtx);
            pNext = Ov008_RefreshListView;
        }
    } else {
        Session_GetLocalPlayerIndex();
        if (Session_IsReady() != 0) {
            pCtx = MISSION_CONTEXT;
            if (pCtx->transferA != 0) {
                Ov008_ForwardJoinedSlots(pCtx);
                pNext = Ov008_RefreshListView;
            }
            Ov008_MissionResolveDuplicateIds();
            MsgQueue_SendGate(GATE_LOBBY, &MISSION_CONTEXT->liveEntries.header.raw, 0x1c);
        } else {
            pCtx = MISSION_CONTEXT;
            if (pCtx->transferA != 0) {
                Ov008_ForwardJoinedSlots(pCtx);
                pNext = Ov008_RefreshListView;
            }
            MsgQueue_SendGate(GATE_LOBBY, &MISSION_CONTEXT->localEntry, sizeof(MissionEntry));
        }
    }
    if (pNext == Ov008_RefreshListView) {
        StoreToGlobalPtr4Field28(3);
    }
    return pNext;
}
