extern void func_ov107_020c9264(void);
extern void func_ov107_020c5af8(void);
extern void func_0203c634(void);
extern void func_ov288_020d4c98(void);

asm void func_ov288_020d4bcc(void)
{
    stmfd   sp!, {r3, r4, r5, lr}
    mov     r5, r0
    ldr     r4, [r5, #4]
    mov     r1, #3
    ldr     r0, [r4]
    mov     r2, #0
    bl      func_ov107_020c9264
    ldr     r0, [r4]
    add     r0, r0, #0x100
    ldrh    r1, [r0, #0xae]
    orr     r1, r1, #0x10
    strh    r1, [r0, #0xae]
    ldr     r0, [r4]
    ldr     r2, [r0, #0x388]
    ldr     r1, [r2, #8]
    mov     r0, r1, lsl #0x18
    mov     r0, r0, lsr #0x18
    bic     r0, r0, #1
    bic     r1, r1, #0xff
    and     r0, r0, #0xff
    orr     r0, r1, r0
    str     r0, [r2, #8]
    ldr     r0, [r4]
    add     r0, r0, #0x100
    ldrh    r1, [r0, #0xae]
    orr     r1, r1, #1
    strh    r1, [r0, #0xae]
    ldr     r0, [r4]
    ldr     r3, [r4, #0xc]
    ldr     r1, [r0, #0x38c]
    cmp     r1, #0
    moveq   r1, #4
    movne   r1, #5
    mov     r2, r1, lsl #0x10
    ldr     r1, =0x15b
    mov     r2, r2, lsr #0x10
    bl      func_ov107_020c5af8
    ldr     r0, [r4]
    mov     r1, #0
    str     r1, [r0, #0x394]
    str     r1, [r4, #0x34]
    str     r1, [r4, #0x4c]
    str     r1, [r4, #0x50]
    strb    r1, [r4, #0x54]
    ldrsb   r1, [r5, #0x20]
    ldr     r2, =func_ov288_020d4c98
    mov     r0, r5
    bl      func_0203c634
    ldmfd   sp!, {r3, r4, r5, pc}
}
