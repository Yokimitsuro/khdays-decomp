extern int func_020235d0(int, int);

asm void func_ov302_020cc168(void *r0, int r1)
{
    stmfd   sp!, {r4, r5, r6, lr}
    mov     r6, r0
    ldrb    r0, [r6, #0x23]
    mov     r5, r1
    cmp     r0, #0
    moveq   r0, #0
    ldmeqfd sp!, {r4, r5, r6, pc}
    ldrh    r0, [r6, #4]
    cmp     r0, #0x384
    movhs   r0, #0
    ldmhsfd sp!, {r4, r5, r6, pc}
    ldrh    r1, [r6, #0xa]
    mov     r0, r5, lsr #8
    and     r0, r0, #0xff
    cmp     r1, r0
    movne   r0, #0
    ldmnefd sp!, {r4, r5, r6, pc}
    tst     r5, #8
    beq     _skipA
    ldrh    r0, [r6, #2]
    cmp     r0, #0xa
    moveq   r0, #1
    ldmeqfd sp!, {r4, r5, r6, pc}
_skipA:
    tst     r5, #3
    beq     _setup2
    ldr     r0, =0x44e
    mov     r1, #3
    bl      func_020235d0
    cmp     r0, #6
    ldrhs   r0, =0x191
    bhs     _skipB
    mov     r0, #0
    mov     r1, #9
    bl      func_020235d0
_skipB:
    ldrh    r1, [r6, #8]
    cmp     r1, r0
    movge   r0, #0
    ldmgefd sp!, {r4, r5, r6, pc}
_setup2:
    ldrb    r1, [r6, #0x23]
    ldrh    r0, [r6, #4]
    and     r3, r5, #0xf
    sub     r1, r1, #1
    mov     r0, r0, lsl #2
    mov     r2, #1
    add     r0, r0, #0x2b
    and     r4, r3, r2, lsl r1
    add     r0, r0, #0x900
    mov     r1, #4
    bl      func_020235d0
    tst     r4, r0
    movne   r0, #1
    ldmnefd sp!, {r4, r5, r6, pc}
    tst     r5, #2
    beq     _end
    ldrb    r0, [r6, #0x23]
    cmp     r0, #2
    bne     _end
    ldrh    r5, [r6, #4]
    cmp     r5, #0x64
    bls     _end
    ldr     r2, =0x51eb851f
    mov     r0, r5, lsr #0x1f
    smull   r1, r3, r2, r5
    add     r3, r0, r3, asr #5
    mov     r2, #0x64
    smull   r0, r1, r2, r3
    subs    r3, r5, r0
    movmi   r0, #0
    ldmmifd sp!, {r4, r5, r6, pc}
    cmp     r3, #0xc8
    movge   r0, #0
    ldmgefd sp!, {r4, r5, r6, pc}
    mov     r0, r3, lsl #2
    add     r0, r0, #0x2b
    add     r0, r0, #0x900
    mov     r1, #4
    bl      func_020235d0
    tst     r4, r0
    movne   r0, #1
    ldmnefd sp!, {r4, r5, r6, pc}
_end:
    mov     r0, #0
    ldmfd   sp!, {r4, r5, r6, pc}
}
