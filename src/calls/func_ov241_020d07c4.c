extern void func_0203c634(void);

asm void func_ov241_020d07c4(void *r0)
{
    stmfd   sp!, {r3, lr}
    ldr     ip, [r0, #4]
    ldr     r2, [ip]
    ldrh    r1, [r2, #0x60]
    mov     r1, r1, lsl #0x18
    mov     r1, r1, lsr #0x18
    tst     r1, #1
    ldmeqfd sp!, {r3, pc}
    ldr     r3, [r2, #0x3a4]
    ldr     r2, [ip, #0x24]
    mov     r1, #0x14
    mla     r1, r2, r1, r3
    str     r1, [ip, #0x1c]
    ldr     r3, [ip]
    mov     r2, #0
    add     r1, r3, #0x100
    ldrsb   r1, [r1, #0xc9]
    strb    r1, [r3, #0x1c7]
    ldrsb   r1, [r0, #0x20]
    bl      func_0203c634
    ldmfd   sp!, {r3, pc}
}
