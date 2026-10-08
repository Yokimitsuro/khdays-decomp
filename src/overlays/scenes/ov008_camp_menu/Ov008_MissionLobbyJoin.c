#include "nitro/types.h"

#include "game/ov008_camp_menu.h"
/* Ov008_MissionLobbyJoin -- Ov008_MissionLobbyJoin: the lobby state that settles
 * the local join packet.  With the session ready, the local slot's packet
 * (+0x4ac, 6 bytes per player, slot from OS_IsTickAvailable) drops its pending
 * bit and is copied into the join packet (+0x4e0).  Otherwise, while the list
 * header word (+0x4a0) is set, the local player's packet either has the
 * pending bit -- then the header is cleared -- or is copied into the join
 * packet; and with the header clear the join packet is sent on gate 0xd and the
 * state stays.  Any other path arms handler 0207a254 on gate 0xd (state 1) and
 * moves on to 0207a424.
 */

#define GATE_LOBBY 0xd

#define MISSION_CONTEXT (data_ov008_02090f24.pContext)
extern int  Session_IsReady(void);                                  /* Session_IsReady */
extern unsigned short WH_GetCurrentAid(void); /* local slot */
extern u32  Session_GetLocalPlayerIndex(void);                                  /* Session_GetLocalPlayerIndex */
extern void MsgQueue_SendGate(int nGate, void *pBuf, int nSize);      /* MsgQueue_SendGate */
extern void StoreToGlobalPtr4Field28(int nState);                            /* StoreToGlobalPtr4Field28 */
extern void StoreGlobalPtrArray4At0c(int nGate, void *pHandler);             /* StoreGlobalPtrArray4At0c */
extern void *Ov008_MissionApplyEntryUpdate(void);                           /* gate handler */
extern void *Ov008_MissionLobbyStartTransfer(void);                           /* next lobby state */

void *Ov008_MissionLobbyJoin(void)
{
    MissionContext *pCtx;

    if (Session_IsReady()) {
        MISSION_CONTEXT->liveEntries.entries[WH_GetCurrentAid()].flags.request = 0;
        pCtx = MISSION_CONTEXT;
        pCtx->localEntry = pCtx->liveEntries.entries[WH_GetCurrentAid()];
    } else {
        pCtx = MISSION_CONTEXT;
        if (pCtx->entryUpdateMask != 0) {
            if (pCtx->liveEntries.entries[Session_GetLocalPlayerIndex()].flags.request) {
                pCtx->entryUpdateMask = 0;
            } else {
                pCtx = MISSION_CONTEXT;
                pCtx->localEntry = pCtx->liveEntries.entries[Session_GetLocalPlayerIndex()];
            }
        }
        if (MISSION_CONTEXT->entryUpdateMask == 0) {
            MISSION_CONTEXT->entryUpdateMask = 0;
            MsgQueue_SendGate(GATE_LOBBY, &MISSION_CONTEXT->localEntry, sizeof(MissionEntry));
            return 0;
        }
    }
    StoreToGlobalPtr4Field28(1);
    StoreGlobalPtrArray4At0c(GATE_LOBBY, Ov008_MissionApplyEntryUpdate);
    return Ov008_MissionLobbyStartTransfer;
}
