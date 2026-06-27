extern int func_02020400(int x);

asm int func_0201e16c(void *p)
{
    stmdb sp!, {r4, lr}
    ldr r1, [r0, #0xc]
    ldr r2, [r0, #8]
    cmp r2, r1
    ldrge r0, [r0, #4]
    ldmgeia sp!, {r4, pc}
    ldr r4, [r0]
    ldr r0, [r0, #4]
    sub r0, r0, r4
    mul r0, r2, r0
    bl func_02020400
    add r0, r4, r0
    ldmia sp!, {r4, pc}
}
