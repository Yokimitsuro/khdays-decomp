extern void func_0202b87c(void);
extern void func_ov002_02076480(void);
extern void func_ov002_02076a38(void);
extern void func_ov021_020809e0(void);

asm void func_ov021_02080bd0(void)
{
    push    {r3, r4, r5, r6, lr}
    sub     sp, #4
    add     r6, r2, #0
    add     r5, r3, #0
    bl      func_ov002_02076a38
    add     r4, r0, #0
    mov     r1, #0
    mov     r0, #0x49
    lsl     r0, r0, #2
    add     r0, r4, r0
    add     r2, r4, #0
    add     r3, r1, #0
    str     r1, [sp, #0]
    bl      func_0202b87c
    mov     r2, #0xaa
    lsl     r2, r2, #2
    ldmia   r5!, {r0, r1}
    add     r3, r4, r2
    stmia   r3!, {r0, r1}
    ldr     r0, [r5, #0]
    add     r1, sp, #8
    str     r0, [r3, #0]
    mov     r0, #0x10
    ldrsh   r0, [r1, r0]
    mov     r3, #0
    strh    r0, [r4, #0x18]
    add     r0, r2, #0
    add     r0, #0xc
    strb    r3, [r4, r0]
    add     r0, r2, #0
    sub     r3, r3, #1
    add     r0, #0x14
    strb    r3, [r4, r0]
    mov     r0, #0x4b
    lsl     r0, r0, #0xe
    add     r2, #0x10
    str     r0, [r4, r2]
    ldr     r0, [pc, #0x1c]
    strb    r6, [r4, #0x10]
    str     r0, [r4, #0xc]
    ldrh    r0, [r1, #0x14]
    strh    r0, [r4, #0x14]
    ldrb    r0, [r1, #0x18]
    add     r1, r4, #0
    strb    r0, [r4, #0x16]
    mov     r0, #0xff
    strb    r0, [r4, #0x17]
    add     r0, r6, #0
    bl      func_ov002_02076480
    add     sp, #4
    pop     {r3, r4, r5, r6, pc}
    dcd     func_ov021_020809e0
}
