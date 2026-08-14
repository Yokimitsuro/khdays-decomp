/* Configure the main and sub display engines, fade registers, and cameras. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct {
    u8 dispatch[2][0x58];
} Ov003DisplayDispatch;

typedef struct {
    u8 pad_00[0x10];
    u8 camera[2][0x58];
} Ov003DisplayCameras;

typedef struct {
    u8 pad_0000[0x3c];
    int displayMode;
    u8 pad_0040[4];
    u8 displayHeapRequest[0x10];
    int selectedEngine;
    union {
        Ov003DisplayDispatch dispatch;
        Ov003DisplayCameras cameras;
    } engineData;
    u8 pad_0118[0x17ac - 0x118];
    int displayEnabled;
    int blendOffset;
    int fadeStep;
    u8 pad_17b8[0x1e08 - 0x17b8];
    u32 blendAlpha;
    int brightness;
} Ov003DisplayState;

typedef struct {
    u8 pad_000[0x7b0];
    int blendOffset;
    int fadeStep;
    u8 pad_7b8[0xe08 - 0x7b8];
    u32 blendAlpha;
} Ov003DisplayTailPage;

typedef struct {
    volatile u32 scroll;
    u8 pad_04[0x28];
    volatile u16 bg2Control;
    volatile u16 bg3Control;
    volatile u16 bg2ScrollX;
    volatile u16 bg2ScrollY;
    volatile u16 bg3ScrollX;
    volatile u16 bg3ScrollY;
    u8 pad_38[4];
    volatile u16 blendControl;
} Ov003FadeRegisters;

typedef struct {
    u32 scroll;
    u8 pad_04[0x28];
    volatile u16 bg2Control;
    u16 bg3Control;
    u16 bg2ScrollX;
    u16 bg2ScrollY;
    u16 bg3ScrollX;
    u16 bg3ScrollY;
    u8 pad_38[4];
    u16 blendControl;
} Ov003SubFadeLowRegisters;

typedef struct {
    u32 scroll;
    u8 pad_04[0x28];
    volatile u16 bg2Control;
    u16 bg3Control;
    u16 bg2ScrollX;
    u16 bg2ScrollY;
    u16 bg3ScrollX;
    u16 bg3ScrollY;
    u8 pad_38[4];
    u16 blendControl;
} Ov003SubFadeHighRegisters;

typedef struct {
    u16 bg3;
    u16 bg2;
} Ov003SubLowControlPair;

typedef struct {
    u16 bg2;
    u16 bg3;
} Ov003SubHighControlPair;

extern Ov003DisplayState *data_ov003_0204f9a0;
#define OV003_DISPLAY_STATE (data_ov003_0204f9a0)
#define OV003_LOCAL_STATE ((Ov003DisplayState *)displayState)
extern char func_0202e9b8(void *request);
extern int func_ov003_0204cadc(int mode);
extern void *G2S_GetBG0ScrPtr(void);
extern void *G2_GetBG3ScrPtr(void);
extern void func_ov003_0204cb44(void *screen);
extern void G2x_SetBlendBrightness_(u32 reg, u32 plane, int brightness);
extern void G2x_SetBlendAlpha_(u32 reg, int plane1, int plane2, int eva, int evb);
extern void GX_SetBankForSubBG(int bank);
extern void func_0202e4f4(void *state, int size);
extern void func_02023cc0(void *p);

static inline void Ov003CommitDisplay(void) {
    func_0202e4f4(OV003_DISPLAY_STATE->engineData.dispatch.dispatch[0], 0x800);
    func_0202e4f4(OV003_DISPLAY_STATE->engineData.dispatch.dispatch[1], 0x800);
    func_02023cc0(OV003_DISPLAY_STATE->engineData.cameras.camera[OV003_DISPLAY_STATE->selectedEngine]);
}

static inline void Ov003SetSubVisiblePlanes(unsigned int planes) {
    volatile unsigned int *display = (volatile unsigned int *)0x04001000;
    *display = (*display & ~0x1f00) | (planes << 8);
}

static inline void Ov003SetSubBg3Priority(unsigned int priority) {
    volatile unsigned short *bg3Control = (volatile unsigned short *)0x0400100e;
    *bg3Control = (*bg3Control & ~3) | priority;
}

static inline void Ov003SetSubBg2Priority(unsigned int priority) {
    volatile unsigned short *bg2Control = (volatile unsigned short *)0x0400100c;
    *bg2Control = (*bg2Control & ~3) | priority;
}

static inline void Ov003SetSubLowBg3Control(void) {
    volatile unsigned short *control = (volatile unsigned short *)0x04001042;
    *control = 0xff;
}

static inline void Ov003SetSubLowBg2Control(void) {
    volatile unsigned short *control = (volatile unsigned short *)0x04001040;
    *control = 0x10ff;
}

static inline void Ov003SetSubHighBg2Control(void) {
    volatile unsigned short *control = (volatile unsigned short *)0x04001040;
    *control = 0xff;
}

static inline void Ov003SetSubHighBg3Control(void) {
    volatile unsigned short *control = (volatile unsigned short *)0x04001042;
    *control = 0x10ff;
}

static inline void Ov003SetSubBg2ControlSdk(Ov003FadeRegisters *regs,
                                            unsigned int screenBase,
                                            unsigned int lowBits) {
    regs->bg2Control = (screenBase << 8) | lowBits;
}

static inline void Ov003SetSubBg3ControlSdk(Ov003FadeRegisters *regs,
                                            unsigned int screenBase,
                                            unsigned int lowBits) {
    regs->bg3Control = (screenBase << 8) | lowBits;
}

static inline void Ov003ApplyMainFadeLow(Ov003DisplayState *state,
                                         Ov003FadeRegisters *regs,
                                         unsigned int alpha) {
    unsigned int scratch;
    unsigned short scrollX;
    volatile unsigned int *display = (volatile unsigned int *)0x04000000;

    scratch = (unsigned int)state->blendOffset;
    regs->bg3Control = 0xff;
    regs->bg2ScrollY = (-scratch << 8 & 0xff00) | 0xbf;
    regs->bg3ScrollX =
        (scrollX = regs->bg3ScrollX,
         scratch = 0xafbf,
         (unsigned short)(scrollX & ~0x3f00 | 0x3b00));
    regs->bg2Control = 0x10ff;
    regs->bg2ScrollX = (unsigned short)scratch;
    regs->bg3ScrollX =
        (scrollX = regs->bg3ScrollX,
         scratch = 0xf - alpha,
         (unsigned short)(scrollX & ~0x3f | 0x33));
    regs->bg3ScrollY = regs->bg3ScrollY & ~0x3f | 0x19;
    *display = *display & ~0xe000 | 0x6000;
    G2x_SetBlendAlpha_(0x04000050, 2, 1, alpha, scratch);
}

void func_ov003_0204cba0(void) {
    char cVar4;
    int layout;
    unsigned short *puVar3;
    int iVar5;
    int iVar6;
    unsigned int uVar7;
    unsigned short *puVar8;
    volatile unsigned int *puVar9;
    unsigned int uVar10;
    register volatile unsigned int *puVar11;
    Ov003FadeRegisters *fadeRegs;
    int fadeStep;
    volatile unsigned int *reg_dispcnt = (volatile unsigned int *)0x04000000;

    cVar4 = func_0202e9b8(OV003_DISPLAY_STATE->displayHeapRequest);
    OV003_DISPLAY_STATE->selectedEngine = (int)cVar4;
    iVar5 = func_ov003_0204cadc(OV003_DISPLAY_STATE->displayMode);
    layout = iVar5 << 3;
    if (OV003_DISPLAY_STATE->selectedEngine != 0) {
        volatile unsigned int *display = (volatile unsigned int *)0x04000000;
        volatile unsigned short *display16 = (volatile unsigned short *)display;

        *display = *display & ~0x1f00 | 0x500;
        display16[4] = display16[4] & ~3 | 3;
        display16[6] = display16[6] & ~3;
        *display = *display & ~0xe000;
        display16[0x28] = 0;
        iVar6 = (int)G2S_GetBG0ScrPtr();
        func_ov003_0204cb44((void *)iVar6);
        puVar9 = (unsigned int *)0x04001000;
        iVar6 = (int)data_ov003_0204f9a0;
        if (*(int *)(iVar6 + 0x17ac) != 0) {
            if (*(int *)(iVar6 + 0x1e0c) > 0) {
                puVar11 = (unsigned int *)0x04001014;
                *puVar11 = 0;
                G2x_SetBlendBrightness_((u32)(puVar11 += 0xf), 2,
                                        *(int *)((int)data_ov003_0204f9a0 + 0x1e0c));
                uVar7 = ((layout << 8) & 0xff00) | ((layout + 0x3f) & 0xff);
                puVar8 = (unsigned short *)0x04001040;
                *puVar8 = (unsigned short)uVar7;
                puVar8[2] = 0x17;
                puVar8[4] = puVar8[4] & ~0x3f | 0x2a;
                puVar8[5] = puVar8[5] & ~0x3f | 0xb;
                *puVar9 = *puVar9 & ~0xe000 | 0x2000;
            } else {
                fadeRegs = (Ov003FadeRegisters *)0x04001014;
                uVar10 = (unsigned int)(*(int *)(iVar6 + 0x17b4) / 2);
                fadeRegs->scroll = 0x01ff0000 & *(int *)(iVar6 + 0x17b0) << 0x10;
                if ((int)uVar10 < 0xf) {
                    iVar5 = (int)data_ov003_0204f9a0;
                    uVar7 = *(unsigned int *)(iVar5 + 0x17b0);
                    fadeRegs->bg3Control = 0xff;
                    fadeRegs->bg2ScrollY = (-uVar7 << 8 & 0xff00) | 0xbf;
                    fadeRegs->bg3ScrollX = fadeRegs->bg3ScrollX & ~0x3f00 | 0x3b00;
                    fadeRegs->bg2Control = 0x10ff;
                    fadeRegs->bg2ScrollX = 0xafbf;
                    fadeRegs->bg3ScrollX = fadeRegs->bg3ScrollX & ~0x3f | 0x3a;
                    fadeRegs->bg3ScrollY = fadeRegs->bg3ScrollY & ~0x3f | 0x19;
                    *puVar9 = *puVar9 & ~0xe000 | 0x6000;
                    G2x_SetBlendAlpha_((u32)&fadeRegs->blendControl, 2, 8, uVar10, 0xf - uVar10);
                } else {
                    iVar5 = (int)data_ov003_0204f9a0;
                    uVar10 = *(unsigned int *)(iVar5 + 0x1e08);
                    fadeRegs->bg2Control = 0xff;
                    fadeRegs->bg2ScrollX = 0xaf;
                    fadeRegs->bg3ScrollX = fadeRegs->bg3ScrollX & ~0x3f | 0x3b;
                    fadeRegs->bg3Control = 0x10ff;
                    fadeRegs->bg2ScrollY = 0xafbf;
                    fadeRegs->bg3ScrollX = fadeRegs->bg3ScrollX & ~0x3f00 | 0x3900;
                    fadeRegs->bg3ScrollY = fadeRegs->bg3ScrollY & ~0x3f | 0x19;
                    *puVar9 = *puVar9 & ~0xe000 | 0x6000;
                    if (uVar10 == 0xf) {
                        fadeRegs->blendControl = 0;
                    } else {
                        G2x_SetBlendAlpha_((u32)&fadeRegs->blendControl, 1, 10, uVar10, 0xf - uVar10);
                    }
                }
            }
            *(unsigned int *)0x04001000 = *(unsigned int *)0x04001000 & ~0x1f00 | 0xb00;
        } else {
            *(volatile unsigned int *)0x04001000 = *(volatile unsigned int *)0x04001000 & ~0x1f00 | 0x900;
            *puVar9 = *puVar9 & ~0xe000;
            *(unsigned short *)(puVar9 + 0x14) = 0;
        }
        puVar11 = (unsigned int *)0x0400100e;
        puVar9 = (unsigned int *)0x0400100e - 1;
        puVar8 = (unsigned short *)(0x0400100e - 6);
        *(unsigned short *)0x0400100e = *(unsigned short *)0x0400100e & ~3 | 3;
        *(unsigned short *)puVar9 = *(unsigned short *)puVar9 & ~3 | 1;
        *puVar8 = *puVar8 & ~3;
    } else {
        iVar6 = (int)G2_GetBG3ScrPtr();
        func_ov003_0204cb44((void *)iVar6);
        puVar11 = (unsigned int *)0x04000014;
        iVar6 = (int)OV003_DISPLAY_STATE;
        if (*(int *)(iVar6 + 0x17ac) != 0) {
            if (*(int *)(iVar6 + 0x1e0c) > 0) {
                *puVar11 = 0;
                G2x_SetBlendBrightness_((u32)(puVar11 += 0xf), 2,
                                        *(int *)((int)OV003_DISPLAY_STATE + 0x1e0c));
                uVar7 = ((layout << 8) & 0xff00) | ((layout + 0x3f) & 0xff);
                puVar8 = (unsigned short *)0x04000040;
                *puVar8 = (unsigned short)uVar7;
                puVar8[2] = 0x17;
                puVar8[4] = puVar8[4] & ~0x3f | 0x23;
                puVar8[5] = puVar8[5] & ~0x3f | 0xb;
                *reg_dispcnt = *reg_dispcnt & ~0xe000 | 0x2000;
            } else {
                Ov003DisplayState *fadeState;
                fadeRegs = (Ov003FadeRegisters *)0x04000014;
                puVar11 = (unsigned int *)fadeRegs;
                uVar10 = (unsigned int)(*(int *)(iVar6 + 0x17b4) / 2);
                *puVar11 = 0x01ff0000 & *(int *)(iVar6 + 0x17b0) << 0x10;
                if ((int)uVar10 >= 0xf) {
                    goto main_fade_high;
                }
                fadeState = data_ov003_0204f9a0;
                Ov003ApplyMainFadeLow(fadeState, fadeRegs, uVar10);
                goto main_fade_done;
main_fade_high:
                {
                    fadeState = data_ov003_0204f9a0;
                    uVar10 = fadeState->blendAlpha;
                    *(unsigned short *)(puVar11 + 0xb) = 0xff;
                    *(unsigned short *)(puVar11 + 0xc) = 0xaf;
                    *(unsigned short *)(puVar11 + 0xd) = *(unsigned short *)(puVar11 + 0xd) & ~0x3f | 0x3b;
                    *(unsigned short *)((int)puVar11 + 0x2e) = 0x10ff;
                    *(unsigned short *)((int)puVar11 + 0x32) = 0xafbf;
                    *(unsigned short *)(puVar11 + 0xd) = *(unsigned short *)(puVar11 + 0xd) & ~0x3f00 | 0x3900;
                    *(unsigned short *)((int)puVar11 + 0x36) = *(unsigned short *)((int)puVar11 + 0x36) & ~0x3f | 0x19;
                    *reg_dispcnt = *reg_dispcnt & ~0xe000 | 0x6000;
                    if (uVar10 == 0xf) {
                        *(volatile unsigned short *)0x04000050 = 0;
                    } else {
                        G2x_SetBlendAlpha_(0x04000050, 8, 3, uVar10, 0xf - uVar10);
                    }
                }
main_fade_done:
                ;
            }
            *reg_dispcnt = *reg_dispcnt & ~0x1f00 | 0xb00;
        } else {
            *reg_dispcnt = *reg_dispcnt & ~0x1f00 | 0x900;
            *(volatile unsigned short *)0x04000050 = 0;
        }
        puVar8 = (unsigned short *)0x04000008;
        *(unsigned short *)0x04000008 = *(unsigned short *)0x04000008 & ~3 | 3;
        puVar8[1] = puVar8[1] & ~3 | 1;
        puVar8[3] = puVar8[3] & ~3;
        GX_SetBankForSubBG(0x180);
        *(volatile unsigned short *)0x04001050 = 0;
        Ov003SetSubVisiblePlanes(0x14);
        Ov003SetSubBg3Priority(3);
        Ov003SetSubBg2Priority(0);
        *(volatile unsigned int *)0x04001000 &= ~0xe000;
    }
    Ov003CommitDisplay();
}

