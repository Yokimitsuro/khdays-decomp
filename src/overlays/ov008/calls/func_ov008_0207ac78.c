typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef void (*MissionCallback)(void);

typedef struct {
    u32 field_00[0x30];
} MissionRecord;

typedef struct {
    void *buffer;
    u32 field_4;
} MissionWorkBuffer;

typedef struct {
    void *primary_buffer;
    u8 pad_004[4];
    MissionWorkBuffer work_buffers[4];
    u32 transition_requested;
    u32 field_02c;
    u32 field_030;
    u8 pad_034[0xc];
    MissionRecord active_record;
    u8 pad_100[0x3e8];
    u32 exit_requested;
    u8 pad_4ec[2];
    u8 mode;
    u8 signal;
    u8 pad_4f0[4];
} MissionContext;

typedef struct {
    MissionContext *context;
    void *controller_instance;
} MissionGlobals;

extern MissionGlobals data_ov008_02090f24;
extern int func_02001030(void);
extern void func_ov105_020bf1f4(u8 *mode, int value);
extern int func_ov105_020bf7f4(int value, MissionRecord *record);
extern void func_ov105_020bf8c8(MissionCallback callback);
extern u16 func_ov105_020bf25c(void);
extern void MI_CpuFill8(void *dst, int value, u32 size);
extern void func_ov008_0207aad0(void);
extern void func_ov008_020797e8(void);
extern void func_ov008_0207adb4(void);
extern void func_ov008_0207aac8(void);

MissionCallback func_ov008_0207ac78(void) {
    MissionCallback result = 0;

    switch (func_02001030()) {
    case 1:
        data_ov008_02090f24.context->signal = 0;
        func_ov105_020bf1f4(&data_ov008_02090f24.context->mode, 1);
        if (func_ov105_020bf7f4(1,
                &data_ov008_02090f24.context->active_record) == 0) {
            result = func_ov008_0207aad0;
        }
        break;

    case 3:
    case 8:
        break;

    case 4:
        data_ov008_02090f24.context->mode = 0;
        func_ov105_020bf8c8(func_ov008_020797e8);
        data_ov008_02090f24.context->transition_requested = 1;
        data_ov008_02090f24.context->field_02c = 0;
        data_ov008_02090f24.context->field_030 = 0;
        MI_CpuFill8(data_ov008_02090f24.context->work_buffers[0].buffer,
                    0, 4);
        result = func_ov008_0207adb4;
        break;

    default:
        if (func_ov105_020bf25c() == 12) {
            data_ov008_02090f24.context->signal = 1;
            return func_ov008_0207aac8;
        }
        if (func_ov105_020bf25c() == 11) {
            data_ov008_02090f24.context->signal = 1;
            return func_ov008_0207aac8;
        }
        result = func_ov008_0207aad0;
        break;
    }

    return result;
}
