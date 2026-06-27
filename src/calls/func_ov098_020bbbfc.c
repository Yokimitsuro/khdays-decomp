extern void func_0202aa9c(void *);

asm void func_ov098_020bbbfc(void)
{
    stmdb sp!, {r3, lr}
    ldr r1, [r0]
    cmp r1, #0
    ldmeqia sp!, {r3, pc}
    add r0, r0, #4
    bl func_0202aa9c
    ldmia sp!, {r3, pc}
}
