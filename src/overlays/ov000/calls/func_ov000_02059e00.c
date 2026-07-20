typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef void (*OverlayCallback)(void);

typedef struct {
    u16 second_value;
    u16 first_value;
    u8 pad_0004[0x965c];
    u32 resource;
} OverlayContext;

typedef struct {
    u32 first;
    u32 second;
} OverlayStartParams;

extern u8 data_ov000_0205abd0[];
extern OverlayContext *NNSi_FndGetCurrentRootHeap(void);
extern void func_ov000_020589e4(void);
extern void func_0201e374(int value);
extern void func_0201e3cc(int value);
extern u32 func_0201ebdc(const void *data, int id);
extern void func_ov000_02059e60(void);

OverlayCallback func_ov000_02059e00(const OverlayStartParams *params) {
    OverlayContext *context = NNSi_FndGetCurrentRootHeap();

    func_ov000_020589e4();
    func_0201e374(-16);
    func_0201e3cc(-16);

    if (params != 0) {
        context->first_value = params->first;
        context->second_value = params->second;
    }

    context->resource = func_0201ebdc(data_ov000_0205abd0, 14);
    return func_ov000_02059e60;
}
