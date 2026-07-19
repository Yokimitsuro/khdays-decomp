extern int OS_DisableInterrupts(void);
extern void OS_RestoreInterrupts(int state);
extern void OSi_RescheduleThread(void);

/* Marks a thread runnable and reschedules immediately, without going through the wait queue. */
void OS_WakeupThreadDirect(char *thread) {
    int enabled = OS_DisableInterrupts();
    *(int *)(thread + 0x64) = 1;
    OSi_RescheduleThread();
    OS_RestoreInterrupts(enabled);
}
