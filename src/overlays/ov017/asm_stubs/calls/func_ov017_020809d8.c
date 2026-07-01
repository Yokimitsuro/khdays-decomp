extern void func_ov002_02076a38(void);
extern void func_02030788(void);
extern void func_ov002_02076480(void);
extern void func_ov017_02080720(void);

asm void func_ov017_020809d8(void)
{
    push    {r4, r5, r6, lr}
    add     r6, r2, #0
    add     r5, r3, #0
    bl      func_ov002_02076a38
    add     r4, r0, #0
    add     r3, r4, #0
    add     r2, sp, #0
    mov     r0, #0x10
    ldrsh   r0, [r2, r0]
    add     r3, #0x1c
    strh    r0, [r4, #0x18]
    ldmia   r5!, {r0, r1}
    stmia   r3!, {r0, r1}
    ldr     r0, [r5, #0]
    str     r0, [r3, #0]
    mov     r0, #4
    str     r0, [r4, #0x28]
    mov     r0, #0x24
    ldrsh   r1, [r2, r0]
    ldr     r0, [pc, #0x54]
    mov     r2, #0
    strh    r1, [r4, r0]
    sub     r1, r0, #6
    str     r2, [r4, r1]
    sub     r1, r2, #1
    add     r0, r0, #3
    strb    r1, [r4, r0]
    bl      func_02030788
    cmp     r0, #0
    bne     _L_0044
    mov     r0, #0
    b       _L_0046
_L_0044:
    mov     r0, #1
_L_0046:
    mov     r1, #0x6d
    lsl     r1, r1, #2
    strb    r0, [r4, r1]
    add     r2, sp, #0
    ldrh    r3, [r2, #0x1c]
    add     r0, r1, #6
    add     r1, #8
    strh    r3, [r4, r0]
    add     r0, sp, #0x20
    ldrb    r0, [r0, #0]
    strb    r0, [r4, r1]
    ldr     r0, [pc, #0x24]
    strb    r6, [r4, #0x10]
    str     r0, [r4, #0xc]
    ldrh    r1, [r4, #0x12]
    mov     r0, #8
    orr     r0, r1
    strh    r0, [r4, #0x12]
    ldrh    r0, [r2, #0x14]
    add     r1, r4, #0
    strh    r0, [r4, #0x14]
    ldrb    r0, [r2, #0x18]
    strb    r0, [r4, #0x16]
    mov     r0, #1
    strb    r0, [r4, #0x17]
    add     r0, r6, #0
    bl      func_ov002_02076480
    pop     {r4, r5, r6, pc}
    lsl     r6, r6, #6
    lsl     r0, r0, #0
    dcd     func_ov017_02080720
}
