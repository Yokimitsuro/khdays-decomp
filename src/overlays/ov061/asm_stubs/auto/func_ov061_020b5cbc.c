#pragma thumb on

asm void func_ov061_020b5cbc(int r0)
{
    ldr     r1, [pc, #0x20]
    ldrb    r0, [r0, r1]
    cmp     r0, #0x14
    beq     _L_12
    cmp     r0, #0x15
    beq     _L_16
    cmp     r0, #0x16
    beq     _L_1a
    b       _L_1e
_L_12:
    mov     r0, #0xa3
    bx      lr
_L_16:
    mov     r0, #0xa4
    bx      lr
_L_1a:
    mov     r0, #0xa5
    bx      lr
_L_1e:
    mov     r0, #0xa2
    bx      lr
    nop
    dcd     0x00000918
}
