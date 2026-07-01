extern void func_0202aa9c(void);

asm void func_ov045_020b4450(void)
{
    stmfd   sp!, {r3, lr}
    ldrsb   r2, [r1]
    cmp     r2, #2
    cmpne   r2, #3
    cmpne   r2, #4
    ldmnefd sp!, {r3, pc}
    ldrb    r0, [r0, #0x694]
    mov     r0, r0, lsl #0x1f
    movs    r0, r0, lsr #0x1f
    ldmeqfd sp!, {r3, pc}
    add     r0, r1, #4
    bl      func_0202aa9c
    ldmfd   sp!, {r3, pc}
}
