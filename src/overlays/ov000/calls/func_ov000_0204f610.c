typedef unsigned char u8;
typedef void (*OverlayCallback)(void);

typedef struct {
    int state_0;
    u8 pad_0004[8];
    u8 update_object[0x4bdc];
    u8 overlay_image[0x58];
    int transition_flag;
    u8 pad_4c44[0x42c];
    int sharing_handle;
    int sharing_state;
} OverlayContext;

extern OverlayContext *NNSi_FndGetCurrentRootHeap(void);
extern void FS_UnloadOverlayImage_0x020362ec(void *image);
extern void func_020362fc(void *image);
extern void func_ov000_020548c8(void);
extern void func_0202aa9c(void *object);
extern int func_ov000_020548e0(void);
extern void WM_EndKeySharing_0x02023ad0(int handle);
extern void func_ov000_0204d72c(void);
extern void func_ov000_0204cac0(void);
extern void func_ov000_0204d7a0(void);
extern void func_02033fb4(int first, int second);
extern void func_02033fec(int first, int second);
extern void func_ov000_0204ea68(void);
extern void func_ov000_0204ebe4(void);

OverlayCallback func_ov000_0204f610(void) {
    OverlayContext *context = NNSi_FndGetCurrentRootHeap();

    FS_UnloadOverlayImage_0x020362ec(context->overlay_image);
    func_020362fc(context->overlay_image);
    func_ov000_020548c8();
    func_0202aa9c(context->update_object);

    switch (func_ov000_020548e0()) {
    case 4:
        WM_EndKeySharing_0x02023ad0(context->sharing_handle);
        context->sharing_handle = context->sharing_state = 0;
        func_ov000_0204d72c();
        func_ov000_0204cac0();
        func_ov000_0204d7a0();
        return func_ov000_0204ea68;
    case 5:
        context->state_0 = 0;
        context->transition_flag = 1;
        func_02033fb4(1, 3);
        func_02033fec(0, 30);
        return func_ov000_0204ebe4;
    default:
        return 0;
    }
}
