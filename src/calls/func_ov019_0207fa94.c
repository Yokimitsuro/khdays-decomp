extern int func_02021948();
extern int func_02021980();
extern void MIi_CpuClear16();
extern void MI_CpuFill8();
extern void func_0202fcb8();
extern void func_020235d0();
extern void OS_SPrintf();
extern void func_ov002_0206d3ec();
extern void func_ov002_02057300();
extern char data_ov019_0207fd40[];
extern char data_ov019_0207fd78[];

asm int func_ov019_0207fa94(void *a, void *b)
{
    push    {r4, r5, r6, r7, lr}
    sub     sp, #0x1fc
    sub     sp, #0x88
    add     r4, r1, #0
    add     r5, r0, #0
    bl      func_02021948
    add     r1, r4, #0
    add     r6, r0, #0
    add     r0, r5, #0
    add     r1, #8
    bl      func_02021980
    add     r1, r4, #0
    str     r0, [sp, #4]
    add     r0, r5, #0
    add     r1, #0x10
    bl      func_02021980
    add     r4, #0x18
    str     r0, [sp, #0]
    add     r0, r5, #0
    add     r1, r4, #0
    bl      func_02021980
    ldr     r1, =data_ov019_0207fd40
    add     r7, r0, #0
    ldrb    r2, [r1, #2]
    add     r0, sp, #8
    mov     r4, #0
    strb    r2, [r0, #4]
    ldrb    r2, [r1, #3]
    strb    r2, [r0, #5]
    ldrb    r2, [r1, #4]
    strb    r2, [r0, #2]
    ldrb    r2, [r1, #5]
    strb    r2, [r0, #3]
    ldrb    r2, [r1, #0]
    strb    r2, [r0, #0]
    ldrb    r1, [r1, #1]
    mov     r2, #2
    lsl     r2, r2, #8
    strb    r1, [r0, #1]
    add     r0, r4, #0
    add     r1, sp, #0x84
    bl      MIi_CpuClear16
    add     r0, r6, #0
    add     r1, sp, #0x84
    bl      func_0202fcb8
    cmp     r7, #3
    beq     _L_134
    add     r5, r4, #0
_L_6c:
    mov     r0, #0
    add     r1, sp, #0x54
    mov     r2, #0x20
    bl      MIi_CpuClear16
    mov     r0, #0
    add     r1, sp, #0x34
    mov     r2, #0x20
    bl      MIi_CpuClear16
    add     r0, sp, #0x74
    mov     r1, #0
    mov     r2, #0x10
    bl      MI_CpuFill8
    cmp     r5, #0
    bne     _L_a2
    ldr     r0, =0x0000140b
    mov     r1, #0xa
    bl      func_020235d0
    add     r6, r0, #0
    add     r0, sp, #0xc
    add     r1, sp, #0x54
    bl      func_0202fcb8
    b       _L_ce
_L_a2:
    cmp     r5, #1
    bne     _L_bc
    ldr     r0, =0x00001415
    mov     r1, #0xa
    bl      func_020235d0
    add     r6, r0, #0
    add     r0, sp, #8
    add     r0, #2
    add     r1, sp, #0x54
    bl      func_0202fcb8
    b       _L_ce
_L_bc:
    ldr     r0, =0x0000141f
    mov     r1, #0xa
    bl      func_020235d0
    add     r6, r0, #0
    add     r0, sp, #8
    add     r1, sp, #0x54
    bl      func_0202fcb8
_L_ce:
    ldr     r1, =data_ov019_0207fd78
    add     r0, sp, #0x74
    add     r2, r6, #0
    bl      OS_SPrintf
    add     r0, sp, #0x74
    add     r1, sp, #0x34
    bl      func_0202fcb8
    mov     r0, #1
    lsl     r0, r0, #8
    add     r2, r4, #0
    cmp     r4, r0
    bge     _L_10a
    add     r1, sp, #0x84
    lsl     r0, r4, #1
    add     r3, r1, r0
    add     r0, sp, #0x54
    ldrh    r6, [r0, #0]
    mov     r0, #1
    lsl     r0, r0, #8
_L_f8:
    ldrh    r1, [r3, #0]
    cmp     r6, r1
    bne     _L_102
    add     r4, r2, #0
    b       _L_10a
_L_102:
    add     r2, r2, #1
    add     r3, r3, #2
    cmp     r2, r0
    blt     _L_f8
_L_10a:
    add     r3, sp, #0x84
    lsl     r2, r4, #1
    mov     r1, #0
    add     r0, sp, #0x34
    add     r3, r3, r2
_L_114:
    ldrh    r2, [r0, #0]
    cmp     r2, #0
    beq     _L_128
    add     r1, r1, #1
    strh    r2, [r3, #0]
    add     r3, r3, #2
    add     r4, r4, #1
    add     r0, r0, #2
    cmp     r1, #0x10
    blt     _L_114
_L_128:
    cmp     r5, r7
    beq     _L_1b4
    add     r5, r5, #1
    cmp     r5, #3
    blt     _L_6c
    b       _L_1b4
_L_134:
    add     r0, r4, #0
    add     r1, sp, #0x54
    mov     r2, #0x20
    bl      MIi_CpuClear16
    add     r0, r4, #0
    add     r1, sp, #0x34
    mov     r2, #0x20
    bl      MIi_CpuClear16
    add     r0, sp, #0x74
    add     r1, r4, #0
    mov     r2, #0x10
    bl      MI_CpuFill8
    mov     r0, #5
    lsl     r0, r0, #0xa
    mov     r1, #0xa
    bl      func_020235d0
    add     r5, r0, #0
    add     r0, sp, #0xc
    add     r1, sp, #0x54
    bl      func_0202fcb8
    ldr     r1, =data_ov019_0207fd78
    add     r0, sp, #0x74
    add     r2, r5, #0
    bl      OS_SPrintf
    add     r0, sp, #0x74
    add     r1, sp, #0x34
    bl      func_0202fcb8
    add     r0, sp, #0x54
    ldrh    r3, [r0, #0]
    mov     r0, #1
    add     r5, r4, #0
    add     r2, sp, #0x84
    lsl     r0, r0, #8
_L_184:
    ldrh    r1, [r2, #0]
    cmp     r3, r1
    bne     _L_18e
    add     r4, r5, #0
    b       _L_196
_L_18e:
    add     r5, r5, #1
    add     r2, r2, #2
    cmp     r5, r0
    blt     _L_184
_L_196:
    add     r1, sp, #0x84
    lsl     r0, r4, #1
    mov     r3, #0
    add     r2, sp, #0x34
    add     r1, r1, r0
_L_1a0:
    ldrh    r0, [r2, #0]
    cmp     r0, #0
    beq     _L_1b4
    add     r3, r3, #1
    strh    r0, [r1, #0]
    add     r1, r1, #2
    add     r4, r4, #1
    add     r2, r2, #2
    cmp     r3, #0x18
    blt     _L_1a0
_L_1b4:
    ldr     r1, [sp, #4]
    mov     r0, #0
    bl      func_ov002_0206d3ec
    mov     r1, #0
    add     r0, sp, #0x84
    str     r0, [sp, #0x10]
    ldr     r0, [sp, #0]
    str     r1, [sp, #0x1c]
    str     r0, [sp, #0x20]
    sub     r0, r1, #1
    str     r0, [sp, #0x24]
    add     r0, sp, #0x10
    str     r1, [sp, #0x18]
    str     r1, [sp, #0x14]
    str     r1, [sp, #0x28]
    bl      func_ov002_02057300
    mov     r0, #0
    add     sp, #0x1fc
    add     sp, #0x88
    pop     {r4, r5, r6, r7, pc}
}
