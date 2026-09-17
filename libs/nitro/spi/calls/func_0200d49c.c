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



typedef enum {
    PM_LED_NONE = 0,
    PM_LED_ON = 1,
    PM_LED_BLINK_LOW = 2,
    PM_LED_BLINK_HIGH = 3
} PMLEDStatus;
typedef enum {
    PM_LCD_POWER_OFF = 0,
    PM_LCD_POWER_ON = 1
} PMLCDPower;
BOOL func_0200d3a4(PMLCDPower sw, PMLEDStatus led, BOOL skip, BOOL isSync);
extern BOOL func_0200d3a4 (PMLCDPower sw, PMLEDStatus led, BOOL skip, BOOL isSync);

/* func_0200d49c -- NitroSDK pm.c: PM_SetLCDPower. */
BOOL func_0200d49c (PMLCDPower sw)
{
    if (sw != PM_LCD_POWER_ON) {
        sw = PM_LCD_POWER_OFF;
    }

    return func_0200d3a4(sw, PM_LED_NONE, FALSE, TRUE);
}
