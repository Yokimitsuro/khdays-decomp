typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Ov008SurfaceConfig {
    u32 words[5];
} Ov008SurfaceConfig;

typedef struct Ov008HeaderLimits {
    u16 width;
    u16 height;
} Ov008HeaderLimits;

typedef struct Ov008UiContext {
    char pad_0000[0x95a4];
    void *buffers[7];
    char pad_95c0[0x10];
    int bufferUnits;
} Ov008UiContext;

extern const Ov008SurfaceConfig data_ov025_020b37b0;
extern const Ov008HeaderLimits data_ov025_020b37ac;
extern int data_ov025_020b5744[];
extern char data_ov025_020b4a48[];
extern char data_ov025_020b4a54[];
extern char data_ov025_020b4a64[];
extern char data_ov025_020b4aec[];
extern u16 data_0204c23c;

#define CTX (*(volatile int *)((char *)data_ov025_020b5744 + 4))
#define UCTX ((Ov008UiContext *)CTX)
#define REG_DISPCNT_SUB (*(volatile u32 *)0x04001000)

extern void *NNSi_FndAllocFromDefaultExpHeap(int size);
extern void MI_CpuFill8(void *destination, int value, int size);
extern void func_0201e470(int async, int overlayId);
extern void *func_02024ee8(const char *path, int heapId);
extern int func_02024e5c(void);
extern void func_02024d68(void);
extern int func_02023930(void *descriptor, void *parent);
extern void NNS_FndInitList(void *list, int offset);
extern void func_ov025_02082c80(void);
extern void func_ov025_020850b0(void);
extern void *NNS_FndAllocFromDefaultExpHeapEx(int size, int alignment);
extern void MIi_CpuClear16(int value, void *destination, int size);
extern void func_02035f84(void *tween);
extern void func_ov025_02089114(void *surface, const Ov008SurfaceConfig *config);
extern void func_ov025_02087f90(void *surface, void *parent);
extern void func_ov025_02082fd4(int enabled);
extern void func_02036298(void *header, const Ov008HeaderLimits *limits);
extern u32 func_020235d0(u32 id, int field);
extern void func_ov025_02084c54(int value);
extern void func_ov025_02084fd8(int value);
extern void func_ov025_02084df0(int value);
extern void func_ov025_02084e20(int value);
extern void func_ov025_02084798(int slot, int target);
extern void func_ov025_02084d14(int enabled);

void func_ov025_02083e84(int initialMode)
{
    Ov008SurfaceConfig surfaceConfig = data_ov025_020b37b0;
    Ov008HeaderLimits limits = data_ov025_020b37ac;
    int isModeOne;
    int i;

    data_ov025_020b5744[0] = 0;
    data_ov025_020b5744[1] =
        (int)NNSi_FndAllocFromDefaultExpHeap(0x976c);
    MI_CpuFill8((void *)data_ov025_020b5744[1], 0, 0x976c);

    *(int *)(CTX + 0x9600) = 1;
    *(int *)(CTX + 0x9604) = 1;
    func_0201e470(0, 0x12e);
    *(void **)(CTX + 0x96b0) =
        func_02024ee8(data_ov025_020b4a48, 0xe);
    isModeOne = func_02024e5c() == 1;
    if (isModeOne == 0) {
        *(void **)(CTX + 0x96b4) =
            func_02024ee8(data_ov025_020b4a54, 0xe);
    }
    *(void **)(CTX + 0x96b8) =
        func_02024ee8(data_ov025_020b4a64, 0xe);

    func_02024d68();
    *(int *)(CTX + 0x9598) = func_02023930(data_ov025_020b4aec, 0);
    *(int *)(CTX + 0x95d0) = 0x40;
    *(int *)(CTX + 0x9628) = 1;
    *(int *)(CTX + 0x962c) = 1;
    NNS_FndInitList((void *)(CTX + 0x9660), 4);
    *(int *)(CTX + 0x95d4) = -0x10000;
    *(int *)(CTX + 0x961c) = 1;
    func_ov025_02082c80();
    *(u32 *)(CTX + 0x9674) = (REG_DISPCNT_SUB & 0xe000) >> 13;
    func_ov025_020850b0();

    for (i = 0; i < 7; i++) {
        Ov008UiContext *context;

        UCTX->buffers[i] =
            NNS_FndAllocFromDefaultExpHeapEx(
                UCTX->bufferUnits << 6, 2);
        context = UCTX;
        MIi_CpuClear16(0, context->buffers[i], context->bufferUnits << 6);
    }

    func_02035f84((void *)(CTX + 0x95d8));
    func_ov025_02089114((void *)(CTX + 0x9500), &surfaceConfig);
    func_ov025_02089114((void *)(CTX + 0x954c), &surfaceConfig);
    func_ov025_02087f90((void *)CTX, 0);
    func_ov025_02087f90((void *)(CTX + 0x4a80), 0);
    func_ov025_02082fd4(0);
    func_02036298((void *)(CTX + 0x963e), &limits);

    switch ((unsigned int)initialMode) {
    case 0:
        func_ov025_02084798(0, -1);
        *(int *)(CTX + 0x95c0) = 2;
        break;
    case -1:
        func_ov025_02084798(0, -1);
        *(int *)(CTX + 0x95c0) = 0;
        break;
    case -2:
        func_ov025_02084798(1, -1);
        *(int *)(CTX + 0x95c0) = 0;
        break;
    case -3:
        func_ov025_02084798(1, -1);
        *(int *)(CTX + 0x95c0) = 1;
        break;
    case -4:
        if (func_020235d0(0, 9) >= 0xe) {
            func_ov025_02084c54(0);
            func_ov025_02084fd8(0);
            func_ov025_02084df0(1);
            func_ov025_02084e20(0);
            func_ov025_02084798(1, -1);
        } else {
            func_ov025_02084798(0, -1);
        }
        *(int *)(CTX + 0x95c0) = 0;
        break;
    case -5:
        func_ov025_02084798(2, -1);
        *(int *)(CTX + 0x95c0) = 0;
        break;
    case -6: {
        int found = 0;
        u32 id = 0x92b;

        for (i = 0; i < 0x78; i++, id += 4) {
            if ((func_020235d0(id, 4) & 7) != 0) {
                found = 1;
                break;
            }
        }
        if (found != 0) {
            func_ov025_02084c54(0);
            func_ov025_02084fd8(data_0204c23c);
            func_ov025_02084df0(1);
            func_ov025_02084e20(1);
            func_ov025_02084798(1, -1);
        } else {
            func_ov025_02084798(0, -1);
        }
        *(int *)(CTX + 0x95c0) = 0;
        break;
    }
    }

    func_ov025_02084d14(1);
    *(int *)(CTX + 0x9618) = 1;
}
