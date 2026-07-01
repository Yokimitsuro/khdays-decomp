extern int data_0204c240;
extern void func_01fffe14(void);
extern void func_020235d0(void);
extern void func_020235e8(void);
extern void func_0203c960(void);
extern void func_0203ca30(void);
extern void func_ov002_0206bbb8(void);
extern void func_ov107_020c0794(void);
extern void func_ov107_020c7500(void);

asm void func_ov234_020cc274(void)
{
    stmfd   sp!, {r3, r4, r5, r6, r7, lr}
    sub     sp, sp, #0x48
    mov     r5, r1
    ldrb    r1, [r5, #2]
    mov     r6, r0
    mov     r4, r2
    cmp     r1, #5
    bne     _L244
    ldrb    r2, [r5, #5]
    ldrb    r0, [r5, #7]
    ldrb    r1, [r5, #6]
    strb    r2, [sp, #7]
    strb    r0, [sp, #5]
    strb    r1, [sp, #6]
    ldr     r1, [sp, #4]
    add     r0, sp, #0x1c
    mov     r1, r1, asr #8
    str     r1, [sp, #0x10]
    ldrb    r3, [r5, #8]
    ldrb    r2, [r5, #9]
    ldrb    r1, [r5, #0xa]
    strb    r3, [sp, #0xb]
    strb    r2, [sp, #0xa]
    strb    r1, [sp, #9]
    ldr     r1, [sp, #8]
    mov     r1, r1, asr #8
    str     r1, [sp, #0x14]
    ldrb    r3, [r5, #0xb]
    ldrb    r2, [r5, #0xc]
    ldrb    r1, [r5, #0xd]
    strb    r3, [sp, #0xf]
    strb    r2, [sp, #0xe]
    strb    r1, [sp, #0xd]
    ldr     r1, [sp, #0xc]
    mov     r1, r1, asr #8
    str     r1, [sp, #0x18]
    bl      func_0203c960
    add     r0, sp, #0x1c
    add     r1, sp, #0x10
    bl      func_0203ca30
    ldrb    r1, [r5, #3]
    cmp     r1, #6
    addls   pc, pc, r1, lsl #2
    b       _L244
    b       _Lcc
    b       _L244
    b       _Lfc
    b       _L158
    b       _L198
    b       _L21c
    b       _L234
_Lcc:
    add     r0, sp, #0x1c
    str     r0, [sp]
    add     r1, r6, r1, lsl #3
    ldr     r0, [r6, #0x3c]
    ldr     r1, [r1, #0x3bc]
    mov     r2, #5
    mov     r3, #0
    bl      func_ov107_020c0794
    ldrb    r1, [r5, #3]
    add     r1, r6, r1, lsl #3
    str     r0, [r1, #0x3c0]
    b       _L244
_Lfc:
    ldr     r2, [r6, #0x3b8]
    ldr     r0, =0x000003e7
    cmp     r2, r0
    bge     _L244
    add     r1, r2, #1
    str     r1, [r6, #0x3b8]
    cmp     r1, r0
    strge   r0, [r6, #0x3b8]
    ldr     r0, [r6, #0x3b8]
    sub     r7, r0, r2
    bl      func_01fffe14
    mov     r2, r7
    mov     r1, #3
    bl      func_ov002_0206bbb8
    ldr     r0, =data_0204c240
    ldrb    r0, [r0]
    tst     r0, #4
    beq     _L244
    ldrb    r0, [r5, #4]
    mov     r2, r7
    mov     r1, #7
    bl      func_ov002_0206bbb8
    b       _L244
_L158:
    ldr     r0, =data_0204c240
    ldrb    r0, [r0]
    tst     r0, #4
    bne     _L244
    mov     r0, #0x1400
    mov     r1, #0xa
    bl      func_020235d0
    ldr     r1, [r6, #0x3b8]
    cmp     r0, r1
    bge     _L244
    mov     r0, r1, lsl #0x10
    mov     r2, r0, lsr #0x10
    mov     r0, #0x1400
    mov     r1, #0xa
    bl      func_020235e8
    b       _L244
_L198:
    ldr     r0, =data_0204c240
    ldrb    r0, [r0]
    tst     r0, #4
    bne     _L1d4
    mov     r0, #0x1400
    mov     r1, #0xa
    bl      func_020235d0
    ldr     r1, [r6, #0x3b8]
    cmp     r0, r1
    bge     _L1d4
    mov     r0, r1, lsl #0x10
    mov     r2, r0, lsr #0x10
    mov     r0, #0x1400
    mov     r1, #0xa
    bl      func_020235e8
_L1d4:
    ldr     r0, =0x0000208f
    mov     r2, #0
    mov     r1, #0xa
    str     r2, [r6, #0x3b8]
    bl      func_020235e8
    bl      func_01fffe14
    mov     r1, #3
    mov     r2, #0
    bl      func_ov002_0206bbb8
    ldr     r0, =data_0204c240
    ldrb    r0, [r0]
    tst     r0, #4
    beq     _L244
    ldrb    r0, [r5, #4]
    mov     r1, #7
    mov     r2, #0
    bl      func_ov002_0206bbb8
    b       _L244
_L21c:
    ldr     r0, =0x0000208f
    mov     r2, #0
    mov     r1, #0xa
    str     r2, [r6, #0x3b8]
    bl      func_020235e8
    b       _L244
_L234:
    mov     r1, #1
    ldr     r0, =0x000020dc
    mov     r2, r1
    bl      func_020235e8
_L244:
    mov     r0, r6
    mov     r1, r5
    mov     r2, r4
    bl      func_ov107_020c7500
    add     sp, sp, #0x48
    ldmfd   sp!, {r3, r4, r5, r6, r7, pc}
}
