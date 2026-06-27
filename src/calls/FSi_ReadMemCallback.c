extern void MI_CpuCopy8(void);

asm int FSi_ReadMemCallback(int *object)
{
    stmdb sp!, {r3, lr}
    ldr r0, [r0, #0x28]
    add r0, r0, r2
    mov r2, r3
    bl MI_CpuCopy8
    mov r0, #0
    ldmia sp!, {r3, pc}
}
