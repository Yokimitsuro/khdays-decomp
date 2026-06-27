asm int func_ov102_020baa4c(void *self)
{
    ldr     r1, =0x918
    ldrb    r0, [r0, r1]
    cmp     r0, #1
    beq     _one
    cmp     r0, #2
    beq     _two
    b       _default
_one:
    mov     r0, #0xad
    bx      lr
_two:
    mov     r0, #0xae
    bx      lr
_default:
    mov     r0, #0xac
    bx      lr
}
