typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed char s8;
typedef short s16;
typedef int s32;
typedef unsigned long long u64;
typedef int BOOL;
typedef int OSIntrMode;
typedef void *OSMessage;
typedef unsigned short vu16;
typedef unsigned int vu32;
typedef unsigned char vu8;

#define NULL ((void *)0)
#define TRUE 1
#define FALSE 0
#define HW_MAIN_MEM 0x02000000

/* NitroSDK gx_vramcnt.c: VRAM bank control (gx_vramcnt.h enums and the bank register values). */
typedef enum {
	GX_VRAM_A = 0x1,
	GX_VRAM_B = 0x2,
	GX_VRAM_C = 0x4,
	GX_VRAM_D = 0x8,
	GX_VRAM_E = 0x10,
	GX_VRAM_F = 0x20,
	GX_VRAM_G = 0x40,
	GX_VRAM_H = 0x80,
	GX_VRAM_I = 0x100,
	GX_VRAM_ALL = 0x1ff
} GXVRam;

typedef enum {
	GX_VRAM_LCDC_NONE = 0x0000,
	GX_VRAM_LCDC_A = GX_VRAM_A,
	GX_VRAM_LCDC_B = GX_VRAM_B,
	GX_VRAM_LCDC_C = GX_VRAM_C,
	GX_VRAM_LCDC_D = GX_VRAM_D,
	GX_VRAM_LCDC_E = GX_VRAM_E,
	GX_VRAM_LCDC_F = GX_VRAM_F,
	GX_VRAM_LCDC_G = GX_VRAM_G,
	GX_VRAM_LCDC_H = GX_VRAM_H,
	GX_VRAM_LCDC_I = GX_VRAM_I,

	GX_VRAM_LCDC_ALL = GX_VRAM_ALL
} GXVRamLCDC;


typedef enum {
	GX_VRAM_BG_NONE        = 0x0000,
	GX_VRAM_BG_16_F        = GX_VRAM_F,
	GX_VRAM_BG_16_G        = GX_VRAM_G,
	GX_VRAM_BG_32_FG       = GX_VRAM_F | GX_VRAM_G,
	GX_VRAM_BG_64_E        = GX_VRAM_E,
	GX_VRAM_BG_80_EF       = GX_VRAM_E | GX_VRAM_F,
	GX_VRAM_BG_96_EFG      = GX_VRAM_E | GX_VRAM_F | GX_VRAM_G,
	GX_VRAM_BG_128_A       = GX_VRAM_A,
	GX_VRAM_BG_128_B       = GX_VRAM_B,
	GX_VRAM_BG_128_C       = GX_VRAM_C,
	GX_VRAM_BG_128_D       = GX_VRAM_D,
	GX_VRAM_BG_256_AB      = GX_VRAM_A | GX_VRAM_B,
	GX_VRAM_BG_256_BC      = GX_VRAM_B | GX_VRAM_C,
	GX_VRAM_BG_256_CD      = GX_VRAM_C | GX_VRAM_D,
	GX_VRAM_BG_384_ABC     = GX_VRAM_A | GX_VRAM_B | GX_VRAM_C,
	GX_VRAM_BG_384_BCD     = GX_VRAM_B | GX_VRAM_C | GX_VRAM_D,
	GX_VRAM_BG_512_ABCD    = GX_VRAM_A | GX_VRAM_B | GX_VRAM_C | GX_VRAM_D,
	GX_VRAM_BG_80_EG       = GX_VRAM_E | GX_VRAM_G,
	GX_VRAM_BG_256_AC      = GX_VRAM_A | GX_VRAM_C,
	GX_VRAM_BG_256_AD      = GX_VRAM_A | GX_VRAM_D,
	GX_VRAM_BG_256_BD      = GX_VRAM_B | GX_VRAM_D,
	GX_VRAM_BG_384_ABD     = GX_VRAM_A | GX_VRAM_B | GX_VRAM_D,
	GX_VRAM_BG_384_ACD     = GX_VRAM_A | GX_VRAM_C | GX_VRAM_D
} GXVRamBG;




typedef enum {
	GX_VRAM_OBJ_NONE      = 0x0000,
	GX_VRAM_OBJ_16_F      = GX_VRAM_F,
	GX_VRAM_OBJ_16_G      = GX_VRAM_G,
	GX_VRAM_OBJ_32_FG     = GX_VRAM_F | GX_VRAM_G,
	GX_VRAM_OBJ_64_E      = GX_VRAM_E,
	GX_VRAM_OBJ_80_EF     = GX_VRAM_E | GX_VRAM_F,
	GX_VRAM_OBJ_80_EG     = GX_VRAM_E | GX_VRAM_G,
	GX_VRAM_OBJ_96_EFG    = GX_VRAM_E | GX_VRAM_F | GX_VRAM_G,
	GX_VRAM_OBJ_128_A     = GX_VRAM_A,
	GX_VRAM_OBJ_128_B     = GX_VRAM_B,
	GX_VRAM_OBJ_256_AB    = GX_VRAM_A | GX_VRAM_B
} GXVRamOBJ;


typedef enum {
	GX_VRAM_ARM7_NONE      = 0x0000,
	GX_VRAM_ARM7_128_C     = GX_VRAM_C,
	GX_VRAM_ARM7_128_D     = GX_VRAM_D,
	GX_VRAM_ARM7_256_CD    = GX_VRAM_C | GX_VRAM_D
} GXVRamARM7;


typedef enum {
	GX_VRAM_TEX_NONE         = 0x0000,
	GX_VRAM_TEX_0_A          = GX_VRAM_A,
	GX_VRAM_TEX_0_B          = GX_VRAM_B,
	GX_VRAM_TEX_0_C          = GX_VRAM_C,
	GX_VRAM_TEX_0_D          = GX_VRAM_D,
	GX_VRAM_TEX_01_AB        = GX_VRAM_A | GX_VRAM_B,
	GX_VRAM_TEX_01_BC        = GX_VRAM_B | GX_VRAM_C,
	GX_VRAM_TEX_01_CD        = GX_VRAM_C | GX_VRAM_D,
	GX_VRAM_TEX_012_ABC      = GX_VRAM_A | GX_VRAM_B | GX_VRAM_C,
	GX_VRAM_TEX_012_BCD      = GX_VRAM_B | GX_VRAM_C | GX_VRAM_D,
	GX_VRAM_TEX_0123_ABCD    = GX_VRAM_A | GX_VRAM_B | GX_VRAM_C | GX_VRAM_D,
	GX_VRAM_TEX_01_AC        = GX_VRAM_A | GX_VRAM_C,
	GX_VRAM_TEX_01_AD        = GX_VRAM_A | GX_VRAM_D,
	GX_VRAM_TEX_01_BD        = GX_VRAM_B | GX_VRAM_D,
	GX_VRAM_TEX_012_ABD      = GX_VRAM_A | GX_VRAM_B | GX_VRAM_D,
	GX_VRAM_TEX_012_ACD      = GX_VRAM_A | GX_VRAM_C | GX_VRAM_D
} GXVRamTex;


typedef enum {
	GX_VRAM_CLEARIMAGE_NONE      = 0x0000,
	GX_VRAM_CLEARIMAGE_256_AB    = GX_VRAM_A | GX_VRAM_B,
	GX_VRAM_CLEARIMAGE_256_CD    = GX_VRAM_C | GX_VRAM_D,
	GX_VRAM_CLEARDEPTH_128_A     = GX_VRAM_A,
	GX_VRAM_CLEARDEPTH_128_B     = GX_VRAM_B,
	GX_VRAM_CLEARDEPTH_128_C     = GX_VRAM_C,
	GX_VRAM_CLEARDEPTH_128_D     = GX_VRAM_D
} GXVRamClearImage;


typedef enum {
	GX_VRAM_TEXPLTT_NONE          = 0x0000,
	GX_VRAM_TEXPLTT_0_F           = GX_VRAM_F,
	GX_VRAM_TEXPLTT_0_G           = GX_VRAM_G,
	GX_VRAM_TEXPLTT_01_FG         = GX_VRAM_F | GX_VRAM_G,
	GX_VRAM_TEXPLTT_0123_E        = GX_VRAM_E,
	GX_VRAM_TEXPLTT_01234_EF      = GX_VRAM_E | GX_VRAM_F,
	GX_VRAM_TEXPLTT_012345_EFG    = GX_VRAM_E | GX_VRAM_F | GX_VRAM_G
} GXVRamTexPltt;


typedef enum {
	GX_VRAM_BGEXTPLTT_NONE       = 0x0000,
	GX_VRAM_BGEXTPLTT_01_F       = GX_VRAM_F,
	GX_VRAM_BGEXTPLTT_23_G       = GX_VRAM_G,
	GX_VRAM_BGEXTPLTT_0123_E     = GX_VRAM_E,
	GX_VRAM_BGEXTPLTT_0123_FG    = GX_VRAM_F | GX_VRAM_G
} GXVRamBGExtPltt;


#define GX_VRAM_OBJEXTPLTT_8_F    GX_VRAM_OBJEXTPLTT_0_F
#define GX_VRAM_OBJEXTPLTT_8_G    GX_VRAM_OBJEXTPLTT_0_G

typedef enum {
	GX_VRAM_OBJEXTPLTT_NONE    = 0,
	GX_VRAM_OBJEXTPLTT_0_F     = GX_VRAM_F,
	GX_VRAM_OBJEXTPLTT_0_G     = GX_VRAM_G
} GXVRamOBJExtPltt;


typedef enum {
	GX_VRAM_SUB_BG_NONE     = 0x0000,
	GX_VRAM_SUB_BG_128_C    = GX_VRAM_C,
	GX_VRAM_SUB_BG_32_H     = GX_VRAM_H,
	GX_VRAM_SUB_BG_48_HI    = GX_VRAM_H | GX_VRAM_I
} GXVRamSubBG;


typedef enum {
	GX_VRAM_SUB_OBJ_NONE     = 0x0000,
	GX_VRAM_SUB_OBJ_128_D    = GX_VRAM_D,
	GX_VRAM_SUB_OBJ_16_I     = GX_VRAM_I
} GXVRamSubOBJ;


#define GX_VRAM_SUB_BGEXTPLTT_32_H GX_VRAM_SUB_BGEXTPLTT_0123_H

typedef enum {
	GX_VRAM_SUB_BGEXTPLTT_NONE = 0x0000,
	GX_VRAM_SUB_BGEXTPLTT_0123_H = GX_VRAM_H
} GXVRamSubBGExtPltt;


#define GX_VRAM_SUB_OBJEXTPLTT_16_I GX_VRAM_SUB_OBJEXTPLTT_0_I

typedef enum {
	GX_VRAM_SUB_OBJEXTPLTT_NONE = 0x0000,
	GX_VRAM_SUB_OBJEXTPLTT_0_I = GX_VRAM_I
} GXVRamSubOBJExtPltt;

typedef enum {
	GX_VRAMCNT_A_DISABLE           = 0,
	GX_VRAMCNT_A_LCDC_0x06800000   = (0 << 0) | (0 << 3) | (1 << 7),
	GX_VRAMCNT_A_BG_0x06000000     = (1 << 0) | (0 << 3) | (1 << 7),
	GX_VRAMCNT_A_BG_0x06020000     = (1 << 0) | (1 << 3) | (1 << 7),
	GX_VRAMCNT_A_BG_0x06040000     = (1 << 0) | (2 << 3) | (1 << 7),
	GX_VRAMCNT_A_BG_0x06060000     = (1 << 0) | (3 << 3) | (1 << 7),
	GX_VRAMCNT_A_OBJ_0x06400000    = (2 << 0) | (0 << 3) | (1 << 7),
	GX_VRAMCNT_A_OBJ_0x06420000    = (2 << 0) | (1 << 3) | (1 << 7),
	GX_VRAMCNT_A_TEX_0             = (3 << 0) | (0 << 3) | (1 << 7),
	GX_VRAMCNT_A_TEX_1             = (3 << 0) | (1 << 3) | (1 << 7),
	GX_VRAMCNT_A_TEX_2             = (3 << 0) | (2 << 3) | (1 << 7),
	GX_VRAMCNT_A_TEX_3             = (3 << 0) | (3 << 3) | (1 << 7)
} GX_VRAMCNT_A;

typedef enum {
	GX_VRAMCNT_B_DISABLE           = 0,
	GX_VRAMCNT_B_LCDC_0x06820000   = (0 << 0) | (0 << 3) | (1 << 7),
	GX_VRAMCNT_B_BG_0x06000000     = (1 << 0) | (0 << 3) | (1 << 7),
	GX_VRAMCNT_B_BG_0x06020000     = (1 << 0) | (1 << 3) | (1 << 7),
	GX_VRAMCNT_B_BG_0x06040000     = (1 << 0) | (2 << 3) | (1 << 7),
	GX_VRAMCNT_B_BG_0x06060000     = (1 << 0) | (3 << 3) | (1 << 7),
	GX_VRAMCNT_B_OBJ_0x06400000    = (2 << 0) | (0 << 3) | (1 << 7),
	GX_VRAMCNT_B_OBJ_0x06420000    = (2 << 0) | (1 << 3) | (1 << 7),
	GX_VRAMCNT_B_TEX_0             = (3 << 0) | (0 << 3) | (1 << 7),
	GX_VRAMCNT_B_TEX_1             = (3 << 0) | (1 << 3) | (1 << 7),
	GX_VRAMCNT_B_TEX_2             = (3 << 0) | (2 << 3) | (1 << 7),
	GX_VRAMCNT_B_TEX_3             = (3 << 0) | (3 << 3) | (1 << 7)
} GX_VRAMCNT_B;

typedef enum {
	GX_VRAMCNT_C_DISABLE           = 0,
	GX_VRAMCNT_C_LCDC_0x06840000   = (0 << 0) | (0 << 3) | (1 << 7),
	GX_VRAMCNT_C_BG_0x06000000     = (1 << 0) | (0 << 3) | (1 << 7),
	GX_VRAMCNT_C_BG_0x06020000     = (1 << 0) | (1 << 3) | (1 << 7),
	GX_VRAMCNT_C_BG_0x06040000     = (1 << 0) | (2 << 3) | (1 << 7),
	GX_VRAMCNT_C_BG_0x06060000     = (1 << 0) | (3 << 3) | (1 << 7),
	GX_VRAMCNT_C_ARM7_0x06000000   = (2 << 0) | (0 << 3) | (1 << 7),
	GX_VRAMCNT_C_ARM7_0x06020000   = (2 << 0) | (1 << 3) | (1 << 7),
	GX_VRAMCNT_C_TEX_0             = (3 << 0) | (0 << 3) | (1 << 7),
	GX_VRAMCNT_C_TEX_1             = (3 << 0) | (1 << 3) | (1 << 7),
	GX_VRAMCNT_C_TEX_2             = (3 << 0) | (2 << 3) | (1 << 7),
	GX_VRAMCNT_C_TEX_3             = (3 << 0) | (3 << 3) | (1 << 7),
	GX_VRAMCNT_C_SUBBG_0x06200000  = (4 << 0) | (1 << 7)
} GX_VRAMCNT_C;

typedef enum {
	GX_VRAMCNT_D_DISABLE           = 0,
	GX_VRAMCNT_D_LCDC_0x06860000   = (0 << 0) | (0 << 3) | (1 << 7),
	GX_VRAMCNT_D_BG_0x06000000     = (1 << 0) | (0 << 3) | (1 << 7),
	GX_VRAMCNT_D_BG_0x06020000     = (1 << 0) | (1 << 3) | (1 << 7),
	GX_VRAMCNT_D_BG_0x06040000     = (1 << 0) | (2 << 3) | (1 << 7),
	GX_VRAMCNT_D_BG_0x06060000     = (1 << 0) | (3 << 3) | (1 << 7),
	GX_VRAMCNT_D_ARM7_0x06000000   = (2 << 0) | (0 << 3) | (1 << 7),
	GX_VRAMCNT_D_ARM7_0x06020000   = (2 << 0) | (1 << 3) | (1 << 7),
	GX_VRAMCNT_D_TEX_0             = (3 << 0) | (0 << 3) | (1 << 7),
	GX_VRAMCNT_D_TEX_1             = (3 << 0) | (1 << 3) | (1 << 7),
	GX_VRAMCNT_D_TEX_2             = (3 << 0) | (2 << 3) | (1 << 7),
	GX_VRAMCNT_D_TEX_3             = (3 << 0) | (3 << 3) | (1 << 7),
	GX_VRAMCNT_D_SUBOBJ_0x06600000 = (4 << 0) | (1 << 7)
} GX_VRAMCNT_D;

typedef enum {
	GX_VRAMCNT_E_DISABLE           = 0,
	GX_VRAMCNT_E_LCDC_0x06880000   = (0 << 0) | (1 << 7),
	GX_VRAMCNT_E_BG_0x06000000     = (1 << 0) | (1 << 7),
	GX_VRAMCNT_E_OBJ_0x06400000    = (2 << 0) | (1 << 7),
	GX_VRAMCNT_E_TEXPLTT_0123      = (3 << 0) | (1 << 7),
	GX_VRAMCNT_E_BGEXTPLTT_0123    = (4 << 0) | (1 << 7)
}
GX_VRAMCNT_E;

typedef enum {
	GX_VRAMCNT_F_DISABLE           = 0,
	GX_VRAMCNT_F_LCDC_0x06890000   = (0 << 0) | (0 << 3) | (1 << 7),
	GX_VRAMCNT_F_BG_0x06000000     = (1 << 0) | (0 << 3) | (1 << 7),
	GX_VRAMCNT_F_BG_0x06004000     = (1 << 0) | (1 << 3) | (1 << 7),
	GX_VRAMCNT_F_BG_0x06010000     = (1 << 0) | (2 << 3) | (1 << 7),
	GX_VRAMCNT_F_BG_0x06014000     = (1 << 0) | (3 << 3) | (1 << 7),
	GX_VRAMCNT_F_OBJ_0x06400000    = (2 << 0) | (0 << 3) | (1 << 7),
	GX_VRAMCNT_F_OBJ_0x06404000    = (2 << 0) | (1 << 3) | (1 << 7),
	GX_VRAMCNT_F_OBJ_0x06410000    = (2 << 0) | (2 << 3) | (1 << 7),
	GX_VRAMCNT_F_OBJ_0x06414000    = (2 << 0) | (3 << 3) | (1 << 7),
	GX_VRAMCNT_F_TEXPLTT_0         = (3 << 0) | (0 << 3) | (1 << 7),
	GX_VRAMCNT_F_TEXPLTT_1         = (3 << 0) | (1 << 3) | (1 << 7),
	GX_VRAMCNT_F_TEXPLTT_4         = (3 << 0) | (2 << 3) | (1 << 7),
	GX_VRAMCNT_F_TEXPLTT_5         = (3 << 0) | (3 << 3) | (1 << 7),
	GX_VRAMCNT_F_BGEXTPLTT_01      = (4 << 0) | (0 << 3) | (1 << 7),
	GX_VRAMCNT_F_BGEXTPLTT_23      = (4 << 0) | (1 << 3) | (1 << 7),
	GX_VRAMCNT_F_OBJEXTPLTT        = (5 << 0) | (0 << 3) | (1 << 7)
} GX_VRAMCNT_F;

typedef enum {
	GX_VRAMCNT_G_DISABLE           = 0,
	GX_VRAMCNT_G_LCDC_0x06894000   = (0 << 0) | (0 << 3) | (1 << 7),
	GX_VRAMCNT_G_BG_0x06000000     = (1 << 0) | (0 << 3) | (1 << 7),
	GX_VRAMCNT_G_BG_0x06004000     = (1 << 0) | (1 << 3) | (1 << 7),
	GX_VRAMCNT_G_BG_0x06010000     = (1 << 0) | (2 << 3) | (1 << 7),
	GX_VRAMCNT_G_BG_0x06014000     = (1 << 0) | (3 << 3) | (1 << 7),
	GX_VRAMCNT_G_OBJ_0x06400000    = (2 << 0) | (0 << 3) | (1 << 7),
	GX_VRAMCNT_G_OBJ_0x06404000    = (2 << 0) | (1 << 3) | (1 << 7),
	GX_VRAMCNT_G_OBJ_0x06410000    = (2 << 0) | (2 << 3) | (1 << 7),
	GX_VRAMCNT_G_OBJ_0x06414000    = (2 << 0) | (3 << 3) | (1 << 7),
	GX_VRAMCNT_G_TEXPLTT_0         = (3 << 0) | (0 << 3) | (1 << 7),
	GX_VRAMCNT_G_TEXPLTT_1         = (3 << 0) | (1 << 3) | (1 << 7),
	GX_VRAMCNT_G_TEXPLTT_4         = (3 << 0) | (2 << 3) | (1 << 7),
	GX_VRAMCNT_G_TEXPLTT_5         = (3 << 0) | (3 << 3) | (1 << 7),
	GX_VRAMCNT_G_BGEXTPLTT_01      = (4 << 0) | (0 << 3) | (1 << 7),
	GX_VRAMCNT_G_BGEXTPLTT_23      = (4 << 0) | (1 << 3) | (1 << 7),
	GX_VRAMCNT_G_OBJEXTPLTT        = (5 << 0) | (0 << 3) | (1 << 7)
} GX_VRAMCNT_G;

typedef enum {
	GX_VRAMCNT_H_DISABLE           = 0,
	GX_VRAMCNT_H_LCDC_0x06898000   = (0 << 0) | (1 << 7),
	GX_VRAMCNT_H_SUBBG_0x06200000  = (1 << 0) | (1 << 7),
	GX_VRAMCNT_H_SUBBGEXTPLTT_0123 = (2 << 0) | (1 << 7)
} GX_VRAMCNT_H;

typedef enum {
	GX_VRAMCNT_I_DISABLE           = 0,
	GX_VRAMCNT_I_LCDC_0x068A0000   = (0 << 0) | (1 << 7),
	GX_VRAMCNT_I_SUBBG_0x06208000  = (1 << 0) | (1 << 7),
	GX_VRAMCNT_I_SUBOBJ_0x06600000 = (2 << 0) | (1 << 7),
	GX_VRAMCNT_I_SUBOBJEXTPLTT     = (3 << 0) | (1 << 7)
} GX_VRAMCNT_I;

#ifdef SDK_CW_WARNOFF_SAFESTRB
    #include <nitro/code32.h>
#endif

typedef volatile u8 REGType8v;
typedef volatile u16 REGType16v;
typedef volatile u32 REGType32v;
#define reg_GX_DISPCNT      (*(REGType32v *)0x04000000)
#define reg_G3X_DISP3DCNT   (*(REGType16v *)0x04000060)
#define reg_GXS_DB_DISPCNT  (*(REGType32v *)0x04001000)
#define reg_GX_VRAMCNT_A    (*(REGType8v *)0x04000240)
#define reg_GX_VRAMCNT_B    (*(REGType8v *)0x04000241)
#define reg_GX_VRAMCNT_C    (*(REGType8v *)0x04000242)
#define reg_GX_VRAMCNT_D    (*(REGType8v *)0x04000243)
#define reg_GX_VRAMCNT_E    (*(REGType8v *)0x04000244)
#define reg_GX_VRAMCNT_F    (*(REGType8v *)0x04000245)
#define reg_GX_VRAMCNT_G    (*(REGType8v *)0x04000246)
#define reg_GX_VRAMCNT_H    (*(REGType8v *)0x04000248)
#define reg_GX_VRAMCNT_I    (*(REGType8v *)0x04000249)
#define REG_GX_DISPCNT_BG_MASK        0x40000000
#define REG_GX_DISPCNT_O_MASK         0x80000000
#define REG_GXS_DB_DISPCNT_BG_MASK    0x40000000
#define REG_GXS_DB_DISPCNT_O_MASK     0x80000000
#define REG_G3X_DISP3DCNT_TME_MASK    0x0001
#define REG_G3X_DISP3DCNT_RO_MASK     0x1000
#define REG_G3X_DISP3DCNT_GO_MASK     0x2000
#define REG_G3X_DISP3DCNT_PRI_MASK    0x4000
#define GX_StateCheck_VRAMCnt() ((void)0)

typedef struct {
    u16 lcdc;
    u16 bg;
    u16 obj;
    u16 arm7;
    u16 tex;
    u16 texPltt;
    u16 clrImg;
    u16 bgExtPltt;
    u16 objExtPltt;
    u16 sub_bg;
    u16 sub_obj;
    u16 sub_bgExtPltt;
    u16 sub_objExtPltt;
} GX_VRAMCnt_;

typedef struct {
    GX_VRAMCnt_ vramCnt;
} GX_State;

extern GX_State data_020446d4;   /* gGXState */
#define gGXState data_020446d4
extern void GX_VRAMCNT_SetLCDC_(int lcdc);

static inline void GX_VRAMCNT_SetBG_ (GXVRamBG bg)
{
	switch (bg) {
	case GX_VRAM_BG_128_D:
		reg_GX_VRAMCNT_D = (u8)GX_VRAMCNT_D_BG_0x06000000;
		break;
	case GX_VRAM_BG_256_CD:
		reg_GX_VRAMCNT_D = (u8)GX_VRAMCNT_D_BG_0x06020000;
	case GX_VRAM_BG_128_C:
		reg_GX_VRAMCNT_C = (u8)GX_VRAMCNT_C_BG_0x06000000;
		break;
	case GX_VRAM_BG_384_BCD:
		reg_GX_VRAMCNT_D = (u8)GX_VRAMCNT_D_BG_0x06040000;
	case GX_VRAM_BG_256_BC:
		reg_GX_VRAMCNT_C = (u8)GX_VRAMCNT_C_BG_0x06020000;
	case GX_VRAM_BG_128_B:
		reg_GX_VRAMCNT_B = (u8)GX_VRAMCNT_B_BG_0x06000000;
		break;
	case GX_VRAM_BG_512_ABCD:
		reg_GX_VRAMCNT_D = (u8)GX_VRAMCNT_D_BG_0x06060000;
	case GX_VRAM_BG_384_ABC:
		reg_GX_VRAMCNT_C = (u8)GX_VRAMCNT_C_BG_0x06040000;
	case GX_VRAM_BG_256_AB:
		reg_GX_VRAMCNT_B = (u8)GX_VRAMCNT_B_BG_0x06020000;
	case GX_VRAM_BG_128_A:
		reg_GX_VRAMCNT_A = (u8)GX_VRAMCNT_A_BG_0x06000000;
	case GX_VRAM_BG_NONE:
		break;
	case GX_VRAM_BG_384_ABD:
		reg_GX_VRAMCNT_A = (u8)GX_VRAMCNT_A_BG_0x06000000;
		reg_GX_VRAMCNT_B = (u8)GX_VRAMCNT_B_BG_0x06020000;
		reg_GX_VRAMCNT_D = (u8)GX_VRAMCNT_D_BG_0x06040000;
		break;
	case GX_VRAM_BG_384_ACD:
		reg_GX_VRAMCNT_D = (u8)GX_VRAMCNT_D_BG_0x06040000;
	case GX_VRAM_BG_256_AC:
		reg_GX_VRAMCNT_A = (u8)GX_VRAMCNT_A_BG_0x06000000;
		reg_GX_VRAMCNT_C = (u8)GX_VRAMCNT_C_BG_0x06020000;
		break;
	case GX_VRAM_BG_256_AD:
		reg_GX_VRAMCNT_A = (u8)GX_VRAMCNT_A_BG_0x06000000;
		reg_GX_VRAMCNT_D = (u8)GX_VRAMCNT_D_BG_0x06020000;
		break;
	case GX_VRAM_BG_256_BD:
		reg_GX_VRAMCNT_B = (u8)GX_VRAMCNT_B_BG_0x06000000;
		reg_GX_VRAMCNT_D = (u8)GX_VRAMCNT_D_BG_0x06020000;
		break;
	case GX_VRAM_BG_96_EFG:
		reg_GX_VRAMCNT_G = (u8)GX_VRAMCNT_G_BG_0x06014000;
	case GX_VRAM_BG_80_EF:
		reg_GX_VRAMCNT_F = (u8)GX_VRAMCNT_F_BG_0x06010000;
	case GX_VRAM_BG_64_E:
		reg_GX_VRAMCNT_E = (u8)GX_VRAMCNT_E_BG_0x06000000;
		break;
	case GX_VRAM_BG_80_EG:
		reg_GX_VRAMCNT_G = (u8)GX_VRAMCNT_G_BG_0x06010000;
		reg_GX_VRAMCNT_E = (u8)GX_VRAMCNT_E_BG_0x06000000;
		break;
	case GX_VRAM_BG_32_FG:
		reg_GX_VRAMCNT_G = (u8)GX_VRAMCNT_G_BG_0x06004000;
	case GX_VRAM_BG_16_F:
		reg_GX_VRAMCNT_F = (u8)GX_VRAMCNT_F_BG_0x06000000;
		break;
	case GX_VRAM_BG_16_G:
		reg_GX_VRAMCNT_G = (u8)GX_VRAMCNT_G_BG_0x06000000;
		break;
	default:
		break;
	}
}

static inline void GX_VRAMCNT_SetBGEx1_ (GXVRamBG bg)
{
	switch (bg) {
	case GX_VRAM_BG_96_EFG:
		reg_GX_VRAMCNT_G = (u8)GX_VRAMCNT_G_BG_0x06014000;
	case GX_VRAM_BG_80_EF:
		reg_GX_VRAMCNT_F = (u8)GX_VRAMCNT_F_BG_0x06010000;
	case GX_VRAM_BG_64_E:
		reg_GX_VRAMCNT_E = (u8)GX_VRAMCNT_E_BG_0x06000000;
		break;
	case GX_VRAM_BG_80_EG:
		reg_GX_VRAMCNT_G = (u8)GX_VRAMCNT_G_BG_0x06010000;
		reg_GX_VRAMCNT_E = (u8)GX_VRAMCNT_E_BG_0x06000000;
		break;
	case GX_VRAM_BG_32_FG:
		reg_GX_VRAMCNT_G = (u8)GX_VRAMCNT_G_BG_0x06004000;
	case GX_VRAM_BG_16_F:
		reg_GX_VRAMCNT_F = (u8)GX_VRAMCNT_F_BG_0x06000000;
		break;
	case GX_VRAM_BG_16_G:
		reg_GX_VRAMCNT_G = (u8)GX_VRAMCNT_G_BG_0x06000000;
		break;
	default:
		break;
	}
}

static inline void GX_VRAMCNT_SetBGEx2_ (GXVRamBG bg)
{
	switch (bg) {
	case GX_VRAM_BG_128_D:
		reg_GX_VRAMCNT_D = (u8)GX_VRAMCNT_D_BG_0x06020000;
		break;
	case GX_VRAM_BG_256_CD:
		reg_GX_VRAMCNT_D = (u8)GX_VRAMCNT_D_BG_0x06040000;
	case GX_VRAM_BG_128_C:
		reg_GX_VRAMCNT_C = (u8)GX_VRAMCNT_C_BG_0x06020000;
		break;
	case GX_VRAM_BG_384_BCD:
		reg_GX_VRAMCNT_D = (u8)GX_VRAMCNT_D_BG_0x06060000;
	case GX_VRAM_BG_256_BC:
		reg_GX_VRAMCNT_C = (u8)GX_VRAMCNT_C_BG_0x06040000;
	case GX_VRAM_BG_128_B:
		reg_GX_VRAMCNT_B = (u8)GX_VRAMCNT_B_BG_0x06020000;
		break;
	case GX_VRAM_BG_384_ABC:
		reg_GX_VRAMCNT_C = (u8)GX_VRAMCNT_C_BG_0x06060000;
	case GX_VRAM_BG_256_AB:
		reg_GX_VRAMCNT_B = (u8)GX_VRAMCNT_B_BG_0x06040000;
	case GX_VRAM_BG_128_A:
		reg_GX_VRAMCNT_A = (u8)GX_VRAMCNT_A_BG_0x06020000;
	case GX_VRAM_BG_NONE:
		break;
	case GX_VRAM_BG_384_ABD:
		reg_GX_VRAMCNT_A = (u8)GX_VRAMCNT_A_BG_0x06020000;
		reg_GX_VRAMCNT_B = (u8)GX_VRAMCNT_B_BG_0x06040000;
		reg_GX_VRAMCNT_D = (u8)GX_VRAMCNT_D_BG_0x06060000;
		break;
	case GX_VRAM_BG_384_ACD:
		reg_GX_VRAMCNT_D = (u8)GX_VRAMCNT_D_BG_0x06060000;
	case GX_VRAM_BG_256_AC:
		reg_GX_VRAMCNT_A = (u8)GX_VRAMCNT_A_BG_0x06020000;
		reg_GX_VRAMCNT_C = (u8)GX_VRAMCNT_C_BG_0x06040000;
		break;
	case GX_VRAM_BG_256_AD:
		reg_GX_VRAMCNT_A = (u8)GX_VRAMCNT_A_BG_0x06020000;
		reg_GX_VRAMCNT_D = (u8)GX_VRAMCNT_D_BG_0x06040000;
		break;
	case GX_VRAM_BG_256_BD:
		reg_GX_VRAMCNT_B = (u8)GX_VRAMCNT_B_BG_0x06020000;
		reg_GX_VRAMCNT_D = (u8)GX_VRAMCNT_D_BG_0x06040000;
		break;
	default:
		break;
	}
}

static inline void GX_VRAMCNT_SetOBJ_ (GXVRamOBJ obj)
{
	switch (obj) {
	case GX_VRAM_OBJ_256_AB:
		reg_GX_VRAMCNT_B = (u8)GX_VRAMCNT_B_OBJ_0x06420000;
	case GX_VRAM_OBJ_128_A:
		reg_GX_VRAMCNT_A = (u8)GX_VRAMCNT_A_OBJ_0x06400000;
	case GX_VRAM_OBJ_NONE:
		break;
	case GX_VRAM_OBJ_128_B:
		reg_GX_VRAMCNT_B = (u8)GX_VRAMCNT_B_OBJ_0x06400000;
		break;
	case GX_VRAM_OBJ_96_EFG:
		reg_GX_VRAMCNT_G = (u8)GX_VRAMCNT_G_OBJ_0x06414000;
	case GX_VRAM_OBJ_80_EF:
		reg_GX_VRAMCNT_F = (u8)GX_VRAMCNT_F_OBJ_0x06410000;
	case GX_VRAM_OBJ_64_E:
		reg_GX_VRAMCNT_E = (u8)GX_VRAMCNT_E_OBJ_0x06400000;
		break;
	case GX_VRAM_OBJ_80_EG:
		reg_GX_VRAMCNT_G = (u8)GX_VRAMCNT_G_OBJ_0x06410000;
		reg_GX_VRAMCNT_E = (u8)GX_VRAMCNT_E_OBJ_0x06400000;
		break;
	case GX_VRAM_OBJ_32_FG:
		reg_GX_VRAMCNT_G = (u8)GX_VRAMCNT_G_OBJ_0x06404000;
	case GX_VRAM_OBJ_16_F:
		reg_GX_VRAMCNT_F = (u8)GX_VRAMCNT_F_OBJ_0x06400000;
		break;
	case GX_VRAM_OBJ_16_G:
		reg_GX_VRAMCNT_G = (u8)GX_VRAMCNT_G_OBJ_0x06400000;
		break;
	default:
		break;
	}
}

static inline void GX_VRAMCNT_SetARM7_ (GXVRamARM7 arm7)
{
	switch (arm7) {
	case GX_VRAM_ARM7_256_CD:
		reg_GX_VRAMCNT_D = (u8)GX_VRAMCNT_D_ARM7_0x06020000;
		reg_GX_VRAMCNT_C = (u8)GX_VRAMCNT_C_ARM7_0x06000000;
		break;
	case GX_VRAM_ARM7_128_C:
		reg_GX_VRAMCNT_C = (u8)GX_VRAMCNT_C_ARM7_0x06000000;
		break;
	case GX_VRAM_ARM7_128_D:
		reg_GX_VRAMCNT_D = (u8)GX_VRAMCNT_D_ARM7_0x06000000;
	case GX_VRAM_ARM7_NONE:
		break;
	default:
		break;
	}
}

static inline void texOn_ (void)
{
	reg_G3X_DISP3DCNT = (u16)((reg_G3X_DISP3DCNT &
	                           ~(REG_G3X_DISP3DCNT_RO_MASK | REG_G3X_DISP3DCNT_GO_MASK)) |
	                          REG_G3X_DISP3DCNT_TME_MASK);
}

static inline void texOff_ (void)
{
	reg_G3X_DISP3DCNT &= (u16) ~(REG_G3X_DISP3DCNT_TME_MASK |
	                             REG_G3X_DISP3DCNT_RO_MASK | REG_G3X_DISP3DCNT_GO_MASK);
}

static inline void GX_VRAMCNT_SetTEX_ (GXVRamTex tex)
{
	if (tex == GX_VRAM_TEX_NONE) {
		texOff_();
		return;
	}

	texOn_();

	switch (tex) {
	case GX_VRAM_TEX_01_AC:
		reg_GX_VRAMCNT_A = (u8)GX_VRAMCNT_A_TEX_0;
		reg_GX_VRAMCNT_C = (u8)GX_VRAMCNT_C_TEX_1;
		break;
	case GX_VRAM_TEX_01_AD:
		reg_GX_VRAMCNT_A = (u8)GX_VRAMCNT_A_TEX_0;
		reg_GX_VRAMCNT_D = (u8)GX_VRAMCNT_D_TEX_1;
		break;
	case GX_VRAM_TEX_01_BD:
		reg_GX_VRAMCNT_B = (u8)GX_VRAMCNT_B_TEX_0;
		reg_GX_VRAMCNT_D = (u8)GX_VRAMCNT_D_TEX_1;
		break;
	case GX_VRAM_TEX_012_ABD:
		reg_GX_VRAMCNT_A = (u8)GX_VRAMCNT_A_TEX_0;
		reg_GX_VRAMCNT_B = (u8)GX_VRAMCNT_B_TEX_1;
		reg_GX_VRAMCNT_D = (u8)GX_VRAMCNT_D_TEX_2;
		break;
	case GX_VRAM_TEX_012_ACD:
		reg_GX_VRAMCNT_A = (u8)GX_VRAMCNT_A_TEX_0;
		reg_GX_VRAMCNT_C = (u8)GX_VRAMCNT_C_TEX_1;
		reg_GX_VRAMCNT_D = (u8)GX_VRAMCNT_D_TEX_2;
		break;
	case GX_VRAM_TEX_0_D:
		reg_GX_VRAMCNT_D = (u8)GX_VRAMCNT_D_TEX_0;
		break;
	case GX_VRAM_TEX_01_CD:
		reg_GX_VRAMCNT_D = (u8)GX_VRAMCNT_D_TEX_1;
	case GX_VRAM_TEX_0_C:
		reg_GX_VRAMCNT_C = (u8)GX_VRAMCNT_C_TEX_0;
		break;
	case GX_VRAM_TEX_012_BCD:
		reg_GX_VRAMCNT_D = (u8)GX_VRAMCNT_D_TEX_2;
	case GX_VRAM_TEX_01_BC:
		reg_GX_VRAMCNT_C = (u8)GX_VRAMCNT_C_TEX_1;
	case GX_VRAM_TEX_0_B:
		reg_GX_VRAMCNT_B = (u8)GX_VRAMCNT_B_TEX_0;
		break;
	case GX_VRAM_TEX_0123_ABCD:
		reg_GX_VRAMCNT_D = (u8)GX_VRAMCNT_D_TEX_3;
	case GX_VRAM_TEX_012_ABC:
		reg_GX_VRAMCNT_C = (u8)GX_VRAMCNT_C_TEX_2;
	case GX_VRAM_TEX_01_AB:
		reg_GX_VRAMCNT_B = (u8)GX_VRAMCNT_B_TEX_1;
	case GX_VRAM_TEX_0_A:
		reg_GX_VRAMCNT_A = (u8)GX_VRAMCNT_A_TEX_0;
		break;
	default:
		break;
	}
}

static inline void clearImageOn_ (void)
{
	reg_G3X_DISP3DCNT |= REG_G3X_DISP3DCNT_PRI_MASK;
}

static inline void clearImageOff_ (void)
{
	reg_G3X_DISP3DCNT &= ~REG_G3X_DISP3DCNT_PRI_MASK;
}

static inline void GX_VRAMCNT_SetCLRIMG_ (GXVRamClearImage clrImg)
{
	switch (clrImg) {
	case GX_VRAM_CLEARIMAGE_256_AB:
		reg_GX_VRAMCNT_A = (u8)GX_VRAMCNT_A_TEX_2;
	case GX_VRAM_CLEARDEPTH_128_B:
		reg_GX_VRAMCNT_B = (u8)GX_VRAMCNT_B_TEX_3;
		clearImageOn_();
		break;
	case GX_VRAM_CLEARIMAGE_256_CD:
		reg_GX_VRAMCNT_C = (u8)GX_VRAMCNT_C_TEX_2;
	case GX_VRAM_CLEARDEPTH_128_D:
		reg_GX_VRAMCNT_D = (u8)GX_VRAMCNT_D_TEX_3;
		clearImageOn_();
		break;
	case GX_VRAM_CLEARIMAGE_NONE:
		clearImageOff_();
		break;
	case GX_VRAM_CLEARDEPTH_128_A:
		reg_GX_VRAMCNT_A = (u8)GX_VRAMCNT_A_TEX_3;
		clearImageOn_();
		break;
	case GX_VRAM_CLEARDEPTH_128_C:
		reg_GX_VRAMCNT_C = (u8)GX_VRAMCNT_C_TEX_3;
		clearImageOn_();
		break;
	default:
		break;
	}
}

static inline void GX_VRAMCNT_SetTEXPLTT_ (GXVRamTexPltt texPltt)
{
	switch (texPltt) {
	case GX_VRAM_TEXPLTT_01_FG:
		reg_GX_VRAMCNT_G = (u8)GX_VRAMCNT_G_TEXPLTT_1;
	case GX_VRAM_TEXPLTT_0_F:
		reg_GX_VRAMCNT_F = (u8)GX_VRAMCNT_F_TEXPLTT_0;
		break;
	case GX_VRAM_TEXPLTT_0_G:
		reg_GX_VRAMCNT_G = (u8)GX_VRAMCNT_G_TEXPLTT_0;
		break;
	case GX_VRAM_TEXPLTT_012345_EFG:
		reg_GX_VRAMCNT_G = (u8)GX_VRAMCNT_G_TEXPLTT_5;
	case GX_VRAM_TEXPLTT_01234_EF:
		reg_GX_VRAMCNT_F = (u8)GX_VRAMCNT_F_TEXPLTT_4;
	case GX_VRAM_TEXPLTT_0123_E:
		reg_GX_VRAMCNT_E = (u8)GX_VRAMCNT_E_TEXPLTT_0123;
		break;
	case GX_VRAM_TEXPLTT_NONE:
		break;
	default:
		break;
	}
}

static inline void bgExtPlttOn_ (void)
{
	reg_GX_DISPCNT |= REG_GX_DISPCNT_BG_MASK;
}

static inline void bgExtPlttOff_ (void)
{
	reg_GX_DISPCNT &= ~REG_GX_DISPCNT_BG_MASK;
}

static inline void GX_VRAMCNT_SetBGEXTPLTT_ (GXVRamBGExtPltt bgExtPltt)
{
	switch (bgExtPltt) {
	case GX_VRAM_BGEXTPLTT_0123_E:
		bgExtPlttOn_();
		reg_GX_VRAMCNT_E = (u8)GX_VRAMCNT_E_BGEXTPLTT_0123;
		break;
	case GX_VRAM_BGEXTPLTT_23_G:
		bgExtPlttOn_();
		reg_GX_VRAMCNT_G = (u8)GX_VRAMCNT_G_BGEXTPLTT_23;
		break;
	case GX_VRAM_BGEXTPLTT_0123_FG:
		reg_GX_VRAMCNT_G = (u8)GX_VRAMCNT_G_BGEXTPLTT_23;
	case GX_VRAM_BGEXTPLTT_01_F:
		reg_GX_VRAMCNT_F = (u8)GX_VRAMCNT_F_BGEXTPLTT_01;
		bgExtPlttOn_();
		break;
	case GX_VRAM_BGEXTPLTT_NONE:
		bgExtPlttOff_();
		break;
	default:
		break;
	}
}

static inline void objExtPlttOn_ (void)
{
	reg_GX_DISPCNT |= REG_GX_DISPCNT_O_MASK;
}

static inline void objExtPlttOff_ (void)
{
	reg_GX_DISPCNT &= ~REG_GX_DISPCNT_O_MASK;
}

static inline void GX_VRAMCNT_SetOBJEXTPLTT_ (GXVRamOBJExtPltt objExtPltt)
{
	switch (objExtPltt) {
	case GX_VRAM_OBJEXTPLTT_0_F:
		objExtPlttOn_();
		reg_GX_VRAMCNT_F = (u8)GX_VRAMCNT_F_OBJEXTPLTT;
		break;
	case GX_VRAM_OBJEXTPLTT_0_G:
		objExtPlttOn_();
		reg_GX_VRAMCNT_G = (u8)GX_VRAMCNT_G_OBJEXTPLTT;
		break;
	case GX_VRAM_OBJEXTPLTT_NONE:
		objExtPlttOff_();
		break;
	default:
		break;
	}
}

static inline void GX_VRAMCNT_SetSubBG_ (GXVRamSubBG bg)
{
	switch (bg) {
	case GX_VRAM_SUB_BG_128_C:
		reg_GX_VRAMCNT_C = GX_VRAMCNT_C_SUBBG_0x06200000;
		break;
	case GX_VRAM_SUB_BG_48_HI:
		reg_GX_VRAMCNT_I = GX_VRAMCNT_I_SUBBG_0x06208000;
	case GX_VRAM_SUB_BG_32_H:
		reg_GX_VRAMCNT_H = GX_VRAMCNT_H_SUBBG_0x06200000;
		break;
	case GX_VRAM_SUB_BG_NONE:
		break;
	default:
		break;
	}
}

static inline void GX_VRAMCNT_SetSubOBJ_ (GXVRamSubOBJ obj)
{
	switch (obj) {
	case GX_VRAM_SUB_OBJ_128_D:
		reg_GX_VRAMCNT_D = GX_VRAMCNT_D_SUBOBJ_0x06600000;
		break;
	case GX_VRAM_SUB_OBJ_16_I:
		reg_GX_VRAMCNT_I = GX_VRAMCNT_I_SUBOBJ_0x06600000;
		break;
	case GX_VRAM_SUB_OBJ_NONE:
		break;
	default:
		break;
	}
}

static inline void subBGExtPlttOn_ (void)
{
	reg_GXS_DB_DISPCNT |= REG_GXS_DB_DISPCNT_BG_MASK;
}

static inline void subBGExtPlttOff_ (void)
{
	reg_GXS_DB_DISPCNT &= ~REG_GXS_DB_DISPCNT_BG_MASK;
}

static inline void GX_VRAMCNT_SetSubBGExtPltt_ (GXVRamSubBGExtPltt bgExtPltt)
{
	switch (bgExtPltt) {
	case GX_VRAM_SUB_BGEXTPLTT_0123_H:
		subBGExtPlttOn_();
		reg_GX_VRAMCNT_H = GX_VRAMCNT_H_SUBBGEXTPLTT_0123;
		break;
	case GX_VRAM_SUB_BGEXTPLTT_NONE:
		subBGExtPlttOff_();
		break;
	default:
		break;
	}
}

static inline void subOBJExtPlttOn_ (void)
{
	reg_GXS_DB_DISPCNT |= REG_GXS_DB_DISPCNT_O_MASK;
}

static inline void subOBJExtPlttOff_ (void)
{
	reg_GXS_DB_DISPCNT &= ~REG_GXS_DB_DISPCNT_O_MASK;
}

static inline void GX_VRAMCNT_SetSubOBJExtPltt_ (GXVRamSubOBJExtPltt objExtPltt)
{
	switch (objExtPltt) {
	case GX_VRAM_SUB_OBJEXTPLTT_0_I:
		subOBJExtPlttOn_();
		reg_GX_VRAMCNT_I = GX_VRAMCNT_I_SUBOBJEXTPLTT;
		break;
	case GX_VRAM_SUB_OBJEXTPLTT_NONE:
		subOBJExtPlttOff_();
		break;
	}
}


/* GX_SetBankForBGExtPltt -- NitroSDK gx_vramcnt.c: map the banks to this use, the rest back to LCDC. */
static inline void GxSetBankForBGExtPltt (GXVRamBGExtPltt bgExtPltt)
{

	gGXState.vramCnt.lcdc = (u16)(~bgExtPltt & (gGXState.vramCnt.lcdc | gGXState.vramCnt.bgExtPltt));
	gGXState.vramCnt.bgExtPltt = bgExtPltt;

	GX_StateCheck_VRAMCnt();

	GX_VRAMCNT_SetBGEXTPLTT_(bgExtPltt);
	GX_VRAMCNT_SetLCDC_(gGXState.vramCnt.lcdc);
}

void GX_SetBankForBGExtPltt (GXVRamBGExtPltt bgExtPltt)
{
	GxSetBankForBGExtPltt(bgExtPltt);
}
