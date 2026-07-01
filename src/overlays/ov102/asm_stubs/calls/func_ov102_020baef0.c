extern void func_0202a818(void);

asm void func_ov102_020baef0(void *arg0, void *arg1, void *arg2, void *arg3)
{
    stmfd   sp!, {r3, lr}
    ldr     r3, [r1, #0x10]
    cmp     r3, #0
    ldrne   r0, [r0, #0x6bc]
    cmpne   r0, #0x31
    movne   r0, #0
    strne   r0, [r1, #0x10]
    ldr     r0, [r1, #0x10]
    cmp     r0, #1
    beq     _L0034
    cmp     r0, #2
    beq     _L0050
    ldmfd   sp!, {r3, pc}
_L0034:
    ldr     r0, [r1, #0x11c]
    add     r0, r0, r2
    str     r0, [r1, #0x11c]
    cmp     r0, #0x12000
    movge   r0, #2
    strge   r0, [r1, #0x10]
    ldmfd   sp!, {r3, pc}
_L0050:
    add     r0, r1, #0x14
    mov     r1, r2
    bl      func_0202a818
    ldmfd   sp!, {r3, pc}
}
