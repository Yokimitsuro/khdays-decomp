typedef unsigned int u32;
typedef unsigned long long u64;

typedef struct OSAlarm OSAlarm;
typedef u64 OSTick;
typedef void (*OSAlarmHandler)(void *arg);

extern void OS_CreateAlarm(OSAlarm *alarm);
extern void OS_SetAlarm(OSAlarm *alarm, OSTick fire_tick, OSAlarmHandler handler, void *arg);
extern int OS_DisableInterrupts(void);
extern void OS_RestoreInterrupts(int mask);
extern void func_02001f10(void *arg);
extern void OSi_SleepAlarmCallback(void *arg);
extern void **data_0204430c[];

void OS_Sleep(u32 arg0) {
    char alarm[0x2c];
    void *thread;
    int mask;

    OS_CreateAlarm((OSAlarm *)alarm);
    thread = data_0204430c[2][0];
    mask = OS_DisableInterrupts();
    *(void **)((char *)thread + 0xb0) = alarm;
    OS_SetAlarm((OSAlarm *)alarm, (u64)arg0 * 0x82eaULL >> 6, OSi_SleepAlarmCallback, &thread);
    while (thread != 0) {
        func_02001f10(0);
    }
    OS_RestoreInterrupts(mask);
}
