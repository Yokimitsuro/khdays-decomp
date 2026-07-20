typedef unsigned char u8;
typedef unsigned short u16;

typedef struct {
    u8 pad_00[0x4c];
    u8 object[1];
} OverlayContext;

extern OverlayContext *data_ov000_0205ac24;
extern int func_ov000_02055b48(void *object, int id);
extern void func_ov000_02055cb4(void *object, int handle, int enabled);
extern void func_ov000_02055d54(void *object, int handle, u16 value);

void func_ov000_02051920(int id, int value) {
    OverlayContext *context = data_ov000_0205ac24;
    int handle = func_ov000_02055b48(context->object, id);

    if (value >= 0) {
        func_ov000_02055cb4(context->object, handle, 1);
        func_ov000_02055d54(context->object, handle, (u16)value);
    } else {
        func_ov000_02055cb4(context->object, handle, 0);
    }
}
