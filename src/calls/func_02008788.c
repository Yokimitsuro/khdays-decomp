extern unsigned int OS_DisableInterrupts(void);
extern void OS_RestoreInterrupts(unsigned int);
extern int data_02044748[];

asm void func_02008788(void *object)
{
    stmdb sp!, {r4, lr}
    mov r4, r0
    bl OS_DisableInterrupts
    ldr r1, =data_02044748
    ldr r2, [r1, #0xc]
    cmp r2, #0
    streq r4, [r1, #8]
    strne r4, [r2]
    str r4, [r1, #0xc]
    mov r1, #0
    str r1, [r4]
    bl OS_RestoreInterrupts
    ldmia sp!, {r4, pc}
}
