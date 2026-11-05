/* Overlay 1 boot/init entry point. Sets POWCNT2 (0x04000304) bits and clears display engine B's BG3
 * enable (bit 16 of 0x04001000), then runs
 * BootInitHookNoOp/GX_Init/OS_InitTick/RTC_Init/StoreGlobalPairAt118(0x500,0x2400)/GX_DispOff/SetMasterBrightnessMain(0x10)/SetMasterBrightnessSub(0x10)/GfxQueue_Configure(&data_0204be24,0x20)/Boot_InitVBlank
 * to prep subsystems, enables IRQ mask 0x40000, arms IME (0x04000208), and finally dispatches the
 * ov001 subsystems (Ov001_InitGameHeaps heap allocators, Ov001_ClearVideoMemory GX clear,
 * Ov001_SetupDisplayRegs DISPCNT setup, Ov001_InitTouchPanel misc, Ov001_SeedMathRandContexts RNG
 * seed). */

#include "game/engine.h"

extern void BootInitHookNoOp(void);
extern void GX_Init(void);
extern void OS_InitTick(void);
extern void RTC_Init(void);
extern void StoreGlobalPairAt118(int a, int b);
extern void GX_DispOff(void);
extern void GfxQueue_Configure(void *p, int n);
extern void OS_EnableIrqMask(int mask);
extern void Ov001_InitGameHeaps(void);
extern void Ov001_ClearVideoMemory(void);
extern void Ov001_SetupDisplayRegs(void);
extern void Ov001_InitTouchPanel(void);
extern void Ov001_SeedMathRandContexts(void);
extern int data_020422b8;
extern int data_0204be24;

void Ov001_BootInit(void) {
    volatile unsigned short *reg304 = (volatile unsigned short *)0x04000304;
    volatile unsigned int *reg1000 = (volatile unsigned int *)0x04001000;
    volatile unsigned short *reg208 = (volatile unsigned short *)0x04000208;
    unsigned short dummy;

    BootInitHookNoOp();
    *reg304 = (unsigned short)((*reg304 & ~0x20e) | 0x20e);
    data_020422b8 = 1;
    GX_Init();
    OS_InitTick();
    RTC_Init();
    StoreGlobalPairAt118(0x500, 0x2400);
    GX_DispOff();
    *reg1000 &= ~0x10000;
    SetMasterBrightnessMain(0x10);
    SetMasterBrightnessSub(0x10);
    GfxQueue_Configure(&data_0204be24, 0x20);
    Boot_InitVBlank();
    OS_EnableIrqMask(0x40000);
    dummy = *reg208;
    *reg208 = 1;
    Ov001_InitGameHeaps();
    Ov001_ClearVideoMemory();
    Ov001_SetupDisplayRegs();
    Ov001_InitTouchPanel();
    Ov001_SeedMathRandContexts();
}
