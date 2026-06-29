asm void func_ov072_020b8534(void)
{
    ldr     r1, [pc, #0x20]
    ldrb    r0, [r0, r1]
    cmp     r0, #0x13
    beq     _L_0012
    cmp     r0, #0x14
    beq     _L_0016
    cmp     r0, #0x15
    beq     _L_001a
    b       _L_001e
_L_0012:
    mov     r0, #0x75
    bx      lr
_L_0016:
    mov     r0, #0x76
    bx      lr
_L_001a:
    mov     r0, #0x77
    bx      lr
_L_001e:
    mov     r0, #0x74
    bx      lr
    mov     r8, r8
    lsr     r0, r3, #4
    lsl     r0, r0, #0
}
