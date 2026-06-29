asm void func_ov041_020b3510(void)
{
    ldr     r1, [pc, #0x18]
    ldrb    r0, [r0, r1]
    cmp     r0, #1
    beq     _L_000e
    cmp     r0, #2
    beq     _L_0012
    b       _L_0016
_L_000e:
    mov     r0, #0xb3
    bx      lr
_L_0012:
    mov     r0, #0xb4
    bx      lr
_L_0016:
    mov     r0, #0xb2
    bx      lr
    mov     r8, r8
    lsr     r0, r3, #4
    lsl     r0, r0, #0
}
