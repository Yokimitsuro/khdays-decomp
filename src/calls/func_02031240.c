extern int *func_02023c00(void);
extern void func_0203158c(int);

asm int func_02031240(void)
{
    stmdb sp!, {r3, lr}
    bl func_02023c00
    ldr r0, [r0]
    bl func_0203158c
    mov r0, #0
    ldmia sp!, {r3, pc}
}
