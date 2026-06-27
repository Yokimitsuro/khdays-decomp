extern void func_0202aa9c(void *p);

asm void func_ov081_020b953c(void *r0)
{
    stmfd   sp!, {r3, lr}
    ldr     r1, [r0]
    cmp     r1, #0
    ldmeqfd sp!, {r3, pc}
    add     r0, r0, #4
    bl      func_0202aa9c
    ldmfd   sp!, {r3, pc}
}
