extern void func_0203bec0(void);
extern void func_ov107_020c5af8(void);
extern void func_ov107_020c9f48(void);
extern void func_0202f384(void);
extern void VEC_Subtract(void);
extern void func_01ff8d18(void);
extern void func_020050b4(void);
extern void VEC_DotProduct(void);
extern void func_01ffa724(void);
extern void func_0203c634(void);

asm void func_ov241_020d0a80(void *r0)
{
    stmfd   sp!, {r3, r4, r5, r6, r7, lr}
    sub     sp, sp, #0x18
    mov     r7, r0
    ldr     r4, [r7, #4]
    ldrb    r0, [r4, #0x40]
    cmp     r0, #0
    bne     _check1
    ldr     r0, [r4]
    mov     r1, #0
    ldr     r0, [r0, #0x384]
    bl      func_0203bec0
    cmp     r0, #0x16000
    blt     _afterChecks
    ldr     r0, [r4]
    ldr     r3, [r4, #0xc]
    ldr     r1, =0x13a
    mov     r2, #4
    bl      func_ov107_020c5af8
    mov     r0, #1
    strb    r0, [r4, #0x40]
    b       _afterChecks
_check1:
    cmp     r0, #1
    bne     _afterChecks
    ldr     r0, [r4]
    mov     r1, #0
    ldr     r0, [r0, #0x384]
    bl      func_0203bec0
    cmp     r0, #0x16000
    movlt   r0, #0
    strltb  r0, [r4, #0x40]
_afterChecks:
    ldr     r0, [r4]
    add     r1, sp, #0
    ldr     r0, [r0, #0x39c]
    bl      func_ov107_020c9f48
    mov     r1, #0x1800
    umull   r6, r5, r0, r1
    mov     r2, r0, asr #0x1f
    adds    r6, r6, #0x800
    mla     r5, r2, r1, r5
    ldr     r3, [r4]
    add     r0, sp, #0
    mov     r2, r0
    adc     r5, r5, #0
    mov     r6, r6, lsr #0xc
    add     r1, r3, #0xa0
    orr     r6, r6, r5, lsl #0x14
    bl      func_0202f384
    ldr     r0, [r4, #0x1c]
    ldr     r1, [r4, #0xc]
    add     r2, sp, #0xc
    bl      VEC_Subtract
    add     r0, sp, #0xc
    mov     r1, r0
    bl      func_01ff8d18
    mov     r5, r0
    cmp     r5, r6
    ldr     r0, [sp, #0xc]
    ldr     r1, [sp, #0x14]
    movlt   r6, r5, asr #1
    bl      func_020050b4
    str     r0, [r4, #8]
    add     r0, sp, #0xc
    add     r1, sp, #0
    bl      VEC_DotProduct
    cmp     r0, #0
    movlt   r0, #0
    smull   r1, r0, r6, r0
    adds    r1, r1, #0x800
    adc     r2, r0, #0
    mov     r0, r1, lsr #0xc
    orr     r0, r0, r2, lsl #0x14
    add     r1, sp, #0
    add     r2, r4, #0x10
    bl      func_01ffa724
    ldr     r1, [r7]
    mov     r0, #0x1e
    ldr     r1, [r1, #0x2c]
    ldr     r2, =0x66666667
    mul     r3, r1, r0
    mov     r0, r3, lsr #0x1f
    smull   r1, r3, r2, r3
    add     r3, r0, r3, asr #2
    str     r3, [r4, #0x28]
    ldr     r1, [r4]
    ldr     r0, [r1, #0x80]
    cmp     r5, r0
    addgt   sp, sp, #0x18
    ldmgtfd sp!, {r3, r4, r5, r6, r7, pc}
    mov     r0, #2
    strb    r0, [r1, #0x1c7]
    ldrsb   r1, [r7, #0x20]
    mov     r0, r7
    mov     r2, #0
    bl      func_0203c634
    add     sp, sp, #0x18
    ldmfd   sp!, {r3, r4, r5, r6, r7, pc}
}
