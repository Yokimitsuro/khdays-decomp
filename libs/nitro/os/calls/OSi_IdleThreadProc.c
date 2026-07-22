/* Idle thread: enable interrupts once, then halt forever. */
extern void OS_EnableInterrupts(void);
extern void OS_Halt(void);

void OSi_IdleThreadProc(void) {
    OS_EnableInterrupts();
    for (;;) {
        OS_Halt();
    }
}
