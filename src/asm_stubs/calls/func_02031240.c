extern int *NNSi_FndGetCurrentRootHeap(void);
extern void func_0203158c(int);

asm int func_02031240(void)
{
    stmdb sp!, {r3, lr}
    bl NNSi_FndGetCurrentRootHeap
    ldr r0, [r0]
    bl func_0203158c
    mov r0, #0
    ldmia sp!, {r3, pc}
}
