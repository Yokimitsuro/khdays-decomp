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
void GXS_SetGraphicsMode(GXBGMode bgMode);
inline GXBGMode GetBGModeSub (void)
{
    return (GXBGMode)(((*( REGType32v *) (0x04000000 + 0x1000)) & 0x00000007 ) >> 0 );
}

/* func_02012904 -- NitroSystem g2d_Screen.c: ChangeBGModeByTableSub. */
void func_02012904 (const u8 modeTable[])
{
    GXBGMode mode = (GXBGMode)modeTable[GetBGModeSub()];

    if (mode >= BG_MODE_WARNING) {
        mode -= BG_MODE_WARNING;
    }

    GXS_SetGraphicsMode(mode);
}
