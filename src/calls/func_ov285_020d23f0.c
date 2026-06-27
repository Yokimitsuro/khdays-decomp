extern void VEC_Subtract(void);
extern void func_01ff8d18(void);
extern void FX_Inv(void);
extern void func_02023eb4(void);
extern void func_020050b4(void);
extern void func_01ffa724(void);
extern void func_0203c634(void);
extern void data_0203d210(void);

asm void func_ov285_020d23f0(void *r0)
{
    stmfd   sp!, {r3, r4, r5, r6, r7, lr}
    sub     sp, sp, #0x18
    mov     r7, r0
    ldr     r5, [r7, #4]
    add     r2, sp, #0xc
    ldr     r0, [r5]
    ldr     r1, [r5, #0x10]
    add     r0, r0, #0x190
    bl      VEC_Subtract
    add     r0, sp, #0xc
    mov     r2, #0
    mov     r1, r0
    str     r2, [sp, #0x10]
    bl      func_01ff8d18
    mov     r1, #0x14000
    bl      FX_Inv
    mov     r1, r0, lsl #1
    mov     r0, #0x1000
    sub     r6, r1, #0x1000
    rsb     r0, r0, #0
    cmp     r6, r0
    movlt   r6, r0
    cmp     r6, #0x1000
    movgt   r6, #0x1000
    cmp     r6, #0
    rsblt   r0, r6, #0
    movge   r0, r6
    rsb     r4, r0, #0x1000
    movs    r0, r4, lsl #1
    rsbmi   r0, r0, #0
    add     r0, r0, #1
    bl      func_02023eb4
    add     r0, r0, #0
    sub     r2, r0, r4
    ldr     r0, =0x00003244
    mov     r1, r2, asr #0x1f
    umull   r4, r3, r2, r0
    adds    r2, r4, #0x800
    mla     r3, r1, r0, r3
    adc     r0, r3, #0
    mov     r4, r2, lsr #0xc
    cmp     r6, #0
    orr     r4, r4, r0, lsl #0x14
    ble     _alt
    ldr     r0, [sp, #0xc]
    ldr     r1, [sp, #0x14]
    rsb     r0, r0, #0
    rsb     r1, r1, #0
    bl      func_020050b4
    add     r0, r0, #0x244
    add     r0, r0, #0x3000
    sub     r0, r0, r4
    b       _afterAlt
_alt:
    ldr     r0, [sp, #0xc]
    ldr     r1, [sp, #0x14]
    bl      func_020050b4
    add     r0, r0, #0x244
    add     r0, r0, #0x3000
    add     r0, r4, r0
_afterAlt:
    str     r0, [r5, #8]
    ldr     r1, [r7]
    mov     r0, #0x1e
    ldr     r1, [r1, #0x2c]
    ldr     r2, =0x66666667
    mul     r3, r1, r0
    mov     r0, r3, lsr #0x1f
    smull   r1, r3, r2, r3
    add     r3, r0, r3, asr #2
    str     r3, [r5, #0x14]
    ldr     r2, [r5, #4]
    ldr     r0, =0x60db9391
    ldr     r1, =0x000028be
    umull   r4, r3, r2, r0
    mla     r3, r2, r1, r3
    mov     r1, r2, asr #0x1f
    mla     r3, r1, r0, r3
    adds    r0, r4, #0
    adc     r0, r3, #0x800
    mov     r0, r0, lsl #4
    mov     r0, r0, lsr #0x10
    mov     r0, r0, asr #4
    mov     r3, r0, lsl #1
    add     r0, r3, #1
    mov     r2, #0
    str     r2, [sp, #4]
    ldr     r1, =data_0203d210
    mov     r3, r3, lsl #1
    mov     r0, r0, lsl #1
    ldrsh   r3, [r1, r3]
    ldrsh   r0, [r1, r0]
    add     r1, sp, #0
    str     r3, [sp]
    str     r0, [sp, #8]
    add     r2, r5, #0x1c
    mov     r0, #0x400
    bl      func_01ffa724
    ldr     r0, [r7]
    ldr     r1, [r5, #0x28]
    ldr     r0, [r0, #0x2c]
    add     r1, r1, r0
    str     r1, [r5, #0x28]
    ldr     r0, [r5, #0x2c]
    cmp     r1, r0
    addle   sp, sp, #0x18
    ldmlefd sp!, {r3, r4, r5, r6, r7, pc}
    ldr     r0, [r5]
    mov     r1, #2
    strb    r1, [r0, #0x1c7]
    ldrsb   r1, [r7, #0x20]
    mov     r0, r7
    mov     r2, #0
    bl      func_0203c634
    add     sp, sp, #0x18
    ldmfd   sp!, {r3, r4, r5, r6, r7, pc}
}
