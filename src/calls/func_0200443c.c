asm void func_0200443c(void *self, void *buf, const unsigned int *hdr)
{
    str r1, [r0]
    ldr r1, [r2]
    mov r3, #0
    mov r1, r1, lsr #8
    str r1, [r0, #4]
    strb r3, [r0, #0xf]
    strb r3, [r0, #0x10]
    str r3, [r0, #8]
    mov r1, #3
    strb r1, [r0, #0x11]
    strh r3, [r0, #0xc]
    strb r3, [r0, #0xe]
    ldr r1, [r2]
    mov r1, r1, lsl #0x1c
    movs r1, r1, lsr #0x1c
    movne r3, #1
    strb r3, [r0, #0x12]
    bx lr
}
