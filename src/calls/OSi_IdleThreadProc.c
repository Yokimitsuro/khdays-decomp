extern void OS_EnableInterrupts(void);
extern void OS_Halt(void);

asm void OSi_IdleThreadProc(void)
{
    stmdb sp!, {r3, lr}
    bl OS_EnableInterrupts
    bl OS_Halt
    DCD 0xeafffffd
}
