asm void func_ov063_020b5dfc(void)
{
    ldr     r1, [pc, #0x30]
    ldrb    r0, [r0, r1]
    cmp     r0, #0x1a
    bgt     _L_001a
    bge     _L_0020
    cmp     r0, #1
    bgt     _L_0030
    cmp     r0, #0
    blt     _L_0030
    beq     _L_0028
    cmp     r0, #1
    beq     _L_002c
    b       _L_0030
_L_001a:
    cmp     r0, #0x1b
    beq     _L_0024
    b       _L_0030
_L_0020:
    mov     r0, #0x6b
    bx      lr
_L_0024:
    mov     r0, #0x56
    bx      lr
_L_0028:
    mov     r0, #0x55
    bx      lr
_L_002c:
    mov     r0, #0x55
    bx      lr
_L_0030:
    add     r0, #0x55
    bx      lr
    lsr     r0, r3, #4
    lsl     r0, r0, #0
}
