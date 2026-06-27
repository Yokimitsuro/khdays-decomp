extern void func_0200b5ac(void);

asm int func_0200b69c(void)
{
    stmdb sp!, {r3, lr}
    bl func_0200b5ac
    mov r0, #1
    ldmia sp!, {r3, pc}
}
