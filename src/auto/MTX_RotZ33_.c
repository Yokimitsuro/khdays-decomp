asm void MTX_RotZ33_(int *p, int value, int other)
{
    stmia r0!, {r2}
    mov r3, #0
    stmia r0!, {r1, r3}
    neg r1, r1
    stmia r0!, {r1, r2}
    mov r1, #1
    lsl r1, r1, #0xc
    str r3, [r0]
    str r3, [r0, #4]
    str r3, [r0, #8]
    str r1, [r0, #0xc]
    bx lr
}
