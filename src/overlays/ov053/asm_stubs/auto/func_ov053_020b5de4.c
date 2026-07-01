asm int func_ov053_020b5de4(void *arg)
{
    ldr     r1, =0x918
    ldrb    r0, [r0, r1]
    cmp     r0, #0x14
    beq     _state14
    cmp     r0, #0x15
    beq     _state15
    cmp     r0, #0x16
    beq     _state16
    b       _default
_state14:
    mov     r0, #0x7d
    bx      lr
_state15:
    mov     r0, #0x7e
    bx      lr
_state16:
    mov     r0, #0x7f
    bx      lr
_default:
    mov     r0, #0x7c
    bx      lr
}
