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



typedef int OSTimer;
#define OS_TIMER_0 0
#define OS_TIMER_PRESCALER_64 (1UL << 0)
#define REG_OS_TM0CNT_H_E_MASK 0x0080
#define REG_OS_TM0CNT_H_I_MASK 0x0040
#define OSi_TICK_TIMERCONTROL  (REG_OS_TM0CNT_H_E_MASK | REG_OS_TM0CNT_H_I_MASK | OS_TIMER_PRESCALER_64)
#define OSi_TICK_TIMER         OS_TIMER_0
#define REG_TM0CNT_L_ADDR      0x04000100
#define REG_TM0CNT_H_ADDR      0x04000102

static inline void OS_SetTimerCount(OSTimer id, u16 count)
{
    *((vu16 *)((u32)REG_TM0CNT_L_ADDR + id * 4)) = count;
}

static inline void OS_SetTimerControl(OSTimer id, u16 control)
{
    *((vu16 *)((u32)REG_TM0CNT_H_ADDR + id * 4)) = control;
}

/* os_tick.c statics, one .bss block: OSi_UseTick (u16), OSi_NeedResetTimer, OSi_TickCounter. */
extern struct { u16 useTick; u16 pad; BOOL needResetTimer; volatile u64 tickCounter; } data_02044664;
#define OSi_NeedResetTimer data_02044664.needResetTimer
#define OSi_TickCounter data_02044664.tickCounter
extern void OSi_EnterTimerCallback(int timerNo, void (*callback)(void *), void *arg);

/* func_0200316c -- NitroSDK os_tick.c: OSi_CountUpTick, the timer 0 overflow handler:
 * bump the 64-bit tick counter, restart the timer when a reset was requested, and
 * re-arm itself as the timer callback. */
void func_0200316c(void)
{
    OSi_TickCounter++;

    if (OSi_NeedResetTimer) {
        OS_SetTimerControl(OSi_TICK_TIMER, 0);
        OS_SetTimerCount((OSTimer)OSi_TICK_TIMER, (u16)0);
        OS_SetTimerControl(OSi_TICK_TIMER, (u16)OSi_TICK_TIMERCONTROL);

        OSi_NeedResetTimer = FALSE;
    }

    OSi_EnterTimerCallback(OSi_TICK_TIMER, (void (*)(void *))func_0200316c, 0);
}
