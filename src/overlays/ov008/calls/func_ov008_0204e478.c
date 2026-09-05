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

typedef struct Ov008MenuContext {
    u8 pad_0000[0x18];
    u32 sessionState;
    Ov008MessageHeader outgoing9;
    Ov008MessageHeader peerHeaders[4];
    u8 pad_0026[0x6a];
    Ov008TransferState playerTransfer[4];
    u8 pad_00a0[0xd0];
    Ov008TransferState commonTransfer;
} Ov008MenuContext;

extern Ov008MenuContext *data_ov008_02090f00;

extern void func_ov008_0204da6c(void);
extern int func_ov008_0204ed3c(void);
extern void func_ov008_0204cadc(u8 messageType);
extern u32 func_ov008_0204ed98(void);
extern void func_ov008_0204e554(void);

void *func_ov008_0204e478(void)
{
    data_ov008_02090f00->sessionState = 5;
    func_ov008_0204da6c();

    if (func_ov008_0204ed3c() != 0) {
        u32 playerMask;
        u32 i;

        func_ov008_0204cadc(9);
        playerMask = func_ov008_0204ed98();
        i = 1;
        do {
            if ((playerMask & (1 << i)) != 0 &&
                data_ov008_02090f00->peerHeaders[i].sessionState < 6) {
                return 0;
            }
            i++;
        } while ((int)i < 4);

        data_ov008_02090f00->playerTransfer[0].nextChunk = 0;
        data_ov008_02090f00->playerTransfer[1].nextChunk = 0;
        data_ov008_02090f00->playerTransfer[2].nextChunk = 0;
        data_ov008_02090f00->playerTransfer[3].nextChunk = 0;
        return (void *)func_ov008_0204e554;
    }

    if (data_ov008_02090f00->peerHeaders[0].sessionState >= 5) {
        Ov008TransferState *transfer =
            &data_ov008_02090f00->commonTransfer;
        transfer->nextChunk = 0;
        return (void *)func_ov008_0204e554;
    }
    return 0;
}
