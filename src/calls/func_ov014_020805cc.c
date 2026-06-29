extern void func_ov002_02076480(void);
extern void func_ov002_02076a38(void);
extern void func_ov014_02080464(void);

asm void func_ov014_020805cc(void)
{
    push    {r3, r4, r5, r6, r7, lr}
    ldr     r5, [sp, #0x1c]
    add     r7, r0, #0
    add     r6, r2, #0
    str     r3, [sp, #0]
    bl      func_ov002_02076a38
    add     r4, r0, #0
    add     r3, r5, #0
    add     r2, r4, #0
    ldmia   r3!, {r0, r1}
    add     r2, #0xd0
    stmia   r2!, {r0, r1}
    ldr     r0, [r3, #0]
    add     r1, r4, #0
    str     r0, [r2, #0]
    ldr     r0, [sp, #0x20]
    add     r1, #0xa8
    lsl     r0, r0, #0x10
    lsr     r0, r0, #0x10
    strh    r0, [r1, #0]
    ldrh    r2, [r4, #0x2c]
    mov     r1, #0x20
    orr     r1, r2
    strh    r1, [r4, #0x2c]
    strh    r0, [r4, #0x18]
    add     r2, r4, #0
    ldmia   r5!, {r0, r1}
    add     r2, #0x1c
    stmia   r2!, {r0, r1}
    ldr     r0, [r5, #0]
    mov     r1, #0
    str     r0, [r2, #0]
    ldr     r0, [r7, #0x68]
    str     r0, [r4, #0x28]
    ldr     r0, [pc, #0x30]
    strb    r1, [r4, r0]
    sub     r0, r0, #1
    strb    r1, [r4, r0]
    ldr     r0, [pc, #0x2c]
    strb    r6, [r4, #0x10]
    str     r0, [r4, #0xc]
    ldrh    r1, [r4, #0x12]
    mov     r0, #8
    orr     r0, r1
    strh    r0, [r4, #0x12]
    ldr     r0, [sp, #0]
    add     r1, r4, #0
    strh    r0, [r4, #0x14]
    add     r0, sp, #8
    ldrb    r0, [r0, #0x10]
    strb    r0, [r4, #0x16]
    mov     r0, #3
    strb    r0, [r4, #0x17]
    add     r0, r6, #0
    bl      func_ov002_02076480
    add     r0, r4, #0
    pop     {r3, r4, r5, r6, r7, pc}
    mov     r8, r8
    dcd     0x00000135
    dcd     func_ov014_02080464
}
