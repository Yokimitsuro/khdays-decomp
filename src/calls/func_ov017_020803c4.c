extern void func_ov002_02076a38(void);
extern void func_ov002_0207c4c0(void);
extern void func_ov002_0207c53c(void);
extern void func_0202b450(void);
extern void func_ov002_02076480(void);
extern void func_ov017_0207fe2c(void);

asm void func_ov017_020803c4(void)
{
    push    {r4, r5, r6, r7, lr}
    sub     sp, #0x3c
    add     r5, r0, #0
    str     r1, [sp, #0x18]
    add     r6, r2, #0
    add     r7, r3, #0
    bl      func_ov002_02076a38
    mov     r1, #0x8c
    ldrsb   r1, [r5, r1]
    add     r2, sp, #0x40
    add     r4, r0, #0
    str     r1, [sp, #0]
    mov     r1, #0x8e
    ldrsh   r1, [r5, r1]
    str     r1, [sp, #4]
    mov     r1, #0x90
    ldrsh   r1, [r5, r1]
    str     r1, [sp, #8]
    mov     r1, #0x92
    ldrsh   r1, [r5, r1]
    str     r1, [sp, #0xc]
    mov     r1, #0x24
    ldrsh   r1, [r2, r1]
    add     r2, sp, #0x1c
    str     r1, [sp, #0x10]
    mov     r1, #1
    str     r1, [sp, #0x14]
    add     r1, r4, #0
    ldr     r3, [sp, #0x18]
    add     r1, #0x2c
    bl      func_ov002_0207c4c0
    ldr     r1, [sp, #0x60]
    add     r0, sp, #0x30
    add     r2, sp, #0x1c
    bl      func_ov002_0207c53c
    add     r0, r4, #0
    ldr     r1, [sp, #0x60]
    add     r0, #0x38
    bl      func_0202b450
    add     r3, r4, #0
    add     r2, sp, #0x40
    mov     r0, #0x24
    ldrsh   r0, [r2, r0]
    add     r5, sp, #0x30
    add     r3, #0x1c
    strh    r0, [r4, #0x18]
    mov     r0, #2
    ldr     r1, [sp, #0x24]
    lsl     r0, r0, #0xc
    add     r0, r1, r0
    str     r0, [sp, #0x24]
    ldmia   r5!, {r0, r1}
    stmia   r3!, {r0, r1}
    ldr     r0, [r5, #0]
    str     r0, [r3, #0]
    ldr     r0, [sp, #0x24]
    str     r0, [r4, #0x28]
    ldr     r0, [pc, #0x5c]
    strb    r6, [r4, #0x10]
    str     r0, [r4, #0xc]
    ldrh    r1, [r4, #0x12]
    mov     r0, #0xc8
    orr     r0, r1
    strh    r0, [r4, #0x12]
    strh    r7, [r4, #0x14]
    ldrb    r0, [r2, #0x10]
    ldr     r1, [pc, #0x4c]
    strb    r0, [r4, #0x16]
    mov     r0, #0
    strb    r0, [r4, #0x17]
    strb    r0, [r4, r1]
    add     r3, r1, #1
    str     r0, [r4, r3]
    sub     r3, r1, #1
    strb    r0, [r4, r3]
    sub     r3, r1, #3
    strb    r0, [r4, r3]
    ldrh    r5, [r2, #0x1c]
    sub     r3, r1, #2
    strb    r5, [r4, r3]
    add     r3, r1, #0
    sub     r3, #0xf
    str     r0, [r4, r3]
    add     r3, r1, #0
    sub     r3, #0x13
    str     r0, [r4, r3]
    sub     r3, r1, #7
    str     r0, [r4, r3]
    add     r3, r1, #0
    sub     r3, #0xb
    str     r0, [r4, r3]
    ldrh    r3, [r2, #0x14]
    add     r0, r1, #5
    strh    r3, [r4, r0]
    add     r0, r1, #7
    ldrb    r2, [r2, #0x18]
    add     r1, r4, #0
    strb    r2, [r4, r0]
    add     r0, r6, #0
    bl      func_ov002_02076480
    add     r0, r4, #0
    add     sp, #0x3c
    pop     {r4, r5, r6, r7, pc}
    dcd     func_ov017_0207fe2c
    lsl     r3, r3, #0x13
    lsl     r0, r0, #0
}
