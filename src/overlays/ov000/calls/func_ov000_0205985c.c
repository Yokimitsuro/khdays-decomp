typedef unsigned char u8;
typedef signed short s16;
typedef unsigned short u16;

typedef struct {
    s16 value_0;
    s16 selection;
    u8 pad_0004[0x9666];
    u16 mode_changed;
    u8 pad_966c[0x3aac];
    u8 transition_object[0x20];
    int transition_mode;
} OverlayContext;

extern void func_02033b78(int first, int second);
extern void func_02020904(void);
extern void func_02033fec(int first, int second);
extern void func_02035fb0(void *object, int x, int y, int scale, int duration);
extern void func_02035ffc(void *object);

void func_ov000_0205985c(OverlayContext *context) {
    func_02033b78(0, 1);
    func_02020904();
    func_02033fec(0, 15);
    func_02035fb0(context->transition_object, 0, 0, 0x1000, 500);
    func_02035ffc(context->transition_object);

    context->mode_changed = 0;
    switch (context->selection) {
    case 0:
        context->transition_mode = 0;
        context->mode_changed = 1;
        break;
    case 27:
        context->transition_mode = 1;
        context->mode_changed = 1;
        break;
    default:
        context->mode_changed = 0;
        break;
    }
}
