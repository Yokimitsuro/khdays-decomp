extern void func_01ff8b0c(void);
extern void func_01ff8ad4(void);

asm void func_01ff8a40(void)
{
    stmdb sp!, {r3, lr}
    bl func_01ff8b0c
    bl func_01ff8ad4
    ldmia sp!, {r3, pc}
}
