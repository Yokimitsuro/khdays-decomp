extern int OS_EnableInterrupts();
extern int OS_Halt();

void OSi_IdleThreadProc(void) {
    OS_EnableInterrupts();
    for (;;) {
        OS_Halt();
    }
}
