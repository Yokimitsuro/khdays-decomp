extern void func_0203617c(void);

asm int func_020362ec(void)
{
    stmdb sp!, {r3, lr}
    bl func_0203617c
    mov r0, #1
    ldmia sp!, {r3, pc}
}
