extern void func_ov022_02095524(void);
extern void func_ov031_020b3a38(void);
extern void func_0202a818(void);
extern void func_ov031_020b3a00(void);

asm void func_ov031_020b3a9c(void)
{
    stmfd   sp!, {r3, r4, r5, r6, r7, lr}
    mov     r6, r1
    mov     r7, r0
    ldr     r1, [r6, #4]
    add     r0, r7, #0x2c
    mov     r5, r2
    cmp     r1, #0
    add     r4, r0, #0x2c00
    beq     _stage0
    cmp     r1, #6
    ldrne   r0, [r7, #0x6bc]
    cmpne   r0, #0x2e
    beq     _set6
    ldr     r1, [r7, #0x464]
    ldr     r0, [r7, #0x468]
    and     r1, r1, #0x10000
    and     r0, r0, #0
    cmp     r0, #0
    cmpeq   r1, #0
    bne     _set6
    add     r0, r7, #0x2f8
    add     r0, r0, #0x2000
    bl      func_ov022_02095524
    cmp     r0, #0
    bne     _set6
    mov     r0, r6
    mov     r1, #2
    mov     r2, #0xf000
    bl      func_ov031_020b3a38
    mov     r0, #6
    str     r0, [r6, #4]
_set6:
    ldr     r0, [r7, #0x468]
    ldr     r1, [r7, #0x464]
    and     r0, r0, #0x40
    cmp     r0, #0
    and     r1, r1, #0
    mov     r0, #0
    cmpeq   r1, #0
    strne   r0, [r6, #4]
_stage0:
    ldr     r0, [r6, #4]
    cmp     r0, #6
    addls   pc, pc, r0, lsl #2
    ldmfd   sp!, {r3, r4, r5, r6, r7, pc}
    ldmfd   sp!, {r3, r4, r5, r6, r7, pc}
    b       _case1
    b       _case2
    b       _case3
    b       _case4
    b       _case5
    b       _case6
_case1:
    mov     r1, r5
    add     r0, r6, #8
    bl      func_0202a818
    cmp     r0, #0
    ldmeqfd sp!, {r3, r4, r5, r6, r7, pc}
    mov     r0, r6
    mov     r1, #1
    mov     r2, #0
    bl      func_ov031_020b3a38
    mov     r0, #2
    str     r0, [r6, #4]
    ldmfd   sp!, {r3, r4, r5, r6, r7, pc}
_case2:
    mov     r1, r5
    add     r0, r6, #8
    bl      func_0202a818
    ldmfd   sp!, {r3, r4, r5, r6, r7, pc}
_case3:
    mov     r1, r5
    add     r0, r6, #8
    bl      func_0202a818
    ldr     r0, [r6, #0x114]
    add     r1, r0, r5
    str     r1, [r6, #0x114]
    ldr     r0, [r6, #0x110]
    cmp     r1, r0
    ldmltfd sp!, {r3, r4, r5, r6, r7, pc}
    ldr     r0, [r4]
    mov     r1, #2
    cmp     r0, #0
    movne   r1, #3
    mov     r0, r6
    mov     r2, #0
    bl      func_ov031_020b3a38
    mov     r0, #4
    str     r0, [r6, #4]
    ldmfd   sp!, {r3, r4, r5, r6, r7, pc}
_case4:
    mov     r1, r5
    add     r0, r6, #8
    bl      func_0202a818
    cmp     r0, #0
    movne   r0, #5
    strne   r0, [r6, #4]
    ldmfd   sp!, {r3, r4, r5, r6, r7, pc}
_case5:
    ldr     r0, [r7, #0x6bc]
    cmp     r0, #0x2f
    cmpne   r0, #0x30
    ldmeqfd sp!, {r3, r4, r5, r6, r7, pc}
    add     r0, r7, #0x2f8
    add     r0, r0, #0x2000
    bl      func_ov022_02095524
    cmp     r0, #0
    moveq   r0, #0
    streq   r0, [r6, #4]
    ldmeqfd sp!, {r3, r4, r5, r6, r7, pc}
    mov     r0, r6
    bl      func_ov031_020b3a00
    ldmfd   sp!, {r3, r4, r5, r6, r7, pc}
_case6:
    mov     r1, r5
    add     r0, r6, #8
    bl      func_0202a818
    cmp     r0, #0
    movne   r0, #0
    strne   r0, [r6, #4]
    ldmfd   sp!, {r3, r4, r5, r6, r7, pc}
}
