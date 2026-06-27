asm int func_ov014_0208064c(void *r0)
{
    add     r0, r0, #0x100
    ldrsb   r0, [r0, #0x34]
    cmp     r0, #3
    moveq   r0, #1
    movne   r0, #0
    bx      lr
}
