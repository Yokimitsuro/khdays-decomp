/* func_ov023_02083270 -- Ov023_SetupSubBackgrounds: put the sub engine into the event scene's
 * layout.  Graphics mode 0 (GXS_SetGraphicsMode), VRAM bank 0x180 for the sub backgrounds,
 * then BG1..BG3 of the sub engine get their control words (text layers 0x1508 / 0x1600 /
 * 0x1700 over the two preserved bits 0 and 6), DISPCNT_SUB shows BG1..BG3 (bits 9..11) and
 * the priorities are set: BG3 2, BG2 1, BG1 0. */
typedef unsigned short u16;
typedef unsigned int   u32;

static volatile u32 *const REG_DISPCNT_SUB = (volatile u32 *)0x04001000;
static volatile u16 *const REG_BG1CNT_SUB = (volatile u16 *)0x0400100a;
static volatile u16 *const REG_BG2CNT_SUB = (volatile u16 *)0x0400100c;
static volatile u16 *const REG_BG3CNT_SUB = (volatile u16 *)0x0400100e;

extern void GXS_SetGraphicsMode(int nMode);
extern void GX_SetBankForSubBG(int nBank);

void func_ov023_02083270(void)
{
    GXS_SetGraphicsMode(0);
    GX_SetBankForSubBG(0x180);
    *REG_BG1CNT_SUB = (*REG_BG1CNT_SUB & 0x43) | 0x1508;
    *REG_BG2CNT_SUB = (*REG_BG2CNT_SUB & 0x43) | 0x1600;
    *REG_BG3CNT_SUB = (*REG_BG3CNT_SUB & 0x43) | 0x1700;
    *REG_DISPCNT_SUB = (*REG_DISPCNT_SUB & 0xffffe0ff) | 0xe00;
    *REG_BG3CNT_SUB = (*REG_BG3CNT_SUB & ~3) | 2;
    *REG_BG2CNT_SUB = (*REG_BG2CNT_SUB & ~3) | 1;
    *REG_BG1CNT_SUB &= ~3;
}
