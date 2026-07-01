extern void NNSi_FndGetCurrentRootHeap(void);
extern void func_0202b850(void);
extern void func_0202b914(void);
extern void func_0202bfcc(void);
extern void func_0202d968(void);
extern void func_02016f10(void);
extern void func_ov022_0209f6e0(void);
extern char data_ov051_020b7380[];
extern char data_ov051_020b7314[];
extern char data_ov051_020b7328[];
extern void func_ov051_020b5e4c(void);
extern void func_ov051_020b5f10(void);
extern void func_ov051_020b60e0(void);
extern void func_ov051_020b5cac(void);
extern void func_ov051_020b5ce4(void);
extern void func_ov051_020b6170(void);
extern void func_ov051_020b5d0c(void);
extern void func_ov051_020b62bc(void);
extern char data_ov051_020b72a8[];
extern char data_ov051_020b72c8[];
extern char data_ov051_020b72b8[];
extern char data_ov051_020b72e8[];
extern char data_ov051_020b72d8[];

asm void func_ov051_020b5a70(void)
{
    push    {r3, r4, r5, lr}
    sub     sp, #0x18
    add     r5, r0, #0
    bl      NNSi_FndGetCurrentRootHeap
    add     r4, r0, #0
    ldr     r0, [pc, #0x1d4]
    mov     r3, #9
    str     r4, [r0]
    ldr     r0, [r5, #0]
    mov     r2, #0
    strb    r0, [r4, #9]
    ldr     r1, [r5, #4]
    ldr     r0, [pc, #0x1cc]
    lsl     r3, r3, #8
    strb    r1, [r4, r0]
    ldrb    r1, [r5, #8]
    strb    r1, [r4, #8]
    mov     r1, #3
    str     r1, [r4, #0xc]
    str     r2, [r4]
    str     r2, [r4, #4]
    str     r3, [sp, #0xc]
    mov     r3, #0x17
    mov     r1, #1
    lsl     r3, r3, #8
    str     r1, [sp, #4]
    str     r3, [sp, #8]
    str     r2, [sp]
    ldrb    r3, [r4, #8]
    ldrsb   r0, [r4, r0]
    lsl     r1, r3
    lsl     r1, r1, #0x10
    lsr     r1, r1, #0x10
    add     r3, sp, #4
    bl      func_0202b850
    ldr     r0, [r5, #0x18]
    cmp     r0, #0
    ldr     r0, [pc, #0x198]
    bne     _L_0062
    ldr     r3, [r5, #0]
    ldrsb   r0, [r4, r0]
    ldr     r1, [pc, #0x194]
    mov     r2, #1
    add     r3, r3, #7
    bl      func_0202b914
    b       _L_0070
_L_0062:
    ldr     r3, [r5, #0]
    ldrsb   r0, [r4, r0]
    ldr     r1, [pc, #0x188]
    mov     r2, #1
    add     r3, r3, #7
    bl      func_0202b914
_L_0070:
    ldr     r1, [pc, #0x180]
    ldr     r0, [pc, #0x184]
    ldr     r2, [pc, #0x184]
    str     r1, [r4, r0]
    add     r1, r0, #4
    str     r2, [r4, r1]
    add     r1, r0, #0
    ldr     r2, [pc, #0x180]
    add     r1, #8
    str     r2, [r4, r1]
    add     r1, r0, #0
    mov     r2, #0
    add     r1, #0xc
    str     r2, [r4, r1]
    add     r1, r0, #0
    add     r1, #0x10
    str     r2, [r4, r1]
    add     r1, r0, #0
    ldr     r2, [pc, #0x16c]
    add     r1, #0x14
    str     r2, [r4, r1]
    add     r1, r0, #0
    ldr     r2, [pc, #0x168]
    add     r1, #0x18
    str     r2, [r4, r1]
    add     r1, r0, #0
    ldr     r2, [pc, #0x164]
    add     r1, #0x20
    str     r2, [r4, r1]
    add     r1, r0, #0
    ldr     r2, [pc, #0x160]
    add     r1, #0x28
    str     r2, [r4, r1]
    ldr     r1, [pc, #0x160]
    add     r0, #0x24
    str     r1, [r4, r0]
    ldr     r0, [pc, #0x12c]
    ldrsb   r0, [r4, r0]
    bl      func_0202bfcc
    add     r1, r0, #0
    add     r0, r4, #0
    add     r0, #0x20
    bl      func_0202d968
    mov     r3, #0
    sub     r2, r3, #1
    ldr     r0, [pc, #0x148]
    b       _L_00da
_L_00d2:
    lsl     r1, r3, #2
    add     r1, r4, r1
    str     r2, [r1, r0]
    add     r3, r3, #1
_L_00da:
    cmp     r3, #5
    blt     _L_00d2
    ldr     r0, [r4, #0x20]
    add     r0, #0x24
    ldr     r0, [r0, #4]
    cmp     r0, #0
    beq     _L_00ec
    add     r0, #0x40
    b       _L_00ee
_L_00ec:
    mov     r0, #0
_L_00ee:
    cmp     r0, #0
    beq     _L_00fa
    ldr     r1, [pc, #0x128]
    bl      func_02016f10
    b       _L_00fe
_L_00fa:
    mov     r0, #0
    mvn     r0, r0
_L_00fe:
    mov     r1, #0x52
    lsl     r1, r1, #4
    str     r0, [r4, r1]
    ldr     r0, [r4, #0x20]
    add     r0, #0x24
    ldr     r0, [r0, #4]
    cmp     r0, #0
    beq     _L_0112
    add     r0, #0x40
    b       _L_0114
_L_0112:
    mov     r0, #0
_L_0114:
    cmp     r0, #0
    beq     _L_0120
    ldr     r1, [pc, #0x104]
    bl      func_02016f10
    b       _L_0124
_L_0120:
    mov     r0, #0
    mvn     r0, r0
_L_0124:
    ldr     r1, [pc, #0xfc]
    str     r0, [r4, r1]
    ldr     r0, [r4, #0x20]
    add     r0, #0x24
    ldr     r0, [r0, #4]
    cmp     r0, #0
    beq     _L_0136
    add     r0, #0x40
    b       _L_0138
_L_0136:
    mov     r0, #0
_L_0138:
    cmp     r0, #0
    beq     _L_0144
    ldr     r1, [pc, #0xe8]
    bl      func_02016f10
    b       _L_0148
_L_0144:
    mov     r0, #0
    mvn     r0, r0
_L_0148:
    ldr     r1, [pc, #0xcc]
    str     r0, [r4, r1]
    ldr     r0, [r4, #0x20]
    add     r0, #0x24
    ldr     r0, [r0, #4]
    cmp     r0, #0
    beq     _L_015a
    add     r0, #0x40
    b       _L_015c
_L_015a:
    mov     r0, #0
_L_015c:
    cmp     r0, #0
    beq     _L_0168
    ldr     r1, [pc, #0xc8]
    bl      func_02016f10
    b       _L_016c
_L_0168:
    mov     r0, #0
    mvn     r0, r0
_L_016c:
    ldr     r1, [pc, #0xc0]
    str     r0, [r4, r1]
    ldr     r0, [r4, #0x20]
    add     r0, #0x24
    ldr     r0, [r0, #4]
    cmp     r0, #0
    beq     _L_017e
    add     r0, #0x40
    b       _L_0180
_L_017e:
    mov     r0, #0
_L_0180:
    cmp     r0, #0
    beq     _L_018c
    ldr     r1, [pc, #0xac]
    bl      func_02016f10
    b       _L_0190
_L_018c:
    mov     r0, #0
    mvn     r0, r0
_L_0190:
    ldr     r1, [pc, #0xa4]
    str     r0, [r4, r1]
    ldr     r0, [r5, #0xc]
    cmp     r0, #0
    beq     _L_01aa
    ldr     r3, [r4, #0]
    mov     r0, #0x20
    ldr     r2, [r4, #4]
    mov     r1, #0
    orr     r0, r3
    orr     r1, r2
    str     r0, [r4]
    str     r1, [r4, #4]
_L_01aa:
    ldr     r0, [r5, #0x10]
    cmp     r0, #0
    beq     _L_01c2
    mov     r0, #1
    ldr     r3, [r4, #0]
    lsl     r0, r0, #0x10
    ldr     r2, [r4, #4]
    mov     r1, #0
    orr     r0, r3
    orr     r1, r2
    str     r0, [r4]
    str     r1, [r4, #4]
_L_01c2:
    ldr     r0, [r5, #0x14]
    cmp     r0, #0
    beq     _L_01d8
    ldr     r3, [r4, #0]
    mov     r0, #0
    ldr     r2, [r4, #4]
    mov     r1, #0x10
    orr     r0, r3
    orr     r1, r2
    str     r0, [r4]
    str     r1, [r4, #4]
_L_01d8:
    add     r0, r4, #0
    bl      func_ov022_0209f6e0
    add     sp, #0x18
    pop     {r3, r4, r5, pc}
    mov     r8, r8
    dcd     data_ov051_020b7380
    dcd     0x000004bc
    dcd     data_ov051_020b7314
    dcd     data_ov051_020b7328
    dcd     func_ov051_020b5e4c
    dcd     0x00000664
    dcd     func_ov051_020b5f10
    dcd     func_ov051_020b60e0
    dcd     func_ov051_020b5cac
    dcd     func_ov051_020b5ce4
    dcd     func_ov051_020b6170
    dcd     func_ov051_020b5d0c
    dcd     func_ov051_020b62bc
    dcd     0x00000514
    dcd     data_ov051_020b72a8
    dcd     data_ov051_020b72c8
    dcd     0x00000518
    dcd     data_ov051_020b72b8
    dcd     data_ov051_020b72e8
    dcd     0x0000051c
    dcd     data_ov051_020b72d8
    dcd     0x00000524
}
