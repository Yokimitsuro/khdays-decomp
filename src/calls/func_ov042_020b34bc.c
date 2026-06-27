asm int func_ov042_020b34bc(unsigned char *arg)
{
    ldr     r1, =0x918
    ldrb    r0, [r0, r1]
    cmp     r0, #0x14
    beq     _020b34bc_case_14
    cmp     r0, #0x15
    beq     _020b34bc_case_15
    cmp     r0, #0x16
    beq     _020b34bc_case_16
    b       _020b34bc_default
_020b34bc_case_14:
    mov     r0, #0xa3
    bx      lr
_020b34bc_case_15:
    mov     r0, #0xa4
    bx      lr
_020b34bc_case_16:
    mov     r0, #0xa5
    bx      lr
_020b34bc_default:
    mov     r0, #0xa2
    bx      lr
    mov     r8, r8
}
