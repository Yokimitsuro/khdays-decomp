extern void func_020036b0(void);

asm void func_020036a0(void)
{
    stmdb sp!, {r0, lr}
    bl func_020036b0
    ldmia sp!, {r0, lr}
    bx lr
}
