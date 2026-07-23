typedef signed char  s8;
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef void (*Ov000StateFn)(void);

typedef struct Ov000BootContext {
    int frame;
    u8 pad_0004[8];
    u8 renderNode[0x108];
    u8 scrollBounds[0x4b19];
    s8 transitionMode;
    u8 pad_4c2e[0x43e];
    void *sharingHandle;
    void *sharingAux;
} Ov000BootContext;

extern Ov000BootContext *NNSi_FndGetCurrentRootHeap(void);
extern void func_ov000_0204d354(void);
extern void func_02023d70(void *bounds, int right, int left, int top,
                          int bottom);
extern void func_0202aa9c(void *renderNode);
extern void func_0201e374(int brightness);
extern void func_0201e3cc(int brightness);
extern void G2x_SetBlendBrightness_(u32 registerAddress, int planeMask,
                                    int brightness);
extern void func_02033fec(int first, int second);
extern int func_02034014(int processor);
extern void WM_EndKeySharing_0x02023ad0(void *handle);
extern void func_ov000_0204ef34(void);

Ov000StateFn func_ov000_0204ebe4(void) {
    Ov000BootContext *context = NNSi_FndGetCurrentRootHeap();

    func_ov000_0204d354();
    func_02023d70(context->scrollBounds, 0x3b33, -0x3b33,
                  -0x4d9a, 0x4d9a);
    func_0202aa9c(context->renderNode);

    if (context->frame <= 0x20) {
        func_0201e374(context->frame / 2);
        func_0201e3cc(context->frame / 2);
    } else if (context->frame < 0x28) {
        *(volatile u32 *)0x04001000 =
            *(volatile u32 *)0x04001000 & ~0x1f00 | 0x1200;
    } else if (context->frame < 0x30) {
        G2x_SetBlendBrightness_(0x04000050, 3, 0x10);
        G2x_SetBlendBrightness_(0x04001050, 0x12, 0x10);
        func_0201e374((-(context->frame - 0x28)) << 1);
        func_0201e3cc((-(context->frame - 0x28)) << 1);
    } else {
        *(volatile u16 *)0x04000050 = 0;
        *(volatile u16 *)0x04001050 = 0;
        func_0201e374(-0x10);
        func_0201e3cc(-0x10);

        if (context->frame == 0x30) {
            func_02033fec(1, 0x10);
        }

        if (func_02034014(1) == 0) {
            context->frame = 0;
            switch (context->transitionMode) {
            case 0:
                if (context->sharingHandle != 0) {
                    WM_EndKeySharing_0x02023ad0(context->sharingHandle);
                    context->sharingHandle = 0;
                }
                break;
            case 1:
            case 2:
                if (context->sharingHandle != 0) {
                    WM_EndKeySharing_0x02023ad0(context->sharingHandle);
                    context->sharingHandle = 0;
                }
                if (context->sharingAux != 0) {
                    WM_EndKeySharing_0x02023ad0(context->sharingAux);
                    context->sharingAux = 0;
                }
                break;
            }
            return func_ov000_0204ef34;
        }
    }

    context->frame++;
    return 0;
}
