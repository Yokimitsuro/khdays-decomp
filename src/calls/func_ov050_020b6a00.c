extern void func_02030788(void);
extern void func_ov022_0209fe20(void);
extern void VEC_Add(void);
extern void MTX_RotY33_(void);
extern void MTX_MultVec33(void);
extern void VEC_Mag(void);
extern void func_01ff8d18(void);
extern void func_ov022_02091324(void);
extern void func_0202af1c(void);
extern void func_ov022_020a35f4(void);
extern void *data_ov050_020b75c0;
extern void *data_02041dc8;
extern void *data_ov050_020b7448;
extern void *data_ov050_020b7454;
extern void *data_0203d210;

asm void func_ov050_020b6a00(void)
{
    stmfd   sp!, {r4, r5, r6, lr}
    sub     sp, sp, #0x80
    ldr     r1, =data_ov050_020b75c0
    mov     r6, r0
    ldr     r0, [r1]
    mov     r4, #0
    add     r0, r0, #0x2c
    add     r5, r0, #0x2c00
    bl      func_02030788
    cmp     r0, #0
    bne     _skip1
    add     r0, r6, #0x64
    ldr     r2, [r6, #0x464]
    ldr     r1, [r0, #0x404]
    orr     r2, r2, #0x10000
    str     r2, [r6, #0x464]
    orr     r1, r1, #0
    str     r1, [r0, #0x404]
_skip1:
    bl      func_02030788
    cmp     r0, #0
    bne     _skip2
    add     r0, r6, #0x6c
    ldr     r2, [r6, #0x46c]
    ldr     r1, [r0, #0x404]
    orr     r2, r2, #0x10000
    str     r2, [r6, #0x46c]
    orr     r1, r1, #0
    str     r1, [r0, #0x404]
_skip2:
    ldr     r0, =data_02041dc8
    add     r3, sp, #0x74
    ldmia   r0, {r0, r1, r2}
    stmia   r3, {r0, r1, r2}
    mov     r0, r6
    mov     r1, r3
    bl      func_ov022_0209fe20
    ldr     r0, [sp, #0x78]
    cmp     r0, #0
    strne   r0, [r6, #0x58]
    bne     _skipFlag
    ldr     r0, [r6, #0x24]
    tst     r0, #4
    bne     _skipFlag
    ldr     r1, [r6]
    ldr     r0, [r6, #4]
    orr     r1, r1, #0
    str     r1, [r6]
    orr     r0, r0, #0x4000
    str     r0, [r6, #4]
    mov     r0, #0
    str     r0, [r6, #0x58]
_skipFlag:
    add     r0, sp, #0x74
    add     r3, sp, #0
    ldmia   r0, {r0, r1, r2}
    stmia   r3, {r0, r1, r2}
    mov     r0, #0
    add     r2, r6, #0x98
    str     r0, [sp, #4]
    add     r0, r2, #0x400
    mov     r1, r3
    add     r2, r2, #0x400
    bl      VEC_Add
    ldr     r1, [r6, #0x4cc]
    ldr     r0, [r5, #8]
    cmp     r1, r0
    blt     _skipRot
    ldr     r0, [r5, #4]
    cmp     r0, #0
    bne     _skipRot
    ldr     r0, =data_ov050_020b7448
    add     r3, sp, #0x68
    ldmia   r0, {r0, r1, r2}
    stmia   r3, {r0, r1, r2}
    ldr     r12, =data_ov050_020b7454
    add     r3, sp, #0x5c
    ldmia   r12, {r0, r1, r2}
    stmia   r3, {r0, r1, r2}
    ldr     r0, [r6, #0x20]
    ldr     r2, =data_0203d210
    ldrh    r1, [r0, #0x80]
    add     r0, sp, #0x38
    sub     r1, r1, #0x8000
    mov     r1, r1, lsl #0x10
    mov     r1, r1, lsr #0x10
    mov     r1, r1, asr #4
    mov     r3, r1, lsl #1
    add     r1, r3, #1
    mov     r3, r3, lsl #1
    mov     r1, r1, lsl #1
    ldrsh   r3, [r2, r3]
    ldrsh   r2, [r2, r1]
    rsb     r1, r3, #0
    rsb     r2, r2, #0
    bl      MTX_RotY33_
    add     r0, sp, #0x5c
    add     r1, sp, #0x38
    add     r2, sp, #0xc
    bl      MTX_MultVec33
    add     r0, sp, #0xc
    add     r1, r6, #0x8c
    add     r1, r1, #0x400
    mov     r2, r0
    bl      VEC_Add
    add     r0, sp, #0x68
    add     r1, sp, #0x38
    mov     r2, r0
    bl      MTX_MultVec33
    add     r0, sp, #0x68
    bl      VEC_Mag
    cmp     r0, #0
    beq     _afterFix
    add     r0, sp, #0x68
    mov     r1, r0
    bl      func_01ff8d18
_afterFix:
    ldr     lr, [sp, #0x68]
    mov     r2, #0
    ldr     r12, [sp, #0x6c]
    ldr     r3, [sp, #0x70]
    mov     r1, #7
    mov     r0, #0x900
    str     r1, [sp, #0x24]
    strh    lr, [sp, #0x18]
    strh    r12, [sp, #0x1a]
    strh    r3, [sp, #0x1c]
    str     r2, [sp, #0x20]
    str     r2, [sp, #0x28]
    str     r2, [sp, #0x2c]
    str     r2, [sp, #0x30]
    str     r2, [sp, #0x34]
    strh    r0, [sp, #0x1e]
    ldr     r0, [r5]
    add     r1, sp, #0xc
    cmp     r0, #0
    movne   r0, #1
    strne   r0, [sp, #0x20]
    mov     r0, r6
    bl      func_ov022_02091324
    mov     r0, #1
    str     r0, [r5, #4]
_skipRot:
    ldr     r1, [r6, #0x668]
    mov     r0, r6
    blx     r1
    ldrb    r1, [r6, #0x694]
    and     r0, r0, #0xff
    mov     r0, r0, lsl #0x1f
    bic     r1, r1, #2
    orr     r1, r1, r0, lsr #30
    and     r0, r1, #0xff
    mov     r0, r0, lsl #0x1e
    strb    r1, [r6, #0x694]
    movs    r0, r0, lsr #0x1f
    beq     _skipBit
    ldr     r1, [r6]
    ldr     r0, [r6, #4]
    orr     r1, r1, #0
    str     r1, [r6]
    orr     r0, r0, #0x20000
    str     r0, [r6, #4]
    ldr     r1, [r6, #0x20]
    ldr     r0, [r1]
    tst     r0, #0x20
    bne     _skipAf
    add     r0, r1, #4
    bl      func_0202af1c
_skipAf:
    bl      func_02030788
    cmp     r0, #0
    bne     _skipBit
    add     r0, r6, #0x64
    ldr     r2, [r6, #0x464]
    ldr     r1, [r0, #0x404]
    orr     r2, r2, #2
    str     r2, [r6, #0x464]
    orr     r1, r1, #0
    str     r1, [r0, #0x404]
_skipBit:
    ldrb    r0, [r6, #0x694]
    mov     r0, r0, lsl #0x1e
    movs    r0, r0, lsr #0x1f
    beq     _endElse
    mov     r1, #0
    str     r1, [r6, #0x4a0]
    str     r1, [r6, #0x49c]
    str     r1, [r6, #0x498]
    str     r1, [r6, #0x6a0]
    str     r1, [r6, #0x69c]
    str     r1, [r6, #0x698]
    ldr     r0, [r6, #0x24]
    tst     r0, #4
    beq     _elseB
    ldr     r2, [r6, #0x664]
    mov     r0, r6
    blx     r2
    mov     r0, r6
    mov     r1, #0
    bl      func_ov022_020a35f4
    mov     r4, r0
    b       _endElse
_elseB:
    mov     r0, r6
    mov     r1, #2
    bl      func_ov022_020a35f4
    mov     r4, r0
_endElse:
    mov     r0, r4
    add     sp, sp, #0x80
    ldmfd   sp!, {r4, r5, r6, pc}
}
