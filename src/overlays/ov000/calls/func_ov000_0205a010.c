typedef unsigned char u8;
typedef unsigned int u32;
typedef void (*OverlayCallback)(void);

typedef struct {
    u8 pad_0000[0x10c];
    u8 object010c[0x4c];
    u8 object0158[1];
    u8 pad_0159[0x4a7f];
    u8 object4bd8[1];
    u8 pad_4bd9[0x4a91];
    short mode;
    u8 pad_966c[0x3aac];
    u8 tweenBody[0x18];
    u32 tweenFlags01 : 2;
    u32 tweenFinished : 1;
    u32 tweenFlags3_31 : 29;
    u8 pad_d134[0x50];
    int transitionReadyA;
    int transitionReadyB;
} Ov000SceneContext;

extern Ov000SceneContext *NNSi_FndGetCurrentRootHeap(void);
extern void func_0203602c(void *tween, int *value);
extern void func_0201e374(int brightness);
extern void func_0201e3cc(int brightness);
extern void func_ov000_020564f4(void *object);
extern void func_ov000_0205577c(void *object, int value);
extern void func_ov000_0205a3e0(void);
extern void func_ov000_0205a4d4(void);
extern void func_ov000_0205a19c(void);

OverlayCallback func_ov000_0205a010(void) {
    Ov000SceneContext *context = NNSi_FndGetCurrentRootHeap();
    OverlayCallback result = 0;
    int brightness;

    func_0203602c(context->tweenBody, &brightness);
    brightness /= 256;
    if (context->mode == 3) {
        brightness -= 16;
    } else {
        brightness = -brightness;
    }

    func_0201e374(brightness);
    func_0201e3cc(brightness);

    if (context->tweenFinished) {
        context->transitionReadyA = 1;
        context->transitionReadyB = 1;

        switch (context->mode) {
        case 0:
            result = func_ov000_0205a3e0;
            break;
        case 1:
            result = func_ov000_0205a4d4;
            break;
        case 2:
            context->mode = 6;
            result = (OverlayCallback)-2;
            break;
        case 3:
            context->mode = 4;
            result = func_ov000_0205a19c;
            break;
        }
    }

    func_ov000_020564f4(context->object010c);
    func_ov000_0205577c(context->object0158, 0);
    func_ov000_0205577c(context->object4bd8, 0);
    return result;
}
