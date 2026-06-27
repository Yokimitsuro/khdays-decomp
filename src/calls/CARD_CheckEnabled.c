extern int OS_IsThreadAvailable_0x0200e068(void);
extern void OS_Terminate(void);

asm void CARD_CheckEnabled(void)
{
    stmdb sp!, {r3, lr}
    bl OS_IsThreadAvailable_0x0200e068
    cmp r0, #0
    ldmneia sp!, {r3, pc}
    bl OS_Terminate
    ldmia sp!, {r3, pc}
}
