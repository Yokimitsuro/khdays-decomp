extern void func_01ff8b68(void);
extern void func_01ff8ad4(void);

asm void func_01ff8a04(void)
{
    stmdb sp!, {r3, lr}
    bl func_01ff8b68
    bl func_01ff8ad4
    ldmia sp!, {r3, pc}
}
