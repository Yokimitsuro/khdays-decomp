typedef signed char    s8;
typedef unsigned char   u8;
typedef signed short    s16;
typedef unsigned short  u16;
typedef unsigned int    u32;

typedef void *(*Ov000SceneCallback)(void);

typedef struct Ov000TouchEntry {
    u16 x;
    u16 y;
    u16 active;
    u16 state;
} Ov000TouchEntry;

typedef struct Ov000ListSceneContext {
    s16 selection;
    s16 cursor;
    u16 reserved0004;
    u16 buttonState;
    u8 pad_0008[0x5c];
    int touchTracking;
    u16 inputSource;
    u8 pad_006a[0xa2];
    u8 object010c[0x4c];
    u8 object0158;
    u8 pad_0159[0x4a7f];
    u8 object4bd8;
    u8 pad_4bd9[0x4a8b];
    signed int touchPhase : 8;
    unsigned int touchStateRest : 24;
    u8 pad_9668[2];
    s16 mode;
    u8 pad_966c[0x3b18];
    int touchTransition;
    int inputLocked;
} Ov000ListSceneContext;

extern Ov000ListSceneContext *NNSi_FndGetCurrentRootHeap(void);
extern void FS_UnloadOverlayImage_0x020362ec(void *input);
extern u16 func_020362fc(const void *input);
extern void func_ov000_0205a118(Ov000TouchEntry *touch);
extern int func_ov000_020589a0(const Ov000TouchEntry *touch,
                              const u8 *bounds);
extern void func_ov000_02059450(const Ov000TouchEntry *touch);
extern void func_ov000_0205985c(Ov000ListSceneContext *context);
extern void func_ov000_02059d78(void);
extern void func_ov000_02059910(Ov000ListSceneContext *context);
extern void func_ov000_02059680(Ov000ListSceneContext *context);
extern void func_ov000_020596f0(Ov000ListSceneContext *context);
extern void func_ov000_0205976c(Ov000ListSceneContext *context);
extern void func_ov000_020597dc(Ov000ListSceneContext *context);
extern void func_ov000_020564f4(void *object);
extern void func_ov000_0205577c(void *object, int value);
extern void *func_ov000_0205a010(void);

extern const u8 data_ov000_0205a954[4];
extern u16 data_0204c190;

Ov000SceneCallback func_ov000_0205a19c(void)
{
    Ov000ListSceneContext *context = NNSi_FndGetCurrentRootHeap();
    Ov000SceneCallback result = 0;
    Ov000TouchEntry touch;

    FS_UnloadOverlayImage_0x020362ec(&context->inputSource);
    context->buttonState = func_020362fc(&context->inputSource);
    func_ov000_0205a118(&touch);

    if (context->touchTransition != 0) {
        if (touch.active == 0) {
            context->touchTransition = 0;
        }
    }

    if (context->touchTransition == 0 && touch.active != 0) {
        if (context->touchPhase == 0) {
            context->touchPhase = 1;

            if (context->touchTracking == 0 &&
                func_ov000_020589a0(&touch, data_ov000_0205a954) != 0) {
                context->touchTracking = 1;
                func_ov000_02059450(&touch);
            } else if (touch.x >= 0x10 && touch.x < 0xd8 &&
                       touch.y >= 0x10) {
                int threshold = 0x20;
                int row = 0;

                do {
                    if (touch.y < threshold) {
                        context->cursor = context->selection + row;
                        func_ov000_0205985c(context);
                        func_ov000_02059d78();
                        result = func_ov000_0205a010;
                        break;
                    }
                    row++;
                    threshold += 0x10;
                } while (row < 10);
            }
        } else if (context->touchTracking != 0) {
            func_ov000_02059450(&touch);
        }
    } else {
        context->touchPhase = 0;
        if (context->touchTracking != 0) {
            context->touchTracking = 0;
        }

        if (context->inputLocked == 0) {
            if ((data_0204c190 & 1) != 0) {
                func_ov000_0205985c(context);
            } else if ((data_0204c190 & 0x0a) != 0) {
                func_ov000_02059910(context);
            } else if ((context->buttonState & 0x40) != 0) {
                func_ov000_02059680(context);
            } else if ((context->buttonState & 0x80) != 0) {
                func_ov000_020596f0(context);
            } else if ((context->buttonState & 0x20) != 0) {
                func_ov000_0205976c(context);
            } else if ((context->buttonState & 0x10) != 0) {
                func_ov000_020597dc(context);
            }

            if (context->mode != 4) {
                result = func_ov000_0205a010;
            }
        }
    }

    context->inputLocked = 0;
    func_ov000_020564f4(context->object010c);
    func_ov000_0205577c(&context->object0158, 0);
    func_ov000_0205577c(&context->object4bd8, 0);
    return result;
}
