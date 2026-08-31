typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef void (*MissionCallback)(void);

typedef struct {
    u8 selectable : 1;
    u8 request : 1;
    u8 flag_2 : 1;
    u8 acknowledged : 1;
    u8 unused_4 : 4;
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
    u32 active;
    int resourceSlot;
} MissionResourceSlot;

typedef struct {
    u8 pad_000[0x4a0];
    u32 entryUpdateMask;
    u32 entryInputReady;
    MissionEntryBlock liveEntries;
    MissionEntryBlock sentEntries;
    MissionEntry localEntry;
    u8 pad_4e6[2];
    u32 exitRequested;
    u16 messageHandle;
} MissionContext;

typedef struct {
    MissionContext *context;
    void *controllerInstance;
} MissionGlobals;

extern MissionGlobals data_ov006_020565e4;
extern void MI_CpuFill8(void *dst, int value, u32 size);
extern void func_02031618(void *record, int index);
extern int func_ov006_0204d610(int characterId);
extern u32 func_02030788(void);
extern int func_ov006_0204e5bc(void);
extern int func_02030694(void);
extern void func_ov006_0204dc78(void);
extern int func_02031258(int type, u16 *payload, u16 size);
extern u16 func_01fff974(void);
extern u16 func_02031384(int type, void *payload, u16 size);
extern int func_02031440(u32 handle);
extern void func_020307b8(int active);
extern void func_02023c14(int state);
extern void func_ov006_0204eca4(void);
extern void func_ov006_0204ece4(void);

MissionCallback func_ov006_0204e8b0(void) {
    MissionCallback result = 0;
    MissionContext *context = data_ov006_020565e4.context;

    if (context->exitRequested != 0) {
        if (context->liveEntries.locked) {
            MissionEntry *entries = context->liveEntries.entries;
            MissionResourceSlot slot;
            u8 outputIndex;
            u8 entryIndex;

            MI_CpuFill8(&slot, 0, sizeof(slot));
            for (entryIndex = 0; entryIndex < 4; entryIndex++) {
                func_02031618(&slot, entryIndex);
            }

            outputIndex = 0;
            for (entryIndex = 0; entryIndex < 4; entryIndex++) {
                MI_CpuFill8(&slot, 0, sizeof(slot));
                if (entries[entryIndex].flags.selectable) {
                    slot.active = 1;
                    slot.resourceSlot = func_ov006_0204d610(
                        entries[entryIndex].characterId);
                    func_02031618(&slot, outputIndex);
                    outputIndex = (outputIndex + 1) & 0xff;
                }
            }
            result = func_ov006_0204eca4;
        }
    } else {
        func_02030788();
        if (func_ov006_0204e5bc() != 0) {
            return func_ov006_0204ece4;
        }

        if (func_02030694() != 0) {
            if (data_ov006_020565e4.context->entryUpdateMask != 0) {
                u16 sessionMask;
                u8 entryIndex;

                data_ov006_020565e4.context->entryUpdateMask = 0;
                func_ov006_0204dc78();
                func_02031258(0xd,
                    (u16 *)&data_ov006_020565e4.context->liveEntries,
                    sizeof(MissionEntryBlock));

                if (data_ov006_020565e4.context->liveEntries.locked) {
                    MissionResourceSlot slot;
                    MissionEntry *entries;
                    int peerIndex;
                    u8 *peerFlags;
                    u8 *peerFlagsBase;
                    u8 outputIndex;

                    sessionMask = func_01fff974();
                    context = data_ov006_020565e4.context;
                    peerIndex = 1;
                    peerFlagsBase = (u8 *)&context->liveEntries.entries[0].flags;
                    peerFlags = peerFlagsBase + sizeof(MissionEntry);
                    do {
                        if ((sessionMask & (1 << peerIndex)) != 0 &&
                            !((MissionEntryFlags *)peerFlags)->acknowledged) {
                            return 0;
                        }
                        peerIndex++;
                        peerFlags += sizeof(MissionEntry);
                    } while (peerIndex < 4);

                    entries = context->liveEntries.entries;
                    MI_CpuFill8(&slot, 0, sizeof(slot));
                    for (entryIndex = 0; entryIndex < 4; entryIndex++) {
                        func_02031618(&slot, entryIndex);
                    }

                    outputIndex = 0;
                    for (entryIndex = 0; entryIndex < 4; entryIndex++) {
                        MI_CpuFill8(&slot, 0, sizeof(slot));
                        if (entries[entryIndex].flags.selectable) {
                            slot.active = 1;
                            slot.resourceSlot = func_ov006_0204d610(
                                entries[entryIndex].characterId);
                            func_02031618(&slot, outputIndex);
                            outputIndex = (outputIndex + 1) & 0xff;
                        }
                    }
                    result = func_ov006_0204eca4;
                }
            }
        } else {
            context = data_ov006_020565e4.context;
            if (context->liveEntries.locked) {
                if (context->messageHandle == 0xffff) {
                    u16 messageHandle;

                    context->localEntry.flags.acknowledged = 1;
                    messageHandle = func_02031384(
                        0xd, &data_ov006_020565e4.context->localEntry,
                        sizeof(MissionEntry));
                    data_ov006_020565e4.context->messageHandle = messageHandle;
                    return 0;
                }

                if (func_02031440(context->messageHandle) == 0) {
                    MissionResourceSlot slot;
                    MissionEntry *entries;
                    u8 outputIndex;
                    u8 entryIndex;

                    data_ov006_020565e4.context->messageHandle = 0xffff;
                    context = data_ov006_020565e4.context;
                    entries = context->liveEntries.entries;
                    MI_CpuFill8(&slot, 0, sizeof(slot));
                    for (entryIndex = 0; entryIndex < 4; entryIndex++) {
                        func_02031618(&slot, entryIndex);
                    }

                    outputIndex = 0;
                    for (entryIndex = 0; entryIndex < 4; entryIndex++) {
                        MI_CpuFill8(&slot, 0, sizeof(slot));
                        if (entries[entryIndex].flags.selectable) {
                            slot.active = 1;
                            slot.resourceSlot = func_ov006_0204d610(
                                entries[entryIndex].characterId);
                            func_02031618(&slot, outputIndex);
                            outputIndex = (outputIndex + 1) & 0xff;
                        }
                    }
                    result = func_ov006_0204eca4;
                }
            } else {
                func_02031258(0xd, (u16 *)&context->localEntry,
                              sizeof(MissionEntry));
            }
        }
    }

    if (result == func_ov006_0204eca4) {
        func_020307b8(1);
        func_02023c14(3);
    }
    return result;
}
