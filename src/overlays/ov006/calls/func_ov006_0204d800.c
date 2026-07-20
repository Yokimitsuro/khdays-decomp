typedef unsigned char u8;
typedef unsigned int u32;

typedef struct {
    u8 field_00[4];
    u8 key[6];
    u8 field_0a[0xb6];
} MissionRecord;

typedef struct {
    u8 pad_000[0x100];
    volatile u8 row_count;
    u8 pad_101[3];
    MissionRecord rows[4];
    u32 row_states[4];
} MissionContext;

extern MissionContext *data_ov006_020565e4;
extern void MI_CpuCopy8(const void *src, void *dst, u32 size);

void func_ov006_0204d800(const MissionRecord *record) {
    MissionContext *context = data_ov006_020565e4;
    int initial_count = context->row_count;
    int found = 0;
    int i = 0;

    if (initial_count > 0) {
        u8 *key = context->rows[0].key;

        do {
            if (key[0] == record->key[0] &&
                key[1] == record->key[1] &&
                key[2] == record->key[2] &&
                key[3] == record->key[3] &&
                key[4] == record->key[4] &&
                key[5] == record->key[5]) {
                MI_CpuCopy8(record, &context->rows[i],
                            sizeof(MissionRecord));
                data_ov006_020565e4->row_states[i] = 0;
                found = 1;
                break;
            }
            i++;
            key += sizeof(MissionRecord);
        } while (i < context->row_count);
    }

    if (found != 0) {
        return;
    }
    if (data_ov006_020565e4->row_count >= 4) {
        return;
    }

    MI_CpuCopy8(record, &data_ov006_020565e4->rows[i],
                sizeof(MissionRecord));
    data_ov006_020565e4->row_states[i] = 0;
    data_ov006_020565e4->row_count++;
}
