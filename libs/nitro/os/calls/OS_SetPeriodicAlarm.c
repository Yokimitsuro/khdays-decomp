/* NitroSDK OS: arms a periodic alarm (start, period, handler, arg) and inserts it into the alarm
 * queue. */

#include "nitro/types.h"
#include "nitro/os_types.h"

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
extern void OSi_InsertAlarm(OSAlarm *alarm, OSTick fire);

void OS_SetPeriodicAlarm(OSAlarm *alarm, s64 fire, s64 period, OSAlarmHandler handler, void *arg)
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
    OSi_InsertAlarm(alarm, 0);
    OS_RestoreInterrupts(irq);
}
