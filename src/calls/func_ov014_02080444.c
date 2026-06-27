asm void *func_ov014_02080444(void *r0)
{
    ldrh    r1, [r0, #0x12]
    tst     r1, #8
    ldrne   r0, [r0, #0x28]
    moveq   r0, #0
    bx      lr
}
