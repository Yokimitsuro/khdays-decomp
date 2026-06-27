extern void func_02002f9c(void);
extern void func_0200302c(void);

asm void func_02002f88(void)
{
    stmdb sp!, {r0, lr}
    bl func_02002f9c
    bl func_0200302c
    ldmia sp!, {r0, lr}
    bx lr
}
