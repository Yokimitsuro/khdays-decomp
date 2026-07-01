asm int func_ov285_020d1cbc(void *r0)
{
    ldr     r0, [r0, #0x214]
    mvn     r1, #0
    ldr     r2, [r0]
    add     r0, r2, #0x100
    ldrsb   r0, [r0, #0xc7]
    cmp     r0, r1
    movne   r0, #0
    bxne    lr
    mov     r0, #5
    strb    r0, [r2, #0x1c7]
    mov     r0, #1
    bx      lr
}
