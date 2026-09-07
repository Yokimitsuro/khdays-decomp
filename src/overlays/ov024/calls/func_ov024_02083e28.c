/* MobiClip: set the main engine up for movie playback.
 *
 * Gives the movie its VRAM banks, points the four backgrounds at the screen
 * blocks the player uses, lays the sprite grid out, resets the background
 * affine transform sixteen scanlines up, and finally hides every layer and
 * puts the backgrounds back in priority order.
 */
typedef unsigned short u16;
typedef unsigned int u32;

struct Mtx22 {
    int m[4];
};

extern void GX_SetBankForBG(int nBank);
extern void GX_SetBankForOBJ(int nBank);
extern void GX_SetBankForBGExtPltt(int nBank);
extern void func_020056b4(u16 param_1, u32 param_2, int param_3);
extern void func_ov024_02083d0c(int bMainScreen);
extern void MTX_Identity22_(struct Mtx22 *pMtx);
extern void G2x_SetBGyAffine_(volatile void *pReg, const struct Mtx22 *pMtx,
                              int nCentreX, int nCentreY, int nX, int nY);

void func_ov024_02083e28(void)
{
    struct Mtx22 mtx;

    GX_SetBankForBG(1);
    GX_SetBankForOBJ(2);
    func_020056b4(1, 3, 0);

    {
        volatile u16 *reg_bg0cnt = (volatile u16 *)0x04000008;
        volatile u16 *reg_bg1cnt = (volatile u16 *)0x0400000a;
        volatile u16 *reg_bg2cnt = (volatile u16 *)0x0400000c;
        volatile u16 *reg_bg3cnt = (volatile u16 *)0x0400000e;

        *reg_bg0cnt = (u16)((*reg_bg0cnt & 0x43) | 0xc00);
        *reg_bg1cnt = (u16)((*reg_bg1cnt & 0x43) | 0xd00);
        *reg_bg2cnt = (u16)((*reg_bg2cnt & 0x43) | 0xe00);
        *reg_bg3cnt = (u16)((*reg_bg3cnt & 0x43) | 0x284 | 0x4000);
    }

    func_ov024_02083d0c(1);
    GX_SetBankForBGExtPltt(0);
    MTX_Identity22_(&mtx);
    G2x_SetBGyAffine_((volatile void *)0x04000030, &mtx, 0, 0, 0, -0x10);

    {
        volatile u32 *reg_dispcnt = (volatile u32 *)0x04000000;
        volatile u32 *reg_bg0ofs = (volatile u32 *)0x04000010;
        volatile u32 *reg_bg1ofs = (volatile u32 *)0x04000014;
        volatile u32 *reg_bg2ofs = (volatile u32 *)0x04000018;
        volatile u16 *reg_bg0cnt = (volatile u16 *)0x04000008;
        volatile u16 *reg_bg1cnt = (volatile u16 *)0x0400000a;
        volatile u16 *reg_bg2cnt = (volatile u16 *)0x0400000c;
        volatile u16 *reg_bg3cnt = (volatile u16 *)0x0400000e;

        *reg_dispcnt = *reg_dispcnt & ~0x1f00;
        *reg_bg0ofs = 0;
        *reg_bg1ofs = 1;
        *reg_bg2ofs = 0x10000;
        *reg_bg0cnt = (u16)(*reg_bg0cnt & ~3);
        *reg_bg1cnt = (u16)((*reg_bg1cnt & ~3) | 1);
        *reg_bg2cnt = (u16)((*reg_bg2cnt & ~3) | 2);
        *reg_bg3cnt = (u16)((*reg_bg3cnt & ~3) | 3);
    }
}
