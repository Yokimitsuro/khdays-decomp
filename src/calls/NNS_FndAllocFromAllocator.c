asm void NNS_FndAllocFromAllocator(void *object)
{
    stmdb sp!, {r3, lr}
    ldr r2, [r0]
    ldr r2, [r2]
    blx r2
    ldmia sp!, {r3, pc}
}
