extern void func_020036b0(void);

asm void OSi_AlarmHandler(void)
{
    stmdb sp!, {r0, lr}
    bl func_020036b0
    ldmia sp!, {r0, lr}
    bx lr
}
