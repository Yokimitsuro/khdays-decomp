/* func_ov008_0204d7c0 -- bring up the menu display, ov008. Resets the 2D/3D engines,
 * powers the LCD, assigns VRAM banks (BG A=3, sub-BG=4, OBJ=0x70, sub-OBJ=8), sets the
 * sub graphics mode, and programs the BG priorities on both engines (main BG0..3 = 1/3/2/-,
 * sub BG1..3 = 2/1/-). */
typedef unsigned short u16;
typedef unsigned int   u32;
typedef volatile u16   vu16;
typedef volatile u32   vu32;

#define reg_GX_DISPCNT (*(vu32 *)0x04000000)

extern void func_0201e1d0(void);
extern void func_02023c30(int);
extern void GX_SetBankForBG(int);
extern void GX_SetBankForSubBG(int);
extern void GX_SetBankForOBJ(int);
extern void GX_SetBankForSubOBJ(int);
extern void GXS_SetGraphicsMode(int);
extern void func_020056b4(int, int, int);

void func_ov008_0204d7c0(void) {
    func_0201e1d0();
    func_02023c30(0);
    *(vu16 *)0x04000304 |= 0x8000;
    reg_GX_DISPCNT &= ~0x38000000;
    reg_GX_DISPCNT &= ~0x7000000;
    GX_SetBankForBG(3);
    GX_SetBankForSubBG(4);
    GX_SetBankForOBJ(0x70);
    GX_SetBankForSubOBJ(8);
    GXS_SetGraphicsMode(0);
    func_020056b4(1, 0, 0);
    {
        vu16 *bg1 = (vu16 *)0x0400000a;
        vu16 *bg0 = (vu16 *)0x04000008;
        vu16 *sub1 = (vu16 *)0x0400100a;
        vu16 *sub2 = (vu16 *)0x0400100c;
        bg1[0] = (bg1[0] & ~3) | 3;
        bg1[1] = (bg1[1] & ~3) | 2;
        *bg0 = (*bg0 & ~3) | 1;
        bg1[2] = bg1[2] & ~3;
        *sub1 = (*sub1 & ~3) | 2;
        *sub2 = (*sub2 & ~3) | 1;
        sub2[1] = sub2[1] & ~3;
    }
}
