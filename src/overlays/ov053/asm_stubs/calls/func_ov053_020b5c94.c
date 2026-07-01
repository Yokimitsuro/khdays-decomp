extern char data_ov053_020b7e60[];
extern void func_ov002_02051d6c(void);
extern void func_ov002_02051eec(void);
extern void func_ov022_0209fb60(void);
extern void func_ov022_0209fb98(void);

asm void func_ov053_020b5c94(void)
{
    push    {r3, r4, r5, r6, r7, lr}
    ldr     r1, [pc, #0x12c]
    add     r6, r0, #0
    ldr     r4, [r1, #0]
    mov     r1, #0
    mov     r2, #3
    bl      func_ov022_0209fb60
    add     r0, r6, #0
    mov     r1, #0
    mov     r2, #1
    bl      func_ov022_0209fb98
    ldr     r1, [pc, #0x118]
    ldrsb   r0, [r6, r1]
    cmp     r0, #0
    beq     _L_002e
    sub     r0, r1, #1
    ldrb    r2, [r6, r0]
    mov     r0, #1
    orr     r2, r0
    sub     r0, r1, #1
    strb    r2, [r6, r0]
_L_002e:
    ldr     r0, [pc, #0x108]
    ldr     r1, [pc, #0x108]
    mov     r2, #0x91
    lsl     r2, r2, #4
    add     r0, r6, r0
    add     r1, r4, r1
    add     r2, r6, r2
    bl      func_ov002_02051d6c
    mov     r0, #0x78
    str     r0, [sp, #0]
    ldr     r2, [pc, #0xf4]
    ldr     r0, [pc, #0xf0]
    add     r1, r4, r2
    sub     r2, #0x5c
    ldrb    r3, [r6, #9]
    ldr     r2, [r6, r2]
    add     r0, r6, r0
    bl      func_ov002_02051eec
    add     r0, r6, #0
    mov     r1, #1
    mov     r2, #4
    bl      func_ov022_0209fb60
    mov     r1, #1
    add     r0, r6, #0
    add     r2, r1, #0
    bl      func_ov022_0209fb98
    ldr     r1, [pc, #0xd4]
    ldrsb   r0, [r6, r1]
    cmp     r0, #0
    beq     _L_007e
    sub     r0, r1, #1
    ldrb    r2, [r6, r0]
    mov     r0, #1
    orr     r2, r0
    sub     r0, r1, #1
    strb    r2, [r6, r0]
_L_007e:
    ldr     r0, [pc, #0xc4]
    mov     r1, #0xb2
    mov     r2, #0x91
    lsl     r1, r1, #6
    lsl     r2, r2, #4
    add     r0, r6, r0
    add     r1, r4, r1
    add     r2, r6, r2
    bl      func_ov002_02051d6c
    ldr     r1, [pc, #0xb0]
    ldr     r7, [pc, #0xb0]
    ldrb    r2, [r6, r1]
    mov     r0, #8
    add     r5, r7, #0
    bic     r2, r0
    mov     r0, #0
    strb    r2, [r6, r1]
    add     r3, r0, #0
    sub     r1, r0, #1
    sub     r5, #0x4c
_L_00a8:
    add     r2, r4, r3
    strb    r1, [r2, r7]
    add     r3, r3, #1
    strb    r1, [r2, r5]
    cmp     r3, #0xd
    blt     _L_00a8
    ldr     r7, [pc, #0x94]
    mov     r3, #0
_L_00b8:
    add     r2, r4, r3
    ldrsb   r2, [r2, r7]
    mov     r1, #0
    mvn     r1, r1
    cmp     r2, #0
    blt     _L_0116
    cmp     r2, #0xb
    bhi     _L_00fe
    add     r5, r2, r2
    add     r5, pc
    ldrh    r5, [r5, #6]
    lsl     r5, r5, #0x10
    asr     r5, r5, #0x10
    add     pc, r5
    lsl     r0, r5, #0
    lsl     r0, r5, #0
    lsl     r6, r2, #0
    lsl     r0, r5, #0
    lsl     r0, r5, #0
    lsl     r2, r3, #0
    lsl     r0, r5, #0
    lsl     r0, r5, #0
    lsl     r6, r3, #0
    lsl     r2, r4, #0
    lsl     r0, r5, #0
    lsl     r6, r4, #0
    mov     r1, #0
    b       _L_00fe
    mov     r1, #1
    b       _L_00fe
    mov     r1, #2
    b       _L_00fe
    mov     r1, #3
    b       _L_00fe
    mov     r1, #4
_L_00fe:
    cmp     r1, #0
    blt     _L_0110
    add     r5, r4, r2
    ldr     r2, [pc, #0x40]
    strb    r0, [r5, r2]
    add     r5, r4, r0
    sub     r2, #0x4c
    strb    r1, [r5, r2]
    add     r0, r0, #1
_L_0110:
    add     r3, r3, #1
    cmp     r3, #0xd
    blt     _L_00b8
_L_0116:
    mov     r0, #0xbe
    str     r0, [sp, #0]
    mov     r2, #0xb2
    lsl     r2, r2, #6
    ldr     r0, [pc, #0x24]
    add     r1, r4, r2
    sub     r2, #0xb0
    ldrb    r3, [r6, #9]
    ldr     r2, [r6, r2]
    add     r0, r6, r0
    bl      func_ov002_02051eec
    pop     {r3, r4, r5, r6, r7, pc}
    dcd     data_ov053_020b7e60
    dcd     0x00000da9
    dcd     0x00000da8
    dcd     0x00002c2c
    dcd     0x00000f0d
    dcd     0x00000f0c
    dcd     0x00002cd4
    dcd     0x00002c34
}
