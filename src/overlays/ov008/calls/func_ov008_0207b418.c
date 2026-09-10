typedef unsigned char u8;
typedef unsigned int u32;

typedef struct {
    u8 sendStarted : 1;
    u8 changed : 1;
    u8 unused : 6;
} MissionSelectionSendFlags;

typedef struct {
    MissionSelectionSendFlags flags;
    u8 reserved01[3];
    u32 sessionValue;
    unsigned short sessionMask;
    unsigned short playerNames[4][11];
    u8 peerStatus[4];
    u8 reserved66[2];
} MissionSelectionSendBlock;

typedef struct {
    u8 pad_000[0x2c];
    u32 sendBusy;
    u8 pad_030[0x3fc];
    MissionSelectionSendBlock selectionSendBlock;
    u8 pad_494[0x0c];
    u32 entryUpdateMask;
    u8 pad_4a4[0x44];
    u32 exitRequested;
} MissionContext;

extern int data_ov008_02090f24;
#define CONTEXT (*(MissionContext **)&data_ov008_02090f24)
extern int func_ov105_020be3f0();
extern int func_ov008_02079274(void);
extern void func_ov008_02079d60(void);
extern int func_ov008_0207994c(void);
extern int func_ov008_020798a8(const void *payload, u32 payloadSize);
extern void func_ov008_0207aad0(void);
extern void func_ov008_0207b4e4(void);

int func_ov008_0207b418(void)
{
    int zero = 0;
    int nextState = zero;

    if (CONTEXT->exitRequested != zero) {
        nextState = (int)func_ov008_0207b4e4;
        CONTEXT->sendBusy = zero;
    } else {
        if (!CONTEXT->selectionSendBlock.flags.sendStarted) {
            if (func_ov105_020be3f0(zero, zero) == zero) {
                return nextState;
            }
        }
        if (func_ov008_02079274() == zero) {
            return (int)func_ov008_0207aad0;
        }
        func_ov008_02079d60();
        CONTEXT->selectionSendBlock.flags.sendStarted = 1;
        if (func_ov008_0207994c() != zero) {
            if (func_ov008_020798a8(
                    &CONTEXT->selectionSendBlock,
                    sizeof(MissionSelectionSendBlock)) != zero) {
                CONTEXT->entryUpdateMask = zero;
                nextState = (int)func_ov008_0207b4e4;
            }
        }
    }
    return nextState;
}
