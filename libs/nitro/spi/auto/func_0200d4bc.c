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

#define REG_POWCNT_OFFSET 0x304
#define REG_POWCNT_ADDR (HW_REG_BASE + REG_POWCNT_OFFSET)
#define HW_IOREG 0x04000000
#define HW_REG_BASE HW_IOREG        // alias
#define reg_GX_POWCNT (*( REGType16v *) REG_POWCNT_ADDR)
#define REG_GX_POWCNT_LCD_MASK 0x0001

typedef vu16 REGType16v;
typedef enum {
    PM_LCD_POWER_OFF = 0,
    PM_LCD_POWER_ON = 1
} PMLCDPower;

/* func_0200d4bc -- NitroSDK pm.c: PM_GetLCDPower. */
PMLCDPower func_0200d4bc (void)
{
    return (reg_GX_POWCNT & REG_GX_POWCNT_LCD_MASK) ? PM_LCD_POWER_ON : PM_LCD_POWER_OFF;
}
