typedef unsigned char u8;
typedef unsigned int u32;

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
    u8 low_state[0x68];
    u8 pad_0a8[0x384];
    u8 input_state[0x68];
} MissionContext;

typedef struct {
    MissionContext *volatile context;
    void *controller_instance;
} MissionGlobals;

extern MissionGlobals data_ov008_02090f24;
extern int func_02001030(void);
extern void func_02023a44(void *instance, void (*callback)(void));
extern void MI_CpuFill8(void *dst, int value, u32 size);
extern void func_ov008_02079998(void);
extern void func_ov008_0207aea0(void);
extern void func_ov008_0207aac8(void);

int func_ov008_0207b1cc(void) {
    int result = 0;

    if (func_02001030() == 1) {
        u8 i;

        func_02023a44(data_ov008_02090f24.controller_instance,
                      func_ov008_0207aea0);
        MI_CpuFill8(data_ov008_02090f24.context->input_state, 0,
                    sizeof(data_ov008_02090f24.context->input_state));
        MI_CpuFill8(data_ov008_02090f24.context->primary_buffer, 0, 0x100);

        for (i = 0; i < 4; i++) {
            MI_CpuFill8(data_ov008_02090f24.context->work_buffers[i].buffer,
                        0, 0x100);
            data_ov008_02090f24.context->work_states[i] = 0;
        }

        MI_CpuFill8(data_ov008_02090f24.context->low_state, 0,
                    sizeof(data_ov008_02090f24.context->low_state));
        result = 1;
    } else {
        func_02023a44(data_ov008_02090f24.controller_instance,
                      func_ov008_0207aac8);
        func_ov008_02079998();
    }

    return result;
}
