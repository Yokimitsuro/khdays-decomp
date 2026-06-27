asm int func_ov030_020b3694(void *r0)
{
    ldr     r1, =0x918
    ldrb    r0, [r0, r1]
    mov     r1, r0
    sub     r1, #0x16
    cmp     r1, #0x5
    bhi     _L_30
    add     r1, r1, r1
    add     r1, pc
    ldrh    r1, [r1, #0x6]
    lsl     r1, r1, #0x10
    asr     r1, r1, #0x10
    add     pc, r1
    dcd     0x000a000a
    dcd     0x000a000a
    dcd     0x0012000e
_L_24:
    add     r0, #0x56
    bx      lr
_L_28:
    mov     r0, #0x6b
    bx      lr
_L_2c:
    mov     r0, #0x56
    bx      lr
_L_30:
    add     r0, #0x55
    bx      lr
}
