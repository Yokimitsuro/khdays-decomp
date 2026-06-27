extern void VEC_DotProduct(void);
extern void VEC_Subtract(void);
extern int data_0203d210;
extern int data_02041dc8;
extern int data_02042264;
extern void func_01ff8d18(void);
extern void func_01ffa724(void);
extern void func_020050b4(void);
extern void func_0202f188(void);
extern void func_0203c9d0(void);
extern void func_0203d040(void);
extern void func_ov107_020c5af8(void);
extern void func_ov107_020c5c54(void);

asm void func_ov234_020cca84(void)
{
    stmfd   sp!, {r4, r5, lr}
    sub     sp, sp, #0x4c
    mov     r5, r0
    ldmia   r5, {r0, r4}
    ldr     r1, [r0, #0x2c]
    mov     r0, #0x5a
    mul     ip, r1, r0
    ldr     r1, =0x66666667
    ldr     r3, [r4, #0x68]
    smull   r0, r2, r1, ip
    mov     r0, ip, lsr #0x1f
    cmp     r3, #0
    add     r2, r0, r2, asr #2
    ldrne   r0, [r4, #0x38]
    bne     _L4c
    ldr     r0, [r4, #0x34]
    ldr     r1, [r4, #0x38]
    mov     r3, #0
    bl      func_0203d040
_L4c:
    str     r0, [r4, #0x34]
    ldr     r2, [r4, #0x34]
    ldr     r1, =data_02042264
    add     r0, sp, #0x3c
    bl      func_0202f188
    ldr     r0, [r4]
    add     r1, sp, #0x3c
    add     r0, r0, #0xa0
    bl      func_0203c9d0
    ldr     r0, [r4]
    ldrb    r0, [r0, #0x17a]
    mov     r0, r0, lsl #0x1e
    movs    r0, r0, lsr #0x1f
    moveq   r0, #0
    streq   r0, [r4, #0x6c]
    ldr     r2, [r4]
    ldrb    r0, [r2, #0x17a]
    mov     r1, r0, lsl #0x1e
    movs    r1, r1, lsr #0x1f
    beq     _L1d8
    mov     r0, r0, lsl #0x1f
    movs    r0, r0, lsr #0x1f
    ldreq   r0, [r4, #0x6c]
    cmpeq   r0, #0
    bne     _L1d8
    add     r0, r2, #0x114
    add     r3, sp, #0x30
    ldmia   r0, {r0, r1, r2}
    stmia   r3, {r0, r1, r2}
    ldr     r2, [r4, #0x34]
    ldr     r0, =0x60db9391
    ldr     r1, =0x000028be
    umull   lr, ip, r2, r0
    mla     ip, r2, r1, ip
    mov     r1, r2, asr #0x1f
    mla     ip, r1, r0, ip
    adds    r0, lr, #0
    adc     r0, ip, #0x800
    mov     r0, r0, lsl #4
    mov     r0, r0, lsr #0x10
    mov     r0, r0, asr #4
    mov     r2, r0, lsl #1
    add     r0, r2, #1
    mov     ip, #0
    ldr     r1, =data_0203d210
    mov     r2, r2, lsl #1
    ldrsh   r2, [r1, r2]
    mov     r0, r0, lsl #1
    ldrsh   r1, [r1, r0]
    rsb     lr, r2, #0
    add     r0, sp, #0x24
    rsb     r2, r1, #0
    mov     r1, r3
    str     lr, [sp, #0x24]
    str     ip, [sp, #0x28]
    str     r2, [sp, #0x2c]
    bl      VEC_DotProduct
    add     r1, sp, #0x30
    add     r2, sp, #0x18
    mov     r0, r0, lsl #1
    bl      func_01ffa724
    add     r0, sp, #0x18
    add     r1, sp, #0x24
    mov     r2, r0
    bl      VEC_Subtract
    add     r0, sp, #0x18
    mov     r1, r0
    bl      func_01ff8d18
    ldr     r0, [sp, #0x18]
    ldr     r1, [sp, #0x20]
    bl      func_020050b4
    str     r0, [r4, #0x3c]
    add     ip, r4, #0x10
    add     r3, sp, #0xc
    ldmia   ip, {r0, r1, r2}
    stmia   r3, {r0, r1, r2}
    mov     r0, ip
    mov     r1, ip
    bl      func_01ff8d18
    add     r1, sp, #0x18
    add     r2, sp, #0
    bl      func_01ffa724
    ldr     r0, [sp]
    str     r0, [r4, #0x10]
    ldr     r0, [sp, #0x10]
    str     r0, [r4, #0x14]
    ldr     r1, [sp, #8]
    str     r1, [r4, #0x18]
    ldr     r0, [r4, #0x10]
    bl      func_020050b4
    str     r0, [r4, #0x38]
    str     r0, [r4, #0x34]
    ldr     r0, [r4]
    ldr     r3, [r4, #8]
    mov     r1, #0x178
    mov     r2, #4
    bl      func_ov107_020c5af8
    mov     r0, #1
    str     r0, [r4, #0x6c]
_L1d8:
    ldr     r0, [r4]
    add     ip, r4, #0x10
    add     r3, r0, #0xf0
    ldmia   ip, {r0, r1, r2}
    stmia   r3, {r0, r1, r2}
    ldr     r0, [r4]
    ldrb    r0, [r0, #0x17a]
    mov     r0, r0, lsl #0x1f
    movs    r0, r0, lsr #0x1f
    beq     _L214
    ldr     r0, [r4, #0x64]
    cmp     r0, #0
    ldreq   r0, =data_02041dc8
    ldmeqia r0, {r0, r1, r2}
    stmeqia ip, {r0, r1, r2}
_L214:
    ldr     r1, [r4, #0x10]
    mov     r0, #0xd00
    umull   r3, r2, r1, r0
    mov     r1, r1, asr #0x1f
    adds    r3, r3, #0x800
    mla     r2, r1, r0, r2
    adc     r1, r2, #0
    mov     r2, r3, lsr #0xc
    orr     r2, r2, r1, lsl #20
    str     r2, [r4, #0x10]
    ldr     r1, [r4, #0x18]
    mov     r2, #0
    umull   ip, r3, r1, r0
    mov     r1, r1, asr #0x1f
    adds    ip, ip, #0x800
    mla     r3, r1, r0, r3
    adc     r0, r3, #0
    mov     r1, ip, lsr #0xc
    orr     r1, r1, r0, lsl #20
    str     r1, [r4, #0x18]
    ldr     r0, [r4, #8]
    mov     r1, #0x800
    ldr     r0, [r0, #4]
    cmp     r0, #0x19000
    ble     _L2a4
    ldr     r3, [r4, #0x18]
    mov     r0, #0xc00
    umull   lr, ip, r3, r0
    mla     ip, r3, r2, ip
    mov     r3, r3, asr #0x1f
    adds    r1, lr, r1
    mla     ip, r3, r0, ip
    adc     r0, ip, r2
    mov     r1, r1, lsr #0xc
    orr     r1, r1, r0, lsl #20
    str     r1, [r4, #0x18]
_L2a4:
    ldr     r2, [r4, #0x14]
    cmp     r2, #0x100
    ble     _L2d0
    ldr     r0, [r4, #0x5c]
    smull   r1, r0, r2, r0
    adds    r1, r1, #0x800
    adc     r0, r0, #0
    mov     r1, r1, lsr #0xc
    orr     r1, r1, r0, lsl #20
    str     r1, [r4, #0x14]
    b       _L2e4
_L2d0:
    ldr     r0, [r4, #0x54]
    cmp     r2, r0
    ldrgt   r0, [r4, #0x58]
    addgt   r0, r2, r0
    strgt   r0, [r4, #0x14]
_L2e4:
    ldr     r0, [r5]
    ldr     r2, [r4, #0x44]
    ldr     r1, [r0, #0x2c]
    ldr     r0, =0x00077880
    add     r1, r2, r1
    str     r1, [r4, #0x44]
    cmp     r1, r0
    ble     _L318
    ldr     r0, [r4]
    add     r1, r4, #0x1c
    bl      func_ov107_020c5c54
    mov     r0, #0
    str     r0, [r4, #0x44]
_L318:
    ldr     r1, [r4, #0x48]
    cmp     r1, #0
    movle   r0, #0
    ble     _L334
    ldr     r0, [r5]
    ldr     r0, [r0, #0x2c]
    sub     r0, r1, r0
_L334:
    str     r0, [r4, #0x48]
    ldr     r0, [r4]
    ldr     r0, [r0, #0x3b8]
    cmp     r0, #0x1e
    bge     _L374
    mov     r0, #0x280
    rsb     r0, r0, #0
    str     r0, [r4, #0x54]
    add     r0, r0, #0x248
    str     r0, [r4, #0x58]
    mov     r0, #0xe00
    str     r0, [r4, #0x5c]
    mov     r0, #0x400
    add     sp, sp, #0x4c
    str     r0, [r4, #0x60]
    ldmfd   sp!, {r4, r5, pc}
_L374:
    cmp     r0, #0x32
    bge     _L3a8
    mov     r0, #0x2c0
    rsb     r0, r0, #0
    str     r0, [r4, #0x54]
    add     r0, r0, #0x284
    str     r0, [r4, #0x58]
    mov     r0, #0xdc0
    str     r0, [r4, #0x5c]
    mov     r0, #0x480
    add     sp, sp, #0x4c
    str     r0, [r4, #0x60]
    ldmfd   sp!, {r4, r5, pc}
_L3a8:
    cmp     r0, #0x64
    bge     _L3dc
    mov     r0, #0x300
    rsb     r0, r0, #0
    str     r0, [r4, #0x54]
    add     r0, r0, #0x2c0
    str     r0, [r4, #0x58]
    mov     r0, #0xd90
    str     r0, [r4, #0x5c]
    mov     r0, #0x500
    add     sp, sp, #0x4c
    str     r0, [r4, #0x60]
    ldmfd   sp!, {r4, r5, pc}
_L3dc:
    cmp     r0, #0x96
    bge     _L410
    mov     r0, #0x340
    rsb     r0, r0, #0
    str     r0, [r4, #0x54]
    add     r0, r0, #0x2fc
    str     r0, [r4, #0x58]
    mov     r0, #0xd60
    str     r0, [r4, #0x5c]
    mov     r0, #0x600
    add     sp, sp, #0x4c
    str     r0, [r4, #0x60]
    ldmfd   sp!, {r4, r5, pc}
_L410:
    mov     r0, #0x380
    rsb     r0, r0, #0
    str     r0, [r4, #0x54]
    add     r0, r0, #0x338
    str     r0, [r4, #0x58]
    mov     r0, #0xd30
    str     r0, [r4, #0x5c]
    mov     r0, #0x700
    str     r0, [r4, #0x60]
    add     sp, sp, #0x4c
    ldmfd   sp!, {r4, r5, pc}
}
