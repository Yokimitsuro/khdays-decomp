extern int func_02011c44(void *);

asm void func_02011e3c(void *object)
{
    stmdb sp!, {r4, lr}
    mov r4, r0
    bl func_02011c44
    cmp r0, #0
    movne r1, #0
    strne r1, [r4, #0x10]
    ldmia sp!, {r4, pc}
}
