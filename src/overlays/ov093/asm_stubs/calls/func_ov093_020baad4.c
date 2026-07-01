asm void func_ov093_020baad4(void)
{
    ldr     r1, [pc, #0x20]
    ldrb    r0, [r0, r1]
    cmp     r0, #0x14
    beq     _L_0012
    cmp     r0, #0x15
    beq     _L_0016
    cmp     r0, #0x16
    beq     _L_001a
    b       _L_001e
_L_0012:
    mov     r0, #0x81
    bx      lr
_L_0016:
    mov     r0, #0x82
    bx      lr
_L_001a:
    mov     r0, #0x83
    bx      lr
_L_001e:
    mov     r0, #0x80
    bx      lr
    mov     r8, r8
    lsr     r0, r3, #4
    lsl     r0, r0, #0
}
