extern void func_0203c634(void);
extern void func_ov288_020d5218(void);

asm void func_ov288_020d5174(void)
{
    stmfd   sp!, {r3, r4, r5, lr}
    ldr     r3, [r0, #4]
    mov     lr, #0
    ldr     r5, [r3]
    ldr     r2, =func_ov288_020d5218
    ldrh    r4, [r5, #0x60]
    mov     r1, r4, lsl #0x10
    mov     r1, r1, lsr #0x18
    orr     r1, r1, #0x80
    bic     r4, r4, #0xff00
    mov     r1, r1, lsl #0x18
    orr     r1, r4, r1, lsr #16
    strh    r1, [r5, #0x60]
    ldr     r1, [r3]
    ldrh    r5, [r1, #0x60]
    mov     r4, r5, lsl #0x10
    mov     r4, r4, lsr #0x18
    bic     r4, r4, #1
    mov     ip, r4, lsl #0x10
    mov     r4, ip, lsr #0x10
    bic     r5, r5, #0xff00
    mov     r4, r4, lsl #0x18
    orr     r4, r5, r4, lsr #16
    strh    r4, [r1, #0x60]
    ldr     r1, [r3]
    ldr     r4, [r1, #0x388]
    ldr     ip, [r4, #8]
    mov     r1, ip, lsl #0x18
    mov     r1, r1, lsr #0x18
    bic     r1, r1, #1
    bic     ip, ip, #0xff
    and     r1, r1, #0xff
    orr     r1, ip, r1
    str     r1, [r4, #8]
    ldr     r1, [r3]
    str     lr, [r1, #0x394]
    str     lr, [r3, #0x34]
    ldrsb   r1, [r0, #0x20]
    bl      func_0203c634
    ldmfd   sp!, {r3, r4, r5, pc}
}
