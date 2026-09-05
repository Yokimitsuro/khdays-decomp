typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Ov008MessageHeader {
    u8 messageType : 4;
    u8 sessionState : 4;
    u8 playerIndex;
} Ov008MessageHeader;

typedef struct Ov008Message4 {
    Ov008MessageHeader header;
    u16 chunkIndex;
} Ov008Message4;

typedef struct Ov008Message6 {
    Ov008MessageHeader header;
    u8 payload[4];
} Ov008Message6;

typedef struct Ov008Message28 {
    Ov008MessageHeader header;
    u8 payload[26];
} Ov008Message28;

typedef struct Ov008Message32 {
    Ov008MessageHeader header;
    u8 payload[30];
} Ov008Message32;

typedef struct Ov008Message68 {
    Ov008MessageHeader header;
    u16 chunkIndex;
    u8 payload[64];
} Ov008Message68;

typedef struct Ov008TransferState {
    Ov008MessageHeader header;
    u16 nextChunk;
} Ov008TransferState;

typedef union Ov008Message3Region {
    Ov008Message32 message3;
    struct {
        u8 pad_0000[8];
        Ov008Message6 peerInput[4];
    } inputRegion;
} Ov008Message3Region;

typedef struct Ov008MenuContext {
    u32 isHost;
    u32 messageActive;
    u32 playerRecordsReady;
    u32 playerTransferReady;
    u32 commonTransferReady;
    u8 pad_0014[4];
    u32 sessionState;
    Ov008MessageHeader outgoing9;
    Ov008MessageHeader peerHeaders[4];
    Ov008Message3Region message3Region;
    Ov008Message6 outgoing2;
    Ov008Message68 outgoing8;
    Ov008TransferState playerTransfer[4];
    Ov008Message28 peerRecords[4];
    Ov008Message28 outgoing1;
    Ov008Message68 outgoing6;
    Ov008TransferState commonTransfer;
    Ov008MessageHeader outgoing7;
    u8 pad_0176[2];
    u8 transferData[0x444];
} Ov008MenuContext;

extern Ov008MenuContext *data_ov008_02090f00;
extern u32 func_02030788(void);
extern int func_ov008_0204ed3c(void);
extern int func_02023588(u32 flagId);
extern void MI_CpuCopy8(const void *src, void *dst, u32 size);

#define context data_ov008_02090f00

void func_ov008_0204cd94(Ov008Message68 *message)
{
    u16 localPlayerIndex = func_02030788();
    u8 messageType;

    if (context == 0 || message == 0) {
        return;
    }

    context->peerHeaders[message->header.playerIndex] = message->header;
    messageType = message->header.messageType;

    if (func_ov008_0204ed3c() != 0) {
        context->messageActive = 1;
        switch (messageType) {
        case 1:
            context->peerRecords[message->header.playerIndex] =
                *(Ov008Message28 *)message;
            context->playerTransfer[message->header.playerIndex].header.playerIndex =
                message->header.playerIndex;
            context->playerTransfer[message->header.playerIndex].nextChunk = 1;
            context->playerRecordsReady = 1;
            return;
        case 2:
            if (func_02023588(0x200c) != 0) {
                return;
            }
            MI_CpuCopy8(message,
                &context->message3Region.inputRegion.peerInput[message->header.playerIndex],
                sizeof(Ov008Message6));
            return;
        case 6:
        {
            u8 playerIndex = message->header.playerIndex;
            if (playerIndex == 0xff) {
                return;
            }
            if (message->chunkIndex <= context->playerTransfer[playerIndex].nextChunk) {
                u32 offset = (u16)(message->chunkIndex << 6);
                u8 *destination =
                    &context->transferData[playerIndex * 0x104];
                u16 copySize = 0x40;
                u32 remaining = 0x104 - offset;
                if (remaining < 0x40) {
                    copySize = remaining;
                }
                if (offset + copySize <= 0x104) {
                    MI_CpuCopy8(message->payload,
                        destination + offset, copySize);
                }
                context->playerTransfer[message->header.playerIndex].header.playerIndex =
                    message->header.playerIndex;
                context->playerTransfer[message->header.playerIndex].nextChunk =
                    message->chunkIndex + 1;
            }
            context->playerTransferReady = 1;
            return;
        }
        case 7:
            context->playerTransfer[message->header.playerIndex].header.playerIndex =
                message->header.playerIndex;
            context->playerTransfer[message->header.playerIndex].nextChunk = 0;
            return;
        case 4:
            context->playerTransfer[message->header.playerIndex] =
                *(Ov008TransferState *)message;
            return;
        default:
            context->messageActive = 0;
            return;
        }
    }

    context->messageActive = 1;
    switch (messageType) {
    case 3:
        MI_CpuCopy8(message, &context->message3Region.message3, sizeof(Ov008Message32));
        return;
    case 5:
        context->commonTransfer =
            ((Ov008TransferState *)message)[localPlayerIndex];
        return;
    case 8:
        if (message->chunkIndex <= context->commonTransfer.nextChunk) {
            u32 offset = (u16)(message->chunkIndex << 6);
            u8 *destination = context->transferData;
            u16 copySize = 0x40;
            u32 remaining = 0x444 - offset;
            if (remaining < 0x40) {
                copySize = remaining;
            }
            if (offset + copySize <= 0x444) {
                MI_CpuCopy8(message->payload,
                    destination + offset, copySize);
            }
            context->commonTransfer.header.playerIndex = localPlayerIndex;
            context->commonTransfer.nextChunk = message->chunkIndex + 1;
        }
        context->commonTransferReady = 1;
        return;
    default:
        context->messageActive = 0;
        return;
    }
}

#undef context
