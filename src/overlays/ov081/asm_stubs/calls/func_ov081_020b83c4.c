extern void func_ov081_020b9238(void *a, void *b);
extern void func_ov022_020a384c(void *a, int b);

asm void func_ov081_020b83c4(void *r0, int r1)
{
    stmfd   sp!, {r3, r4, r5, lr}
    mov     r4, r1
    mov     r5, r0
    cmp     r4, #0x2f
    add     r1, r5, #0x2c
    cmpne   r4, #0x30
    bne     _L_34
    ldr     r0, [r5, #0x6bc]
    cmp     r4, r0
    beq     _L_34
    mov     r0, r5
    add     r1, r1, #0x2c00
    bl      func_ov081_020b9238
_L_34:
    mov     r0, r5
    mov     r1, r4
    bl      func_ov022_020a384c
    ldmfd   sp!, {r3, r4, r5, pc}
}
