asm int func_ov098_020baa5c(unsigned char *)
{
    ldr r1, =0x918
    ldrb r0, [r0, r1]
    cmp r0, #0x14
    beq label_14
    cmp r0, #0x15
    beq label_15
    cmp r0, #0x16
    beq label_16
    b label_default
label_14:
    mov r0, #0xa3
    bx lr
label_15:
    mov r0, #0xa4
    bx lr
label_16:
    mov r0, #0xa5
    bx lr
label_default:
    mov r0, #0xa2
    bx lr
}
