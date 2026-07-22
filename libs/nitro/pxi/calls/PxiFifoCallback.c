/* Runs the sound alarm handler with interrupts disabled. */
extern int OS_DisableInterrupts(void);
extern void SNDi_CallAlarmHandler(int data);
extern void OS_RestoreInterrupts(int state);

void PxiFifoCallback(int unused, int data) {
    int state = OS_DisableInterrupts();
    SNDi_CallAlarmHandler(data);
    OS_RestoreInterrupts(state);
}
