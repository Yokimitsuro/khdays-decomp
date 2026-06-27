extern int func_0203c634(void *r0, int r1, int r2);

asm void func_ov285_020d21c8(void *r0)
{
    stmfd   sp!, {r3, lr}
    ldmia   r0, {r1, r3}
    ldr     r2, [r3, #0x28]
    ldr     r1, [r1, #0x2c]
    add     r1, r2, r1
    str     r1, [r3, #0x28]
    ldr     r2, [r3]
    ldrb    r1, [r2, #0x17a]
    mov     r1, r1, lsl #0x1f
    movs    r1, r1, lsr #0x1f
    ldmeqfd sp!, {r3, pc}
    ldr     r1, [r3, #0x28]
    cmp     r1, #0x400
    ldmltfd sp!, {r3, pc}
    mov     r1, #2
    strb    r1, [r2, #0x1c7]
    ldrsb   r1, [r0, #0x20]
    mov     r2, #0
    bl      func_0203c634
    ldmfd   sp!, {r3, pc}
}
