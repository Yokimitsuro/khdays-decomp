extern int func_020235d0(int, int);

asm void func_ov302_020cc2bc(void *r0, int r1)
{
    stmfd   sp!, {r3, lr}
    ldrb    r2, [r0, #0x23]
    cmp     r2, #0
    movne   r0, #0
    ldmnefd sp!, {r3, pc}
    ldrh    r2, [r0, #6]
    cmp     r2, r1
    movhi   r0, #0
    ldmhifd sp!, {r3, pc}
    ldrh    r2, [r0, #8]
    cmp     r2, r1
    movlo   r0, #0
    ldmlofd sp!, {r3, pc}
    ldrb    r0, [r0, #0x15]
    cmp     r0, #0
    beq     _ret1
    sub     r0, r0, #1
    add     r0, r0, #0
    mov     r0, r0, lsl #0x10
    mov     r0, r0, lsr #0xf
    add     r0, r0, #0x9f
    add     r0, r0, #0x3700
    mov     r1, #2
    bl      func_020235d0
    cmp     r0, #1
    movhs   r0, #1
    movlo   r0, #0
    cmp     r0, #0
    moveq   r0, #0
    ldmeqfd sp!, {r3, pc}
_ret1:
    mov     r0, #1
    ldmfd   sp!, {r3, pc}
}
