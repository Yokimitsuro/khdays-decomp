extern void MIi_CpuClearFast(unsigned int data, void *destp, unsigned int size);

asm void func_02013e10(void *arg, unsigned int value)
{
    stmdb sp!, {r3, lr}
    mov r3, r0
    ldrb r2, [r3, #0xc]
    ldr ip, [r3, #4]
    cmp r2, #4
    orreq r0, r1, r1, lsl #4
    orreq r0, r0, r0, lsl #8
    orrne r0, r1, r1, lsl #8
    orr r1, r0, r0, lsl #16
    ldr r0, [r3, #8]
    mov r2, r2, lsl #6
    mul lr, ip, r0
    mov r0, r2, asr #2
    add r0, r2, r0, lsr #29
    mov r2, r0, asr #3
    mov r0, r1
    mul r2, lr, r2
    ldr r1, [r3]
    bl MIi_CpuClearFast
    ldmia sp!, {r3, pc}
}
