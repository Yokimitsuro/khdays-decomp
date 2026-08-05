/*
 * Ov008_MainMenu_SetupDisplay - configure the video hardware for the main menu scene:
 * VRAM bank assignment, both display-control registers, the 3D clear colour, and the
 * BG layer control/priority for the main and sub screens. Called from
 * Ov008_MainMenu_StateTick state 0 (first-time setup).
 *
 * Sequence: reset the 3D pipeline (func_0201e1d0), assign texture/OBJ-palette banks,
 * clear the 3D display-control bits and set DISP3DCNT bit3 with a G3X clear colour,
 * load the geometry/matrix state (func_02010f08/e80/011134/011174/0201133c fed a
 * 10-word transform block), assign the OBJ/BG banks, set the main DISPCNT display mode
 * (bits 4/9-12), then the sub DISPCNT, power on the sub-LCD (POWCNT1 bit15), program
 * the BG char/screen-base bits and priorities for the layers used by the menu, zero the
 * sub-screen scroll registers, and clear the sub BG0 screen map.
 *
 * MMIO is done through held `volatile` register pointers (DisplayRegisters struct at
 * 0x04000000 / 0x04001000, DISP3DCNT, POWCNT1) so mwcc emits the ROM's base-register
 * reuse and read-modify-write halfword stores; raw casts mismatch. The DISP3DCNT first
 * mask 0xffffcffd is held in a local because it is reused (shifted >>0x11) as the G3X
 * clear-colour argument, matching the ROM's single pooled constant + runtime lsr.
 */

typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

extern void  func_0201e1d0(void);
extern void  GX_DisableBankForOBJExtPltt_0x02006588(void);
extern void  GX_SetBankForTex(int bank);
extern void  GX_BeginLoadOBJExtPltt(int a);
extern void  G3X_SetClearColor(int r, int g, int b, int a, int e);
extern void  func_02010f08(void);
extern void  func_02010e80(int a, int b);
extern void  func_02011134(void *p);
extern void  func_0201133c(void);
extern void  func_02011174(int a, int b);
extern void  GX_SetBankForOBJ(int bank);
extern void  GX_SetBankForBG(int bank);
extern void  GX_SetBankForBGExtPltt(int bank);
extern void  func_020056b4(int a, int b, int c);
extern void  GX_SetBankForSubBG(int bank);
extern void  GX_SetBankForSubBGExtPltt(int bank);
extern void  GX_SetBankForSubOBJ(int bank);
extern void  GX_SetBankForSubOBJExtPltt(int bank);
extern void *G2S_GetBG0ScrPtr(void);
extern void  MIi_CpuClearFast(u32 value, void *dst, u32 size);
extern void  func_ov025_02084ab4(int arg);

typedef struct DisplayRegisters {
    volatile u32 dispcnt;      /* +0x00 */
    u8 pad_04[4];
    volatile u16 bg0cnt;       /* +0x08 */
    volatile u16 bg1cnt;       /* +0x0a */
    volatile u16 bg2cnt;       /* +0x0c */
    volatile u16 bg3cnt;       /* +0x0e */
    volatile u32 bg0ofs;       /* +0x10 */
    volatile u32 bg1ofs;       /* +0x14 */
    volatile u32 bg2ofs;       /* +0x18 */
    volatile u32 bg3ofs;       /* +0x1c */
    u8 pad_20[0x30];
    volatile u16 bldcnt;       /* +0x50 */
} DisplayRegisters;

static volatile DisplayRegisters *const MAIN_DISPLAY = (volatile DisplayRegisters *)0x04000000;
static volatile DisplayRegisters *const SUB_DISPLAY  = (volatile DisplayRegisters *)0x04001000;
static volatile u16 *const REG_DISP3DCNT = (volatile u16 *)0x04000060;
static volatile u16 *const REG_POWCNT1   = (volatile u16 *)0x04000304;

void func_ov025_0208cde0(void)
{
    u32 mask;
    u32 mtx[10];
    void *scr;

    func_0201e1d0();
    GX_DisableBankForOBJExtPltt_0x02006588();
    GX_SetBankForTex(3);
    GX_BeginLoadOBJExtPltt(0x10);

    mask = 0xffffcffd;
    *REG_DISP3DCNT = *REG_DISP3DCNT & mask;
    *REG_DISP3DCNT = *REG_DISP3DCNT & 0xcffb;
    *REG_DISP3DCNT = (*REG_DISP3DCNT & ~0x3000) | 8;
    G3X_SetClearColor(0, 0, mask >> 0x11, 0x3f, 0);

    func_02010f08();
    func_02010e80(2, 1);

    mtx[0] = 0; mtx[1] = 0x20000; mtx[2] = 0; mtx[3] = 0x20000; mtx[4] = 0;
    mtx[5] = 0; mtx[6] = 0; mtx[7] = 0x20000; mtx[8] = 0; mtx[9] = 0x20000;
    func_02011134(mtx);
    func_0201133c();
    func_02011174(0x10000, 1);

    GX_SetBankForOBJ(0x40);
    MAIN_DISPLAY->dispcnt = (MAIN_DISPLAY->dispcnt & 0xffcfffef) | 0x10;
    GX_SetBankForBG(0x20);
    GX_SetBankForBGExtPltt(0);
    GX_SetBankForOBJExtPltt(0);
    func_020056b4(1, 0, 1);
    MAIN_DISPLAY->dispcnt = (MAIN_DISPLAY->dispcnt & ~0x1f00) | 0x1b00;

    GX_SetBankForSubBG(4);
    GX_SetBankForSubBGExtPltt(0);
    GX_SetBankForSubOBJ(8);
    SUB_DISPLAY->dispcnt = (SUB_DISPLAY->dispcnt & 0xffcfffef) | 0x10;
    GX_SetBankForSubOBJExtPltt(0);
    SUB_DISPLAY->dispcnt = (SUB_DISPLAY->dispcnt & ~0x1f00) | 0x1f00;

    *REG_POWCNT1 |= 0x8000;

    MAIN_DISPLAY->bg1cnt = (MAIN_DISPLAY->bg1cnt & 0x43) | 0x600;
    MAIN_DISPLAY->bg3cnt = (MAIN_DISPLAY->bg3cnt & 0x43) | 0x700;
    SUB_DISPLAY->bg0cnt  = (SUB_DISPLAY->bg0cnt & 0x43) | 0x98;
    SUB_DISPLAY->bg1cnt  = (SUB_DISPLAY->bg1cnt & 0x43) | 0x184;
    SUB_DISPLAY->bg2cnt  = (SUB_DISPLAY->bg2cnt & 0x43) | 0x28c;
    SUB_DISPLAY->bg3cnt  = (SUB_DISPLAY->bg3cnt & 0x43) | 0x384;
    SUB_DISPLAY->bg0ofs  = 0;
    SUB_DISPLAY->bg1ofs  = 0;
    SUB_DISPLAY->bg2ofs  = 0;
    SUB_DISPLAY->bg3ofs  = 0;

    MAIN_DISPLAY->bg0cnt = (MAIN_DISPLAY->bg0cnt & ~3) | 3;
    MAIN_DISPLAY->bg1cnt = (MAIN_DISPLAY->bg1cnt & ~3);
    MAIN_DISPLAY->bg2cnt = (MAIN_DISPLAY->bg2cnt & ~3) | 1;
    MAIN_DISPLAY->bg3cnt = (MAIN_DISPLAY->bg3cnt & ~3) | 2;
    MAIN_DISPLAY->bldcnt = 0;

    scr = G2S_GetBG0ScrPtr();
    MIi_CpuClearFast(0, scr, 0x800);
    func_ov025_02084ab4(0);
}
