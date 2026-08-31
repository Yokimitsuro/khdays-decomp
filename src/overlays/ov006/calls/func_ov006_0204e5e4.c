typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef void (*MissionCallback)(void);

typedef struct {
    u8 selectable : 1;
    u8 flag_1 : 1;
    u8 flag_2 : 1;
    u8 flag_3 : 1;
    u8 unused_4 : 4;
} MissionEntryFlags;

typedef struct {
    u8 index;
    MissionEntryFlags flags;
    s8 state;
    u8 reserved;
    u16 id;
} MissionEntry;

typedef struct {
    u32 locked : 1;
    u32 unused : 31;
    MissionEntry entries[4];
} MissionEntryBlock;

typedef struct {
    u8 pad_000[0x4a0];
    u32 update_mask;
    u32 input_ready;
    MissionEntryBlock live_entries;
    MissionEntryBlock sent_entries;
    MissionEntry local_entry;
    u8 pad_4e6[2];
    u32 exit_requested;
} MissionContext;

typedef struct {
    MissionContext *context;
    void *controller_instance;
} MissionGlobals;

extern MissionGlobals data_ov006_020565e4;
extern u16 func_01fff974(void);
extern void MI_CpuFill8(void *dst, int value, u32 size);
extern int func_ov006_0204d700(int entry);
extern int func_ov006_0204e5bc(void);
extern int func_02030694(void);
extern u32 func_02030788(void);
extern int func_02031258(int type, u16 *payload, u16 size);
extern void func_02023c14(int state);
extern void func_ov006_0204ece4(void);
extern void func_ov006_0204e8b0(void);

MissionCallback func_ov006_0204e5e4(void) {
    int ready = 0;
    MissionCallback next = 0;

    if (data_ov006_020565e4.context->exit_requested != 0) {
        MissionEntry *entries = data_ov006_020565e4.context->live_entries.entries;
        u16 mask = func_01fff974();
        u8 i;

        MI_CpuFill8(&data_ov006_020565e4.context->live_entries, 0,
                    sizeof(MissionEntryBlock));
        for (i = 0; i < 4; i++) {
            entries[i].state = i;
            entries[i].flags.selectable = (mask & (1 << i)) != 0;
        }
        if (data_ov006_020565e4.context->exit_requested != 0) {
            entries[0].state = func_ov006_0204d700(0);
        }
        data_ov006_020565e4.context->sent_entries =
            data_ov006_020565e4.context->live_entries;
        ready = 1;
    } else {
        if (func_ov006_0204e5bc() != 0) {
            return func_ov006_0204ece4;
        }

        if (func_02030694() != 0) {
            MissionEntry *entries = data_ov006_020565e4.context->live_entries.entries;
            u16 mask = func_01fff974();
            u8 i;

            MI_CpuFill8(&data_ov006_020565e4.context->live_entries, 0,
                        sizeof(MissionEntryBlock));
            for (i = 0; i < 4; i++) {
                entries[i].state = i;
                entries[i].flags.selectable = (mask & (1 << i)) != 0;
            }
            if (data_ov006_020565e4.context->exit_requested != 0) {
                entries[0].state = func_ov006_0204d700(0);
            }
            data_ov006_020565e4.context->sent_entries =
                data_ov006_020565e4.context->live_entries;
            func_02031258(0xd,
                          (u16 *)&data_ov006_020565e4.context->live_entries,
                          sizeof(MissionEntryBlock));
            ready = 1;
        } else if (data_ov006_020565e4.context->update_mask == 1) {
            u16 localPlayer = func_02030788();
            MissionContext *context = data_ov006_020565e4.context;

            context->local_entry = context->live_entries.entries[localPlayer];
            context->local_entry.index = localPlayer;
            data_ov006_020565e4.context->update_mask = 0;
            ready = 1;
        } else {
            data_ov006_020565e4.context->update_mask = 0;
            data_ov006_020565e4.context->local_entry.flags.flag_1 = 0;
            data_ov006_020565e4.context->local_entry.index = func_02030788();
            data_ov006_020565e4.context->local_entry.state = -1;
            data_ov006_020565e4.context->local_entry.id = 0;
            func_02031258(0xd,
                          (u16 *)&data_ov006_020565e4.context->local_entry,
                          sizeof(MissionEntry));
        }
    }

    if (ready != 0) {
        func_02023c14(2);
        next = func_ov006_0204e8b0;
    }
    return next;
}
