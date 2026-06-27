asm void *func_ov014_02080430(void *r0)
{
    ldrh    r1, [r0, #0x12]
    tst     r1, #8
    addne   r0, r0, #0x1c
    moveq   r0, #0
    bx      lr
}
