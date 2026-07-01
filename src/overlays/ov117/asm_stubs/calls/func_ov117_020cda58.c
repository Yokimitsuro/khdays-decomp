extern void func_0203c634(void);
extern void func_ov117_020cd594(void);

asm void func_ov117_020cda58(void *r0)
{
    stmfd   sp!, {r4, lr}
    mov     ip, r0
    ldr     r3, [ip, #4]
    mov     lr, #0x1e
    add     r0, r3, #0x64
    add     r4, r3, #0x2c
    ldmia   r0, {r0, r1, r2}
    stmia   r4, {r0, r1, r2}
    ldr     r1, [ip]
    mov     r0, #0x800
    ldr     r1, [r1, #0x2c]
    ldr     r4, [r3, #0x68]
    mul     r2, r1, lr
    mov     r1, r2, asr #0x1f
    mov     r1, r1, lsl #7
    adds    lr, r0, r2, lsl #7
    orr     r1, r1, r2, lsr #25
    adc     r0, r1, #0
    mov     r1, lr, lsr #0xc
    orr     r1, r1, r0, lsl #20
    subs    r0, r4, r1
    str     r0, [r3, #0x68]
    mov     r0, #0
    ldmplfd sp!, {r4, pc}
    ldr     r1, [r3]
    ldrb    r1, [r1, #0x17a]
    mov     r1, r1, lsl #0x1f
    movs    r1, r1, lsr #0x1f
    ldmeqfd sp!, {r4, pc}
    str     r0, [r3, #0x38]
    ldrsb   r1, [ip, #0x20]
    ldr     r2, =func_ov117_020cd594
    mov     r0, ip
    bl      func_0203c634
    ldmfd   sp!, {r4, pc}
}
