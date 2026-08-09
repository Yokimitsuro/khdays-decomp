asm void func_0200386c(register unsigned int cycles)
{
loop:
    subs r0, r0, #4
    bhs loop
    bx lr
}
