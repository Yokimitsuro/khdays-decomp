/* Ov026_SetupShopDisplay -- Ov008_SetupShopDisplay: configure the video hardware
 * for the shop scene.  Both master brightnesses go to -16 (black), the 3D
 * pipeline is reset, banks A / D / B / F assigned (texture, BG, OBJ, OBJ
 * extended palette) with the OBJ extended palette load begun, the geometry
 * state initialised (mode 1 / 1, 0x4000 / 1), graphics mode 1 / 0 / 1 set,
 * the main BG1..3 control words set to character bases 8 / 0x104 / 0x204
 * with priorities 0..3 (BG0 first) and the main DISPCNT set to display mode
 * 1 with BG0 on 3D; the sub engine gets banks C / H / I, graphics mode 0,
 * BG0..3 control words 8 / 0x104 / 0x204 / 0x304 with priorities 0..3, its
 * DISPCNT mode bits, the sub LCD powered, and both DISPCNTs every layer on.
 *
 * MMIO through held volatile register pointers as in Ov008_WorldMap_SetupDisplay.
 */

#include "nitro/types.h"
#include "game/engine.h"

typedef struct DisplayRegisters {
    volatile u32 dispcnt;      /* +0x00 */
    u8 pad_04[4];
    volatile u16 bg0cnt;       /* +0x08 */
    volatile u16 bg1cnt;       /* +0x0a */
    volatile u16 bg2cnt;       /* +0x0c */
    volatile u16 bg3cnt;       /* +0x0e */
} DisplayRegisters;

static volatile DisplayRegisters *const MAIN_DISPLAY = (volatile DisplayRegisters *)0x04000000;
static volatile DisplayRegisters *const SUB_DISPLAY  = (volatile DisplayRegisters *)0x04001000;
static volatile u16 *const REG_POWCNT1 = (volatile u16 *)0x04000304;

extern void  GX_SetBankForTex(int nBank);
extern void  GX_SetBankForTexPltt(int nBank);
extern void  GX_SetBankForBG(int nBank);
extern void  GX_SetBankForOBJ(int nBank);
extern void  GX_SetBankForOBJExtPltt(int nBank);
extern void  NNS_GfdInitFrmTexVramManager(int nA, int nB);
extern void  NNS_GfdInitFrmPlttVramManager(int nA, int nB);
extern void  GX_SetGraphicsMode(int nMode, int nBgMode, int nBg0Mode);         /* GX_SetGraphicsMode */
extern void  GX_SetBankForSubBG(int nBank);
extern void  GX_SetBankForSubOBJ(int nBank);
extern void  GX_SetBankForSubOBJExtPltt(int nBank);
extern void  GXS_SetGraphicsMode(int nMode);

void Ov026_SetupShopDisplay(void)
{
    SetMasterBrightnessMain(-16);
    SetMasterBrightnessSub(-16);
    Gfx_Reset2DEngines();
    GX_SetBankForTex(1);
    GX_SetBankForTexPltt(0x40);
    GX_SetBankForBG(0x10);
    GX_SetBankForOBJ(2);
    GX_SetBankForOBJExtPltt(0x20);
    NNS_GfdInitFrmTexVramManager(1, 1);
    NNS_GfdInitFrmPlttVramManager(0x4000, 1);
    GX_SetGraphicsMode(1, 0, 1);
    MAIN_DISPLAY->bg1cnt = (MAIN_DISPLAY->bg1cnt & 0x43) | 8;
    MAIN_DISPLAY->bg2cnt = (MAIN_DISPLAY->bg2cnt & 0x43) | 0x104;
    MAIN_DISPLAY->bg3cnt = (MAIN_DISPLAY->bg3cnt & 0x43) | 0x204;
    MAIN_DISPLAY->bg0cnt = MAIN_DISPLAY->bg0cnt & ~3;
    MAIN_DISPLAY->bg1cnt = (MAIN_DISPLAY->bg1cnt & ~3) | 1;
    MAIN_DISPLAY->bg2cnt = (MAIN_DISPLAY->bg2cnt & ~3) | 2;
    MAIN_DISPLAY->bg3cnt = (MAIN_DISPLAY->bg3cnt & ~3) | 3;
    MAIN_DISPLAY->dispcnt = (MAIN_DISPLAY->dispcnt & 0xffcfffef) | 0x100010;
    GX_SetBankForSubBG(4);
    GX_SetBankForSubOBJ(8);
    GX_SetBankForSubOBJExtPltt(0x100);
    GXS_SetGraphicsMode(0);
    SUB_DISPLAY->bg0cnt = (SUB_DISPLAY->bg0cnt & 0x43) | 8;
    SUB_DISPLAY->bg1cnt = (SUB_DISPLAY->bg1cnt & 0x43) | 0x104;
    SUB_DISPLAY->bg2cnt = (SUB_DISPLAY->bg2cnt & 0x43) | 0x204;
    SUB_DISPLAY->bg3cnt = (SUB_DISPLAY->bg3cnt & 0x43) | 0x304;
    SUB_DISPLAY->bg0cnt = SUB_DISPLAY->bg0cnt & ~3;
    SUB_DISPLAY->bg1cnt = (SUB_DISPLAY->bg1cnt & ~3) | 1;
    SUB_DISPLAY->bg2cnt = (SUB_DISPLAY->bg2cnt & ~3) | 2;
    SUB_DISPLAY->bg3cnt = (SUB_DISPLAY->bg3cnt & ~3) | 3;
    SUB_DISPLAY->dispcnt = (SUB_DISPLAY->dispcnt & 0xffcfffef) | 0x200010;
    *REG_POWCNT1 |= 0x8000;
    MAIN_DISPLAY->dispcnt = (MAIN_DISPLAY->dispcnt & ~0x1f00) | 0x1f00;
    SUB_DISPLAY->dispcnt = (SUB_DISPLAY->dispcnt & ~0x1f00) | 0x1f00;
}
