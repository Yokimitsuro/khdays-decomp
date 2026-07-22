/* Disables interrupts and halts forever; the loop re-disables on every pass. */
extern void OS_DisableInterrupts(void);
extern void OS_Halt(void);

void OS_Terminate(void) {
    for (;;) {
        OS_DisableInterrupts();
        OS_Halt();
    }
}
