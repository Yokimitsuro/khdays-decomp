#pragma thumb on
/* func_0201e1d0 -- reset both 2D engines to a blank state, MAIN (THUMB). Turns both displays on,
 * hides every plane, releases all VRAM banks, maps everything to LCDC and clears it, clears both
 * palettes and both OAMs (hidden objects), zeroes all BG scroll offsets, resets the four affine BG
 * matrices to identity, restores the default BG priorities (0..3), closes the windows, turns
 * blending off and sets the 3D clear colour to black at the far depth. The bank releases use the
 * SDK's GX_DisableBankFor* entry points, some of which carry other names in the symbol table. */
typedef unsigned short u16;
typedef unsigned int u32;
typedef int fx32;
typedef volatile u16 vu16;
typedef volatile u32 vu32;

typedef struct { fx32 _00, _01, _10, _11; } MtxFx22;

#define reg_GX_DISPCNT      (*(vu32 *)0x04000000)
#define reg_G2_BG0CNT       (*(vu16 *)0x04000008)
#define reg_G2_BG1CNT       (*(vu16 *)0x0400000a)
#define reg_G2_BG2CNT       (*(vu16 *)0x0400000c)
#define reg_G2_BG3CNT       (*(vu16 *)0x0400000e)
#define reg_G2_BG0OFS       (*(vu32 *)0x04000010)
#define reg_G2_BG1OFS       (*(vu32 *)0x04000014)
#define reg_G2_BG2OFS       (*(vu32 *)0x04000018)
#define reg_G2_BG3OFS       (*(vu32 *)0x0400001c)
#define reg_G2_BG2PA        (*(vu16 *)0x04000020)
#define reg_G2_BG3PA        (*(vu16 *)0x04000030)
#define reg_G2_BLDCNT       (*(vu16 *)0x04000050)
#define reg_GXS_DB_DISPCNT  (*(vu32 *)0x04001000)
#define reg_G2S_DB_BG0CNT   (*(vu16 *)0x04001008)
#define reg_G2S_DB_BG1CNT   (*(vu16 *)0x0400100a)
#define reg_G2S_DB_BG2CNT   (*(vu16 *)0x0400100c)
#define reg_G2S_DB_BG3CNT   (*(vu16 *)0x0400100e)
#define reg_G2S_DB_BG0OFS   (*(vu32 *)0x04001010)
#define reg_G2S_DB_BG1OFS   (*(vu32 *)0x04001014)
#define reg_G2S_DB_BG2OFS   (*(vu32 *)0x04001018)
#define reg_G2S_DB_BG3OFS   (*(vu32 *)0x0400101c)
#define reg_G2S_DB_BG2PA    (*(vu16 *)0x04001020)
#define reg_G2S_DB_BG3PA    (*(vu16 *)0x04001030)
#define reg_G2S_DB_BLDCNT   (*(vu16 *)0x04001050)

#define HW_LCDC_VRAM        ((void *)0x06800000)
#define HW_LCDC_VRAM_SIZE   0xa4000
#define HW_BG_PLTT          ((void *)0x05000000)
#define HW_DB_BG_PLTT       ((void *)0x05000400)
#define HW_OAM              ((void *)0x07000000)
#define HW_DB_OAM           ((void *)0x07000400)

extern void func_0200566c(void);                        /* GX_DispOn */
/* The GX_DisableBankFor* calls return the banks they released (u32), as in the SDK; declaring them
 * void changes how the rest of the function is scheduled. */
extern u32 SNDi_UnlockMutex_0x020065ac(void);          /* GX_DisableBankForTex */
extern u32 SNDi_UnlockMutex_0x020065c0(void);          /* GX_DisableBankForTexPltt */
extern u32 SNDi_UnlockMutex_0x0200653c(void);          /* GX_DisableBankForBG */
extern u32 GX_DisableBankForBGExtPltt_0x02006564(void);
extern u32 SNDi_UnlockMutex_0x02006550(void);          /* GX_DisableBankForOBJ */
extern u32 GX_DisableBankForOBJExtPltt_0x02006588(void);
extern u32 SNDi_UnlockMutex_0x020065e8(void);          /* GX_DisableBankForSubBG */
extern u32 SNDi_UnlockMutex_0x020065fc(void);          /* GX_DisableBankForSubOBJ */
extern u32 GX_DisableBankForSubBGExtPltt_0x02006610(void);
extern u32 GX_DisableBankForSubOBJExtPltt_0x02006638(void);
extern u32 SNDi_UnlockMutex_0x020065d4(void);          /* GX_DisableBankForLCDC */
extern void GX_SetBankForLCDC(int banks);
extern void MIi_CpuClearFast(u32 data, void *dest, u32 size);
extern void MTX_Identity22_(MtxFx22 *pDst);
extern void G2x_SetBGyAffine_(vu16 *reg, const MtxFx22 *mtx, int centerX, int centerY, int x1, int y1);
extern void G3X_SetClearColor(int rgb, int alpha, int depth, int polygonID, int fog);

static inline void GXS_DispOn(void)
{
    reg_GXS_DB_DISPCNT |= 0x10000;
}

static inline void GX_SetVisiblePlane(int plane)
{
    reg_GX_DISPCNT = (reg_GX_DISPCNT & ~0x1f00) | (plane << 8);
}

static inline void GXS_SetVisiblePlane(int plane)
{
    reg_GXS_DB_DISPCNT = (reg_GXS_DB_DISPCNT & ~0x1f00) | (plane << 8);
}

static inline void GX_SetVisibleWnd(int window)
{
    reg_GX_DISPCNT = (reg_GX_DISPCNT & ~0xe000) | (window << 13);
}

static inline void GXS_SetVisibleWnd(int window)
{
    reg_GXS_DB_DISPCNT = (reg_GXS_DB_DISPCNT & ~0xe000) | (window << 13);
}

#define BG_OFFSET(h, v) ((u32)((((h) << 0) & 0x1ff) | (((v) << 16) & 0x1ff0000)))
#define BG_PRIORITY(reg, p) ((reg) = (u16)(((reg) & ~3) | ((p) << 0)))

void func_0201e1d0(void)
{
    MtxFx22 mtx;

    func_0200566c();
    GXS_DispOn();
    GX_SetVisiblePlane(0);
    GXS_SetVisiblePlane(0);

    SNDi_UnlockMutex_0x020065ac();
    SNDi_UnlockMutex_0x020065c0();
    SNDi_UnlockMutex_0x0200653c();
    GX_DisableBankForBGExtPltt_0x02006564();
    SNDi_UnlockMutex_0x02006550();
    GX_DisableBankForOBJExtPltt_0x02006588();
    SNDi_UnlockMutex_0x020065e8();
    SNDi_UnlockMutex_0x020065fc();
    GX_DisableBankForSubBGExtPltt_0x02006610();
    GX_DisableBankForSubOBJExtPltt_0x02006638();

    GX_SetBankForLCDC(0x1ff);
    MIi_CpuClearFast(0, HW_LCDC_VRAM, HW_LCDC_VRAM_SIZE);
    SNDi_UnlockMutex_0x020065d4();

    MIi_CpuClearFast(0, HW_BG_PLTT, 0x400);
    MIi_CpuClearFast(0, HW_DB_BG_PLTT, 0x400);
    MIi_CpuClearFast(0xc0, HW_OAM, 0x400);
    MIi_CpuClearFast(0xc0, HW_DB_OAM, 0x400);

    reg_G2_BG0OFS = BG_OFFSET(0, 0);
    reg_G2_BG1OFS = BG_OFFSET(0, 0);
    reg_G2_BG2OFS = BG_OFFSET(0, 0);
    reg_G2_BG3OFS = BG_OFFSET(0, 0);
    reg_G2S_DB_BG0OFS = BG_OFFSET(0, 0);
    reg_G2S_DB_BG1OFS = BG_OFFSET(0, 0);
    reg_G2S_DB_BG2OFS = BG_OFFSET(0, 0);
    reg_G2S_DB_BG3OFS = BG_OFFSET(0, 0);

    MTX_Identity22_(&mtx);
    G2x_SetBGyAffine_(&reg_G2_BG2PA, &mtx, 0, 0, 0, 0);
    G2x_SetBGyAffine_(&reg_G2_BG3PA, &mtx, 0, 0, 0, 0);
    G2x_SetBGyAffine_(&reg_G2S_DB_BG2PA, &mtx, 0, 0, 0, 0);
    G2x_SetBGyAffine_(&reg_G2S_DB_BG3PA, &mtx, 0, 0, 0, 0);

    BG_PRIORITY(reg_G2_BG0CNT, 0);
    BG_PRIORITY(reg_G2_BG1CNT, 1);
    BG_PRIORITY(reg_G2_BG2CNT, 2);
    BG_PRIORITY(reg_G2_BG3CNT, 3);
    BG_PRIORITY(reg_G2S_DB_BG0CNT, 0);
    BG_PRIORITY(reg_G2S_DB_BG1CNT, 1);
    BG_PRIORITY(reg_G2S_DB_BG2CNT, 2);
    BG_PRIORITY(reg_G2S_DB_BG3CNT, 3);

    GX_SetVisibleWnd(0);
    GXS_SetVisibleWnd(0);
    reg_G2_BLDCNT = 0;
    reg_G2S_DB_BLDCNT = 0;
    G3X_SetClearColor(0, 0, 0x7fff, 0, 0);
}
#pragma thumb off
