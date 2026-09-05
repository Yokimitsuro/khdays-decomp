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

extern const Ov008SurfaceConfig data_ov008_0208e84c;
extern const Ov008HeaderLimits data_ov008_0208e848;
extern int data_ov008_02090f04[];
extern char data_ov008_02090034[];
extern char data_ov008_02090040[];
extern char data_ov008_02090050[];
extern char data_ov008_020900d8[];
extern u16 data_0204c23c;

#define CTX (*(volatile int *)((char *)data_ov008_02090f04 + 4))
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
extern void func_ov008_0204ee58(void);
extern void func_ov008_02051300(void);
extern void *NNS_FndAllocFromDefaultExpHeapEx(int size, int alignment);
extern void MIi_CpuClear16(int value, void *destination, int size);
extern void func_02035f84(void *tween);
extern void func_ov008_0205546c(void *surface, const Ov008SurfaceConfig *config);
extern void func_ov008_020542dc(void *surface, void *parent);
extern void func_ov008_0204f1ac(int enabled);
extern void func_02036298(void *header, const Ov008HeaderLimits *limits);
extern u32 func_020235d0(u32 id, int field);
extern void func_ov008_02050e2c(int value);
extern void func_ov008_020511c8(int value);
extern void func_ov008_02050fe0(int value);
extern void func_ov008_02051010(int value);
extern void func_ov008_02050970(int slot, int target);
extern void func_ov008_02050f04(int enabled);

void func_ov008_0205005c(int initialMode)
{
    Ov008SurfaceConfig surfaceConfig = data_ov008_0208e84c;
    Ov008HeaderLimits limits = data_ov008_0208e848;
    int isModeOne;
    int i;

    data_ov008_02090f04[0] = 0;
    data_ov008_02090f04[1] =
        (int)NNSi_FndAllocFromDefaultExpHeap(0x976c);
    MI_CpuFill8((void *)data_ov008_02090f04[1], 0, 0x976c);

    *(int *)(CTX + 0x9600) = 1;
    *(int *)(CTX + 0x9604) = 1;
    func_0201e470(0, 0x12e);
    *(void **)(CTX + 0x96b0) =
        func_02024ee8(data_ov008_02090034, 0xe);
    isModeOne = func_02024e5c() == 1;
    if (isModeOne == 0) {
        *(void **)(CTX + 0x96b4) =
            func_02024ee8(data_ov008_02090040, 0xe);
    }
    *(void **)(CTX + 0x96b8) =
        func_02024ee8(data_ov008_02090050, 0xe);

    func_02024d68();
    *(int *)(CTX + 0x9598) = func_02023930(data_ov008_020900d8, 0);
    *(int *)(CTX + 0x95d0) = 0x40;
    *(int *)(CTX + 0x9628) = 1;
    *(int *)(CTX + 0x962c) = 1;
    NNS_FndInitList((void *)(CTX + 0x9660), 4);
    *(int *)(CTX + 0x95d4) = -0x10000;
    *(int *)(CTX + 0x961c) = 1;
    func_ov008_0204ee58();
    *(u32 *)(CTX + 0x9674) = (REG_DISPCNT_SUB & 0xe000) >> 13;
    func_ov008_02051300();

    for (i = 0; i < 7; i++) {
        Ov008UiContext *context;

        UCTX->buffers[i] =
            NNS_FndAllocFromDefaultExpHeapEx(
                UCTX->bufferUnits << 6, 2);
        context = UCTX;
        MIi_CpuClear16(0, context->buffers[i], context->bufferUnits << 6);
    }

    func_02035f84((void *)(CTX + 0x95d8));
    func_ov008_0205546c((void *)(CTX + 0x9500), &surfaceConfig);
    func_ov008_0205546c((void *)(CTX + 0x954c), &surfaceConfig);
    func_ov008_020542dc((void *)CTX, 0);
    func_ov008_020542dc((void *)(CTX + 0x4a80), 0);
    func_ov008_0204f1ac(0);
    func_02036298((void *)(CTX + 0x963e), &limits);

    switch ((unsigned int)initialMode) {
    case 0:
        func_ov008_02050970(0, -1);
        *(int *)(CTX + 0x95c0) = 2;
        break;
    case -1:
        func_ov008_02050970(0, -1);
        *(int *)(CTX + 0x95c0) = 0;
        break;
    case -2:
        func_ov008_02050970(1, -1);
        *(int *)(CTX + 0x95c0) = 0;
        break;
    case -3:
        func_ov008_02050970(1, -1);
        *(int *)(CTX + 0x95c0) = 1;
        break;
    case -4:
        if (func_020235d0(0, 9) >= 0xe) {
            func_ov008_02050e2c(0);
            func_ov008_020511c8(0);
            func_ov008_02050fe0(1);
            func_ov008_02051010(0);
            func_ov008_02050970(1, -1);
        } else {
            func_ov008_02050970(0, -1);
        }
        *(int *)(CTX + 0x95c0) = 0;
        break;
    case -5:
        func_ov008_02050970(2, -1);
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
            func_ov008_02050e2c(0);
            func_ov008_020511c8(data_0204c23c);
            func_ov008_02050fe0(1);
            func_ov008_02051010(1);
            func_ov008_02050970(1, -1);
        } else {
            func_ov008_02050970(0, -1);
        }
        *(int *)(CTX + 0x95c0) = 0;
        break;
    }
    }

    func_ov008_02050f04(1);
    *(int *)(CTX + 0x9618) = 1;
}
