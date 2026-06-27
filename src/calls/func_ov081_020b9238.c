extern void func_ov081_020b8f1c(void);

asm void func_ov081_020b9238(void *r0, void *r1)
{
    stmfd   sp!, {r4, lr}
    mov     r4, r1
    ldr     r1, [r4]
    cmp     r1, #0
    cmpne   r1, #2
    ldmnefd sp!, {r4, pc}
    cmp     r1, #0
    bne     _L_24
    bl      func_ov081_020b8f1c
_L_24:
    mov     r0, #1
    str     r0, [r4]
    ldmfd   sp!, {r4, pc}
}
