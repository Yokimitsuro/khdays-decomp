typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct {
    u16 width;
    u16 height;
} OverlayInitSize;

typedef struct {
    u8 pad_0000[0x68];
    u8 primary_object[0xd0b0];
    u8 secondary_object[0x74];
} OverlayContext;

extern OverlayContext *data_ov000_0205ac3c;
extern OverlayContext *NNSi_FndGetCurrentRootHeap(void);
extern void MI_CpuFill8(void *dst, int value, u32 size);
extern void func_02036298(void *object, const OverlayInitSize *size);
extern void func_02035f84(void *object);

void func_ov000_020589e4(void) {
    OverlayInitSize size;
    OverlayContext *context = NNSi_FndGetCurrentRootHeap();

    MI_CpuFill8(context, 0, sizeof(OverlayContext));
    data_ov000_0205ac3c = context;
    size.width = 10;
    size.height = 3;
    func_02036298(context->primary_object, &size);
    func_02035f84(context->secondary_object);
}
