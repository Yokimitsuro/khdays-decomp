typedef unsigned char     u8;
typedef unsigned short     u16;
typedef unsigned int       u32;
typedef unsigned long long u64;
typedef void (*OverlayCallback)(void);

typedef struct GameState {
    u32 words[0x72b];
} GameState;

typedef struct Ov000LoadSlot {
    int status;
    u8 pad_0004[0x1c];
} Ov000LoadSlot;

typedef struct Ov000LoadSceneContext {
    u8 pad_0000[0x4ace];
    u8 selectedMode;
    u8 pad_4acf[0x0d];
    int loadPhase;
    u32 reserved4ae0;
    u32 timestampLow;
    u32 timestampHigh;
    void *transferBuffers[3];
    u8 pad_4af8[3];
    u8 loadState;
    u8 pad_4afc[8];
    void *loadResource;
    int selectedResult;
    u8 pad_4b0c[0x14];
    Ov000LoadSlot slots[3];
    u8 pad_4b80[0x1f4];
    u8 tweenPulse[0x24];
    GameState gameStateSnapshot;
    u8 pad_6a44[4];
    signed int resultFlags : 16;
    unsigned int resultFlagsRest : 16;
    int validSlotCount;
    u8 pad_6a50[0x0c];
    int bestPhase;
    u32 bestPackedValue;
} Ov000LoadSceneContext;

extern Ov000LoadSceneContext *data_ov000_0205ac24;
extern GameState *data_0204be18;

extern int func_0201eea8(void *resource);
extern u8 func_ov000_0204fc64(int phase);
extern int func_020235d0(int field, int kind);
extern void *NNS_FndAllocFromDefaultExpHeapEx(u32 size, int alignment);
extern void MIi_CpuClear16(u16 value, void *destination, u32 size);
extern void func_ov000_0204f838(void);
extern void func_ov000_0204fdac(void);
extern void func_ov000_020500d0(void);
extern void func_ov000_02051470(void);
extern void func_02035f84(void *tween);
extern u64 func_020031d4(void);
extern void func_ov000_020505e4(int enabled, int mode);
extern void func_ov000_02052124(void);

OverlayCallback func_ov000_02051d3c(void)
{
    int ready = 0;
    Ov000LoadSceneContext *context;

    context = data_ov000_0205ac24;
    if (func_0201eea8(context->loadResource) == 0) {
        return 0;
    }

    context = data_ov000_0205ac24;
    if (func_ov000_0204fc64(context->loadPhase) == 2) {
        int high = func_020235d0(0xc77, 0x10);
        int low = func_020235d0(0xc87, 0x10);
        u32 packed = low | (high << 16);

        if (packed > data_ov000_0205ac24->bestPackedValue) {
            data_ov000_0205ac24->bestPackedValue = packed;
            data_ov000_0205ac24->bestPhase =
                data_ov000_0205ac24->loadPhase;
        }

        data_ov000_0205ac24->loadPhase =
            data_ov000_0205ac24->loadPhase + 1;
        data_ov000_0205ac24->loadState = 0;
        if (data_ov000_0205ac24->loadPhase >= 3) {
            ready = 1;
        }
    }

    if (ready != 0) {
        context = data_ov000_0205ac24;
        *data_0204be18 = context->gameStateSnapshot;

    context->validSlotCount = 0;
    {
        int i;

        for (i = 0; i < 3; i++) {
            context = data_ov000_0205ac24;
            if (context->slots[i].status > 0) {
                context->validSlotCount++;
            }
        }
    }

    {
        int i;

        for (i = 0; i < 3; i++) {
            data_ov000_0205ac24->transferBuffers[i] =
                NNS_FndAllocFromDefaultExpHeapEx(0x800, 2);
            MIi_CpuClear16(
                0, data_ov000_0205ac24->transferBuffers[i], 0x800);
        }
    }

    func_ov000_0204f838();
    func_ov000_0204fdac();
    func_ov000_020500d0();
    func_ov000_02051470();

    func_02035f84(data_ov000_0205ac24->tweenPulse);
    context = data_ov000_0205ac24;
    {
        u64 tick = func_020031d4();

        context->timestampLow = (u32)tick;
        context->timestampHigh = (u32)(tick >> 32);
    }

    {
        int selected;

        selected =
            context->resultFlags != 0 ? 0 : context->bestPhase;
        context->selectedResult = selected;
    }

    data_ov000_0205ac24->selectedMode =
        (u8)data_ov000_0205ac24->selectedResult;
    func_ov000_020505e4(1, data_ov000_0205ac24->selectedResult);
        return func_ov000_02052124;
    }
    return 0;
}
