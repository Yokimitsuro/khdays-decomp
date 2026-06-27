extern int func_0202a818(void *p);

asm void func_ov081_020b9508(void *r0)
{
    stmfd   sp!, {r4, lr}
    mov     r4, r0
    ldr     r0, [r4]
    cmp     r0, #0
    ldmeqfd sp!, {r4, pc}
    cmp     r0, #1
    ldmnefd sp!, {r4, pc}
    add     r0, r4, #4
    bl      func_0202a818
    cmp     r0, #0
    movne   r0, #0
    strne   r0, [r4]
    ldmfd   sp!, {r4, pc}
}
