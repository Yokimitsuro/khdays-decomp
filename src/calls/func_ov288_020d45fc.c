extern void VEC_Subtract(void);
extern void func_ov107_020c8eb8(void);
extern void func_01fff8e8(void);
extern void func_01fff920(void);
extern void func_01fffd70(void);
extern void func_ov107_020c3504(void);
extern void func_01fffd8c(void);
extern void FX_Inv(void);
extern void func_01ff8d18(void);
extern void func_01ffa724(void);
extern void VEC_DotProduct(void);
extern void OS_IsThreadAvailable_0x020c9848(void);
extern void FX_Inv_0x01ff8a40(void);
extern void func_0203c634(void);
extern int data_0203d210;
extern int data_02042258;
extern int data_02041dc8;

asm void func_ov288_020d45fc(void)
{
    stmfd   sp!, {r4, r5, r6, r7, r8, sb, r10, r11, lr}
    sub     sp, sp, #0x54
    mov     r6, r0
    ldr     r7, [r6, #4]
    add     r2, sp, #0x48
    ldr     r0, [r7, #0xc]
    add     r1, r7, #0x10
    bl      VEC_Subtract
    ldr     r0, [r7, #0xc]
    add     r3, r7, #0x10
    ldmia   r0, {r0, r1, r2}
    stmia   r3, {r0, r1, r2}
    ldr     r0, [r7, #0x58]
    cmp     r0, #0
    beq     _L_02c4
    ldr     r0, [r7]
    ldrb    r1, [r0, #0x17a]
    ldr     r4, [r0, #4]
    mov     r1, r1, lsl #0x1c
    movs    r1, r1, lsr #0x1f
    bne     _L_0574
    add     r2, sp, #0x38
    add     r1, r0, #0x74
    bl      func_ov107_020c8eb8
    cmp     r0, #0
    mov     r3, #0
    ble     _L_008c
    ldr     r5, [r7, #8]
    add     r2, sp, #0x38
_L_0074:
    ldr     r1, [r2, r3, lsl #2]
    cmp     r1, r5
    bne     _L_0574
    add     r3, r3, #1
    cmp     r3, r0
    blt     _L_0074
_L_008c:
    ldr     r0, [r7]
    add     r2, sp, #0x48
    ldr     r0, [r0, #0x390]
    mov     r3, #0x300
    str     r0, [sp]
    ldr     r0, [r4, #0x7c]
    ldr     r1, [r7, #0xc]
    bl      func_01fff8e8
    cmp     r0, #0
    beq     _L_00c0
    ldr     r0, [r0, #8]
    cmp     r0, #0
    beq     _L_0574
_L_00c0:
    ldr     r0, [r7, #0x3c]
    cmp     r0, #0
    ble     _L_00dc
    ldr     r1, [r7, #0x38]
    add     r0, r0, r0, lsr #31
    cmp     r1, r0, asr #1
    blt     _L_0100
_L_00dc:
    ldr     r0, [r4, #0x7c]
    ldr     r1, [r7, #0xc]
    add     r2, sp, #0x48
    bl      func_01fff920
    cmp     r0, #0
    beq     _L_0100
    ldr     r0, [r0, #8]
    cmp     r0, #0
    beq     _L_0574
_L_0100:
    add     r0, r4, #0x80
    bl      func_01fffd70
    cmp     r0, #0
    moveq   r5, #0
    ldrne   r5, [r0]
    cmp     r5, #0
    beq     _L_01bc
_L_011c:
    ldr     r0, [r7]
    cmp     r5, r0
    beq     _L_01a0
    ldrh    r0, [r5, #0x60]
    mov     r0, r0, lsl #0x18
    mov     r0, r0, lsr #0x18
    tst     r0, #1
    beq     _L_01a0
    add     r0, r5, #0x100
    ldrh    r0, [r0, #0xac]
    tst     r0, #3
    bne     _L_01a0
    tst     r0, #4
    beq     _L_0160
    ldrh    r0, [r5]
    tst     r0, #0x8000
    beq     _L_01a0
_L_0160:
    add     r0, r5, #0x22c
    bl      func_01fffd70
    cmp     r0, #0
    beq     _L_01a0
    mov     r8, #0
_L_0174:
    ldr     r1, [r7]
    ldr     r0, [r0]
    mov     r2, r8
    add     r1, r1, #0x74
    bl      func_ov107_020c3504
    cmp     r0, #0
    bne     _L_0574
    add     r0, r5, #0x22c
    bl      func_01fffd8c
    cmp     r0, #0
    bne     _L_0174
_L_01a0:
    add     r0, r4, #0x80
    bl      func_01fffd8c
    cmp     r0, #0
    moveq   r5, #0
    ldrne   r5, [r0]
    cmp     r5, #0
    bne     _L_011c
_L_01bc:
    ldr     r1, [r7, #0x3c]
    cmp     r1, #0
    ble     _L_01d4
    ldr     r0, [r7, #0x38]
    cmp     r0, r1
    ble     _L_0208
_L_01d4:
    ldr     r1, [r6]
    mvn     r0, #0x5f
    ldr     r2, [r1, #0x2c]
    ldr     r1, =0x78787879
    mul     r3, r2, r0
    smull   r0, r2, r1, r3
    mov     r0, r3, lsr #0x1f
    ldr     r1, [r7, #0x20]
    add     r2, r0, r2, asr #6
    add     r0, r1, r2
    add     sp, sp, #0x54
    str     r0, [r7, #0x20]
    ldmfd   sp!, {r4, r5, r6, r7, r8, sb, r10, r11, pc}
_L_0208:
    cmp     r1, #0
    moveq   r3, #0
    beq     _L_0270
    bl      FX_Inv
    ldr     r1, =0x3244
    mov     r2, r0, asr #0x1f
    umull   r4, r3, r0, r1
    mla     r3, r2, r1, r3
    adds    r4, r4, #0x800
    adc     r0, r3, #0
    mov     r2, r4, lsr #0xc
    orr     r2, r2, r0, lsl #20
    ldr     r0, =0x60db9391
    ldr     r1, =0x28be
    umull   r4, r3, r2, r0
    mla     r3, r2, r1, r3
    mov     r1, r2, asr #0x1f
    mla     r3, r1, r0, r3
    adds    r0, r4, #0
    adc     r0, r3, #0x800
    mov     r0, r0, lsl #4
    mov     r0, r0, lsr #0x10
    mov     r1, r0, asr #4
    ldr     r0, =data_0203d210
    mov     r1, r1, lsl #2
    ldrsh   r3, [r0, r1]
_L_0270:
    ldr     r1, [r7, #0x44]
    ldr     r0, [r7, #0x40]
    add     r1, r1, #0x1800
    sub     r0, r3, r0
    smull   r2, r0, r1, r0
    adds    r1, r2, #0x800
    adc     r0, r0, #0
    mov     r1, r1, lsr #0xc
    ldr     r2, [r7, #0x48]
    orr     r1, r1, r0, lsl #20
    add     r0, r2, r1
    str     r0, [r7, #0x20]
    str     r3, [r7, #0x40]
    ldr     r0, [r6]
    ldr     r2, [r7, #0x38]
    ldr     r1, [r0, #0x2c]
    mov     r0, #0x1e
    mla     r0, r1, r0, r2
    add     sp, sp, #0x54
    str     r0, [r7, #0x38]
    ldmfd   sp!, {r4, r5, r6, r7, r8, sb, r10, r11, pc}
_L_02c4:
    ldr     r0, [r7, #8]
    cmp     r0, #0
    addeq   sp, sp, #0x54
    ldmeqfd sp!, {r4, r5, r6, r7, r8, sb, r10, r11, pc}
    ldr     r1, [r7]
    add     r0, sp, #0x2c
    ldr     r1, [r1, #4]
    ldr     r4, [r7, #0x30]
    ldr     r3, [r7, #0x28]
    str     r1, [sp, #4]
    mov     r2, #0
    str     r4, [sp, #0x34]
    mov     r1, r0
    str     r3, [sp, #0x2c]
    str     r2, [sp, #0x30]
    mvn     r4, #0x80000000
    bl      func_01ff8d18
    cmp     r0, #0
    beq     _L_0574
    ldr     r0, =0x666
    add     r1, sp, #0x2c
    add     r2, r7, #0x1c
    bl      func_01ffa724
    mov     r0, #0x300
    str     r0, [r7, #0x20]
    mov     r1, #0
    str     r1, [r7, #0x44]
    ldr     r0, [sp, #4]
    str     r1, [r7, #0x40]
    str     r1, [r7, #0x3c]
    add     r0, r0, #0x80
    str     r1, [r7, #0x38]
    bl      func_01fffd70
    cmp     r0, #0
    moveq   r3, #0
    ldrne   r3, [r0]
    cmp     r3, #0
    beq     _L_0520
    ldr     r0, =data_02042258
    add     r5, sp, #8
    ldmia   r0, {r0, r1, r2}
    stmia   r5, {r0, r1, r2}
_L_036c:
    ldr     r1, [r7]
    cmp     r3, r1
    beq     _L_0500
    ldrh    r0, [r3, #0x60]
    mov     r0, r0, lsl #0x18
    mov     r0, r0, lsr #0x18
    tst     r0, #1
    beq     _L_0500
    add     r0, r3, #0x100
    ldrh    r0, [r0, #0xac]
    tst     r0, #3
    bne     _L_0500
    tst     r0, #4
    beq     _L_03b0
    ldrh    r0, [r3]
    tst     r0, #0x8000
    beq     _L_0500
_L_03b0:
    add     r2, sp, #0x20
    add     r0, r3, #0x74
    add     r1, r1, #0x74
    bl      VEC_Subtract
    add     r0, sp, #0x14
    ldr     r5, [sp, #0x20]
    ldr     r2, [sp, #0x28]
    mov     r3, #0
    mov     r1, r0
    str     r5, [sp, #0x14]
    str     r3, [sp, #0x18]
    str     r2, [sp, #0x1c]
    bl      func_01ff8d18
    cmp     r0, #0
    bne     _L_03fc
    add     r0, sp, #8
    add     r3, sp, #0x14
    ldmia   r0, {r0, r1, r2}
    stmia   r3, {r0, r1, r2}
_L_03fc:
    add     r0, sp, #0x20
    mov     r1, r0
    bl      func_01ff8d18
    movs    r8, r0
    bne     _L_0420
    add     r0, sp, #8
    add     r3, sp, #0x20
    ldmia   r0, {r0, r1, r2}
    stmia   r3, {r0, r1, r2}
_L_0420:
    add     r0, sp, #0x2c
    add     r1, sp, #0x14
    bl      VEC_DotProduct
    cmp     r8, r4
    bge     _L_0500
    ldr     r1, =0xddb
    cmp     r0, r1
    ble     _L_0500
    ldr     r0, =0x666
    add     r1, sp, #0x20
    add     r2, r7, #0x1c
    bl      func_01ffa724
    ldr     r2, =0xa00a00a1
    mov     r0, r8, lsr #0x1f
    smull   r1, r3, r2, r8
    add     r3, r8, r3
    add     r3, r0, r3, asr #10
    str     r3, [r7, #0x3c]
    ldr     r0, [r7, #0x20]
    mov     r10, #0
    str     r0, [r7, #0x48]
    str     r10, [r7, #0x44]
    ldr     r0, [r7, #0x3c]
    mov     sb, r10
    add     r0, r0, r0, lsr #31
    mov     r0, r0, asr #1
    cmp     r0, #0
    ble     _L_04f0
    mvn     r5, #0
    sub     r4, r5, #0x5f
    mov     r6, r10
    mov     r11, #0x800
_L_04a0:
    bl      OS_IsThreadAvailable_0x020c9848
    ldr     r0, [r0, #0x40]
    bl      FX_Inv_0x01ff8a40
    umull   r2, r1, r0, r4
    adds    r2, r2, r11
    mla     r1, r0, r5, r1
    mov     r0, r0, asr #0x1f
    mla     r1, r0, r4, r1
    adc     r0, r1, r6
    mov     r1, r2, lsr #0xc
    orr     r1, r1, r0, lsl #20
    add     sb, sb, r1
    ldr     r0, [r7, #0x44]
    add     r10, r10, #1
    sub     r0, r0, sb
    str     r0, [r7, #0x44]
    ldr     r0, [r7, #0x3c]
    add     r0, r0, r0, lsr #31
    cmp     r10, r0, asr #1
    blt     _L_04a0
_L_04f0:
    ldr     r0, [r7, #0x3c]
    mov     r4, r8
    mov     r0, r0, lsl #0xc
    str     r0, [r7, #0x3c]
_L_0500:
    ldr     r0, [sp, #4]
    add     r0, r0, #0x80
    bl      func_01fffd8c
    cmp     r0, #0
    moveq   r3, #0
    ldrne   r3, [r0]
    cmp     r3, #0
    bne     _L_036c
_L_0520:
    ldr     r0, [r7, #0x3c]
    cmp     r0, #0
    beq     _L_0558
    cmp     r0, #0xf000
    bge     _L_0558
    mov     r1, #0xf000
    bl      FX_Inv
    add     r1, r7, #0x1c
    mov     r2, r1
    bl      func_01ffa724
    ldr     r1, [r7, #0x20]
    mov     r0, #0xf000
    str     r1, [r7, #0x48]
    str     r0, [r7, #0x3c]
_L_0558:
    ldr     r0, [r7]
    mov     r1, #0
    str     r1, [r0, #0x394]
    mov     r0, #1
    add     sp, sp, #0x54
    str     r0, [r7, #0x58]
    ldmfd   sp!, {r4, r5, r6, r7, r8, sb, r10, r11, pc}
_L_0574:
    ldr     r0, =data_02041dc8
    add     r3, r7, #0x1c
    ldmia   r0, {r0, r1, r2}
    stmia   r3, {r0, r1, r2}
    ldr     r0, [r7]
    mov     r1, #4
    strb    r1, [r0, #0x1c7]
    ldrsb   r1, [r6, #0x20]
    mov     r0, r6
    mov     r2, #0
    bl      func_0203c634
    add     sp, sp, #0x54
    ldmfd   sp!, {r4, r5, r6, r7, r8, sb, r10, r11, pc}
}
