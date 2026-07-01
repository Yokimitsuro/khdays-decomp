asm void func_ov290_020cbfc4(void *p)
{
    mov     r2, #0x800
    str     r2, [r0, #0x70]
    mov     r1, #0
    str     r1, [r0, #0x64]
    str     r2, [r0, #0x68]
    str     r1, [r0, #0x6c]
    ldrh    r2, [r0, #0x60]
    mov     r1, r2, lsl #0x10
    mov     r1, r1, lsr #0x18
    orr     r1, r1, #6
    bic     r2, r2, #0xff00
    mov     r1, r1, lsl #0x18
    orr     r1, r2, r1, lsr #16
    strh    r1, [r0, #0x60]
    bx      lr
}
