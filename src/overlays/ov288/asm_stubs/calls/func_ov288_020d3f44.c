extern void func_ov107_020c9264(void);
extern void VEC_Subtract(void);
extern void func_ov107_020c89e8(void);
extern void func_ov107_020c5af8(void);
extern int data_ov288_020d5314;

asm void func_ov288_020d3f44(void)
{
    stmfd   sp!, {r3, r4, r5, r6, r7, r8, sb, lr}
    mov     r7, r0
    ldr     r4, [r7, #0x214]
    ldr     r6, =data_ov288_020d5314
    ldr     r0, [r4]
    ldrb    lr, [r6, #2]
    add     r5, r0, #0x100
    ldrb    ip, [r6, #3]
    ldrb    r3, [r6]
    ldrb    sb, [r6, #1]
    ldrsb   r8, [r5, #0xc6]
    mov     r6, r1
    mov     r5, r2
    strb    lr, [sp, #2]
    strb    ip, [sp, #3]
    strb    r3, [sp]
    strb    sb, [sp, #1]
    cmp     r8, #2
    bne     _L_007c
    ldr     r1, [r5, #0x14]
    mov     r1, r1, asr #0x10
    cmp     r1, #0x6b
    bne     _L_0070
    str     r6, [r4, #8]
    ldr     r0, [r4]
    mov     r1, #4
    strb    r1, [r0, #0x1c7]
    b       _L_007c
_L_0070:
    mov     r1, #2
    mov     r2, #0
    bl      func_ov107_020c9264
_L_007c:
    ldr     r0, [r5]
    mov     r0, r0, lsl #0x10
    mov     r0, r0, lsr #0x10
    tst     r0, #0x20
    beq     _L_00f4
    ldr     r0, [r4, #8]
    cmp     r0, #0
    bne     _L_00f4
    str     r6, [r4, #8]
    add     r0, r5, #4
    add     r3, r4, #0x28
    ldmia   r0, {r0, r1, r2}
    stmia   r3, {r0, r1, r2}
    mov     r0, #0x10000
    ldr     r1, [r5, #0x24]
    rsb     r0, r0, #0
    and     r0, r1, r0
    orr     r0, r0, #6
    str     r0, [r5, #0x24]
    ldr     r1, [r4, #8]
    cmp     r1, #0
    beq     _L_010c
    ldr     r0, [r4]
    mov     r2, r3
    add     r0, r0, #0xb0
    add     r1, r1, #0x190
    bl      VEC_Subtract
    mov     r0, #0
    str     r0, [r4, #0x2c]
    b       _L_010c
_L_00f4:
    mov     r0, #0x10000
    ldr     r1, [r5, #0x24]
    rsb     r0, r0, #0
    and     r0, r1, r0
    orr     r0, r0, #4
    str     r0, [r5, #0x24]
_L_010c:
    mov     r0, r7
    mov     r1, r5
    bl      func_ov107_020c89e8
    str     r0, [r5, #0x28]
    cmp     r0, #0
    ble     _L_0198
    ldr     r0, [r5]
    mov     r1, r0, lsl #0x10
    mov     r1, r1, lsr #0x10
    tst     r1, #8
    beq     _L_014c
    tst     r1, #0x80
    beq     _L_014c
    mov     r0, r0, lsr #0x10
    cmp     r0, #0x80
    beq     _L_0198
_L_014c:
    tst     r1, #0x22
    ldrb    r1, [r4, #0x55]
    beq     _L_0174
    add     r0, sp, #0
    ldrb    r2, [r0, r1]
    ldr     r3, [r4, #0xc]
    ldr     r1, =0x15b
    mov     r0, r7
    bl      func_ov107_020c5af8
    b       _L_018c
_L_0174:
    add     r0, sp, #2
    ldrb    r2, [r0, r1]
    ldr     r3, [r4, #0xc]
    ldr     r1, =0x15b
    mov     r0, r7
    bl      func_ov107_020c5af8
_L_018c:
    ldrb    r0, [r4, #0x55]
    eor     r0, r0, #1
    strb    r0, [r4, #0x55]
_L_0198:
    mov     r0, #1
    ldmfd   sp!, {r3, r4, r5, r6, r7, r8, sb, pc}
}
