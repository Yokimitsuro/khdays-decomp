asm void MI_Zero36B(void *dst)
{
    mov r1, #0
    mov r2, #0
    mov r3, #0
    stmia r0!, {r1, r2, r3}
    stmia r0!, {r1, r2, r3}
    stmia r0!, {r1, r2, r3}
    bx lr
}
