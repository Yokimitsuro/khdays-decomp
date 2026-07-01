asm void func_ov046_020b34f4(void)
{
    ldr     r1, [pc, #0xc]
    ldrb    r0, [r0, r1]
    cmp     r0, #1
    bne     _L_000c
    mov     r0, #0x88
    bx      lr
_L_000c:
    mov     r0, #0x87
    bx      lr
    lsr     r0, r3, #4
    lsl     r0, r0, #0
}
