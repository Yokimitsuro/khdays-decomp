extern void data_0204be18(void);

asm void func_ov069_020b8378(void)
{
    push    {r4, r5, r6, r7}
    mov     r1, #1
    lsl     r1, r1, #0xa
    cmp     r0, r1
    blo     _L_0010
    mov     r0, #0
    pop     {r4, r5, r6, r7}
    bx      lr
_L_0010:
    ldr     r1, [pc, #0x44]
    mov     r6, #0xee
    ldr     r3, [r1, #0]
    mov     r1, #0x81
    add     r2, r3, r0
    lsl     r1, r1, #4
    ldrb    r7, [r2, r1]
    mov     r1, #0
    lsl     r6, r6, #4
_L_0022:
    mov     r2, #0
    add     r4, r3, #0
_L_0026:
    ldrh    r5, [r4, r6]
    cmp     r0, r5
    bne     _L_0036
    cmp     r7, #0
    beq     _L_0036
    sub     r5, r7, #1
    lsl     r5, r5, #0x10
    lsr     r7, r5, #0x10
_L_0036:
    add     r2, r2, #1
    add     r4, r4, #2
    cmp     r2, #0x28
    blt     _L_0026
    add     r1, r1, #1
    add     r3, #0x50
    cmp     r1, #3
    blt     _L_0022
    cmp     r7, #0
    beq     _L_0050
    mov     r0, #1
    pop     {r4, r5, r6, r7}
    bx      lr
_L_0050:
    mov     r0, #0
    pop     {r4, r5, r6, r7}
    bx      lr
    mov     r8, r8
    dcd     data_0204be18
}
