typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct {
    u8 unused_0 : 1;
    u8 flag_1 : 1;
    u8 flag_2 : 1;
    u8 flag_3 : 1;
    u8 unused_4 : 4;
} MissionEntryFlags;

typedef struct {
    u8 index;
    MissionEntryFlags flags;
    s8 state;
    u8 pad_03;
    u16 id;
} MissionEntry;

typedef struct {
    u32 locked : 1;
    u32 unused : 31;
    MissionEntry entries[4];
} MissionEntryBlock;

typedef struct {
    u8 pad_000[0x42c];
    u8 input_state[0x68];
    u8 pad_494[0xc];
    u32 update_mask;
    u32 input_ready;
    MissionEntryBlock entry_block;
} MissionContext;

typedef struct {
    MissionContext *context;
    void *controller_instance;
} MissionGlobals;

extern MissionGlobals data_ov006_020565e4;
extern void func_02023c28(void *instance);
extern int func_02030694(void);
extern void MI_CpuCopy8(const void *src, void *dst, u32 size);

void func_ov006_0204e3ec(const void *data, u32 size) {
    const MissionEntry *entry = data;

    func_02023c28(data_ov006_020565e4.controller_instance);
    if (data == 0) {
        return;
    }

    if (func_02030694() != 0) {
        u8 index;

        if (size != sizeof(MissionEntry)) {
            return;
        }

        index = entry->index;
        if (!data_ov006_020565e4.context->entry_block.locked &&
            entry->id !=
                data_ov006_020565e4.context->entry_block.entries[index].id &&
            entry->state >= 0) {
            MI_CpuCopy8(entry,
                        &data_ov006_020565e4.context->entry_block.entries[index],
                        sizeof(MissionEntry));
        }

        data_ov006_020565e4.context->entry_block.entries[index].flags.flag_2 =
            entry->flags.flag_2;
        data_ov006_020565e4.context->entry_block.entries[index].flags.flag_3 =
            entry->flags.flag_3;

        if (entry->state < 0) {
            data_ov006_020565e4.context->entry_block.entries[index].flags.flag_1 =
                entry->flags.flag_1;
            data_ov006_020565e4.context->entry_block.entries[index].flags.flag_3 =
                0;
        }

        data_ov006_020565e4.context->update_mask |= 1 << index;
        return;
    }

    if (size == sizeof(data_ov006_020565e4.context->input_state)) {
        MI_CpuCopy8(data, data_ov006_020565e4.context->input_state,
                    sizeof(data_ov006_020565e4.context->input_state));
        data_ov006_020565e4.context->input_ready = 1;
    }

    if (size == sizeof(MissionEntryBlock)) {
        MI_CpuCopy8(data, &data_ov006_020565e4.context->entry_block,
                    sizeof(MissionEntryBlock));
        data_ov006_020565e4.context->update_mask = 1;
    }
}
