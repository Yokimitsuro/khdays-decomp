asm void func_ov014_02080230(void *r0, unsigned char *r1)
{
    ldrb    r1, [r1]
    cmp     r1, #1
    moveq   r1, #2
    streqb  r1, [r0, #0x134]
    bx      lr
}
