typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;

typedef struct Ov000ModeSelectContext {
    u8 pad_0000[0x14];
    u32 actionTickLow;
    u32 actionTickHigh;
    u16 inputMask;
    u8 pad_001e[2];
    int selection;
    int actionAccepted;
    u8 pad_0028[0x4b9c];
    int activeMode;
    int pendingMode;
} Ov000ModeSelectContext;

extern Ov000ModeSelectContext *data_ov000_0205ac28;
extern u16 data_0204c190;

extern void func_02033b78(int soundGroup, int soundId);
extern void func_ov000_02053ac8(int marker, int mode);
extern u64 func_020031d4(void);
extern void func_ov000_02053b0c(int mode);
extern void func_ov000_02053c3c(int mode);

void func_ov000_02054288(void) {
    Ov000ModeSelectContext *context = data_ov000_0205ac28;
    int action = -1;
    int oldSelection = context->selection;

    switch (context->inputMask) {
    case 0x40:
        context->selection = oldSelection - 1;
        if (data_ov000_0205ac28->selection < 0) {
            data_ov000_0205ac28->selection = 2;
        }
        func_02033b78(0, 0);
        func_ov000_02053ac8(2, data_ov000_0205ac28->activeMode);
        func_ov000_02053ac8(1, data_ov000_0205ac28->activeMode);
        break;
    case 0x80:
        context->selection = oldSelection + 1;
        if (data_ov000_0205ac28->selection > 2) {
            data_ov000_0205ac28->selection = 0;
        }
        func_02033b78(0, 0);
        func_ov000_02053ac8(2, data_ov000_0205ac28->activeMode);
        func_ov000_02053ac8(1, data_ov000_0205ac28->activeMode);
        break;
    default:
        switch (data_0204c190) {
        case 1:
            action = 3;
            func_02033b78(0, 1);
            break;
        case 2: {
            u64 tick = func_020031d4();
            Ov000ModeSelectContext *current;

            action = 4;
            current = data_ov000_0205ac28;
            current->actionTickLow = (u32)tick;
            current->actionTickHigh = (u32)(tick >> 32);
            func_02033b78(0, 3);
            break;
        }
        default:
            break;
        }
        break;
    }

    switch (action) {
    case 3:
        data_ov000_0205ac28->actionAccepted = 1;
        data_ov000_0205ac28->activeMode = action;
        func_ov000_02053ac8(0, data_ov000_0205ac28->activeMode);
        func_ov000_02053ac8(1, data_ov000_0205ac28->activeMode);
        func_ov000_02053ac8(2, data_ov000_0205ac28->activeMode);
        break;
    case 4: {
        Ov000ModeSelectContext *current = data_ov000_0205ac28;
        u64 tick = func_020031d4();

        current->actionTickLow = (u32)tick;
        current->actionTickHigh = (u32)(tick >> 32);
        current->activeMode = 0;
        data_ov000_0205ac28->pendingMode = action;
        break;
    }
    default:
        break;
    }

    if (action != -1) {
        func_ov000_02053b0c(action);
        func_ov000_02053c3c(action);
    }

    if (oldSelection != data_ov000_0205ac28->selection) {
        func_ov000_02053c3c(data_ov000_0205ac28->activeMode);
    }
}
