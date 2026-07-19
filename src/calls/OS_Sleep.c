extern int OS_DisableInterrupts(void);
extern void OS_RestoreInterrupts(int state);
extern void OS_CreateAlarm(void *alarm);
extern void OS_SetAlarm(void *alarm, long long delay, void *handler, void *arg);
extern void func_02001f10(void *queue);
extern void OSi_SleepAlarmCallback(void);
extern char data_0204430c;

/* Blocks the calling thread for `ms` milliseconds using a one-shot alarm. 0x82ea/64 is the
 * ticks-per-millisecond constant of the system timer. */
void OS_Sleep(unsigned int ms) {
    char alarm[0x2c];
    char *volatile self;
    int enabled;
    OS_CreateAlarm(alarm);
    self = *(char **)*(char **)((char *)&data_0204430c + 8);
    enabled = OS_DisableInterrupts();
    *(void **)(self + 0xb0) = alarm;
    OS_SetAlarm(alarm, (unsigned long long)ms * 0x82ea >> 6,
                (void *)&OSi_SleepAlarmCallback, (void *)&self);
    while (self != 0) {
        func_02001f10(0);
    }
    OS_RestoreInterrupts(enabled);
}
