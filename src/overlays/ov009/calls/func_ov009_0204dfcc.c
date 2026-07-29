typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

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
extern const char data_ov009_02056294[];

extern int   OS_IsThreadAvailable_0x0204ee00(void);
extern void  func_ov009_0204d65c(void);
extern void  func_ov009_0204e540(void);
extern void  func_02000fb4(int mode, const void *descriptor);
extern void  func_ov009_020514f8(void *object);
extern void  func_ov009_020522d0(void *object);
extern void  NNSi_FndFreeFromDefaultHeap(void *allocation);
extern void  func_ov009_0204e678(void);
extern int   func_020362e8(void *inputHeader);
extern void  func_ov009_0204cc18(void);
extern void *G2_GetBG3CharPtr(void);
extern void  MIi_CpuClearFast(u32 value, void *destination, u32 size);
extern void  G3X_SetClearColor(
    u32 color, u32 alpha, u32 depth, u32 polygonId, int fog);
extern void *WM_EndKeySharing_0x02023ad0(void *handle);
extern void  func_0200c5fc(void);
extern void  func_0200ca50(u32 mask);
extern int   func_0200ca68(int mask);
extern int   func_02024fd4(void *resource);
extern void  func_02034258(int id);
extern void  func_0201e4a8(int processor, int overlayId);
extern void  func_02003948(int result);

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

void func_ov009_0204dfcc(void)
{
    int bufferIndex;
    int resourceIndex;

    if (OS_IsThreadAvailable_0x0204ee00() != -1) {
        data_ov009_020563e4[1]->pendingId = -1;
        data_ov009_020563e4[1]->teardownRequested = 1;
        func_ov009_0204d65c();
    }

    func_ov009_0204e540();
    func_02000fb4(1, data_ov009_02056294);
    func_ov009_020514f8(data_ov009_020563e4[1]->subsystem0);
    func_ov009_020514f8(data_ov009_020563e4[1]->subsystem1);
    func_ov009_020522d0(data_ov009_020563e4[1]->object9500);
    func_ov009_020522d0(data_ov009_020563e4[1]->object954c);

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

    func_ov009_0204e678();
    func_020362e8(
        &data_ov009_020563e4[1]->displayState.inputHeader);
    func_ov009_0204cc18();
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

    WM_EndKeySharing_0x02023ad0(
        data_ov009_020563e4[1]->graphicsObject);
    func_0200c5fc();
    func_0200ca50(4);
    func_0200ca68(4);

    if (data_ov009_020563e4[1]->secondaryMessageContainer != 0) {
        func_02024fd4(
            data_ov009_020563e4[1]->secondaryMessageContainer);
    }
    func_02024fd4(data_ov009_020563e4[1]->tertiaryMessageContainer);
    func_02024fd4(data_ov009_020563e4[1]->primaryMessageContainer);

    for (resourceIndex = 0;
         resourceIndex < 0x21;
         resourceIndex++) {
        if (data_ov009_020563e4[1]->
                resourceUsage[resourceIndex] > 0) {
            func_02034258(resourceIndex);
        }
    }

    func_0201e4a8(0, 0x12e);

    if (data_ov009_020563e4[1] != 0) {
        NNSi_FndFreeFromDefaultHeap(data_ov009_020563e4[1]);
        data_ov009_020563e4[1] = 0;
    }

    if (data_ov009_020563e4[0] != 0) {
        func_02003948(-2);
    }
}
