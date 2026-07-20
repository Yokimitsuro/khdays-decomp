typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct {
    u32 field_00[0xf];
    u16 item_count;
    u16 field_3e;
    u16 ready;
    u16 field_42;
    u32 field_44[0x1f];
} MissionRecord;

typedef struct {
    void *buffer;
    u32 field_4;
} MissionWorkBuffer;

typedef struct {
    void *primary_buffer;
    u8 pad_004[4];
    MissionWorkBuffer work_buffers[4];
    u8 pad_028[8];
    u32 work_states[4];
    MissionRecord active_record;
    volatile u8 row_count;
    u8 pad_101[3];
    MissionRecord rows[4];
    u32 row_states[4];
    u8 selection_block[0x18];
    u8 input_state[0x68];
} MissionContext;

typedef struct {
    MissionContext *context;
    void *controller_instance;
} MissionGlobals;

extern MissionGlobals data_ov006_020565e4;
extern int func_02001030(void);
extern void func_02023a44(void *instance, void (*callback)(void));
extern void MI_CpuFill8(void *dst, int value, u32 size);
extern void func_ov006_0204db2c(void);
extern void func_ov006_0204eecc(void);
extern void func_ov006_0204ecdc(void);

int func_ov006_0204f554(int index) {
    int result = 0;
    MissionRecord *record = &data_ov006_020565e4.context->rows[index];

    if (record->item_count >= 16 && record->ready == 1) {
        if (func_02001030() == 1) {
            u8 i;

            func_02023a44(data_ov006_020565e4.controller_instance,
                          func_ov006_0204eecc);
            data_ov006_020565e4.context->active_record =
                data_ov006_020565e4.context->rows[index];
            MI_CpuFill8(data_ov006_020565e4.context->input_state, 0,
                        sizeof(data_ov006_020565e4.context->input_state));
            MI_CpuFill8(data_ov006_020565e4.context->primary_buffer, 0, 0x100);

            for (i = 0; i < 4; i++) {
                MI_CpuFill8(data_ov006_020565e4.context->work_buffers[i].buffer,
                            0, 0x100);
                data_ov006_020565e4.context->work_states[i] = 0;
            }
            result = 1;
        } else {
            func_02023a44(data_ov006_020565e4.controller_instance,
                          func_ov006_0204ecdc);
            func_ov006_0204db2c();
        }
    }

    return result;
}
