extern void func_0201d088(void *);

asm void func_0201cb64(void *object)
{
    stmdb sp!, {r3, lr}
    ldr r2, [r0]
    cmp r2, #0
    ldmeqia sp!, {r3, pc}
    ldr r0, [r0]
    bl func_0201d088
    ldmia sp!, {r3, pc}
}
