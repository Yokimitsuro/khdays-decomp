asm void func_ov069_020b815c(void)
{
    push    {r3, r4}
    ldrh    r2, [r0, #0]
    add     r0, r0, #2
    mov     r4, #0
    cmp     r2, #0
    bls     _L_002a
    lsl     r1, r1, #0x10
    lsr     r3, r1, #0x10
_L_0010:
    ldrh    r1, [r0, #2]
    cmp     r1, r3
    bne     _L_001c
    ldrh    r0, [r0, #4]
    pop     {r3, r4}
    bx      lr
_L_001c:
    ldrh    r1, [r0, #0]
    add     r0, r0, r1
    add     r1, r4, #1
    lsl     r1, r1, #0x10
    lsr     r4, r1, #0x10
    cmp     r4, r2
    blo     _L_0010
_L_002a:
    mov     r0, #0
    mvn     r0, r0
    pop     {r3, r4}
    bx      lr
}
