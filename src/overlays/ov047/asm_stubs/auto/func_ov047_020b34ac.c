asm int func_ov047_020b34ac(void *arg)
{
    ldr     r1, =0x918
    ldrb    r0, [r0, r1]
    cmp     r0, #1
    beq     _state1
    cmp     r0, #2
    beq     _state2
    b       _default
_state1:
    mov     r0, #0xad
    bx      lr
_state2:
    mov     r0, #0xae
    bx      lr
_default:
    mov     r0, #0xac
    bx      lr
}
