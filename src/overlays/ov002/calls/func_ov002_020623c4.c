/*
 * Ov002_SetUpSubScreen - put the sub engine into the layout the caption screen
 * uses.
 *
 * The four backgrounds get their own character and screen bases, the two
 * scroll pairs are zeroed, the blend takes the first two layers over the third
 * with the backdrop, both windows are opened over the whole screen, the display
 * control keeps everything but its background-mode bits, and the four layers
 * are given their priorities. Every screen map is then cleared.
 *
 * THUMB.
 *
 * Three things about the way this is written are load-bearing.
 *
 * The window and display-control registers are reached by their own absolute
 * addresses rather than as offsets from the background base. Derived from that
 * base, the compiler rebuilds the window address before every one of the five
 * volatile accesses, because it can always redo it in two cheap instructions;
 * an address it cannot derive has to be materialised once and kept, which is
 * what the original does. The display control is the same story: derived, the
 * compiler reuses the 0x80 it already has for the first window rectangle,
 * subtracts 0x88 from it to reach minus eight, and ends up addressing the
 * register with a base-plus-index load.
 *
 * The window plane and the effect bit are separate locals carried through a
 * scratch, not folded into the value. Written as one expression the compiler
 * folds 0xe with 0x20 into 0x2e and the pair of shifts into 0x2e00, which is
 * six instructions shorter than the original - the original keeps both values
 * live and ORs them in.
 *
 * Those two pull in opposite directions on size, by six instructions each, and
 * only together do they come out exact.
 */

typedef unsigned short u16;
typedef unsigned int u32;

extern void GXS_SetGraphicsMode(int nMode);
extern void *G2S_GetBG0ScrPtr(void);
extern void *G2S_GetBG1ScrPtr(void);
extern void *G2S_GetBG2ScrPtr(void);
extern void *G2S_GetBG3ScrPtr(void);
extern void MIi_CpuClearFast(u32 nValue, void *pDst, u32 nSize);

void func_ov002_020623c4(void)
{
    int nPlane;
    int nEffect;
    int nWin;
    volatile unsigned short *pWin;
    volatile u16 *pBg = (volatile u16 *)0x04001008;

    GXS_SetGraphicsMode(0);

    pBg[0] = (pBg[0] & 0x43) | 0x5408;
    pBg[1] = (pBg[1] & 0x43) | 0x1508;
    pBg[2] = (pBg[2] & 0x43) | 0x1600;
    pBg[3] = (pBg[3] & 0x43) | 0x1700;
    *(volatile u32 *)(pBg + 4) = 0;
    *(volatile u32 *)(pBg + 6) = 0;

    nPlane = 0xe;
    nEffect = 0x20;
    pWin = (volatile unsigned short *)0x04001048;
    nWin = (pWin[0] & ~0x3f) | nPlane;
    nWin |= nEffect;
    pWin[0] = nWin;
    nWin = (pWin[0] & ~0x3f00) | (nPlane << 8);
    nWin |= nEffect << 8;
    pWin[0] = nWin;
    nWin = (*(volatile unsigned short *)0x0400104a & ~0x3f) | 0xf;
    nWin |= nEffect;
    *(volatile unsigned short *)0x0400104a = nWin;

    pBg[0x1c] = 0x80;
    pBg[0x1e] = 0x28c0;
    pBg[0x1d] = 0x8000;
    pBg[0x1f] = 0x28c0;

    *(volatile u32 *)0x04001000 = (*(volatile u32 *)0x04001000 & ~0xe000) | 0x6000;

    pBg[0] = pBg[0] & ~3;
    pBg[1] = (pBg[1] & ~3) | 1;
    pBg[2] = (pBg[2] & ~3) | 2;
    pBg[3] = (pBg[3] & ~3) | 3;

    MIi_CpuClearFast(0, G2S_GetBG0ScrPtr(), 0x1000);
    MIi_CpuClearFast(0, G2S_GetBG1ScrPtr(), 0x800);
    MIi_CpuClearFast(0, G2S_GetBG2ScrPtr(), 0x800);
    MIi_CpuClearFast(0, G2S_GetBG3ScrPtr(), 0x800);
}
