extern int data_ov020_020800e4;
extern int data_ov020_020800f0;
extern void func_01ff8e94(void);
extern void func_01fffe14(void);
extern void func_02028df0(void);
extern void func_02028e4c(void);
extern void func_0202af2c(void);
extern void func_0202bfa0(void);
extern void func_ov002_020726f4(void);
extern void func_ov002_02072b24(void);
extern void func_ov022_020881f8(void);

asm void func_ov020_0207fe4c(void)
{
    stmfd   sp!, {r3, r4, r5, r6, r7, r8, r9, r10, r11, lr}
    sub     sp, sp, #0x10
    mov     r10, r0
    ldr     r0, [r10, #0x14]
    mov     r6, r2
    cmp     r0, #1
    bne     _L144
    bl      func_01fffe14
    bl      func_ov022_020881f8
    add     r3, sp, #4
    ldmia   r0, {r0, r1, r2}
    stmia   r3, {r0, r1, r2}
    mov     r2, #0
    mov     r0, r3
    mov     r1, r10
    str     r2, [sp, #8]
    bl      func_01ff8e94
    ldr     r1, [r10, #0xc]
    cmp     r0, r1
    bgt     _L23c
    add     r7, r6, #0x100
    ldrsb   r0, [r7, #0x10]
    mov     r4, #0
    cmp     r0, #0
    ble     _L90
    add     r5, r6, #0x114
_L68:
    mov     r0, r5
    bl      func_0202af2c
    ldrb    r0, [r5, #0x108]
    add     r4, r4, #1
    bic     r0, r0, #4
    strb    r0, [r5, #0x108]
    ldrsb   r0, [r7, #0x10]
    add     r5, r5, #0x10c
    cmp     r4, r0
    blt     _L68
_L90:
    ldrsb   r0, [r6, #0xd]
    bl      func_0202bfa0
    mov     r7, r0
    ldrh    r0, [r7, #2]
    mov     r9, #0
    cmp     r0, #0
    ble     _L11c
    mov     r5, #1
    ldr     r4, =func_ov002_02072b24
    mov     r11, r5
_Lb8:
    ldr     r0, [r7, #4]
    ldr     r1, =data_ov020_020800e4
    ldr     r8, [r0, r9, lsl #2]
    mov     r0, r8
    bl      func_02028df0
    mov     r6, r0
    ldr     r1, =data_ov020_020800f0
    mov     r0, r8
    bl      func_02028df0
    mov     r2, r0
    str     r5, [sp]
    mov     r0, r8
    mov     r1, #2
    mov     r3, r4
    bl      func_02028e4c
    mov     r0, r8
    mov     r2, r6
    str     r11, [sp]
    mov     r1, #2
    mov     r3, r4
    bl      func_02028e4c
    ldrh    r0, [r7, #2]
    add     r9, r9, #1
    cmp     r9, r0
    blt     _Lb8
_L11c:
    ldr     r0, [r10, #0x10]
    mov     r1, #0x4d
    cmp     r0, #0
    movne   r0, #9
    moveq   r0, #0xa
    mov     r2, #1
    bl      func_ov002_020726f4
    mov     r0, #2
    str     r0, [r10, #0x14]
    b       _L23c
_L144:
    cmp     r0, #2
    bne     _L194
    add     r0, r6, #0x100
    ldrsb   r3, [r0, #0x10]
    mov     r2, #1
    mov     r4, #0
    cmp     r3, #0
    ble     _L184
    mov     r0, r4
_L168:
    ldrb    r1, [r6, #0x21c]
    add     r4, r4, #1
    add     r6, r6, #0x10c
    tst     r1, #4
    moveq   r2, r0
    cmp     r4, r3
    blt     _L168
_L184:
    cmp     r2, #0
    movne   r0, #3
    strne   r0, [r10, #0x14]
    b       _L23c
_L194:
    cmp     r0, #3
    bne     _L23c
    ldrsb   r0, [r6, #0xd]
    bl      func_0202bfa0
    mov     r7, r0
    ldrh    r0, [r7, #2]
    mov     r9, #0
    cmp     r0, #0
    ble     _L210
    ldr     r5, =data_ov020_020800e4
    ldr     r6, =data_ov020_020800f0
    mov     r4, r9
    mov     r11, #2
_L1c8:
    ldr     r0, [r10, #0x10]
    cmp     r0, #0
    ldr     r0, [r7, #4]
    movne   r1, r6
    ldr     r8, [r0, r9, lsl #2]
    moveq   r1, r5
    mov     r0, r8
    bl      func_02028df0
    mov     r2, r0
    ldr     r3, =func_ov002_02072b24
    mov     r0, r8
    str     r4, [sp]
    mov     r1, r11
    bl      func_02028e4c
    ldrh    r0, [r7, #2]
    add     r9, r9, #1
    cmp     r9, r0
    blt     _L1c8
_L210:
    ldr     r0, [r10, #0x10]
    mov     r2, #1
    cmp     r0, #0
    movne   r1, #0x46
    moveq   r1, #7
    cmp     r0, #0
    movne   r0, #9
    moveq   r0, #0xa
    bl      func_ov002_020726f4
    mov     r0, #4
    str     r0, [r10, #0x14]
_L23c:
    mov     r0, #0
    add     sp, sp, #0x10
    ldmfd   sp!, {r3, r4, r5, r6, r7, r8, r9, r10, r11, pc}
}
