typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;

typedef struct Ov000SubSceneContext {
    u8 pad_0000[0x14];
    u32 tickLow;
    u32 tickHigh;
    u16 inputCode;
    u8 pad_001e[2];
    int setupSlot;
    int baseMode;
    u8 pad_0028[0x4b9c];
    int transitionMode;
} Ov000SubSceneContext;

extern Ov000SubSceneContext *volatile data_ov000_0205ac28;
extern volatile u16 data_0204c190;
extern void func_02033b78(int first, int sound);
extern void func_ov000_02053ac8(int selector, int argument);
extern u64 func_020031d4(void);
extern void func_ov000_02054c50(int slot);
extern void func_ov000_02053b0c(int mode);
extern void func_ov000_02053c3c(int mode);

void func_ov000_020544b0(void) {
    int mode = -1;
    Ov000SubSceneContext *context = data_ov000_0205ac28;
    int previousBaseMode = context->baseMode;

    if (context->inputCode == 0x10) {
        goto input_10;
    }
    if (context->inputCode != 0x20) {
        goto input_other;
    }
    if (previousBaseMode != 0) {
        context->baseMode = 0;
        func_02033b78(0, 0);
    }
    goto input_done;

input_10:
    if (previousBaseMode != 1) {
        context->baseMode = 1;
        func_02033b78(0, 0);
    }
    goto input_done;

input_other:
    {
        u16 externalCode = data_0204c190;

    switch (externalCode) {
    case 1:
        if (previousBaseMode == 0) {
            mode = 5;
        } else {
            mode = 2;
            func_02033b78(0, 3);
        }
        break;
    case 2:
        mode = 2;
        func_02033b78(0, 3);
        break;
    }
    }

input_done:
    switch (mode) {
    case 2:
        data_ov000_0205ac28->transitionMode = mode;
        func_ov000_02053ac8(
            0, data_ov000_0205ac28->transitionMode);
        func_ov000_02053ac8(
            1, data_ov000_0205ac28->transitionMode);
        func_ov000_02053ac8(
            2, data_ov000_0205ac28->transitionMode);
        break;
    case 5:
    {
        u64 tick;

        context = data_ov000_0205ac28;
        tick = func_020031d4();
        context->tickLow = (u32)tick;
        context->tickHigh = (u32)(tick >> 32);
        context->transitionMode = mode;
        func_ov000_02054c50(data_ov000_0205ac28->setupSlot);
    }
        break;
    }

    if (mode != -1) {
        func_ov000_02053b0c(mode);
        func_ov000_02053c3c(mode);
    }

    {
        Ov000SubSceneContext *finalContext =
            data_ov000_0205ac28;

        if (previousBaseMode != finalContext->baseMode) {
            func_ov000_02053c3c(finalContext->transitionMode);
        }
    }
}
