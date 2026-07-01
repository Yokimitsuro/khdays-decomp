extern void func_0203d040(void);
extern void func_0202f188(void);
extern void func_0203c9d0(void);
extern void func_01ffa724(void);
extern void func_ov107_020c5c54(void);
extern int data_02042264;

asm void func_ov301_020cc458(void *r0)
{
    stmfd   sp!, {r4, r5, lr}
    sub     sp, sp, #0x1c
    ldr     r2, [r0]
    mov     r1, #0x5a
    ldr     r2, [r2, #0x2c]
    ldr     ip, [pc, #0x1b8]
    mul     r5, r2, r1
    ldr     r4, [r0, #4]
    smull   r0, r2, ip, r5
    ldr     lr, [pc, #0x1ac]
    ldr     r1, [pc, #0x1ac]
    mov     r3, #0
    mov     r0, r5, lsr #0x1f
    str     lr, [sp]
    str     r3, [sp, #4]
    str     r1, [sp, #8]
    ldr     r1, [r4, #0x40]
    add     r2, r0, r2, asr #2
    cmp     r1, #0
    ldrne   r0, [r4, #0x28]
    bne     _L_60
    ldr     r0, [r4, #0x24]
    ldr     r1, [r4, #0x28]
    bl      func_0203d040
_L_60:
    str     r0, [r4, #0x24]
    ldr     r2, [r4, #0x24]
    ldr     r1, [pc, #0x170]
    add     r0, sp, #0xc
    bl      func_0202f188
    ldr     r0, [r4]
    add     r1, sp, #0xc
    add     r0, r0, #0xa0
    bl      func_0203c9d0
    ldr     r0, [r4]
    ldrb    r0, [r0, #0x17a]
    mov     r0, r0, lsl #0x1e
    movs    r0, r0, lsr #0x1f
    beq     _L_c4
    ldr     r1, [r4, #0xc]
    mvn     r0, #0
    mul     r2, r1, r0
    str     r2, [r4, #0xc]
    ldr     r2, [r4, #0x14]
    add     r1, r4, #0xc
    mul     r3, r2, r0
    mov     r2, r1
    mov     r0, #0x1500
    str     r3, [r4, #0x14]
    bl      func_01ffa724
_L_c4:
    ldr     r1, [r4]
    add     r0, r4, #0xc
    add     r3, r1, #0xf0
    ldmia   r0, {r0, r1, r2}
    stmia   r3, {r0, r1, r2}
    ldr     r1, [r4, #0xc]
    mov     r0, #0xd00
    umull   r3, r2, r1, r0
    mov     r1, r1, asr #0x1f
    adds    r3, r3, #0x800
    mla     r2, r1, r0, r2
    adc     r1, r2, #0
    mov     r2, r3, lsr #0xc
    orr     r2, r2, r1, lsl #20
    str     r2, [r4, #0xc]
    ldr     r1, [r4, #0x14]
    mov     r2, #0
    umull   ip, r3, r1, r0
    mov     r1, r1, asr #0x1f
    adds    ip, ip, #0x800
    mla     r3, r1, r0, r3
    adc     r0, r3, #0
    mov     r1, ip, lsr #0xc
    orr     r1, r1, r0, lsl #20
    str     r1, [r4, #0x14]
    ldr     r3, [r4, #0x10]
    mov     r1, #0x800
    cmp     r3, #0x30
    ble     _L_164
    mov     r0, #0xe00
    umull   lr, ip, r3, r0
    mla     ip, r3, r2, ip
    mov     r3, r3, asr #0x1f
    adds    r1, lr, r1
    mla     ip, r3, r0, ip
    adc     r0, ip, r2
    mov     r1, r1, lsr #0xc
    orr     r1, r1, r0, lsl #20
    str     r1, [r4, #0x10]
    b       _L_174
_L_164:
    sub     r0, r1, #0xb80
    cmp     r3, r0
    subgt   r0, r3, #0x34
    strgt   r0, [r4, #0x10]
_L_174:
    ldr     r3, [r4]
    add     r1, sp, #0
    ldrh    r2, [r3, #0x60]
    mov     r0, r2, lsl #0x10
    mov     r0, r0, lsr #0x18
    orr     r0, r0, #4
    bic     r2, r2, #0xff00
    mov     r0, r0, lsl #0x18
    orr     r0, r2, r0, lsr #16
    strh    r0, [r3, #0x60]
    ldr     r0, [r4]
    ldr     r3, [r0, #0x388]
    ldr     r2, [r3, #8]
    mov     r0, r2, lsl #0x18
    mov     r0, r0, lsr #0x18
    orr     r0, r0, #2
    bic     r2, r2, #0xff
    and     r0, r0, #0xff
    orr     r0, r2, r0
    str     r0, [r3, #8]
    ldr     r0, [r4]
    bl      func_ov107_020c5c54
    add     sp, sp, #0x1c
    ldmfd   sp!, {r4, r5, pc}
    dcd     0x66666667
    dcd     0x00000f2f
    dcd     0x0000eea3
    dcd     data_02042264
}
