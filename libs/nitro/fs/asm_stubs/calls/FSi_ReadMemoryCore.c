extern void MI_CpuCopy8(void);

asm int FSi_ReadMemoryCore(void)
{
    stmdb sp!, {r3, lr}
    mov r0, r2
    mov r2, r3
    bl MI_CpuCopy8
    mov r0, #0
    ldmia sp!, {r3, pc}
}
