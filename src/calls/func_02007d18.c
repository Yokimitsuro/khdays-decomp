extern int func_02006434(void);
extern int data_020446f0[];

asm void func_02007d18(void)
{
    stmdb sp!, {r3, lr}
    bl func_02006434
    ldr r1, =data_020446f0
    str r0, [r1, #0x18]
    ldmia sp!, {r3, pc}
}
