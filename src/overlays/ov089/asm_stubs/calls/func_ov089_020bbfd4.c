extern void func_0202a818(void);

asm void func_ov089_020bbfd4(void)
{
    stmfd   sp!, {r4, lr}
    mov     r4, r0
    ldr     r0, [r4]
    cmp     r0, #1
    ldmnefd sp!, {r4, pc}
    add     r0, r4, #8
    bl      func_0202a818
    cmp     r0, #0
    movne   r0, #0
    strne   r0, [r4]
    ldmfd   sp!, {r4, pc}
}
