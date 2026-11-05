/* Sends the session snapshot to the peers in chunks (host) or receives it (clients): player
 * records, thresholds, rules and configuration, then moves on once everyone has it. */

#include "nitro/types.h"
#include "game/engine.h"

typedef struct Ov008MessageHeader {
    u8 messageType : 4;
    u8 sessionState : 4;
    u8 playerIndex;
} Ov008MessageHeader;

typedef struct Ov008Message68 {
    Ov008MessageHeader header;
    u16 chunkIndex;
    u8 payload[64];
} Ov008Message68;

typedef struct Ov008TransferState {
    Ov008MessageHeader header;
    u16 nextChunk;
} Ov008TransferState;

typedef struct SharedPlayerRecord {
    u32 words[65];
} SharedPlayerRecord;

typedef struct GameplayThresholdSnapshot {
    u32 words[7];
} GameplayThresholdSnapshot;

typedef struct GameplayRules {
    u8 values[12];
} GameplayRules;

typedef struct GameplaySessionConfig {
    u16 values[4];
} GameplaySessionConfig;

typedef struct Ov008MenuContext {
    u8 pad_0000[0xc];
    u32 playerTransferReady;
    u8 pad_0010[8];
    u32 sessionState;
    Ov008MessageHeader outgoing9;
    Ov008MessageHeader peerHeaders[4];
    u8 pad_0026[0x6a];
    Ov008TransferState playerTransfer[4];
    u8 pad_00a0[0x8c];
    Ov008Message68 outgoing6;
    Ov008TransferState commonTransfer;
    Ov008MessageHeader outgoing7;
    u8 pad_0176[2];
    SharedPlayerRecord transferredRecord;
    u8 pad_027c[0x30c];
    GameplayThresholdSnapshot thresholdSnapshot;
    GameplayRules ruleSnapshot;
    GameplaySessionConfig sessionConfig;
    u16 sessionValue;
} Ov008MenuContext;

extern Ov008MenuContext *data_ov008_02090f00;
extern SharedPlayerRecord gPartyMembers;
extern GameplayThresholdSnapshot data_0204c254;
extern GameplayRules data_0204c248;
extern GameplaySessionConfig data_0204c240;
extern u16 gMissionNumber;

extern void Ov008_UpdateCursorSprite(void);
extern int Ov008_IsSessionReady(void);
extern u32 Ov008_GetSlotPresenceMask(void);
extern void Ov008_SendMenuMessage(u8 messageType);
extern void MI_CpuCopy8(const void *src, void *dst, u32 size);
extern void Ov008_WaitForSnapshotTransferState(void);

void *Ov008_TransferSessionSnapshotState(void)
{
    void *result;

    Session_GetLocalPlayerIndex();
    data_ov008_02090f00->sessionState = 4;
    result = 0;
    Ov008_UpdateCursorSprite();

    if (Ov008_IsSessionReady() != 0) {
        Ov008MenuContext *context = data_ov008_02090f00;
        if (context->playerTransferReady == 0) {
            Ov008_SendMenuMessage(9);
        } else {
            u32 playerMask;
            u32 i;

            context->playerTransferReady = 0;
            Ov008_SendMenuMessage(5);
            playerMask = Ov008_GetSlotPresenceMask();
            context = data_ov008_02090f00;
            i = 1;
            do {
                if ((playerMask & (1 << i)) != 0 &&
                    context->playerTransfer[i].nextChunk < 5) {
                    return 0;
                }
                i++;
            } while ((int)i < 4);

            data_ov008_02090f00->transferredRecord = gPartyMembers;
            data_ov008_02090f00->thresholdSnapshot = data_0204c254;
            data_ov008_02090f00->ruleSnapshot = data_0204c248;
            data_ov008_02090f00->sessionConfig = data_0204c240;
            data_ov008_02090f00->sessionValue = gMissionNumber;
            result = (void *)Ov008_WaitForSnapshotTransferState;
        }
    } else {
        Ov008MenuContext *context = data_ov008_02090f00;
        u32 peerCount = context->peerHeaders[0].sessionState;
        if (peerCount < 4) {
            context->commonTransfer.nextChunk = 0;
            Ov008_SendMenuMessage(9);
            return result;
        }
        if (peerCount < 5) {
            u32 offset;
            u32 remaining;
            Ov008Message68 *outgoing;
            u8 *payload;
            u8 *record = (u8 *)&gPartyMembers;
            u16 copySize = 0x40;

            context->outgoing6.chunkIndex = context->commonTransfer.nextChunk;
            outgoing = &data_ov008_02090f00->outgoing6;
            payload = outgoing->payload;
            offset = (u16)(outgoing->chunkIndex << 6);
            remaining = 0x104 - offset;
            if (remaining < 0x40) {
                copySize = (u16)remaining;
            }
            MI_CpuCopy8(record + offset, payload, copySize);
            Ov008_SendMenuMessage(6);
        } else {
            result = (void *)Ov008_WaitForSnapshotTransferState;
        }
    }
    return result;
}
