typedef unsigned char u8;
typedef unsigned int u32;
typedef void (*MissionCallback)(void);

typedef struct {
    void *buffer;
    u32 field_4;
} MissionWorkBuffer;

typedef struct {
    void *primary_buffer;
    u8 pad_004[4];
    MissionWorkBuffer work_buffers[4];
    u8 pad_028[0x474];
    u32 active_object;
    u8 pad_4a0[0x48];
    u32 exit_requested;
    u8 pad_4ec[8];
} MissionContext;

typedef struct {
    MissionContext *context;
    void *controller_instance;
} MissionGlobals;

extern MissionGlobals data_ov006_020565e4;
extern void *NNSi_FndGetCurrentRootHeap(void);
extern void MI_CpuFill8(void *dst, int value, u32 size);
extern int func_02023588(int id);
extern int func_02030640(void);
extern int func_02030670(void);
extern void func_02023c14(int enabled);
extern void func_02030cf8(int slot, MissionCallback callback);
extern void *NNS_FndAllocFromDefaultExpHeapEx(u32 size, int alignment);
extern void func_02001054(void);
extern void func_ov006_0204ecdc(void);
extern void func_ov006_0204e3ec(void);
extern void func_ov006_0204e5e4(void);
extern void func_ov006_0204e35c(void);

MissionCallback func_ov006_0204e1ec(int immediate_exit) {
    int i;

    data_ov006_020565e4.context = NNSi_FndGetCurrentRootHeap();
    MI_CpuFill8(data_ov006_020565e4.context, 0, sizeof(MissionContext));
    data_ov006_020565e4.context->exit_requested =
        func_02023588(0x200d) != 0;

    if (immediate_exit != 0) {
        return func_ov006_0204ecdc;
    }

    if (data_ov006_020565e4.context->exit_requested != 0 ||
        (func_02030640() != 0 && func_02030670() != 0)) {
        data_ov006_020565e4.context->active_object = 1;
        func_02023c14(1);
        func_02030cf8(0xd, func_ov006_0204e3ec);
        return func_ov006_0204e5e4;
    }

    data_ov006_020565e4.context->primary_buffer =
        NNS_FndAllocFromDefaultExpHeapEx(0x100, 0x20);
    for (i = 0; i < 4; i++) {
        data_ov006_020565e4.context->work_buffers[i].buffer =
            NNS_FndAllocFromDefaultExpHeapEx(0x100, 0x20);
    }

    func_02001054();
    func_02023c14(0);
    return func_ov006_0204e35c;
}
