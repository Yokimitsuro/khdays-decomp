typedef unsigned char u8;

typedef struct {
    u8 first;
    u8 pad_01[0x0b];
    u8 second;
    u8 pad_0d[0x3f];
} MissionCleanupBlock;

typedef struct {
    void *primary_resource;
    void *secondary_resource;
    u8 work_object;
    u8 pad_0009[0x4b];
    u8 scene_object;
    u8 pad_0055[0x461f];
    int scene_active;
    u8 pad_4678[0x414];
    u8 renderer;
    u8 pad_4a8d[0x461f];
    int renderer_active;
    u8 pad_90b0[0x41c];
    void *work_buffers[8];
    u8 pad_94ec[0x274];
    MissionCleanupBlock cleanup_blocks[2];
} Ov006RootContext;

extern Ov006RootContext *data_ov008_02090fa4;
extern void func_02032494(void *object);
extern void func_02032428(void *object);
extern void func_ov008_020559a8(void *object);
extern void func_ov008_0205550c(void *object);
extern void func_0202f818(void *object);
extern void func_0202f9ec(void *object);
extern void func_02024fd4(void *resource);
extern void MIi_CpuClear16(int value, void *destination, unsigned size);
extern void NNSi_FndFreeFromDefaultHeap(void *memory);

void func_ov008_020805ec(void) {
    u8 i;

    if (data_ov008_02090fa4->scene_active != 0) {
        func_02032494(&data_ov008_02090fa4->scene_object);
        func_02032428(&data_ov008_02090fa4->scene_object);
    }

    if (data_ov008_02090fa4->renderer_active != 0) {
        func_02032494(&data_ov008_02090fa4->renderer);
        func_02032428(&data_ov008_02090fa4->renderer);
    }

    func_ov008_020559a8(&data_ov008_02090fa4->work_object);
    func_ov008_0205550c(&data_ov008_02090fa4->work_object);
    func_0202f818(&data_ov008_02090fa4->cleanup_blocks[1].first);
    func_0202f818(&data_ov008_02090fa4->cleanup_blocks[0].first);
    func_0202f9ec(&data_ov008_02090fa4->cleanup_blocks[1].second);
    func_0202f9ec(&data_ov008_02090fa4->cleanup_blocks[0].second);
    func_02024fd4(data_ov008_02090fa4->primary_resource);

    if (data_ov008_02090fa4->secondary_resource != 0) {
        func_02024fd4(data_ov008_02090fa4->secondary_resource);
    }

    for (i = 0; i < 8; i++) {
        MIi_CpuClear16(0, data_ov008_02090fa4->work_buffers[i], 0x600);
        if (data_ov008_02090fa4->work_buffers[i] != 0) {
            NNSi_FndFreeFromDefaultHeap(data_ov008_02090fa4->work_buffers[i]);
            data_ov008_02090fa4->work_buffers[i] = 0;
        }
    }

    data_ov008_02090fa4 = 0;
}
