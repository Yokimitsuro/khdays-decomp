typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef void (*MissionCallback)(void);

typedef struct {
    u8 selectable : 1;
    u8 request : 1;
    u8 confirmed : 1;
    u8 acknowledged : 1;
    u8 unused : 4;
} MissionEntryFlags;

typedef struct {
    u8 playerIndex;
    MissionEntryFlags flags;
    s8 characterId;
    u8 reserved;
    u16 missionId;
} MissionEntry;

typedef struct {
    u32 locked : 1;
    u32 unused : 31;
    MissionEntry entries[4];
} MissionEntryBlock;

typedef struct {
    u8 sendStarted : 1;
    u8 unused : 7;
} MissionSendFlags;

typedef struct {
    MissionSendFlags flags;
    u8 pad_01[0x60];
    u8 peerStatus[4];
    u8 pad_65[3];
} MissionSendBlock;

typedef struct {
    u8 pad_000[0x42c];
    MissionSendBlock sendBlock;
    u8 pad_494[0x0c];
    u32 entryUpdateMask;
    u32 entryInputReady;
    MissionEntryBlock liveEntries;
    MissionEntryBlock sentEntries;
    MissionEntry localEntry;
    u8 pad_4e6[2];
    u32 exitRequested;
    u16 messageHandle;
} MissionContext;

extern MissionContext *data_ov006_020565e4;
extern int func_ov006_0204d5f8(void);
extern int func_02030694(void);
extern u16 func_01fff974(void);
extern void func_ov006_0204def4(void);
extern int func_02031258(int type, u16 *payload, u16 size);
extern u32 func_02030788(void);
extern void func_02023c14(int state);
extern void func_ov006_0204ece4(void);
extern void func_ov006_0204e5e4(void);

MissionCallback func_ov006_0204f810(void) {
    MissionCallback nextState = 0;
    int synchronizationComplete = 0;
    MissionContext *context = data_ov006_020565e4;

    if (context->exitRequested != 0) {
        synchronizationComplete = 1;
    } else {
        if (func_ov006_0204d5f8() == 0) {
            return func_ov006_0204ece4;
        }

        if (func_02030694() != 0) {
            if (data_ov006_020565e4->entryUpdateMask != 0) {
                u16 sessionMask = func_01fff974();
                int connectedCount = 0;
                int entryOffset = sizeof(MissionEntry);
                int confirmedCount = 0;
                int playerIndex;

                for (playerIndex = 1; playerIndex < 4;
                     playerIndex++, entryOffset += sizeof(MissionEntry)) {
                    data_ov006_020565e4->sendBlock.peerStatus[playerIndex] = 0;
                    if ((sessionMask & (1 << playerIndex)) != 0) {
                        connectedCount++;
                        if (((MissionEntryFlags *)((u8 *)data_ov006_020565e4 +
                                0x4ad + entryOffset))->confirmed) {
                            confirmedCount++;
                        }
                    }
                }

                if (connectedCount != 0 && connectedCount == confirmedCount) {
                    synchronizationComplete = 1;
                }
                data_ov006_020565e4->entryUpdateMask = 0;
            }

            func_ov006_0204def4();
            context = data_ov006_020565e4;
            context->sendBlock.flags.sendStarted = 1;
            func_02031258(0xd, (u16 *)&data_ov006_020565e4->sendBlock,
                          sizeof(MissionSendBlock));
        } else {
            u32 playerIndex;

            context = data_ov006_020565e4;
            playerIndex = func_02030788();
            if (!context->liveEntries.entries[playerIndex].flags.confirmed) {
                context->localEntry.flags.confirmed = 1;
                data_ov006_020565e4->localEntry.playerIndex =
                    (u8)func_02030788();
                func_02031258(0xd,
                              (u16 *)&data_ov006_020565e4->localEntry,
                              sizeof(MissionEntry));
            } else {
                context->messageHandle = 0xffff;
                synchronizationComplete = 1;
            }
        }
    }

    if (synchronizationComplete != 0) {
        func_02023c14(1);
        nextState = func_ov006_0204e5e4;
    }
    return nextState;
}
