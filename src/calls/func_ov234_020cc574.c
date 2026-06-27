extern int data_0203d210;
extern int data_ov234_020cd104;
extern void func_01ff8d18(void);
extern void func_01ffa724(void);
extern void func_020050b4(void);
extern void func_02023e80(void);
extern void func_02023eb4(void);
extern void func_ov107_020c0b90(void);
extern void func_ov107_020c5af8(void);
extern void func_ov107_020c89e8(void);

asm void func_ov234_020cc574(void)
{
    stmfd   sp!, {r4, r5, r6, r7, r8, lr}
    sub     sp, sp, #0x18
    ldr     r3, =data_ov234_020cd104
    mov     r7, r0
    ldrb    r8, [r3]
    ldrb    lr, [r3, #1]
    ldrb    ip, [r3, #2]
    ldrb    r3, [r3, #3]
    mov     r5, r2
    mov     r6, r1
    ldr     r4, [r7, #0x214]
    mov     r1, r5
    strb    r8, [sp, #0xa]
    strb    lr, [sp, #0xb]
    strb    ip, [sp, #8]
    strb    r3, [sp, #9]
    bl      func_ov107_020c89e8
    str     r0, [r5, #0x28]
    add     r0, r7, #0x200
    ldrsh   r0, [r0, #0x1a]
    cmp     r0, #0
    addle   sp, sp, #0x18
    movle   r0, #0
    ldmlefd sp!, {r4, r5, r6, r7, r8, pc}
    ldr     r0, [r5, #0x28]
    cmp     r0, #0
    addle   sp, sp, #0x18
    movle   r0, #1
    ldmlefd sp!, {r4, r5, r6, r7, r8, pc}
    ldr     r0, [r4, #0x48]
    cmp     r0, #0
    addgt   sp, sp, #0x18
    movgt   r0, #0
    ldmgtfd sp!, {r4, r5, r6, r7, r8, pc}
    ldr     r0, [r5]
    mov     r1, r0, lsl #0x10
    mov     r1, r1, lsr #0x10
    tst     r1, #0x22
    beq     _Ld8
    tst     r1, #8
    beq     _Lb8
    tst     r1, #0x80
    beq     _Lb8
    mov     r0, r0, lsr #0x10
    cmp     r0, #0x80
    beq     _Ld8
_Lb8:
    ldrb    r1, [r4, #0x72]
    add     r0, sp, #8
    ldr     r3, [r4, #8]
    ldrb    r2, [r0, r1]
    mov     r0, r7
    mov     r1, #0x178
    bl      func_ov107_020c5af8
    b       _Lf4
_Ld8:
    ldrb    r1, [r4, #0x72]
    add     r0, sp, #0xa
    ldr     r3, [r4, #8]
    ldrb    r2, [r0, r1]
    mov     r0, r7
    mov     r1, #0x178
    bl      func_ov107_020c5af8
_Lf4:
    str     r6, [r4, #0xc]
    add     r0, r5, #4
    add     r3, r4, #0x28
    ldmia   r0, {r0, r1, r2}
    stmia   r3, {r0, r1, r2}
    ldr     r0, [r5]
    mov     r0, r0, lsl #0x10
    mov     r0, r0, lsr #0x10
    tst     r0, #0x20
    beq     _L148
    mov     r1, r3
    mov     r2, r3
    mov     r0, #0x2000
    bl      func_01ffa724
    mov     r0, #0x3000
    str     r0, [r4, #0x2c]
    ldr     r0, [r4, #0x64]
    cmp     r0, #0
    moveq   r0, #1
    streq   r0, [r4, #0x64]
    b       _L178
_L148:
    ldr     r0, [r4, #0x64]
    cmp     r0, #0
    bne     _L170
    ldr     r0, [r4, #0x60]
    str     r0, [r4, #0x2c]
    ldr     r0, [r4, #0x64]
    cmp     r0, #0
    moveq   r0, #1
    streq   r0, [r4, #0x64]
    b       _L178
_L170:
    mov     r0, #0x200
    str     r0, [r4, #0x2c]
_L178:
    ldr     r0, [r4, #8]
    add     r3, r4, #0x10
    ldr     r0, [r0, #4]
    cmp     r0, #0x19000
    movgt   r0, #0x100
    strgt   r0, [r4, #0x2c]
    mov     r0, #0
    str     r0, [r4, #0x4c]
    str     r0, [r4, #0x44]
    add     r0, r4, #0x28
    ldmia   r0, {r0, r1, r2}
    stmia   r3, {r0, r1, r2}
    ldr     r0, [r4, #0x28]
    ldr     r1, [r4, #0x30]
    bl      func_020050b4
    str     r0, [r4, #0x38]
    str     r0, [r4, #0x34]
    ldr     r0, [r5]
    mov     r0, r0, lsl #0x10
    mov     r0, r0, lsr #0x10
    tst     r0, #0x20
    beq     _L280
    add     r1, sp, #0xc
    add     r0, r4, #0x28
    bl      func_01ff8d18
    mov     r0, #0x64
    bl      func_02023eb4
    cmp     r0, #0x32
    ldr     r0, =0x00001922
    bhs     _L200
    bl      func_02023e80
    ldr     r1, [r4, #0x34]
    sub     r0, r1, r0
    b       _L20c
_L200:
    bl      func_02023e80
    ldr     r1, [r4, #0x34]
    add     r0, r1, r0
_L20c:
    str     r0, [r4, #0x38]
    str     r0, [r4, #0x34]
    ldr     r2, [r4, #0x34]
    ldr     r0, =0x60db9391
    ldr     r1, =0x000028be
    umull   r5, r3, r2, r0
    mla     r3, r2, r1, r3
    mov     r1, r2, asr #0x1f
    mla     r3, r1, r0, r3
    adds    r0, r5, #0
    adc     r0, r3, #0x800
    mov     r0, r0, lsl #4
    mov     r0, r0, lsr #0x10
    mov     r0, r0, asr #4
    mov     r1, r0, lsl #1
    add     r0, r1, #1
    ldr     r2, =data_0203d210
    mov     r1, r1, lsl #1
    mov     r0, r0, lsl #1
    ldrsh   r3, [r2, r0]
    ldrsh   r1, [r2, r1]
    ldr     r5, [sp, #0x10]
    mov     r0, #0xd00
    str     r1, [r4, #0x10]
    add     r1, r4, #0x10
    str     r5, [r4, #0x14]
    mov     r2, r1
    str     r3, [r4, #0x18]
    bl      func_01ffa724
_L280:
    ldrb    r0, [r4, #0x72]
    sub     r3, sp, #8
    eor     r0, r0, #1
    strb    r0, [r4, #0x72]
    ldr     r0, [r4, #0xc]
    ldr     r5, [r4]
    ldrb    r1, [r0, #0x1b4]
    add     r0, r5, #0x74
    str     r1, [sp, #4]
    ldmia   r0, {r0, r1, r2}
    stmia   r3, {r0, r1, r2}
    mov     r0, r5
    mov     r1, #2
    ldmia   r3, {r2, r3}
    bl      func_ov107_020c0b90
    ldr     r0, [r4, #0x64]
    cmp     r0, #0
    ldrne   r0, [r4]
    movne   r1, #5
    strneb  r1, [r0, #0x1c7]
    mov     r0, #1
    add     sp, sp, #0x18
    ldmfd   sp!, {r4, r5, r6, r7, r8, pc}
}
