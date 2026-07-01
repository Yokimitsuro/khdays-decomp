extern void func_0202accc(void);

asm void func_ov049_020b3b2c(void)
{
    stmfd   sp!, {r4, lr}
    mov     r4, r1
    ldrsb   r1, [r4]
    cmp     r1, #0
    beq     _reset
    sub     r0, r1, #5
    mov     r0, r0, lsl #0x18
    mov     r0, r0, asr #0x18
    and     r0, r0, #0xff
    cmp     r0, #1
    bhi     _check3
_reset:
    mov     r0, #0
    str     r0, [r4, #0x110]
    str     r0, [r4, #0x114]
    mov     r0, #1
    strb    r0, [r4]
    ldmfd   sp!, {r4, pc}
_check3:
    cmp     r1, #3
    ldmnefd sp!, {r4, pc}
    ldr     r2, [r4, #0x10c]
    add     r0, r4, #4
    mov     r1, #0
    mov     r3, #3
    bl      func_0202accc
    ldr     r2, [r4, #0x10c]
    add     r0, r4, #4
    mov     r1, #2
    mov     r3, #3
    bl      func_0202accc
    mov     r0, #4
    strb    r0, [r4]
    ldmfd   sp!, {r4, pc}
}
