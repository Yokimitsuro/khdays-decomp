typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed char s8;
typedef short s16;
typedef int s32;
typedef unsigned long long u64;
typedef long long s64;
typedef int BOOL;
typedef int OSIntrMode;
typedef void *OSMessage;
typedef volatile unsigned short vu16;
typedef volatile unsigned int vu32;
typedef volatile unsigned char vu8;

#define NULL ((void *)0)
#define TRUE 1
#define FALSE 0
#define HW_MAIN_MEM 0x02000000

#define offsetof(type, member) ((u32)&(((type *)0)->member))

#define BG_MODE_WARNING 8

typedef vu32 REGType32v;
typedef enum {
    GX_BGMODE_0 = 0,
    GX_BGMODE_1 = 1,
    GX_BGMODE_2 = 2,
    GX_BGMODE_3 = 3,
    GX_BGMODE_4 = 4,
    GX_BGMODE_5 = 5,
    GX_BGMODE_6 = 6
} GXBGMode;
typedef enum {
    GX_BG0_AS_2D = 0,
    GX_BG0_AS_3D = 1
} GXBG0As;
typedef enum {
    GX_DISPMODE_GRAPHICS = 0x01,
    GX_DISPMODE_VRAM_A = 0x02,
    GX_DISPMODE_VRAM_B = 0x06,
    GX_DISPMODE_VRAM_C = 0x0a,
    GX_DISPMODE_VRAM_D = 0x0e,
    GX_DISPMODE_MMEM = 0x03
} GXDispMode;
void func_020056b4(GXDispMode dispMode, GXBGMode bgMode, GXBG0As bg0_2d3d);
inline BOOL IsBG03D (void)
{
    return ((*( REGType32v *) (0x04000000 + 0x000)) & 0x00000008 ) != 0;
}
inline GXBGMode GetBGModeMain (void)
{
    return (GXBGMode)(((*( REGType32v *) (0x04000000 + 0x000)) & 0x00000007 ) >> 0 );
}

/* func_020128c0 -- NitroSystem g2d_Screen.c: ChangeBGModeByTableMain. */
void func_020128c0 (const u8 modeTable[])
{
    GXBGMode mode = (GXBGMode)modeTable[GetBGModeMain()];
    GXBG0As bg0as = IsBG03D() ? GX_BG0_AS_3D: GX_BG0_AS_2D;

    if (mode >= BG_MODE_WARNING) {
        mode -= BG_MODE_WARNING;
    }

    func_020056b4(GX_DISPMODE_GRAPHICS, mode, bg0as);
}
