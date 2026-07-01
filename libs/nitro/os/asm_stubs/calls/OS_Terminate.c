extern void OS_DisableInterrupts(void);
extern void OS_Halt(void);

asm void OS_Terminate(void)
{
    stmdb sp!, {r3, lr}
    bl OS_DisableInterrupts
    bl OS_Halt
    DCD 0xeafffffc
}
