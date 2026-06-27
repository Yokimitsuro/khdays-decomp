extern void WaitByLoop(int);
extern void OS_WaitIrq(int, int);

asm void OS_WaitVBlankIntr(void)
{
    stmdb sp!, {r3, lr}
    mov r0, #1
    blx WaitByLoop
    mov r0, #1
    mov r1, r0
    bl OS_WaitIrq
    ldmia sp!, {r3, pc}
}
