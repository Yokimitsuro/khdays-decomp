/* Sets up the display capture used by a screen effect: both screens are swapped back (POWCNT bit 15),
 * the capture mode is chosen (func_020056b4 1/0/1 for a full blend of 16, else 0xa/4/1), the VRAM
 * banks are laid out (sub OBJ bank D, LCDC bank C) and DISPCAPCNT is programmed: with blending
 * (flag 1) capture of A+B into bank +4 with EVA = +0xc and EVB = 16 - EVA, otherwise a plain 3D
 * capture into bank +4. The main screen's layers take the +8 mask and the sub screen shows OBJ. */
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct {
    u32 flags;          /* 0x00 */
    u32 bank;           /* 0x04 */
    u32 layers;         /* 0x08 */
    u32 eva;            /* 0x0c */
} CaptureCfg;

extern void func_020056b4(int a, int b, int c);
extern void SNDi_UnlockMutex_0x020063e4(void);
extern void GX_SetBankForSubOBJ(int bank);
extern void GX_SetBankForLCDC(int bank);

void func_0202e760(CaptureCfg *cfg)
{
    *(volatile u16 *)0x04000304 &= ~0x8000;
    if (cfg->eva != 0x10) {
        func_020056b4(0xa, 4, 1);
    } else {
        func_020056b4(1, 0, 1);
    }
    SNDi_UnlockMutex_0x020063e4();
    GX_SetBankForSubOBJ(8);
    GX_SetBankForLCDC(4);
    if (cfg->flags & 1) {
        /* built in two steps: the single expression schedules the EVB term differently */
        u32 dispcapcnt = 0xc0320000 | (cfg->bank << 24);
        dispcapcnt = cfg->eva | (dispcapcnt | ((0x10 - cfg->eva) << 8));
        *(volatile u32 *)0x04000064 = dispcapcnt;
    } else {
        *(volatile u32 *)0x04000064 = 0x80360010 | (cfg->bank << 24);
    }
    *(volatile u32 *)0x04000000 = (*(volatile u32 *)0x04000000 & ~0x1f00) | (cfg->layers << 8);
    *(volatile u32 *)0x04001000 = (*(volatile u32 *)0x04001000 & ~0x1f00) | 0x1000;
}
