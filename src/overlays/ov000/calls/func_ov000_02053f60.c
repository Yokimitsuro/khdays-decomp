typedef unsigned char  u8;
typedef unsigned int u32;

typedef struct Ov000SubSceneContext {
    void *heapBuffers[4];
    u8 pad_0010[0x18];
    void *resource0028;
    u8 sceneBlock[0x4c];
    u8 objectList[0x4a88];
    void *resource4b00;
    u8 surface0[0x3c];
    u8 surface1[0x3c];
    u8 surface2[0x3c];
    u8 variantSource[0x0c];
} Ov000SubSceneContext;

extern Ov000SubSceneContext *volatile data_ov000_0205ac28;
extern void func_ov000_02056960(void *resource);
extern void func_0202ffbc(void *surface);
extern void NNSi_FndFreeFromDefaultHeap(void *allocation);
extern void func_ov000_020568c8(void *sceneBlock);
extern void func_ov000_0205651c(void *sceneBlock);
extern void func_ov000_02055ad8(void *objectList);
extern void func_ov000_02055b0c(void *objectList);
extern void func_ov000_02055750(void *objectList);
extern void func_02024fd4(void *resource);
extern void *G2S_GetBG0ScrPtr(void);
extern void *G2S_GetBG1ScrPtr(void);
extern void *G2S_GetBG2ScrPtr(void);
extern void *G2S_GetBG3ScrPtr(void);
extern void *G2S_GetBG0CharPtr(void);
extern void *G2S_GetBG1CharPtr(void);
extern void *G2S_GetBG2CharPtr(void);
extern void *G2S_GetBG3CharPtr(void);
extern void MIi_CpuClearFast(int value, void *destination, u32 size);

void func_ov000_02053f60(void) {
    Ov000SubSceneContext *context = data_ov000_0205ac28;
    u8 i;

    func_ov000_02056960(context->variantSource);
    func_0202ffbc(data_ov000_0205ac28->surface0);
    func_0202ffbc(data_ov000_0205ac28->surface1);
    func_0202ffbc(data_ov000_0205ac28->surface2);

    {
        void *allocation = data_ov000_0205ac28->resource4b00;

        if (allocation != 0) {
            NNSi_FndFreeFromDefaultHeap(allocation);
            data_ov000_0205ac28->resource4b00 = 0;
        }
    }

    func_ov000_020568c8(context->sceneBlock);
    func_ov000_0205651c(context->sceneBlock);
    func_ov000_02055ad8(context->objectList);
    func_ov000_02055b0c(context->objectList);
    func_ov000_02055750(context->objectList);

    for (i = 0; i < 4; i++) {
        void *allocation = data_ov000_0205ac28->heapBuffers[i];

        if (allocation != 0) {
            NNSi_FndFreeFromDefaultHeap(allocation);
            data_ov000_0205ac28->heapBuffers[i] = 0;
        }
    }

    func_02024fd4(data_ov000_0205ac28->resource0028);

    MIi_CpuClearFast(0, G2S_GetBG0ScrPtr(), 0x800);
    MIi_CpuClearFast(0, G2S_GetBG1ScrPtr(), 0x800);
    MIi_CpuClearFast(0, G2S_GetBG2ScrPtr(), 0x800);
    MIi_CpuClearFast(0, G2S_GetBG3ScrPtr(), 0x800);
    MIi_CpuClearFast(0, G2S_GetBG0CharPtr(), 0x20);
    MIi_CpuClearFast(0, G2S_GetBG1CharPtr(), 0x20);
    MIi_CpuClearFast(0, G2S_GetBG2CharPtr(), 0x20);
    MIi_CpuClearFast(0, G2S_GetBG3CharPtr(), 0x20);

    data_ov000_0205ac28 = 0;
}
