extern void func_0203c634(void);

asm void func_ov234_020ccef4(void *r0)
{
    stmfd   sp!, {r3, lr}
    mov     r3, r0
    ldr     lr, [r3, #4]
    ldr     r1, [lr]
    ldrh    r0, [r1, #0x60]
    mov     r0, r0, lsl #0x18
    mov     r0, r0, lsr #0x18
    tst     r0, #1
    ldmeqfd sp!, {r3, pc}
    add     r0, r1, #0xb0
    add     ip, lr, #0x1c
    ldmia   r0, {r0, r1, r2}
    stmia   ip, {r0, r1, r2}
    ldr     ip, [lr]
    mov     r0, r3
    add     r1, ip, #0x100
    ldrsb   r1, [r1, #0xc9]
    mov     r2, #0
    strb    r1, [ip, #0x1c7]
    ldrsb   r1, [r3, #0x20]
    bl      func_0203c634
    ldmfd   sp!, {r3, pc}
}
