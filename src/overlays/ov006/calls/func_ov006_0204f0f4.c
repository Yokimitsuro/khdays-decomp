#pragma opt_dead_assignments off
/* Ov006_MissionPeerSyncState -- synchronize Mission Mode peer names and
 * presence latches while the scene connection state advances. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef void (*MissionCallback)(void);

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
    u8 flags;
    u8 reserved01[3];
    u32 sessionValue;
    u16 sessionMask;
    u16 playerNames[4][11];
    u8 peerStatus[4];
    u8 reserved66[2];
} MissionSelectionSendBlock;

typedef struct {
    u8 pad_000[0x28];
    u32 transitionRequested;
    u32 sendBusy;
    u8 pad_030[0x10];
    u8 remotePeerCapacity;
    u8 pad_041[3];
    MissionPeerRecords records;
    u8 remotePeerActive[3];
    u8 pad_0a7[0x385];
    MissionSelectionSendBlock selectionSendBlock;
    u32 refreshRequested;
} MissionContext;

typedef struct {
    u32 header;
    u8 payload[0x50];
} MissionSelectionBuffer;

extern MissionContext *data_ov006_020565e4;
extern u16 data_ov006_02056600[];

extern int func_02001030(void);
extern void func_ov105_020bf1e4(u32 value);
extern void func_02003a20(MissionSelectionBuffer *buffer);
extern u16 *func_020200e4(u16 *dst, const u16 *src);
extern void MI_CpuCopy8(const void *src, void *dst, u32 size);
extern void func_ov105_020bf27c(void);
extern void func_ov006_0204de5c(void);
extern u16 OS_IsTickAvailable_0x01ff8138(void);
extern int func_ov006_0204db14(int peerIndex);
extern void func_ov006_0204d9fc(int peerIndex, u16 *name, u32 size);
extern void MI_CpuFill8(void *dst, int value, u32 size);
extern void func_ov006_0204def4(void);
extern int func_ov006_0204dae0(void);
extern int func_ov006_0204da3c(const void *payload, u32 payloadSize);
extern void func_ov006_0204ece4(void);

MissionCallback func_ov006_0204f0f4(void) {
    MissionSelectionBuffer localProfile;
    MissionCallback nextState = 0;

    switch (func_02001030()) {
    case 1: {
        MissionContext *context;

        func_ov105_020bf1e4(0x800356);
        context = data_ov006_020565e4;
        func_02003a20(&localProfile);
        func_020200e4(context->records.split.local.name,
                      (u16 *)localProfile.payload);
        *(u16 *)&context->records.split.local.status = 1;
        data_ov006_020565e4->remotePeerCapacity = 3;
        MI_CpuCopy8(&data_ov006_020565e4->records.split.local,
                    data_ov006_02056600, sizeof(MissionPeerRecord));
        func_ov105_020bf27c();
        break;
    }
    case 3:
        break;
    case 7:
        func_ov006_0204de5c();
        break;
    case 4: {
        u16 sessionMask;
        u8 *remotePeerActive;
        u32 peerIndex;
        int remoteIndex;

        peerIndex = 0;
        remotePeerActive = 0;
        remotePeerActive = data_ov006_020565e4->remotePeerActive;
        sessionMask = OS_IsTickAvailable_0x01ff8138();

        peerIndex = 1;
        goto check_peer;
    process_peer:
        {
            if (func_ov006_0204db14(peerIndex) != 0) {
                func_ov006_0204d9fc(
                    peerIndex,
                    data_ov006_020565e4->records.split.remote[peerIndex - 1].name,
                    sizeof(MissionPeerRecord));
                remoteIndex = peerIndex - 1;
                remotePeerActive[remoteIndex] = 1;
                data_ov006_020565e4->transitionRequested = 1;
                data_ov006_020565e4->sendBusy = 0;
            } else {
                remoteIndex = peerIndex - 1;
                if (remotePeerActive[remoteIndex] != 0 &&
                    (sessionMask & (1 << peerIndex)) == 0) {
                    remotePeerActive[remoteIndex] = 0;
                data_ov006_020565e4->selectionSendBlock.peerStatus[peerIndex] = 0;
                MI_CpuFill8(
                    data_ov006_020565e4->selectionSendBlock.playerNames[peerIndex],
                    0, sizeof(data_ov006_020565e4->selectionSendBlock.playerNames[0]));
                MI_CpuFill8(
                    &data_ov006_020565e4->records.split.remote[peerIndex - 1], 0,
                    sizeof(MissionPeerRecord));
                    data_ov006_020565e4->refreshRequested = 1;
                }
            }
            peerIndex = (u8)(peerIndex + 1);
        }
    check_peer:
        if (peerIndex < 4) {
            goto process_peer;
        }

        func_ov006_0204def4();
        if (func_ov006_0204dae0() != 0) {
            func_ov006_0204da3c(
                &data_ov006_020565e4->selectionSendBlock,
                sizeof(MissionSelectionSendBlock));
        }
        break;
    }
    default:
        data_ov006_020565e4->sendBusy = 0;
        nextState = func_ov006_0204ece4;
        break;
    }

    return nextState;
}