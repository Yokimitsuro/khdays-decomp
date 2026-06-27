extern void func_02008430(void);

asm void func_0200819c(void)
{
    stmdb sp!, {r3, lr}
    mov r3, r2
    mov ip, #1
    mov r2, #9
    str ip, [sp]
    bl func_02008430
    ldmia sp!, {r3, pc}
}
