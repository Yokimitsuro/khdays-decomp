/* Creates the camp-menu context: allocates and clears it, loads its overlay and message containers,
 * starts touch sampling, instantiates its classes and lists, sets up its surfaces and header
 * limits, and restores the saved selections. */

#include "nitro/types.h"

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
extern char gOv025UiCmCmPath[];
extern char gOv025UiCmCmbPath[];
extern char data_ov025_020b4a64[];
extern char data_ov025_020b4aec[];
extern u16 gMissionNumber;

#define CTX (*(volatile int *)((char *)data_ov025_020b5744 + 4))
#define UCTX ((Ov008UiContext *)CTX)
#define REG_DISPCNT_SUB (*(volatile u32 *)0x04001000)

extern void *NNSi_FndAllocFromDefaultExpHeap(int size);
extern void MI_CpuFill8(void *destination, int value, int size);
extern void LoadOverlaySync(int async, int overlayId);
extern void *Msg_OpenContainerAndReadHeader(const char *path, int heapId);
extern int GetLanguage(void);
extern void Touch_StartAutoSampling(void);
extern int InstantiateClass(void *descriptor, void *parent);
extern void NNS_FndInitList(void *list, int offset);
extern void Ov025_PushCannedDescriptors(void);
extern void Ov025_ClearActiveHandlers(void);
extern void *NNS_FndAllocFromDefaultExpHeapEx(int size, int alignment);
extern void MIi_CpuClear16(int value, void *destination, int size);
extern void Tween_Clear(void *tween);
extern void Ov025_Container_Init(void *surface, const Ov008SurfaceConfig *config);
extern void Ov025_InitSubsystemObject(void *surface, void *parent);
extern void Ov025_EnableBothHalves(int enabled);
extern void Header_InitWithLimits(void *header, const Ov008HeaderLimits *limits);
extern u32 GameState_GetField(u32 id, int field);
extern void Ov025_SetCtxField9678(int value);
extern void Ov025_SetCtxField967c(int value);
extern void Ov025_SetCtxObject9630(int value);
extern void Ov025_SetCtxObject9634(int value);
extern void Ov025_SetTargetSlot(int slot, int target);
extern void Ov025_CampaignModeHookNoOp(int enabled);

void Ov025_InitCampaignMenuContext(int initialMode)
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
    LoadOverlaySync(0, 0x12e);
    *(void **)(CTX + 0x96b0) =
        Msg_OpenContainerAndReadHeader(gOv025UiCmCmPath, 0xe);
    isModeOne = GetLanguage() == 1;
    if (isModeOne == 0) {
        *(void **)(CTX + 0x96b4) =
            Msg_OpenContainerAndReadHeader(gOv025UiCmCmbPath, 0xe);
    }
    *(void **)(CTX + 0x96b8) =
        Msg_OpenContainerAndReadHeader(data_ov025_020b4a64, 0xe);

    Touch_StartAutoSampling();
    *(int *)(CTX + 0x9598) = InstantiateClass(data_ov025_020b4aec, 0);
    *(int *)(CTX + 0x95d0) = 0x40;
    *(int *)(CTX + 0x9628) = 1;
    *(int *)(CTX + 0x962c) = 1;
    NNS_FndInitList((void *)(CTX + 0x9660), 4);
    *(int *)(CTX + 0x95d4) = -0x10000;
    *(int *)(CTX + 0x961c) = 1;
    Ov025_PushCannedDescriptors();
    *(u32 *)(CTX + 0x9674) = (REG_DISPCNT_SUB & 0xe000) >> 13;
    Ov025_ClearActiveHandlers();

    for (i = 0; i < 7; i++) {
        Ov008UiContext *context;

        UCTX->buffers[i] =
            NNS_FndAllocFromDefaultExpHeapEx(
                UCTX->bufferUnits << 6, 2);
        context = UCTX;
        MIi_CpuClear16(0, context->buffers[i], context->bufferUnits << 6);
    }

    Tween_Clear((void *)(CTX + 0x95d8));
    Ov025_Container_Init((void *)(CTX + 0x9500), &surfaceConfig);
    Ov025_Container_Init((void *)(CTX + 0x954c), &surfaceConfig);
    Ov025_InitSubsystemObject((void *)CTX, 0);
    Ov025_InitSubsystemObject((void *)(CTX + 0x4a80), 0);
    Ov025_EnableBothHalves(0);
    Header_InitWithLimits((void *)(CTX + 0x963e), &limits);

    switch ((unsigned int)initialMode) {
    case 0:
        Ov025_SetTargetSlot(0, -1);
        *(int *)(CTX + 0x95c0) = 2;
        break;
    case -1:
        Ov025_SetTargetSlot(0, -1);
        *(int *)(CTX + 0x95c0) = 0;
        break;
    case -2:
        Ov025_SetTargetSlot(1, -1);
        *(int *)(CTX + 0x95c0) = 0;
        break;
    case -3:
        Ov025_SetTargetSlot(1, -1);
        *(int *)(CTX + 0x95c0) = 1;
        break;
    case -4:
        if (GameState_GetField(0, 9) >= 0xe) {
            Ov025_SetCtxField9678(0);
            Ov025_SetCtxField967c(0);
            Ov025_SetCtxObject9630(1);
            Ov025_SetCtxObject9634(0);
            Ov025_SetTargetSlot(1, -1);
        } else {
            Ov025_SetTargetSlot(0, -1);
        }
        *(int *)(CTX + 0x95c0) = 0;
        break;
    case -5:
        Ov025_SetTargetSlot(2, -1);
        *(int *)(CTX + 0x95c0) = 0;
        break;
    case -6: {
        int found = 0;
        u32 id = 0x92b;

        for (i = 0; i < 0x78; i++, id += 4) {
            if ((GameState_GetField(id, 4) & 7) != 0) {
                found = 1;
                break;
            }
        }
        if (found != 0) {
            Ov025_SetCtxField9678(0);
            Ov025_SetCtxField967c(gMissionNumber);
            Ov025_SetCtxObject9630(1);
            Ov025_SetCtxObject9634(1);
            Ov025_SetTargetSlot(1, -1);
        } else {
            Ov025_SetTargetSlot(0, -1);
        }
        *(int *)(CTX + 0x95c0) = 0;
        break;
    }
    }

    Ov025_CampaignModeHookNoOp(1);
    *(int *)(CTX + 0x9618) = 1;
}
