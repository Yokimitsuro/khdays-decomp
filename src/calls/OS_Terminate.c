extern int OS_DisableInterrupts();
extern int OS_Halt();

void OS_Terminate(void)
{
    for (;;) {
        OS_DisableInterrupts();
        OS_Halt();
    }
}
