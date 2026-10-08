/* Tears down the page: cancels the pending request, frees the tile buffers and restores the saved
 * BG controls and display state. */

#include "nitro/types.h"

typedef union GXBg01Control {
    u16 raw;
    struct {
        u16 priority : 2;
        u16 charBase : 4;
        u16 mosaic : 1;
        u16 colorMode : 1;
        u16 screenBase : 5;
        u16 bgExtPltt : 1;
        u16 screenSize : 2;
    };
} GXBg01Control;

typedef enum {
    GX_BG_SCRSIZE_TEXT_256x256 = 0,
    GX_BG_SCRSIZE_TEXT_512x256 = 1,
    GX_BG_SCRSIZE_TEXT_256x512 = 2,
    GX_BG_SCRSIZE_TEXT_512x512 = 3
} GXBGScrSizeText;

typedef enum {
    GX_BG_COLORMODE_16 = 0,
    GX_BG_COLORMODE_256 = 1
} GXBGColorMode;

typedef enum {
    GX_BG_SCRBASE_0x0000 = 0,
    GX_BG_SCRBASE_0xf800 = 31
} GXBGScrBase;

typedef enum {
    GX_BG_CHARBASE_0x00000 = 0,
    GX_BG_CHARBASE_0x3c000 = 15
} GXBGCharBase;

typedef enum {
    GX_BG_EXTPLTT_01 = 0,
    GX_BG_EXTPLTT_23 = 1
} GXBGExtPltt;

typedef struct Ov009DisplayState {
    u8 pad_00[2];
    u16 inputHeader;
    u8 pad_04[0x30 - 0x04];
    GXBg01Control savedMainBg1Control;
    GXBg01Control savedSubBg0Control;
    GXBg01Control savedSubBg1Control;
    u8 pad_36[2];
    int subDisplayMode;
} Ov009DisplayState;

typedef struct Ov009MenuContext {
    u8 subsystem0[0x4a80];
    u8 subsystem1[0x9500 - 0x4a80];
    u8 object9500[0x4c];
    u8 object954c[0x4c];
    void *graphicsObject;
    u8 pad_959c[0x95a4 - 0x959c];
    void *tileBuffers[7];
    void *field_95c0;
    int pendingId;
    u8 pad_95c8[0x95f8 - 0x95c8];
    int teardownRequested;
    u8 pad_95fc[0x963c - 0x95fc];
    Ov009DisplayState displayState;
    u8 pad_9678[0x96b0 - 0x9678];
    void *primaryMessageContainer;
    void *secondaryMessageContainer;
    void *tertiaryMessageContainer;
    int resourceUsage[0x21];
} Ov009MenuContext;

extern Ov009MenuContext *data_ov009_020563e4[2];
extern const char gOv009CampmenumngrName[];

extern int   func_ov009_0204ee00(void);
extern void  Ov009_FullScreenTeardown(void);
extern void  Ov009_DestroyAllRegistryEntries(void);
extern void  VBlank_UnregisterCallback(int mode, const void *descriptor);
extern void  Ov009_DestroyObjectsAndRelease(void *object);
extern void  Ov009_ReleaseThreeBuffers(void *object);
extern void  NNSi_FndFreeFromDefaultHeap(void *allocation);
extern void  Ov009_ResetActiveHandlers(void);
extern int   ConstReturn1_2(void *inputHeader);
extern void  Ov009_ResetFourChannels(void);
extern void *G2_GetBG3CharPtr(void);
extern void  MIi_CpuClearFast(u32 value, void *destination, u32 size);
extern void  G3X_SetClearColor(
    u32 color, u32 alpha, u32 depth, u32 polygonId, int fog);
extern void *VeneerTo_Obj_Destroy(void *handle);
extern void  TP_RequestAutoSamplingStopAsync(void);
extern void  TP_WaitBusy(u32 mask);
extern int   TP_CheckError(int mask);
extern int   ZeroHalfThenFree(void *resource);
extern void  ResSlot_Release_2(int id);
extern void  UnloadOverlaySync(int processor, int overlayId);
extern void  OS_ResetSystem(int result);

static volatile u16 *const REG_BG1CNT_MAIN =
    (volatile u16 *)0x0400000a;
static volatile u16 *const REG_BG0CNT_SUB =
    (volatile u16 *)0x04001008;
static volatile u32 *const REG_DISPCNT_SUB =
    (volatile u32 *)0x04001000;
static volatile u32 *const REG_SUB_BG_OFFSETS =
    (volatile u32 *)0x04001010;

static inline void G2_SetBG1Control(
    GXBGScrSizeText screenSize,
    GXBGColorMode colorMode,
    GXBGScrBase screenBase,
    GXBGCharBase charBase,
    GXBGExtPltt bgExtPltt)
{
    *REG_BG1CNT_MAIN = (u16)(
        (*REG_BG1CNT_MAIN & 0x43)
        | (screenSize << 14) | (colorMode << 7)
        | (screenBase << 8) | (charBase << 2)
        | (bgExtPltt << 13));
}

static inline void G2S_SetBG0Control(
    GXBGScrSizeText screenSize,
    GXBGColorMode colorMode,
    GXBGScrBase screenBase,
    GXBGCharBase charBase,
    GXBGExtPltt bgExtPltt)
{
    REG_BG0CNT_SUB[0] = (u16)(
        (REG_BG0CNT_SUB[0] & 0x43)
        | (screenSize << 14) | (colorMode << 7)
        | (screenBase << 8) | (charBase << 2)
        | (bgExtPltt << 13));
}

static inline void G2S_SetBG1Control(
    GXBGScrSizeText screenSize,
    GXBGColorMode colorMode,
    GXBGScrBase screenBase,
    GXBGCharBase charBase,
    GXBGExtPltt bgExtPltt)
{
    REG_BG0CNT_SUB[1] = (u16)(
        (REG_BG0CNT_SUB[1] & 0x43)
        | (screenSize << 14) | (colorMode << 7)
        | (screenBase << 8) | (charBase << 2)
        | (bgExtPltt << 13));
}

void Ov009_PageTeardown(void)
{
    int bufferIndex;
    int resourceIndex;

    if (func_ov009_0204ee00() != -1) {
        data_ov009_020563e4[1]->pendingId = -1;
        data_ov009_020563e4[1]->teardownRequested = 1;
        Ov009_FullScreenTeardown();
    }

    Ov009_DestroyAllRegistryEntries();
    VBlank_UnregisterCallback(1, gOv009CampmenumngrName);
    Ov009_DestroyObjectsAndRelease(data_ov009_020563e4[1]->subsystem0);
    Ov009_DestroyObjectsAndRelease(data_ov009_020563e4[1]->subsystem1);
    Ov009_ReleaseThreeBuffers(data_ov009_020563e4[1]->object9500);
    Ov009_ReleaseThreeBuffers(data_ov009_020563e4[1]->object954c);

    for (bufferIndex = 0; bufferIndex < 7; bufferIndex++) {
        if (data_ov009_020563e4[1]->
                tileBuffers[bufferIndex] != 0) {
            NNSi_FndFreeFromDefaultHeap(
                data_ov009_020563e4[1]->
                    tileBuffers[bufferIndex]);
            data_ov009_020563e4[1]->
                tileBuffers[bufferIndex] = 0;
        }
    }

    Ov009_ResetActiveHandlers();
    ConstReturn1_2(
        &data_ov009_020563e4[1]->displayState.inputHeader);
    Ov009_ResetFourChannels();
    MIi_CpuClearFast(0, (u8 *)G2_GetBG3CharPtr() + 0x4000, 0x20);

    {
    G2_SetBG1Control(
        data_ov009_020563e4[1]->
            displayState.savedMainBg1Control.screenSize,
        data_ov009_020563e4[1]->
            displayState.savedMainBg1Control.colorMode,
        data_ov009_020563e4[1]->
            displayState.savedMainBg1Control.screenBase,
        data_ov009_020563e4[1]->
            displayState.savedMainBg1Control.charBase,
        data_ov009_020563e4[1]->
            displayState.savedMainBg1Control.bgExtPltt);

    G2S_SetBG0Control(
        data_ov009_020563e4[1]->
            displayState.savedSubBg0Control.screenSize,
        data_ov009_020563e4[1]->
            displayState.savedSubBg0Control.colorMode,
        data_ov009_020563e4[1]->
            displayState.savedSubBg0Control.screenBase,
        data_ov009_020563e4[1]->
            displayState.savedSubBg0Control.charBase,
        data_ov009_020563e4[1]->
            displayState.savedSubBg0Control.bgExtPltt);

    G2S_SetBG1Control(
        data_ov009_020563e4[1]->
            displayState.savedSubBg1Control.screenSize,
        data_ov009_020563e4[1]->
            displayState.savedSubBg1Control.colorMode,
        data_ov009_020563e4[1]->
            displayState.savedSubBg1Control.screenBase,
        data_ov009_020563e4[1]->
            displayState.savedSubBg1Control.charBase,
        data_ov009_020563e4[1]->
            displayState.savedSubBg1Control.bgExtPltt);

    *REG_DISPCNT_SUB =
        (*REG_DISPCNT_SUB & ~0xe000)
        | (data_ov009_020563e4[1]->
               displayState.subDisplayMode << 13);
    }

    G3X_SetClearColor(0, 0x1f, 0x7fff, 0x3f, 0);

    REG_SUB_BG_OFFSETS[0] = 0;
    REG_SUB_BG_OFFSETS[1] = 0;
    REG_SUB_BG_OFFSETS[2] = 0;
    REG_SUB_BG_OFFSETS[3] = 0;

    VeneerTo_Obj_Destroy(
        data_ov009_020563e4[1]->graphicsObject);
    TP_RequestAutoSamplingStopAsync();
    TP_WaitBusy(4);
    TP_CheckError(4);

    if (data_ov009_020563e4[1]->secondaryMessageContainer != 0) {
        ZeroHalfThenFree(
            data_ov009_020563e4[1]->secondaryMessageContainer);
    }
    ZeroHalfThenFree(data_ov009_020563e4[1]->tertiaryMessageContainer);
    ZeroHalfThenFree(data_ov009_020563e4[1]->primaryMessageContainer);

    for (resourceIndex = 0;
         resourceIndex < 0x21;
         resourceIndex++) {
        if (data_ov009_020563e4[1]->
                resourceUsage[resourceIndex] > 0) {
            ResSlot_Release_2(resourceIndex);
        }
    }

    UnloadOverlaySync(0, 0x12e);

    if (data_ov009_020563e4[1] != 0) {
        NNSi_FndFreeFromDefaultHeap(data_ov009_020563e4[1]);
        data_ov009_020563e4[1] = 0;
    }

    if (data_ov009_020563e4[0] != 0) {
        OS_ResetSystem(-2);
    }
}
