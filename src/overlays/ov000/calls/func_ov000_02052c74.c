typedef unsigned char u8;
typedef unsigned short u16;

typedef struct Ov000Marker {
    int position;
    int reserved;
} Ov000Marker;

typedef struct Ov000MarkerSceneContext {
    u8 pad_0000[0x4ad0];
    int nextState;
    int transitionStep;
    u8 pad_4ad8[8];
    int pendingMode;
    u8 pad_4ae4[0x14];
    u16 pendingId;
    u8 pad_4afa[0x0e];
    int selectedMarker;
    u8 pad_4b0c[0x64];
    int toggle;
    u8 pad_4b74[0x120];
    Ov000Marker markers[4];
    u8 pad_4cb4[0xe0];
    int resetFlag;
} Ov000MarkerSceneContext;

extern Ov000MarkerSceneContext *data_ov000_0205ac24;
extern u16 data_0204c190;

extern void func_ov000_020505e4(int enabled, int mode);
extern void func_02033b78(int soundGroup, int soundId);
extern int func_02020904(void);
extern void func_ov000_0205042c(
    int positionEnabled, int groupEnabled, int primaryEnabled);
extern void func_ov000_0204f7d0(int mode);
extern void func_ov000_02050514(int enabled);

void func_ov000_02052c74(void)
{
    int zero = 0;
    int action = zero;

    switch (data_ov000_0205ac24->pendingId) {
    case 0x20:
        if (data_ov000_0205ac24->toggle != 1) {
            data_ov000_0205ac24->toggle = 1;
            func_ov000_020505e4(zero, data_ov000_0205ac24->toggle);
            func_02033b78(zero, zero);
        }
        break;
    case 0x10:
        if (data_ov000_0205ac24->toggle != 0) {
            data_ov000_0205ac24->toggle = zero;
            func_ov000_020505e4(zero, data_ov000_0205ac24->toggle);
            func_02033b78(zero, zero);
        }
        break;
    default:
        switch (data_0204c190) {
        case 1:
            if (data_ov000_0205ac24->toggle != 0) {
                if (data_ov000_0205ac24->transitionStep != 0) {
                    func_02020904();
                }
                action = 4;
                func_02033b78(zero, 1);
            } else {
                action = 2;
                func_02033b78(zero, 3);
            }
            break;
        case 2:
            action = 2;
            func_02033b78(zero, 3);
            break;
        default:
            break;
        }
        break;
    }

    if (action == zero) {
        return;
    }

    switch (action) {
    case 4:
        if (data_ov000_0205ac24->transitionStep == 0) {
            data_ov000_0205ac24->toggle = zero;
            func_ov000_020505e4(zero, data_ov000_0205ac24->toggle);
            data_ov000_0205ac24->transitionStep =
                data_ov000_0205ac24->transitionStep + 1;
            data_ov000_0205ac24->resetFlag = zero;
            return;
        } else {
            int marker;

            for (marker = 0; marker < 4; marker++) {
                Ov000MarkerSceneContext *current =
                    data_ov000_0205ac24;

                if (marker == current->selectedMarker) {
                    current->markers[marker].position = zero;
                } else {
                    current->markers[marker].position = -0x100000;
                }
            }
        }

        func_ov000_0205042c(1, zero, zero);
        func_ov000_0204f7d0(
            data_ov000_0205ac24->selectedMarker);
        data_ov000_0205ac24->pendingMode = zero;
        data_ov000_0205ac24->transitionStep = zero;
        break;
    case 2:
        data_ov000_0205ac24->transitionStep = zero;
        func_ov000_0205042c(zero, zero, 1);
        func_ov000_020505e4(
            1, data_ov000_0205ac24->selectedMarker);
        break;
    default:
        break;
    }

    data_ov000_0205ac24->toggle = zero;
    func_ov000_02050514(zero);
    data_ov000_0205ac24->nextState = action;
    if (action != zero) {
        data_ov000_0205ac24->resetFlag = zero;
    }
}
