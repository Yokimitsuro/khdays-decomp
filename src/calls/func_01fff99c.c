asm void func_01fff99c(int x)
{
    cmp r0, #1
    cmpne r0, #4
    bne ret_zero
    mov r0, #1
    bx lr
ret_zero:
    mov r0, #0
    bx lr
}
