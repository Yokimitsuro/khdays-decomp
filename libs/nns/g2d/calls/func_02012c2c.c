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



typedef vu16 REGType16v;
typedef enum {
    GX_BG_SCRSIZE_AFFINE_128x128      = 0,
    GX_BG_SCRSIZE_AFFINE_256x256      = 1,
    GX_BG_SCRSIZE_AFFINE_512x512      = 2,
    GX_BG_SCRSIZE_AFFINE_1024x1024    = 3
} GXBGScrSizeAffine;
typedef enum {
    GX_BG_AREAOVER_XLU = 0,
    GX_BG_AREAOVER_REPEAT = 1
} GXBGAreaOver;
typedef enum {
    GX_BG_CHARBASE_0x00000 = 0,
    GX_BG_CHARBASE_0x04000 = 1,
    GX_BG_CHARBASE_0x08000 = 2,
    GX_BG_CHARBASE_0x0c000 = 3,
    GX_BG_CHARBASE_0x10000 = 4,
    GX_BG_CHARBASE_0x14000 = 5,
    GX_BG_CHARBASE_0x18000 = 6,
    GX_BG_CHARBASE_0x1c000 = 7,
    GX_BG_CHARBASE_0x20000 = 8,
    GX_BG_CHARBASE_0x24000 = 9,
    GX_BG_CHARBASE_0x28000 = 10,
    GX_BG_CHARBASE_0x2c000 = 11,
    GX_BG_CHARBASE_0x30000 = 12,
    GX_BG_CHARBASE_0x34000 = 13,
    GX_BG_CHARBASE_0x38000 = 14,
    GX_BG_CHARBASE_0x3c000 = 15
} GXBGCharBase;
typedef enum {
    GX_BG_SCRBASE_0x0000 = 0,
    GX_BG_SCRBASE_0x0800 = 1,
    GX_BG_SCRBASE_0x1000 = 2,
    GX_BG_SCRBASE_0x1800 = 3,
    GX_BG_SCRBASE_0x2000 = 4,
    GX_BG_SCRBASE_0x2800 = 5,
    GX_BG_SCRBASE_0x3000 = 6,
    GX_BG_SCRBASE_0x3800 = 7,
    GX_BG_SCRBASE_0x4000 = 8,
    GX_BG_SCRBASE_0x4800 = 9,
    GX_BG_SCRBASE_0x5000 = 10,
    GX_BG_SCRBASE_0x5800 = 11,
    GX_BG_SCRBASE_0x6000 = 12,
    GX_BG_SCRBASE_0x6800 = 13,
    GX_BG_SCRBASE_0x7000 = 14,
    GX_BG_SCRBASE_0x7800 = 15,
    GX_BG_SCRBASE_0x8000 = 16,
    GX_BG_SCRBASE_0x8800 = 17,
    GX_BG_SCRBASE_0x9000 = 18,
    GX_BG_SCRBASE_0x9800 = 19,
    GX_BG_SCRBASE_0xa000 = 20,
    GX_BG_SCRBASE_0xa800 = 21,
    GX_BG_SCRBASE_0xb000 = 22,
    GX_BG_SCRBASE_0xb800 = 23,
    GX_BG_SCRBASE_0xc000 = 24,
    GX_BG_SCRBASE_0xc800 = 25,
    GX_BG_SCRBASE_0xd000 = 26,
    GX_BG_SCRBASE_0xd800 = 27,
    GX_BG_SCRBASE_0xe000 = 28,
    GX_BG_SCRBASE_0xe800 = 29,
    GX_BG_SCRBASE_0xf000 = 30,
    GX_BG_SCRBASE_0xf800 = 31
} GXBGScrBase;
typedef enum NNSG2dBGSelect {
    NNS_G2D_BGSELECT_MAIN0,
    NNS_G2D_BGSELECT_MAIN1,
    NNS_G2D_BGSELECT_MAIN2,
    NNS_G2D_BGSELECT_MAIN3,
    NNS_G2D_BGSELECT_SUB0,
    NNS_G2D_BGSELECT_SUB1,
    NNS_G2D_BGSELECT_SUB2,
    NNS_G2D_BGSELECT_SUB3,
    NNS_G2D_BGSELECT_NUM
} NNSG2dBGSelect;
inline REGType16v * GetBGnCNT (NNSG2dBGSelect n)
{
    extern REGType16v * const data_02041ac0[];
    return data_02041ac0[n];
}
inline BOOL IsMainBG (NNSG2dBGSelect bg)
{
    return (bg <= NNS_G2D_BGSELECT_MAIN3);
}
inline u16 MakeBGnCNTValAffine (GXBGScrSizeAffine screenSize, GXBGAreaOver areaOver, GXBGScrBase screenBase, GXBGCharBase charBase)
{
    return (u16)(
        (screenSize << 14 )
        | (screenBase << 8 )
        | (charBase << 2 )
        | (areaOver << 13 )
        );
}
inline void SetBGnControlAffine (NNSG2dBGSelect n, GXBGScrSizeAffine screenSize, GXBGAreaOver areaOver, GXBGScrBase screenBase, GXBGCharBase charBase)
{
    *GetBGnCNT(n) = (u16)(
        (*GetBGnCNT(n) & (0x0003 | 0x0040 ))
        | MakeBGnCNTValAffine(screenSize, areaOver, screenBase, charBase)
        );
}
extern const u8 data_02041a14[2][8];
extern void func_020128c0 (const u8 modeTable[]);
extern void func_02012904 (const u8 modeTable[]);

/* func_02012c2c -- NitroSystem g2d_Screen.c: SetBGnControlToAffine. */
void func_02012c2c (NNSG2dBGSelect n, GXBGScrSizeAffine size, GXBGAreaOver areaOver, GXBGScrBase scnBase, GXBGCharBase chrBase)
{
    if (IsMainBG(n)) {
        func_020128c0(data_02041a14[n - 2]);
    } else {
        func_02012904(data_02041a14[n - 6]);
    }
    SetBGnControlAffine(n, size, areaOver, scnBase, chrBase);
}
