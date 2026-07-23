typedef unsigned char u8;
typedef unsigned int u32;
typedef void (*OverlayCallback)(void);

typedef struct {
    u32 words[0x72b];
} GameState;

typedef struct {
    int status;
    u8 pad_0004[0x1c];
} MenuSlot;

typedef struct {
    u8 pad_0000[0x4acc];
    u8 active;
    u8 positionShifted;
    u8 pad_4ace[0x36];
    void *fontResource;
    u8 pad_4b08[0x18];
    MenuSlot slots[3];
    u8 pad_4b80[0x218];
    GameState gameStateSnapshot;
    u8 pad_6a44[0x20];
} Ov000SceneContext;

extern Ov000SceneContext *data_ov000_0205ac24;
extern GameState *data_0204be18;
extern u8 data_ov000_0205aae4[];

extern Ov000SceneContext *NNSi_FndGetCurrentRootHeap(void);
extern void MI_CpuFill8(void *destination, u8 value, u32 size);
extern void *func_0201ebdc(const void *data, int id);
extern void func_ov000_02051d3c(void);

OverlayCallback func_ov000_02051c48(int mode) {
    Ov000SceneContext *context;
    int i;

    NNSi_FndGetCurrentRootHeap();
    context = NNSi_FndGetCurrentRootHeap();
    data_ov000_0205ac24 = context;
    MI_CpuFill8(context, 0, sizeof(Ov000SceneContext));

    data_ov000_0205ac24->gameStateSnapshot = *data_0204be18;
    data_ov000_0205ac24->fontResource =
        func_0201ebdc(data_ov000_0205aae4, 14);

    switch (mode) {
    case 1:
        data_ov000_0205ac24->positionShifted = 1;
    case 2:
        data_ov000_0205ac24->active = 1;
    }

initialize_slots:
    for (i = 0; i < 3; i++) {
        data_ov000_0205ac24->slots[i].status = -1;
    }

    return func_ov000_02051d3c;
}
