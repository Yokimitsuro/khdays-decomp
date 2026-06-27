asm void func_ov088_020bafc0(void)
{
    mov     r2, #3
    str     r2, [r0, #4]
    str     r1, [r0, #0x110]
    mov     r1, #0
    str     r1, [r0, #0x114]
    bx      lr
}
