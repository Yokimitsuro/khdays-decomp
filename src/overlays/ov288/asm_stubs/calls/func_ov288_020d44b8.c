extern void func_02023eb4(void);
extern void func_ov107_020c9264(void);
extern void func_0203c634(void);
extern void func_ov288_020d4558(void);

asm void func_ov288_020d44b8(void)
{
    stmfd   sp!, {r3, r4, r5, lr}
    mov     r5, r0
    ldmia   r5, {r0, r4}
    ldr     r1, [r4, #0x34]
    ldr     r0, [r0, #0x2c]
    add     r0, r1, r0
    str     r0, [r4, #0x34]
    cmp     r0, #0x2a8
    ldmltfd sp!, {r3, r4, r5, pc}
    ldr     r1, [r4]
    mov     r3, #1
    ldrh    ip, [r1, #0x60]
    mov     r0, #0x64
    mov     r2, ip, lsl #0x10
    mov     r2, r2, lsr #0x18
    bic     r2, r2, #0x80
    mov     r2, r2, lsl #0x10
    mov     r2, r2, lsr #0x10
    bic     ip, ip, #0xff00
    mov     r2, r2, lsl #0x18
    orr     r2, ip, r2, lsr #16
    strh    r2, [r1, #0x60]
    ldr     r1, [r4]
    str     r3, [r1, #0x394]
    bl      func_02023eb4
    cmp     r0, #0xa
    movlo   r2, #1
    ldr     r0, [r4]
    movhs   r2, #0
    str     r2, [r0, #0x38c]
    mov     r1, #0
    ldr     r0, [r4]
    mov     r2, r1
    bl      func_ov107_020c9264
    ldrsb   r1, [r5, #0x20]
    ldr     r2, =func_ov288_020d4558
    mov     r0, r5
    bl      func_0203c634
    ldmfd   sp!, {r3, r4, r5, pc}
}
