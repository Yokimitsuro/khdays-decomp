typedef unsigned char u8;
typedef void (*OverlayCallback)(void);

typedef struct {
    OverlayCallback entries[9];
} CallbackTable;

typedef struct {
    u8 pad_0000[0x4c];
    u8 object[1];
    u8 pad_004d[0x4a83];
    int activeState;
    u8 pad_4ad4[0x2c0];
    int field4d94;
    u8 pad_4d98[0x1cb0];
    int transition;
} Ov000SceneContext;

extern const CallbackTable data_ov000_0205a710;
extern Ov000SceneContext *data_ov000_0205ac24;
extern const int data_ov000_0205a6bc[2];

extern void func_ov000_02050514(int enabled);
extern int func_ov000_02055b48(int object, int id);
extern void func_ov000_02055cb4(int object, int entry, int enabled);
extern void func_ov000_020508a0(void);
extern void func_ov000_02050ec4(void);
extern void func_ov000_02052fdc(void);
extern void func_ov000_02051b98(void);

OverlayCallback func_ov000_02052124(void) {
    CallbackTable callbacks = data_ov000_0205a710;
    Ov000SceneContext *context = data_ov000_0205ac24;
    u8 i;
    int entry;

    if ((short)context->transition == 0 || context->activeState == 1) {
        callbacks.entries[context->activeState]();
    }

    if ((short)data_ov000_0205ac24->transition != 0) {
        func_ov000_02050514(0);

        for (i = 0; i < 2; i++) {
            entry = func_ov000_02055b48(
                (int)context->object, data_ov000_0205a6bc[i]);
            func_ov000_02055cb4((int)context->object, entry, 0);
        }

        entry = func_ov000_02055b48((int)context->object, 16);
        func_ov000_02055cb4((int)context->object, entry, 0);
        data_ov000_0205ac24->field4d94 = 0;
    }

    func_ov000_020508a0();
    func_ov000_02050ec4();
    func_ov000_02052fdc();
    func_ov000_02051b98();
    return 0;
}
