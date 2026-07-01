extern int func_0203c634(void *r0, int r1, int r2);

asm void func_ov292_020d438c(void *r0)
{
    stmfd   sp!, {r3, lr}
    ldr     r3, [r0, #4]
    ldr     r1, [r3]
    ldrh    r1, [r1, #0x60]
    mov     r1, r1, lsl #0x18
    mov     r1, r1, lsr #0x18
    tst     r1, #1
    ldmeqfd sp!, {r3, pc}
    mov     r2, #0
    str     r2, [r3, #0x2c]
    str     r2, [r3, #0x34]
    mov     r1, #0x1000
    str     r1, [r3, #0x30]
    ldr     r3, [r3]
    add     r1, r3, #0x100
    ldrsb   r1, [r1, #0xc9]
    strb    r1, [r3, #0x1c7]
    ldrsb   r1, [r0, #0x20]
    bl      func_0203c634
    ldmfd   sp!, {r3, pc}
}
