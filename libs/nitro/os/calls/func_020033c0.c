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

#define OSi_ALARM_TIMER OS_TIMER_1

extern OSIntrMode OS_DisableInterrupts(void);
extern OSIntrMode OS_RestoreInterrupts(OSIntrMode state);
typedef enum {
    OS_TIMER_0 = 0,
    OS_TIMER_1 = 1,
    OS_TIMER_2 = 2,
    OS_TIMER_3 = 3
} OSTimer;
extern u16 data_02044674;
void OSi_ClearAlarmBit(int timerNum);

/* func_020033c0 -- NitroSDK os_alarm.c: OS_EndAlarm. */
void func_020033c0 (void)
{
    OSIntrMode enabled;

    enabled = OS_DisableInterrupts();

    if (data_02044674) {

        OSi_ClearAlarmBit(OSi_ALARM_TIMER);

        data_02044674 = FALSE;
    }

    (void)OS_RestoreInterrupts(enabled);
}
