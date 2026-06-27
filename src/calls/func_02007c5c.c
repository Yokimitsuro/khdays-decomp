extern int func_0200640c(void);
extern int data_020446f0[];

asm void func_02007c5c(void)
{
    stmdb sp!, {r3, lr}
    bl func_0200640c
    ldr r1, =data_020446f0
    str r0, [r1]
    ldmia sp!, {r3, pc}
}
