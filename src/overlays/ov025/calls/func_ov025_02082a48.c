/* func_ov025_02082a48 -- Ov025_SetupDisplay: the records scene's display setup (hook 0 of the
 * sub-flow table).  Both master brightnesses go black (-16), both DISPCNTs lose their BG bits
 * (8..12), the sub engine goes to graphics mode 0 and the ov002 display to the top screen
 * (02076028); the BG priorities become main BG0 3, BG1 0, BG2 1, BG3 2 and sub BG0 0, BG1 1,
 * BG2 2, BG3 3. */
typedef unsigned short u16;
typedef unsigned int   u32;

static volatile u32 *const REG_DISPCNT = (volatile u32 *)0x04000000;
static volatile u16 *const REG_BG0CNT = (volatile u16 *)0x04000008;
static volatile u16 *const REG_BG1CNT = (volatile u16 *)0x0400000a;
static volatile u16 *const REG_BG2CNT = (volatile u16 *)0x0400000c;
static volatile u16 *const REG_BG3CNT = (volatile u16 *)0x0400000e;
static volatile u32 *const REG_DB_DISPCNT = (volatile u32 *)0x04001000;
static volatile u16 *const REG_DB_BG0CNT = (volatile u16 *)0x04001008;
static volatile u16 *const REG_DB_BG1CNT = (volatile u16 *)0x0400100a;
static volatile u16 *const REG_DB_BG2CNT = (volatile u16 *)0x0400100c;
static volatile u16 *const REG_DB_BG3CNT = (volatile u16 *)0x0400100e;

extern void  func_0201e374(int nBrightness);                        /* SetMasterBrightnessMain */
extern void  func_0201e3cc(int nBrightness);                        /* SetMasterBrightnessSub */
extern void  GXS_SetGraphicsMode(int nMode);
extern void  func_ov002_02076028(int bTop);                         /* ov002: put the display on the top screen */

void func_ov025_02082a48(void)
{
    func_0201e374(-16);
    func_0201e3cc(-16);
    *REG_DISPCNT = *REG_DISPCNT & 0xffffe0ff;
    *REG_DB_DISPCNT = *REG_DB_DISPCNT & 0xffffe0ff;
    GXS_SetGraphicsMode(0);
    func_ov002_02076028(1);
    *REG_BG0CNT = (*REG_BG0CNT & ~3) | 3;
    *REG_BG1CNT = *REG_BG1CNT & ~3;
    *REG_BG2CNT = (*REG_BG2CNT & ~3) | 1;
    *REG_BG3CNT = (*REG_BG3CNT & ~3) | 2;
    *REG_DB_BG0CNT = *REG_DB_BG0CNT & ~3;
    *REG_DB_BG1CNT = (*REG_DB_BG1CNT & ~3) | 1;
    *REG_DB_BG2CNT = (*REG_DB_BG2CNT & ~3) | 2;
    *REG_DB_BG3CNT = (*REG_DB_BG3CNT & ~3) | 3;
}
