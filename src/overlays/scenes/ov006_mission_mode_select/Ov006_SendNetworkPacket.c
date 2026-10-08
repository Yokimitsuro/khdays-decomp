#include "nitro/types.h"

#include "game/ov006_mission_mode_select.h"
/* Ov006_SendNetworkPacket -- Ov008_SendPacket (164 B, 4 relocs).
 * Queues one outgoing packet on the singleton send context MISSION_CONTEXT, if it is idle.
 * Returns 0 immediately when a send is already in flight (busy != 0). Otherwise it bumps the
 * sequence counter, marks the context busy, writes the sequence into the packet buffer header
 * (word 0), copies the caller's payload right after it (buf + 4, MI_CpuCopy8), and hands the
 * whole buffer -- header + payload, (u16)(size + 4) bytes total -- to the transport send call
 * with Ov006_PacketSentCallback as the completion callback. On a successful hand-off it returns 1
 * with the context left busy (cleared later by the callback); if the send call reports failure
 * it clears the busy flag again and returns 0. */

typedef struct Ov008SendCtx {
    char *buf;       /* 0x00: packet buffer: word[0]=seq counter, [4..]=payload */
    int   seq;       /* 0x04: outgoing sequence counter */
    u8    pad_08[0x24];
    int   busy;      /* 0x2c: 1 while a send is in flight */
} Ov008SendCtx;

#define MISSION_CONTEXT (data_ov006_020565e4.pContext)
extern void MI_CpuCopy8(const void *src, void *dst, unsigned int size);
extern int  Ov105_WH_SendData(void *buf, int size, void *callback);
extern void Ov006_PacketSentCallback(void);

int Ov006_SendNetworkPacket(const void *src, int size)
{
    if (MISSION_CONTEXT->sendBusy != 0) {
        return 0;
    }
    MISSION_CONTEXT->sendSeq += 1;
    MISSION_CONTEXT->sendBusy = 1;
    *(int *)MISSION_CONTEXT->primaryBuffer = MISSION_CONTEXT->sendSeq;
    MI_CpuCopy8(src, MISSION_CONTEXT->primaryBuffer + 4, size);
    if (Ov105_WH_SendData(MISSION_CONTEXT->primaryBuffer, (u16)(size + 4),
                                    Ov006_PacketSentCallback) != 0) {
        return 1;
    }
    MISSION_CONTEXT->sendBusy = 0;
    return 0;
}
