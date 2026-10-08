#include "nitro/types.h"

#include "game/ov008_camp_menu.h"
/* Ov008_SendPacket -- Ov008_SendPacket (164 B, 4 relocs).
 * Queues one outgoing packet on the singleton send context MISSION_CONTEXT, if it is idle.
 * Returns 0 immediately when a send is already in flight (busy != 0). Otherwise it bumps the
 * sequence counter, marks the context busy, writes the sequence into the packet buffer header
 * (word 0), copies the caller's payload right after it (buf + 4, MI_CpuCopy8), and hands the
 * whole buffer -- header + payload, (u16)(size + 4) bytes total -- to the transport send call
 * with Ov008_PacketSentCallback as the completion callback. On a successful hand-off it returns 1
 * with the context left busy (cleared later by the callback); if the send call reports failure
 * it clears the busy flag again and returns 0. */

#define MISSION_CONTEXT (data_ov008_02090f24.pContext)
extern void MI_CpuCopy8(const void *src, void *dst, unsigned int size);
extern int  Ov105_WH_SendData(void *buf, int size, void *callback);
extern void Ov008_PacketSentCallback(void);

int Ov008_SendPacket(const void *src, int size)
{
    if (MISSION_CONTEXT->sendBusy != 0) {
        return 0;
    }
    MISSION_CONTEXT->sendSeq += 1;
    MISSION_CONTEXT->sendBusy = 1;
    *(int *)MISSION_CONTEXT->primaryBuffer = MISSION_CONTEXT->sendSeq;
    MI_CpuCopy8(src, MISSION_CONTEXT->primaryBuffer + 4, size);
    if (Ov105_WH_SendData(MISSION_CONTEXT->primaryBuffer, (u16)(size + 4),
                                    Ov008_PacketSentCallback) != 0) {
        return 1;
    }
    MISSION_CONTEXT->sendBusy = 0;
    return 0;
}
