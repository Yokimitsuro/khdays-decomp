typedef long long s64;
typedef unsigned long long u64;
typedef unsigned int u32;

typedef void (*OSAlarmHandler)(void *);

typedef struct OSAlarm {
    OSAlarmHandler handler;     /* 0x00 */
    void *arg;                  /* 0x04 */
    u32 pad_08[5];              /* 0x08..0x1c */
    s64 period;                 /* 0x1c..0x24 */
    s64 fire;                   /* 0x24..0x2c */
} OSAlarm;

extern u32 OS_DisableInterrupts(void);
extern void OS_RestoreInterrupts(u32);
extern void OS_Terminate(void);
extern void func_02003410(OSAlarm *, int, int);

void func_020035a8(OSAlarm *alarm, s64 fire, s64 period, OSAlarmHandler handler, void *arg)
{
    u32 irq;

    if (alarm == 0 || alarm->handler != 0) {
        OS_Terminate();
    }

    irq = OS_DisableInterrupts();
    alarm->period = period;
    alarm->fire = fire;
    alarm->handler = handler;
    alarm->arg = arg;
    func_02003410(alarm, 0, 0);
    OS_RestoreInterrupts(irq);
}
