typedef unsigned char u8;
typedef void (*OverlayCallback)(void);

typedef struct {
    OverlayCallback entries[6];
} OverlayCallbackTable;

typedef struct {
    u8 pad_0000[0x2c];
    u8 object_2c[1];
    u8 pad_002d[0x4b];
    u8 object_78[1];
    u8 pad_0079[0x4b4b];
    int callback_index;
} OverlayContext;

extern const OverlayCallbackTable data_ov000_0205a86c;
extern OverlayContext *data_ov000_0205ac28;
extern void func_ov000_020564f4(void *object);
extern void func_ov000_0205577c(void *object, int value);
extern void func_ov000_02054668(void);

int func_ov000_02054108(void) {
    OverlayCallbackTable callbacks = data_ov000_0205a86c;
    OverlayContext *context = data_ov000_0205ac28;

    callbacks.entries[context->callback_index]();
    func_ov000_020564f4(context->object_2c);
    func_ov000_0205577c(context->object_78, 0);
    func_ov000_02054668();
    return 0;
}
