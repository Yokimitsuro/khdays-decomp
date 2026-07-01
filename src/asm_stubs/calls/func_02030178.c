asm void func_02030178(void *object)
{
    stmdb sp!, {r3, lr}
    ldr r0, [r0, #0x18]
    ldr r2, [r0, #0x1c]
    add r0, r0, #0x8
    ldr r2, [r2, #0x4]
    blx r2
    ldmia sp!, {r3, pc}
}
