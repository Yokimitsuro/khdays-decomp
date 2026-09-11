/* GX_Init: power the 2D/3D engines on, reset the software GX state, claim the
 * VRAM spin-lock id, blank both engines' display registers and reset both
 * background affine matrices to identity.
 *
 * Algorithm cross-checked against pret/pokediamond's
 * arm9/lib/NitroSDK/src/GX.c (GX_Init); verified byte-exact against this ROM.
 */
typedef unsigned short u16;
typedef unsigned int u32;
typedef int s32;
typedef volatile unsigned short vu16;
typedef volatile unsigned int vu32;

#define reg_GX_POWCNT        (*(vu16 *)0x04000304)
#define reg_GX_DISPCNT       (*(vu32 *)0x04000000)
#define reg_GX_DISPSTAT      (*(vu16 *)0x04000004)
#define reg_GX_MASTER_BRIGHT (*(vu16 *)0x0400006c)
#define reg_G2_BG0CNT        ((void *)0x04000008)
#define reg_GXS_DB_DISPCNT   ((void *)0x04001000)

/* Enable 2D engine A, its 2D graphics, the rendering engine and the geometry
 * engine in one go. */
#define POWCNT_INIT_MASK 0x20e
#define POWCNT_DSEL      0x8000
#define POWCNT_LCD       0x0001

#define OS_LOCK_ID_ERROR (-3)

extern void GX_InitGXState(void);
extern s32 OS_GetLockID(void);
extern void OS_Terminate(void);
extern void MI_DmaFill32(u32 dmaNo, void *dest, u32 data, u32 size);
extern void INITi_CpuClear32_0x01ff86fc(u32 data, void *dest, u32 size);

/* [0] is the saved display mode (see func_02005630/func_0200566c),
   [1] is the VRAM spin-lock id. */
extern vu16 data_020446d0[];
/* [0] is the display-on flag (see func_020056b4), [1] is the DMA channel GX
   uses for its own fills, or -1 for "no DMA". */
extern u32 data_020422b4[];

void func_020054b0(void)
{
    s32 lockId;

    reg_GX_POWCNT |= POWCNT_DSEL;
    reg_GX_POWCNT = (u16)((reg_GX_POWCNT & ~POWCNT_INIT_MASK) | POWCNT_INIT_MASK);
    reg_GX_POWCNT = (u16)(reg_GX_POWCNT | POWCNT_LCD);

    GX_InitGXState();

    while (data_020446d0[1] == 0) {
        lockId = OS_GetLockID();
        if (lockId == OS_LOCK_ID_ERROR) {
            OS_Terminate();
        }
        data_020446d0[1] = (u16)lockId;
    }

    reg_GX_DISPSTAT = 0;
    reg_GX_DISPCNT = 0;

    if (data_020422b4[1] != (u32)-1) {
        MI_DmaFill32(data_020422b4[1], reg_G2_BG0CNT, 0, 0x60);
        reg_GX_MASTER_BRIGHT = 0;
        MI_DmaFill32(data_020422b4[1], reg_GXS_DB_DISPCNT, 0, 0x70);
    } else {
        INITi_CpuClear32_0x01ff86fc(0, reg_G2_BG0CNT, 0x60);
        reg_GX_MASTER_BRIGHT = 0;
        INITi_CpuClear32_0x01ff86fc(0, reg_GXS_DB_DISPCNT, 0x70);
    }

    *(vu16 *)0x04000020 = 0x100; /* BG2PA */
    *(vu16 *)0x04000026 = 0x100; /* BG2PD */
    *(vu16 *)0x04000030 = 0x100; /* BG3PA */
    *(vu16 *)0x04000036 = 0x100; /* BG3PD */
    *(vu16 *)0x04001020 = 0x100; /* sub BG2PA */
    *(vu16 *)0x04001026 = 0x100; /* sub BG2PD */
    *(vu16 *)0x04001030 = 0x100; /* sub BG3PA */
    *(vu16 *)0x04001036 = 0x100; /* sub BG3PD */
}
