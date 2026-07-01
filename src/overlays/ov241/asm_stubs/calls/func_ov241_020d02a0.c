extern void func_01ffa724(void);
extern void VEC_Add(void);
extern void func_01fffd70(void);
extern void VEC_Subtract(void);
extern void func_01ff8d18(void);
extern void VEC_DotProduct(void);
extern void func_ov241_020d01bc(void);
extern void func_01fffd8c(void);
extern int data_0203d210;
extern int data_02042258;

asm void func_ov241_020d02a0(void)
{
    stmfd   sp!, {r3, r4, r5, r6, r7, r8, sb, r10, r11, lr}
    sub     sp, sp, #0x40
    ldr     r6, [r0, #4]
    ldr     r1, =0x60db9391
    ldr     r0, [r6]
    ldr     r2, =0x28be
    ldr     r4, [r0, #0x3bc]
    ldr     sb, [r0, #4]
    umull   r7, r5, r4, r1
    mla     r5, r4, r2, r5
    mov     r2, r4, asr #0x1f
    mla     r5, r2, r1, r5
    adds    r1, r7, #0
    mov     r11, #0
    adc     r1, r5, #0x800
    mov     r1, r1, lsl #4
    mov     r1, r1, lsr #0x10
    mov     r1, r1, asr #4
    mov     r4, r1, lsl #1
    add     r1, r4, #1
    mov     r0, r1, lsl #1
    ldr     r2, =data_0203d210
    mov     r4, r4, lsl #1
    ldrsh   r4, [r2, r4]
    ldrsh   r0, [r2, r0]
    mov     r3, #0x800
    add     r1, sp, #0x34
    str     r0, [sp, #0x3c]
    add     r2, sp, #0x28
    str     r4, [sp, #0x34]
    str     r11, [sp, #0x38]
    sub     r0, r3, #0x2000
    sub     r7, r11, #0x80000001
    bl      func_01ffa724
    ldr     r1, [r6]
    add     r0, sp, #0x28
    add     r1, r1, #0x74
    mov     r2, r0
    bl      VEC_Add
    add     r0, sb, #0xa8
    bl      func_01fffd70
    cmp     r0, #0
    moveq   r10, r11
    ldrne   r10, [r0]
    cmp     r10, #0
    beq     _L_01e0
    ldr     r0, =data_02042258
    add     r3, sp, #4
    ldmia   r0, {r0, r1, r2}
    stmia   r3, {r0, r1, r2}
    add     r5, sp, #0x10
    add     r4, sp, #0x1c
_L_00d0:
    ldr     r0, [r10, #0x40]
    mov     r0, r0, lsl #0x1e
    movs    r0, r0, asr #0x1f
    beq     _L_01c4
    ldrh    r0, [r10, #0x60]
    mov     r0, r0, lsl #0x18
    mov     r0, r0, lsr #0x18
    tst     r0, #1
    beq     _L_01c4
    add     r0, r10, #0x74
    ldmia   r0, {r0, r1, r2}
    stmia   r5, {r0, r1, r2}
    ldr     r1, [r6]
    mov     r0, r5
    mov     r2, r4
    add     r1, r1, #0x74
    bl      VEC_Subtract
    ldr     r0, [sp, #0x20]
    cmp     r0, #0
    rsblt   r0, r0, #0
    cmp     r0, #0x1e000
    bgt     _L_01c4
    mov     r0, #0
    str     r0, [sp, #0x20]
    mov     r0, r4
    mov     r1, r4
    bl      func_01ff8d18
    mov     r8, r0
    cmp     r8, r7
    bge     _L_01c4
    mov     r0, r5
    add     r1, sp, #0x28
    mov     r2, r4
    bl      VEC_Subtract
    mov     r0, #0
    str     r0, [sp, #0x20]
    mov     r0, r4
    mov     r1, r4
    bl      func_01ff8d18
    cmp     r0, #0
    addeq   r0, sp, #4
    ldmeqia r0, {r0, r1, r2}
    stmeqia r4, {r0, r1, r2}
    cmp     r8, #0x1800
    ble     _L_01a4
    cmp     r8, #0xf000
    bgt     _L_01c4
    mov     r0, r4
    add     r1, sp, #0x34
    bl      VEC_DotProduct
    ldr     r1, =0xf74
    cmp     r0, r1
    blt     _L_01c4
_L_01a4:
    ldr     r1, [r10, #0x80]
    mov     r0, r6
    str     r1, [sp]
    ldmia   r5, {r1, r2, r3}
    bl      func_ov241_020d01bc
    cmp     r0, #0
    movne   r7, r8
    movne   r11, r10
_L_01c4:
    add     r0, sb, #0xa8
    bl      func_01fffd8c
    cmp     r0, #0
    moveq   r10, #0
    ldrne   r10, [r0]
    cmp     r10, #0
    bne     _L_00d0
_L_01e0:
    mov     r0, r11
    add     sp, sp, #0x40
    ldmfd   sp!, {r3, r4, r5, r6, r7, r8, sb, r10, r11, pc}
}
