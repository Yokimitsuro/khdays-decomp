typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef void (*Ov000StateFn)(void);

typedef struct Ov000BootContext {
    int frame;
    u8 pad_0004[8];
    u8 renderNode[0x108];
    u8 scrollBounds[0x9c];
    u8 pad_01b0[0x4a38];
    u8 overlayImage[0x47];
    u8 resumeBoot;
    u8 pad_4c30[0x10];
    int transitionFlag;
    u8 pad_4c44[0xf];
    u8 savedSceneFlag;
    int savedSceneId;
    u8 pad_4c58[0x414];
    void *sharingHandle;
    u8 pad_5070[4];
    void *sharingAux;
} Ov000BootContext;

extern Ov000BootContext *NNSi_FndGetCurrentRootHeap(void);
extern void FS_UnloadOverlayImage_0x020362ec(void *image);
extern u16 func_020362fc(const void *image);
extern void func_ov000_0205324c(u16 id);
extern void func_02023d70(void *bounds, int left, int right,
                          int top, int bottom);
extern void func_0202aa9c(void *renderNode);
extern int func_ov000_0205328c(void);
extern int func_ov000_020532b0(void);
extern int func_ov000_020532d0(void);
extern void *WM_EndKeySharing_0x02023ad0(void *handle);
extern void func_ov000_0204d72c(void);
extern void func_ov000_0204cac0(void);
extern void func_ov000_0204d7a0(void);
extern void func_02033fb4(int first, int second);
extern void func_02033fec(int first, int second);
extern void func_ov000_0204ea68(void);
extern void func_ov000_0204ebe4(void);

Ov000StateFn func_ov000_0204f124(void) {
    Ov000BootContext *context = NNSi_FndGetCurrentRootHeap();
    int state;

    FS_UnloadOverlayImage_0x020362ec(context->overlayImage);
    func_ov000_0205324c(func_020362fc(context->overlayImage));
    func_02023d70(context->scrollBounds, 0x3b33, -0x3b33,
                  -0x4d9a, 0x4d9a);
    func_0202aa9c(context->renderNode);

    state = func_ov000_0205328c();
    switch (state) {
    case 7:
        context->savedSceneFlag = func_ov000_020532b0();
        context->savedSceneId = func_ov000_020532d0();
        WM_EndKeySharing_0x02023ad0(context->sharingHandle);
        context->sharingHandle = context->sharingAux = 0;
        *(volatile u32 *)0x04001000 &= ~0xe000;

        func_ov000_0204d72c();
        func_ov000_0204cac0();
        func_ov000_0204d7a0();
        if (context->savedSceneFlag == 0) {
            context->resumeBoot = 0;
        }
        return func_ov000_0204ea68;
    case 8:
        context->frame = 0;
        context->transitionFlag = 1;
        func_02033fb4(1, 3);
        func_02033fec(0, 0x1e);
        return func_ov000_0204ebe4;
    default:
        return 0;
    }
}
