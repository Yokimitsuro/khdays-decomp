extern void func_01fffd70(void);
extern void func_ov107_020c3504(void);
extern void VEC_Subtract(void);
extern void func_01ff8d18(void);
extern void func_ov107_020c5cfc(void);
extern void func_01ffa724(void);
extern void VEC_Add(void);
extern void func_ov107_020c0b90(void);
extern void func_01fffd8c(void);
extern void func_ov107_020c9b68(void);
extern void func_02031384(void);
extern void func_0203c634(void);

asm void func_ov288_020d4c98(void)
{
    stmfd   sp!, {r3, r4, r5, r6, r7, r8, sb, r10, r11, lr}
    sub     sp, sp, #0x78
    mov     r11, r0
    ldmia   r11, {r0, r5}
    ldr     r1, [r5, #0x34]
    ldr     r0, [r0, #0x2c]
    add     r0, r1, r0
    str     r0, [r5, #0x34]
    cmp     r0, #0x800
    bge     _L_02fc
    ldr     r2, [r5]
    ldr     r1, [r2, #0x38c]
    cmp     r1, #0
    bne     _L_004c
    addne   sp, sp, #0x78
    ldmnefd sp!, {r3, r4, r5, r6, r7, r8, sb, r10, r11, pc}
    cmp     r0, #0x200
    addlt   sp, sp, #0x78
    ldmltfd sp!, {r3, r4, r5, r6, r7, r8, sb, r10, r11, pc}
_L_004c:
    ldr     r0, [r2, #4]
    cmp     r1, #0
    str     r0, [sp, #0xc]
    add     r0, r2, #0x74
    add     r4, sp, #0x68
    ldmia   r0, {r0, r1, r2, r3}
    stmia   r4, {r0, r1, r2, r3}
    ldr     r0, [r5]
    movne   r6, #1
    moveq   r6, #0
    ldr     r0, [r0, #0x38c]
    ldr     r1, [sp, #0x74]
    cmp     r0, #0
    movne   r2, #0x6000
    moveq   r2, #0x1000
    smull   r3, r2, r1, r2
    ldr     r0, [sp, #0xc]
    adds    r3, r3, #0x800
    adc     r1, r2, #0
    mov     r2, r3, lsr #0xc
    orr     r2, r2, r1, lsl #20
    add     r0, r0, #0x80
    and     r4, r6, #0xff
    str     r2, [sp, #0x74]
    bl      func_01fffd70
    cmp     r0, #0
    moveq   r7, #0
    ldrne   r7, [r0]
    cmp     r7, #0
    addeq   sp, sp, #0x78
    ldmeqfd sp!, {r3, r4, r5, r6, r7, r8, sb, r10, r11, pc}
    mov     r0, #6
    mul     r0, r4, r0
    str     r0, [sp, #8]
_L_00d4:
    ldr     r0, [r5]
    cmp     r7, r0
    beq     _L_02d4
    ldrh    r0, [r7, #0x60]
    mov     r0, r0, lsl #0x18
    mov     r0, r0, lsr #0x18
    tst     r0, #1
    beq     _L_02d4
    add     r0, r7, #0x100
    ldrh    r0, [r0, #0xac]
    tst     r0, #3
    bne     _L_02d4
    ldrh    r1, [r7, #2]
    ldr     r0, [r5, #0x4c]
    ldr     r2, [r5, #0x50]
    mov     r3, r0, lsr r1
    rsb     r0, r1, #0x20
    orr     r3, r3, r2, lsl r0
    sub     r0, r1, #0x20
    orr     r3, r3, r2, lsr r0
    mov     r0, #0
    and     r0, r0, r2, lsr r1
    and     r1, r3, #1
    cmp     r0, #0
    cmpeq   r1, #0
    bne     _L_02d4
    add     r0, r7, #0x22c
    bl      func_01fffd70
    movs    r6, r0
    beq     _L_02d4
    mov     r8, #0x10000
    sub     sb, sp, #8
    rsb     r8, r8, #0
    mov     r10, #1
    add     r4, sp, #0x30
    add     r11, sp, #0x40
_L_0164:
    ldr     r0, [r6]
    add     r1, sp, #0x68
    mov     r2, #0
    bl      func_ov107_020c3504
    cmp     r0, #0
    beq     _L_02c4
    mov     r0, #0
    add     r2, sp, #0x3c
    mov     r1, r0
    stmia   r2!, {r0, r1}
    stmia   r2!, {r0, r1}
    stmia   r2!, {r0, r1}
    stmia   r2!, {r0, r1}
    stmia   r2!, {r0, r1}
    str     r0, [r2]
    ldr     r1, [r5]
    add     r0, r7, #0x74
    mov     r2, r11
    add     r1, r1, #0x74
    bl      VEC_Subtract
    mov     r0, r11
    mov     r1, r11
    bl      func_01ff8d18
    ldr     r0, [sp, #0x3c]
    ldr     r1, [sp, #0x4c]
    and     r2, r0, r8
    orr     lr, r2, #4
    and     ip, r1, r8
    ldmia   r11, {r0, r1, r2}
    stmia   r4, {r0, r1, r2}
    orr     lr, lr, #0x8000
    str     lr, [sp, #0x3c]
    ldr     r3, [sp, #0x50]
    ldr     r2, [r5]
    ldr     r1, [sp, #8]
    and     r3, r3, r8
    add     r1, r1, r2
    add     r1, r1, #0x200
    ldrh    r1, [r1, #0x90]
    mov     r0, r7
    add     r2, sp, #0x3c
    orr     r1, ip, r1
    str     r1, [sp, #0x4c]
    ldr     r1, [r5]
    ldr     r1, [r1, #0x258]
    mov     r1, r1, lsl #0x10
    orr     r1, r3, r1, lsr #16
    str     r1, [sp, #0x50]
    ldr     r3, [r5]
    mov     r1, r1, lsl #0x10
    ldrb    r3, [r3, #0x19c]
    mov     r3, r3, lsl #0x10
    orr     r1, r3, r1, lsr #16
    str     r6, [sp, #0x54]
    str     r1, [sp, #0x50]
    ldr     r1, [r5, #8]
    bl      func_ov107_020c5cfc
    cmp     r0, #0
    beq     _L_02c4
    ldrh    r0, [r7, #2]
    ldr     r3, [r5, #0x4c]
    ldr     r6, [r5, #0x50]
    orr     r3, r3, r10, lsl r0
    str     r3, [r5, #0x4c]
    mov     r3, #0
    mov     r3, r3, lsl r0
    rsb     ip, r0, #0x20
    orr     r3, r3, r10, lsr ip
    sub     r0, r0, #0x20
    orr     r3, r3, r10, lsl r0
    orr     r0, r6, r3
    str     r0, [r5, #0x50]
    ldr     r0, [sp, #0x74]
    mov     r1, r4
    mov     r2, r4
    bl      func_01ffa724
    mov     r0, r4
    add     r1, sp, #0x68
    mov     r2, r4
    bl      VEC_Add
    mov     r0, #0
    str     r0, [sp, #4]
    ldmia   r4, {r0, r1, r2}
    stmia   sb, {r0, r1, r2}
    ldr     r0, [r5]
    mov     r1, #0
    ldmia   sb, {r2, r3}
    bl      func_ov107_020c0b90
_L_02c4:
    add     r0, r7, #0x22c
    bl      func_01fffd8c
    movs    r6, r0
    bne     _L_0164
_L_02d4:
    ldr     r0, [sp, #0xc]
    add     r0, r0, #0x80
    bl      func_01fffd8c
    cmp     r0, #0
    moveq   r7, #0
    ldrne   r7, [r0]
    cmp     r7, #0
    bne     _L_00d4
    add     sp, sp, #0x78
    ldmfd   sp!, {r3, r4, r5, r6, r7, r8, sb, r10, r11, pc}
_L_02fc:
    ldrb    r0, [r5, #0x54]
    cmp     r0, #0
    bne     _L_04a4
    ldr     r0, [r5, #8]
    cmp     r0, #0
    beq     _L_04a4
    mov     r10, #0
    add     r0, sp, #0x20
    strh    r10, [r0]
    strh    r10, [r0, #2]
    strh    r10, [r0, #4]
    strh    r10, [r0, #6]
    strh    r10, [r0, #8]
    strh    r10, [r0, #0xa]
    strh    r10, [r0, #0xc]
    ldr     r0, [r5, #8]
    mov     sb, #4
    ldr     r0, [r0, #0x18c]
    mov     r6, r10
    str     r0, [sp, #0x10]
    mov     r4, #1
    mov     r8, r10
    mov     r7, r10
_L_0358:
    ldr     r0, [r5, #0x4c]
    ldr     r1, [r5, #0x50]
    mov     r2, r0, lsr sb
    rsb     r0, sb, #0x20
    orr     r2, r2, r1, lsl r0
    sub     r0, sb, #0x20
    orr     r2, r2, r1, lsr r0
    and     r0, r6, r1, lsr sb
    cmp     r0, r8
    and     r0, r2, r4
    cmpeq   r0, r7
    beq     _L_03ac
    mov     r0, sb, lsl #0x10
    mov     r0, r0, lsr #0x10
    bl      func_ov107_020c9b68
    cmp     r0, #0
    beq     _L_03a8
    ldrb    r0, [r0, #0x19c]
    cmp     r0, #0x6b
    beq     _L_03ac
_L_03a8:
    add     r10, r10, #1
_L_03ac:
    add     sb, sb, #1
    cmp     sb, #0x40
    blt     _L_0358
    ldr     r0, [r5]
    mov     r3, #5
    ldrh    r4, [r0, #2]
    ldr     r0, [sp, #0x10]
    mov     r2, #3
    add     r1, r0, #0x2000
    add     r0, sp, #0x20
    strh    r4, [r0]
    strb    r3, [r0, #2]
    strb    r2, [r0, #3]
    ldr     r0, [r5]
    ldr     r7, [r0, #0x74]
    mov     r4, r7, lsr #0x10
    mov     r3, r7, lsr #0x18
    mov     r2, r7, lsr #8
    and     r4, r4, #0x7f
    and     r3, r3, #0x80
    orr     r3, r4, r3
    strb    r3, [sp, #0x25]
    strb    r2, [sp, #0x26]
    strb    r7, [sp, #0x27]
    ldr     r6, [r0, #0x78]
    str     r7, [sp, #0x14]
    mov     r4, r6, lsr #0x10
    mov     r3, r6, lsr #0x18
    mov     r2, r6, lsr #8
    and     r4, r4, #0x7f
    and     r3, r3, #0x80
    orr     r3, r4, r3
    strb    r3, [sp, #0x28]
    strb    r2, [sp, #0x29]
    strb    r6, [sp, #0x2a]
    ldr     r4, [r0, #0x7c]
    str     r6, [sp, #0x18]
    mov     r3, r4, lsr #0x10
    mov     r2, r4, lsr #0x18
    mov     r0, r4, lsr #8
    and     r3, r3, #0x7f
    and     r2, r2, #0x80
    orr     r2, r3, r2
    strb    r2, [sp, #0x2b]
    strb    r0, [sp, #0x2c]
    strb    r4, [sp, #0x2d]
    ldrb    r1, [r1, #0xab3]
    str     r4, [sp, #0x1c]
    cmp     r1, #8
    movhi   r1, #8
    bhi     _L_0480
    cmp     r1, #1
    movlo   r1, #1
_L_0480:
    add     r0, r10, #1
    mul     r3, r0, r1
    add     r1, sp, #0x20
    mov     r0, #1
    mov     r2, #0xe
    strb    r3, [sp, #0x24]
    bl      func_02031384
    mov     r0, #1
    strb    r0, [r5, #0x54]
_L_04a4:
    ldr     r0, [r5, #4]
    ldrb    r0, [r0, #0xad]
    cmp     r0, #0
    addne   sp, sp, #0x78
    ldmnefd sp!, {r3, r4, r5, r6, r7, r8, sb, r10, r11, pc}
    ldr     r0, [r5]
    mov     r1, #3
    strb    r1, [r0, #0x1c7]
    ldrsb   r1, [r11, #0x20]
    mov     r0, r11
    mov     r2, #0
    bl      func_0203c634
    add     sp, sp, #0x78
    ldmfd   sp!, {r3, r4, r5, r6, r7, r8, sb, r10, r11, pc}
}
