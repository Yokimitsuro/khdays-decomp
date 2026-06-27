asm void func_02010dd8(void *object)
{
    stmdb sp!, {r3, lr}
    ldr r2, [r0]
    ldr r2, [r2]
    blx r2
    ldmia sp!, {r3, pc}
}
