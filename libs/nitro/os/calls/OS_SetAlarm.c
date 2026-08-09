extern int OS_DisableInterrupts(void);
extern void OS_RestoreInterrupts(int state);
extern void OS_Terminate(void);
extern long long func_020031d4(void);
extern void func_02003410(void *alarm, long long fire);

/* Arms an alarm to fire `delay` ticks from now. Re-arming a live alarm is a fatal error. */
void OS_SetAlarm(char *alarm, long long delay, void *handler, void *arg) {
    int enabled;
    if (alarm == 0 || *(int *)alarm != 0) {
        OS_Terminate();
    }
    enabled = OS_DisableInterrupts();
    *(int *)(alarm + 0x1c) = 0;
    *(int *)(alarm + 0x20) = 0;
    *(void **)alarm = handler;
    *(void **)(alarm + 4) = arg;
    func_02003410(alarm, delay + func_020031d4());
    OS_RestoreInterrupts(enabled);
}
