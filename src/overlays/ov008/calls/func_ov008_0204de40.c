typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Ov008MessageHeader {
    u8 messageType : 4;
    u8 sessionState : 4;
    u8 playerIndex;
} Ov008MessageHeader;

typedef struct Ov008TransferState {
    Ov008MessageHeader header;
    u16 nextChunk;
} Ov008TransferState;

typedef struct Ov008Message28 {
    Ov008MessageHeader header;
    u8 payload[26];
} Ov008Message28;

typedef struct Ov008MenuContext {
    u8 pad_0000[8];
    u32 playerRecordsReady;
    u8 pad_000c[0xc];
    u32 sessionState;
    Ov008MessageHeader outgoing9;
    Ov008MessageHeader peerHeaders[4];
    u8 pad_0026[0x6a];
    Ov008TransferState playerTransfer[4];
    Ov008Message28 peerRecords[4];
    Ov008Message28 outgoingRecord;
} Ov008MenuContext;

extern u32   func_02030788(void);
extern u32   func_ov008_0204cac0(void);
extern void  func_ov008_0204da6c(void);
extern int   func_ov008_0207baf8(void);
extern int   func_ov008_0204ed3c(void);
extern void  func_ov008_0204cadc(u8 messageType);
extern void  func_ov008_0204e04c(void);
extern void  func_ov008_0204dfb4(void);
extern Ov008MenuContext *data_ov008_02090f00;

void *func_ov008_0204de40(void)
{
    void *result;
    u32 playerMask;

    func_02030788();
    result = 0;
    playerMask = func_ov008_0204cac0();
    func_ov008_0204da6c();
    data_ov008_02090f00->sessionState = 1;

    if (func_ov008_0207baf8() != 0) {
        data_ov008_02090f00->peerRecords[0] =
            data_ov008_02090f00->outgoingRecord;
        return (void *)func_ov008_0204e04c;
    }

    if (func_ov008_0204ed3c() != 0) {
        Ov008MenuContext *context = data_ov008_02090f00;
        if (context->playerRecordsReady == 0) {
            func_ov008_0204cadc(9);
        } else {
            u32 i;
            context->playerRecordsReady = 0;
            func_ov008_0204cadc(5);
            context = data_ov008_02090f00;
            i = 1;
            do {
                if ((playerMask & (1 << i)) != 0 &&
                    context->playerTransfer[i].nextChunk < 1) {
                    return 0;
                }
                i++;
            } while ((int)i < 4);

            data_ov008_02090f00->peerRecords[0] =
                data_ov008_02090f00->outgoingRecord;
            result = (void *)func_ov008_0204dfb4;
        }
    } else {
        u32 peerCount = data_ov008_02090f00->peerHeaders[0].sessionState;
        if (peerCount < 1) {
            func_ov008_0204cadc(9);
            return result;
        }
        if (peerCount >= 2) {
            result = (void *)func_ov008_0204dfb4;
        } else {
            func_ov008_0204cadc(1);
        }
    }
    return result;
}
