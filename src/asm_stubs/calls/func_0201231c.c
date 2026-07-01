extern void func_0201232c(void);

asm void func_0201231c(void *r0, int r1)
{
    ldr     ip, =func_0201232c
    str     r1, [r0]
    bx      ip
}
