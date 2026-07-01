extern void func_ov107_020c0b90(void);
extern void func_ov107_020c5af8(void);
extern void func_0203c634(void);
extern void func_ov288_020d44b8(void);

asm void func_ov288_020d43dc(void)
{
    stmfd   sp!, {r3, r4, r5, lr}
    sub     sp, sp, #8
    mov     r5, r0
    ldr     r4, [r5, #4]
    mov     r1, #0
    ldr     ip, [r4]
    sub     r3, sp, #8
    ldrh    r2, [ip, #0x60]
    mov     r0, r2, lsl #0x10
    mov     r0, r0, lsr #0x18
    orr     r0, r0, #0x80
    bic     r2, r2, #0xff00
    mov     r0, r0, lsl #0x18
    orr     r0, r2, r0, lsr #16
    strh    r0, [ip, #0x60]
    ldr     r0, [r4]
    add     r0, r0, #0x100
    ldrh    r2, [r0, #0xae]
    orr     r2, r2, #1
    strh    r2, [r0, #0xae]
    ldr     r0, [r4]
    ldr     ip, [r0, #0x388]
    ldr     r2, [ip, #8]
    mov     r0, r2, lsl #0x18
    mov     r0, r0, lsr #0x18
    bic     r0, r0, #1
    bic     r2, r2, #0xff
    and     r0, r0, #0xff
    orr     r0, r2, r0
    str     r0, [ip, #8]
    ldr     r0, [r4]
    str     r1, [r0, #0x394]
    str     r1, [sp, #4]
    ldr     r0, [r4, #0xc]
    ldmia   r0, {r0, r1, r2}
    stmia   r3, {r0, r1, r2}
    ldr     r0, [r4]
    mov     r1, #1
    ldmia   r3, {r2, r3}
    bl      func_ov107_020c0b90
    ldr     r0, [r4]
    ldr     r1, =0x15b
    add     r3, r0, #0x74
    mov     r2, #6
    bl      func_ov107_020c5af8
    mov     r0, #0
    str     r0, [r4, #0x34]
    ldrsb   r1, [r5, #0x20]
    ldr     r2, =func_ov288_020d44b8
    mov     r0, r5
    bl      func_0203c634
    add     sp, sp, #8
    ldmfd   sp!, {r3, r4, r5, pc}
}
