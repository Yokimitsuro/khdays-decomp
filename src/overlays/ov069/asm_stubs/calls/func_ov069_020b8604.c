extern void func_02021980(void);
extern void data_0204be18(void);

asm void func_ov069_020b8604(void)
{
    push    {r3, r4, r5, r6, r7, lr}
    sub     sp, #8
    str     r0, [sp, #0]
    str     r1, [sp, #4]
    bl      func_02021980
    add     r5, r0, #0
    cmp     r5, #0
    ble     _L_0020
    mov     r0, #1
    lsl     r0, r0, #0xa
    cmp     r5, r0
    blt     _L_0020
    add     sp, #8
    mov     r0, #1
    pop     {r3, r4, r5, r6, r7, pc}
_L_0020:
    ldr     r0, [pc, #0x6c]
    mov     r7, #0
    ldr     r3, [r0, #0]
    mov     r0, #0x81
    add     r1, r3, r5
    lsl     r0, r0, #4
    ldrb    r4, [r1, r0]
    mov     r0, #0xee
    lsl     r0, r0, #4
_L_0032:
    mov     r2, #0
    add     r6, r3, #0
_L_0036:
    ldrh    r1, [r6, r0]
    cmp     r5, r1
    bne     _L_0046
    cmp     r4, #0
    beq     _L_0046
    sub     r1, r4, #1
    lsl     r1, r1, #0x10
    lsr     r4, r1, #0x10
_L_0046:
    add     r2, r2, #1
    add     r6, r6, #2
    cmp     r2, #0x28
    blt     _L_0036
    add     r7, r7, #1
    add     r3, #0x50
    cmp     r7, #3
    blt     _L_0032
    ldr     r1, [sp, #4]
    ldr     r0, [sp, #0]
    add     r1, #8
    str     r1, [sp, #4]
    bl      func_02021980
    lsl     r0, r0, #0x10
    lsr     r2, r0, #0x10
    cmp     r4, r2
    bls     _L_007c
    ldr     r0, [pc, #0x24]
    ldr     r1, [r0, #0]
    mov     r0, #0x81
    lsl     r0, r0, #4
    add     r1, r1, r0
    ldrb    r0, [r1, r5]
    sub     r0, r0, r2
    strb    r0, [r1, r5]
    b       _L_008a
_L_007c:
    ldr     r0, [pc, #0x10]
    mov     r2, #0
    ldr     r0, [r0, #0]
    add     r1, r0, r5
    mov     r0, #0x81
    lsl     r0, r0, #4
    strb    r2, [r1, r0]
_L_008a:
    mov     r0, #1
    add     sp, #8
    pop     {r3, r4, r5, r6, r7, pc}
    dcd     data_0204be18
}
