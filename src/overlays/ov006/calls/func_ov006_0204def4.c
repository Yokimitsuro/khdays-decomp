#pragma opt_dead_assignments off
/* Ov006_RefreshSelectionSendBlock -- rebuild the Mission Mode selection-send
 * message from the current session mask and four player records. The four dead
 * initial assignments emit no code under this pragma and reproduce the retail
 * register allocation. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct {
    u16 name[11];
    u8 status;
    u8 reserved;
} MissionPeerRecord;

typedef union {
    MissionPeerRecord all[4];
    struct {
        MissionPeerRecord local;
        MissionPeerRecord remote[3];
    } split;
} MissionPeerRecords;

typedef struct {
    u8 sendStarted : 1;
    u8 changed : 1;
    u8 unused : 6;
} MissionSelectionFlags;

typedef struct {
    MissionSelectionFlags flags;
    u8 reserved01[3];
    u32 sessionValue;
    u16 sessionMask;
    u16 playerNames[4][11];
    u8 peerStatus[4];
    u8 reserved66[2];
} MissionSelectionSendBlock;

typedef struct {
    u8 pad_000[0x44];
    MissionPeerRecords records;
    u8 pad_0a4[0x388];
    MissionSelectionSendBlock selectionSendBlock;
    u32 refreshRequested;
    int refreshTimer;
} MissionContext;

extern MissionContext *data_ov006_020565e4;
extern const u16 data_ov006_020563d4[];
extern u16 OS_IsTickAvailable_0x01ff8138(void);
extern void MI_CpuFill8(void *dst, int value, u32 size);
extern u32 OS_IsThreadAvailable(void);
extern void func_020200e4(u16 *dst, const u16 *src);
extern u32 func_ov006_0204fe4c(void);

void func_ov006_0204def4(void) {
    MissionContext *context;
    MissionSelectionSendBlock *sendBlock;
    u16 sessionMask;
    const u16 *placeholderName;
    const u16 *name;
    u8 status;
    u8 playerIndex;
    int changed;

    sendBlock = 0;
    sessionMask = 0;
    placeholderName = 0;
    name = 0;

    sendBlock = &data_ov006_020565e4->selectionSendBlock;
    sessionMask = OS_IsTickAvailable_0x01ff8138();

    data_ov006_020565e4->refreshTimer--;
    if (data_ov006_020565e4->refreshTimer < 0) {
        data_ov006_020565e4->refreshTimer = 0;
    }

    MI_CpuFill8(&data_ov006_020565e4->selectionSendBlock, 0,
                sizeof(MissionSelectionSendBlock));
    data_ov006_020565e4->selectionSendBlock.sessionValue = OS_IsThreadAvailable();
    data_ov006_020565e4->selectionSendBlock.sessionMask = sessionMask;

    placeholderName = data_ov006_020563d4;

    for (playerIndex = 0; playerIndex < 4; playerIndex++) {
        func_020200e4(sendBlock->playerNames[playerIndex], placeholderName);
    }

    context = data_ov006_020565e4;
    changed = 0;
    for (playerIndex = 1; playerIndex < 4; playerIndex++) {
        if (context->records.all[playerIndex].status == 1) {
            changed = 1;
        }
    }

    if (context->refreshRequested != 0) {
        context->refreshRequested = 0;
        changed = 1;
    }
    data_ov006_020565e4->selectionSendBlock.flags.changed = changed;
    if (changed != 0) {
        data_ov006_020565e4->refreshTimer = 30;
    }

    for (playerIndex = 0; playerIndex < 4; playerIndex++) {
        name = data_ov006_020563d4;
        status = 0;

        if ((sessionMask & (1 << playerIndex)) != 0) {
            if (playerIndex == 0) {
                name = data_ov006_020565e4->records.split.local.name;
            } else {
                if (func_ov006_0204fe4c() == 0) {
                    name = data_ov006_020565e4->records.split
                        .remote[playerIndex - 1].name;
                }
                status = data_ov006_020565e4->records
                    .all[playerIndex].status;
                if (data_ov006_020565e4->selectionSendBlock.flags.sendStarted) {
                    status = 0;
                }
            }
        }

        if (name != 0) {
            func_020200e4(sendBlock->playerNames[playerIndex], name);
        }
        sendBlock->peerStatus[playerIndex] = status;
    }
}


