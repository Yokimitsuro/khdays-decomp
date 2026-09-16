/* func_ov023_020838b8 -- Ov023_ApplyScreenBlend: push the event scene's screen blend weight
 * (+0x1d6dc, 0..16) to the display.  In 3D mode (bit 3 of the global mode 02020a9c) the weight
 * goes to the dual-3D block (+0x87554) as its blend factor (0202ea24) while the top screen is
 * active (+0x87590 == 0); otherwise, while the weight is not the full 16, VRAM bank D is given
 * to the LCDC (GX_SetBankForLCDC 8) and a 256x192 display capture of the A+B blend is armed
 * into it (DISPCAPCNT 0xc0330000 with EVA = weight and EVB = 16 - weight). */
typedef unsigned char  u8;
typedef unsigned int   u32;

static volatile u32 *const REG_DISPCAPCNT = (volatile u32 *)0x04000064;

typedef struct Ov023Scene {
    u8   pad_00000[0x1d6dc];
    int  nBlendWeight;        /* 0x1d6dc */
    u8   pad_1d6e0[0x87554 - 0x1d6e0];
    u8   dual3d[0x87590 - 0x87554]; /* 0x87554: the dual-3D block */
    int  nActiveScreen;       /* 0x87590 */
} Ov023Scene;

typedef struct Ov023SceneRoot {
    int  nField00;            /* 0x00 */
    Ov023Scene *pScene;       /* 0x04 */
} Ov023SceneRoot;

extern int  func_02020a9c(void);                                    /* the global mode halfword */
extern void func_0202ea24(void *pDual3D, int nWeight);              /* Dual3D_SetBlendWeight */
extern void GX_SetBankForLCDC(int nBanks);
extern Ov023SceneRoot data_ov023_0208a784;

void func_ov023_020838b8(void)
{
    if (func_02020a9c() & 8) {
        if (data_ov023_0208a784.pScene->nActiveScreen == 0) {
            func_0202ea24(data_ov023_0208a784.pScene->dual3d, data_ov023_0208a784.pScene->nBlendWeight);
        }
    } else if (data_ov023_0208a784.pScene->nBlendWeight != 0x10) {
        GX_SetBankForLCDC(8);
        *REG_DISPCAPCNT = data_ov023_0208a784.pScene->nBlendWeight | (0xc0330000 | ((0x10 - data_ov023_0208a784.pScene->nBlendWeight) << 8));
    }
}
