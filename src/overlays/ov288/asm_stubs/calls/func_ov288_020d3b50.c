extern void func_ov002_02076b68(void);
extern void func_ov002_02076b48(void);
extern void func_ov107_020c08cc(void);
extern void func_ov002_02072754(void);
extern void func_ov002_02077cec(void);
extern void func_0203b9fc(void);
extern void func_0203c7ac(void);
extern void func_ov107_020c7500(void);
extern int data_0204c240;

asm void func_ov288_020d3b50(void)
{
    stmfd   sp!, {r4, r5, r6, r7, r8, lr}
    sub     sp, sp, #0x28
    mov     r6, r1
    ldrb    r1, [r6, #2]
    mov     r7, r0
    mov     r5, r2
    cmp     r1, #0
    bne     _L_0048
    ldr     r0, [r7, #0x390]
    cmp     r0, #0
    beq     _L_022c
    ldrb    r1, [r6, #0x24]
    cmp     r1, #0
    beq     _L_0040
    bl      func_ov002_02076b68
    b       _L_022c
_L_0040:
    bl      func_ov002_02076b48
    b       _L_022c
_L_0048:
    cmp     r1, #5
    bne     _L_022c
    ldrb    r1, [r6, #3]
    cmp     r1, #4
    addls   pc, pc, r1, lsl #2
    b       _L_022c
    b       _L_00ac
    b       _L_0074
    b       _L_022c
    b       _L_00e4
    b       _L_01c4
_L_0074:
    mov     r0, #0x1000
    str     r0, [sp]
    add     r0, r6, #5
    str     r0, [sp, #4]
    add     r1, r7, r1, lsl #3
    ldr     r0, [r7, #0x3c]
    ldr     r1, [r1, #0x3c0]
    mov     r2, #5
    mov     r3, #0
    bl      func_ov107_020c08cc
    ldrb    r1, [r6, #3]
    add     r1, r7, r1, lsl #3
    str     r0, [r1, #0x3c4]
    b       _L_022c
_L_00ac:
    mov     r0, #0x1000
    str     r0, [sp]
    add     r0, r6, #5
    str     r0, [sp, #4]
    add     r1, r7, r1, lsl #3
    ldrb    r3, [r6, #4]
    ldr     r0, [r7, #0x3c]
    ldr     r1, [r1, #0x3c0]
    mov     r2, #5
    bl      func_ov107_020c08cc
    ldrb    r1, [r6, #3]
    add     r1, r7, r1, lsl #3
    str     r0, [r1, #0x3c4]
    b       _L_022c
_L_00e4:
    ldr     r0, [r7, #4]
    add     r2, sp, #0x14
    mov     r1, #0
    strb    r1, [r2]
    strb    r1, [r2, #1]
    strb    r1, [r2, #2]
    strb    r1, [r2, #3]
    strb    r1, [r2, #4]
    strb    r1, [r2, #5]
    ldr     r1, =data_0204c240
    ldrb    r3, [r6, #4]
    ldr     r2, [r7, #0x220]
    ldrb    r1, [r1]
    mul     r4, r3, r2
    mov     r2, r4, asr #0x1f
    mov     r3, r4, lsr #0xc
    orr     r3, r3, r2, lsl #20
    tst     r1, #4
    and     r1, r3, #0xff
    strneb  r1, [sp, #0x14]
    streqb  r1, [sp, #0x15]
    ldrb    r3, [r6, #5]
    ldrb    r2, [r6, #6]
    ldrb    r1, [r6, #7]
    strb    r3, [sp, #0xb]
    strb    r2, [sp, #0xa]
    strb    r1, [sp, #9]
    ldr     r1, [sp, #8]
    mov     r1, r1, asr #8
    str     r1, [sp, #0x1c]
    ldrb    r3, [r6, #8]
    ldrb    r2, [r6, #9]
    ldrb    r1, [r6, #0xa]
    strb    r3, [sp, #0xf]
    strb    r2, [sp, #0xe]
    strb    r1, [sp, #0xd]
    ldr     r1, [sp, #0xc]
    mov     r1, r1, asr #8
    str     r1, [sp, #0x20]
    ldrb    r3, [r6, #0xb]
    ldrb    r2, [r6, #0xc]
    ldrb    r1, [r6, #0xd]
    strb    r3, [sp, #0x13]
    strb    r2, [sp, #0x12]
    strb    r1, [sp, #0x11]
    ldr     r1, [sp, #0x10]
    mov     r1, r1, asr #8
    str     r1, [sp, #0x24]
    ldr     r0, [r0, #0x78]
    bl      func_ov002_02072754
    mov     r1, r0, lsl #0x10
    add     r0, sp, #0x14
    add     r2, sp, #0x1c
    mov     r1, r1, lsr #0x10
    bl      func_ov002_02077cec
    b       _L_022c
_L_01c4:
    ldr     r0, [r7, #0x50]
    cmp     r0, #2
    bne     _L_022c
    ldrb    r0, [r6, #4]
    and     r4, r0, #0x7f
    mov     r1, r4, lsr #0x1f
    tst     r0, #0x80
    movne   r2, #1
    rsb     r0, r1, r4, lsl #30
    moveq   r2, #0
    add     r0, r1, r0, ror #30
    and     r8, r2, #0xff
    mov     r1, r0, lsl #0x10
    mov     r2, r1, asr #0x10
    ldr     r0, [r7, #0x384]
    mov     r3, r8
    mov     r1, #0
    bl      func_0203b9fc
    ldr     r0, [r7, #0x384]
    mov     r2, r4
    mov     r3, r8
    mov     r1, #2
    bl      func_0203b9fc
    ldr     r0, [r7, #0x384]
    mov     r1, #0
    bl      func_0203c7ac
_L_022c:
    mov     r0, r7
    mov     r1, r6
    mov     r2, r5
    bl      func_ov107_020c7500
    add     sp, sp, #0x28
    ldmfd   sp!, {r4, r5, r6, r7, r8, pc}
}
