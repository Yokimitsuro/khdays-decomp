extern void func_01fff8b8(void);
extern void func_01ffd144(void);
extern void func_01ff8d18(void);
extern void func_ov107_020c5c54(void);
extern void func_0202ed60(void);
extern void func_0203c9d0(void);
extern void func_0203c634(void);
extern void func_ov107_020ca414(void);
extern void VEC_Subtract(void);
extern void VEC_Mag(void);
extern int data_02042264;

asm void func_ov296_020d5c48(void *r0)
{
    stmfd   sp!, {r3, r4, r5, r6, r7, r8, r9, r10, r11, lr}
    sub     sp, sp, #0x80
    mov     r10, r0
    ldr     r5, [r10, #4]
    mov     r3, #0
    ldr     r2, [r5]
    mov     r1, #0x1200
    ldr     r0, [r2, #0x388]
    ldr     r6, [r2, #4]
    ldr     r7, [r0, #8]
    add     r2, sp, #0x74
    mov     r4, r7, lsl #0x18
    mov     r4, r4, lsr #0x18
    orr     r4, r4, #1
    bic     r7, r7, #0xff
    and     r4, r4, #0xff
    orr     r4, r7, r4
    str     r4, [r0, #8]
    str     r3, [sp, #0x74]
    str     r1, [sp, #0x78]
    str     r3, [sp, #0x7c]
    ldr     r0, [r6, #0x7c]
    ldr     r1, [r5, #4]
    bl      func_01fff8b8
    movs    r4, r0
    beq     _L_0204
    ldr     r0, [r4, #8]
    cmp     r0, #0
    beq     _L_0084
    beq     _L_0204
    ldrh    r0, [r0, #0x22]
    tst     r0, #0xff
    bne     _L_0204
_L_0084:
    add     r1, sp, #0x74
    ldr     r0, [r4, #0xc]
    mov     r2, r1
    bl      func_01ffd144
    ldr     r1, [r4, #4]
    add     r0, sp, #0x5c
    ldrsh   r2, [r1, #0x14]
    mov     r1, r0
    str     r2, [sp, #0x5c]
    ldr     r2, [r4, #4]
    ldrsh   r2, [r2, #0x16]
    str     r2, [sp, #0x60]
    ldr     r2, [r4, #4]
    ldrsh   r2, [r2, #0x18]
    str     r2, [sp, #0x64]
    bl      func_01ff8d18
    ldr     r1, [sp, #0x5c]
    mov     r0, #0x1200
    umull   r6, r4, r1, r0
    mov     r1, r1, asr #0x1f
    mla     r4, r1, r0, r4
    adds    r6, r6, #0x800
    adc     r1, r4, #0
    mov     r4, r6, lsr #0xc
    ldr     r6, [r5, #4]
    orr     r4, r4, r1, lsl #20
    ldr     r1, [sp, #0x74]
    ldr     r6, [r6]
    ldr     r3, [sp, #0x60]
    add     r1, r6, r1
    add     r1, r1, r4
    str     r1, [sp, #0x68]
    ldr     r4, [r5, #4]
    mov     r1, r3, asr #0x1f
    ldr     r8, [r4, #4]
    umull   r6, r4, r3, r0
    ldr     r7, [sp, #0x78]
    adds    r3, r6, #0x800
    mla     r4, r1, r0, r4
    adc     r1, r4, #0
    mov     r3, r3, lsr #0xc
    add     r7, r8, r7
    orr     r3, r3, r1, lsl #20
    add     r1, r7, r3
    str     r1, [sp, #0x6c]
    ldr     r1, [r5, #4]
    ldr     r2, [sp, #0x64]
    ldr     r4, [r1, #8]
    ldr     r3, [sp, #0x7c]
    mov     r1, r2, asr #0x1f
    add     r6, r4, r3
    umull   r4, r3, r2, r0
    mla     r3, r1, r0, r3
    adds    r1, r4, #0x800
    adc     r0, r3, #0
    mov     r1, r1, lsr #0xc
    orr     r1, r1, r0, lsl #20
    add     r0, r6, r1
    str     r0, [sp, #0x70]
    ldr     r0, [r5]
    add     r1, sp, #0x68
    bl      func_ov107_020c5c54
    ldr     r1, [pc, #0x2c4]
    add     r0, sp, #0x4c
    add     r2, sp, #0x5c
    bl      func_0202ed60
    ldr     r0, [r5]
    add     r1, sp, #0x4c
    add     r0, r0, #0xa0
    bl      func_0203c9d0
    ldr     r2, [r5]
    ldrh    r0, [r2, #0x60]
    bic     r1, r0, #0xff00
    mov     r0, r0, lsl #0x10
    mov     r0, r0, lsr #0x18
    orr     r0, r0, #0x40
    mov     r0, r0, lsl #0x18
    orr     r0, r1, r0, lsr #16
    strh    r0, [r2, #0x60]
    ldr     r2, [r5]
    ldrh    r0, [r2, #0x60]
    bic     r1, r0, #0xff00
    mov     r0, r0, lsl #0x10
    mov     r0, r0, lsr #0x18
    bic     r0, r0, #0x1e
    mov     r0, r0, lsl #0x10
    mov     r0, r0, lsr #0x10
    mov     r0, r0, lsl #0x18
    orr     r0, r1, r0, lsr #16
    strh    r0, [r2, #0x60]
    ldrsb   r1, [r10, #0x20]
    mov     r0, r10
    mov     r2, #0
    bl      func_0203c634
    add     sp, sp, #0x80
    ldmfd   sp!, {r3, r4, r5, r6, r7, r8, r9, r10, r11, pc}
_L_0204:
    ldr     r0, [r5, #4]
    add     r4, sp, #0x3c
    ldmia   r0, {r0, r1, r2}
    stmia   r4, {r0, r1, r2}
    mov     r0, #0x1200
    str     r0, [sp, #0x48]
    ldr     r0, [r6, #0x7c]
    add     r2, sp, #0xc
    add     r3, sp, #0x5c
    mov     r1, r4
    bl      func_ov107_020ca414
    mov     r7, r0
    cmp     r7, #0
    ble     _L_03a8
    cmp     r7, #0
    mvn     r8, #0x80000000
    mov     r6, #0
    ble     _L_0298
    add     r9, sp, #0xc
    add     r4, sp, #0
    add     r11, sp, #0x3c
_L_0258:
    mov     r0, r11
    mov     r1, r9
    mov     r2, r4
    bl      VEC_Subtract
    mov     r0, r4
    bl      VEC_Mag
    cmp     r0, r8
    bge     _L_0288
    mov     r8, r0
    mov     r0, r4
    add     r1, sp, #0x5c
    bl      func_01ff8d18
_L_0288:
    add     r6, r6, #1
    cmp     r6, r7
    add     r9, r9, #0xc
    blt     _L_0258
_L_0298:
    ldr     r1, [sp, #0x5c]
    rsb     r0, r8, #0x1200
    smull   r2, r6, r1, r0
    adds    r7, r2, #0x800
    ldr     r2, [sp, #0x60]
    ldr     r8, [r5, #4]
    smull   r4, r3, r2, r0
    adc     r2, r6, #0
    mov     r6, r7, lsr #0xc
    adds    r4, r4, #0x800
    ldr     r7, [r8]
    orr     r6, r6, r2, lsl #20
    add     r2, r7, r6
    str     r2, [sp, #0x68]
    ldr     r1, [sp, #0x64]
    ldr     r6, [r5, #4]
    smull   r2, r0, r1, r0
    adc     r3, r3, #0
    adds    r1, r2, #0x800
    mov     r2, r4, lsr #0xc
    ldr     r4, [r6, #4]
    orr     r2, r2, r3, lsl #20
    add     r2, r4, r2
    str     r2, [sp, #0x6c]
    ldr     r2, [r5, #4]
    adc     r0, r0, #0
    mov     r1, r1, lsr #0xc
    ldr     r2, [r2, #8]
    orr     r1, r1, r0, lsl #20
    add     r0, r2, r1
    str     r0, [sp, #0x70]
    ldr     r0, [r5]
    add     r1, sp, #0x68
    bl      func_ov107_020c5c54
    ldr     r1, [pc, #0x120]
    add     r0, sp, #0x4c
    add     r2, sp, #0x5c
    bl      func_0202ed60
    ldr     r0, [r5]
    add     r1, sp, #0x4c
    add     r0, r0, #0xa0
    bl      func_0203c9d0
    ldr     r4, [r5]
    mov     r0, r10
    ldrh    r1, [r4, #0x60]
    mov     r2, #0
    bic     r3, r1, #0xff00
    mov     r1, r1, lsl #0x10
    mov     r1, r1, lsr #0x18
    orr     r1, r1, #0x40
    mov     r1, r1, lsl #0x18
    orr     r1, r3, r1, lsr #16
    strh    r1, [r4, #0x60]
    ldr     r4, [r5]
    ldrh    r1, [r4, #0x60]
    bic     r3, r1, #0xff00
    mov     r1, r1, lsl #0x10
    mov     r1, r1, lsr #0x18
    bic     r1, r1, #0x1e
    mov     r1, r1, lsl #0x10
    mov     r1, r1, lsr #0x10
    mov     r1, r1, lsl #0x18
    orr     r1, r3, r1, lsr #16
    strh    r1, [r4, #0x60]
    ldrsb   r1, [r10, #0x20]
    bl      func_0203c634
    add     sp, sp, #0x80
    ldmfd   sp!, {r3, r4, r5, r6, r7, r8, r9, r10, r11, pc}
_L_03a8:
    ldr     r2, [r5]
    ldrb    r0, [r2, #0x17a]
    mov     r0, r0, lsl #0x1f
    movs    r0, r0, lsr #0x1f
    beq     _L_0418
    ldr     r1, [pc, #0x84]
    add     r0, sp, #0x4c
    add     r2, r2, #0x124
    bl      func_0202ed60
    ldr     r0, [r5]
    add     r1, sp, #0x4c
    add     r0, r0, #0xa0
    bl      func_0203c9d0
    ldr     r4, [r5]
    mov     r0, r10
    ldrh    r3, [r4, #0x60]
    mov     r2, #0
    mov     r1, r3, lsl #0x10
    mov     r1, r1, lsr #0x18
    orr     r1, r1, #0x40
    bic     r3, r3, #0xff00
    mov     r1, r1, lsl #0x18
    orr     r1, r3, r1, lsr #16
    strh    r1, [r4, #0x60]
    ldrsb   r1, [r10, #0x20]
    bl      func_0203c634
    add     sp, sp, #0x80
    ldmfd   sp!, {r3, r4, r5, r6, r7, r8, r9, r10, r11, pc}
_L_0418:
    ldrh    r1, [r2, #0x60]
    mov     r0, r1, lsl #0x10
    mov     r0, r0, lsr #0x18
    bic     r0, r0, #0x48
    mov     r0, r0, lsl #0x10
    mov     r0, r0, lsr #0x10
    bic     r1, r1, #0xff00
    mov     r0, r0, lsl #0x18
    orr     r0, r1, r0, lsr #16
    strh    r0, [r2, #0x60]
    add     sp, sp, #0x80
    ldmfd   sp!, {r3, r4, r5, r6, r7, r8, r9, r10, r11, pc}
    dcd     data_02042264
}
