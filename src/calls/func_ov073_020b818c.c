extern void NNSi_FndGetCurrentRootHeap(void);
extern char data_ov073_020ba45c[];
extern char data_ov073_020ba46c[];
extern char data_ov073_020ba47c[];
extern char data_ov073_020ba4b4[];
extern char data_ov073_020ba4c8[];
extern char data_ov073_020ba540[];
extern void func_02016f10(void);
extern void func_0202b850(void);
extern void func_0202b914(void);
extern void func_0202bfcc(void);
extern void func_0202d968(void);
extern void func_ov022_0209f6e0(void);
extern void func_ov073_020b8374(void);
extern void func_ov073_020b84c4(void);
extern void func_ov073_020b84ec(void);
extern void func_ov073_020b8664(void);
extern void func_ov073_020b8b50(void);
extern void func_ov073_020b8b88(void);
extern void func_ov073_020b8d74(void);
extern void func_ov073_020b8e10(void);

asm void func_ov073_020b818c(void)
{
    push    {r3, r4, r5, lr}
    sub     sp, #0x18
    add     r5, r0, #0
_L_0006:
    bl      NNSi_FndGetCurrentRootHeap
    add     r4, r0, #0
    ldr     r0, [pc, #0x18c]
    mov     r3, #9
    str     r4, [r0, #0]
    ldr     r0, [r5, #0]
    mov     r2, #0
    strb    r0, [r4, #9]
    ldr     r1, [r5, #4]
    ldr     r0, [pc, #0x184]
    lsl     r3, r3, #8
    strb    r1, [r4, r0]
    ldrb    r1, [r5, #8]
    strb    r1, [r4, #8]
    mov     r1, #4
    str     r1, [r4, #0xc]
    str     r2, [r4, #0]
    str     r2, [r4, #4]
    str     r3, [sp, #0xc]
    mov     r3, #0x1f
    mov     r1, #1
    lsl     r3, r3, #8
    str     r1, [sp, #4]
    str     r3, [sp, #8]
    str     r2, [sp, #0]
    ldrb    r3, [r4, #8]
    ldrsb   r0, [r4, r0]
    lsl     r1, r3
    lsl     r1, r1, #0x10
    lsr     r1, r1, #0x10
    add     r3, sp, #4
_L_0046:
    bl      func_0202b850
    ldr     r0, [r5, #0x18]
    cmp     r0, #0
    ldr     r0, [pc, #0x150]
    bne     _L_0062
    ldr     r3, [r5, #0]
    ldrsb   r0, [r4, r0]
    ldr     r1, [pc, #0x14c]
    mov     r2, #1
    add     r3, r3, #7
_L_005c:
    bl      func_0202b914
    b       _L_0070
_L_0062:
    ldr     r3, [r5, #0]
    ldrsb   r0, [r4, r0]
    ldr     r1, [pc, #0x140]
    mov     r2, #1
    add     r3, r3, #7
_L_006c:
    bl      func_0202b914
_L_0070:
    ldr     r1, [pc, #0x138]
    ldr     r0, [pc, #0x13c]
    ldr     r2, [pc, #0x13c]
    str     r1, [r4, r0]
    add     r1, r0, #4
    str     r2, [r4, r1]
    add     r1, r0, #0
    ldr     r2, [pc, #0x138]
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
    ldr     r2, [pc, #0x124]
    add     r1, #0x14
    str     r2, [r4, r1]
    add     r1, r0, #0
    ldr     r2, [pc, #0x120]
    add     r1, #0x18
    str     r2, [r4, r1]
    add     r1, r0, #0
    ldr     r2, [pc, #0x11c]
    add     r1, #0x20
    str     r2, [r4, r1]
    add     r1, r0, #0
    ldr     r2, [pc, #0x118]
    add     r1, #0x28
    str     r2, [r4, r1]
    ldr     r1, [pc, #0x118]
    add     r0, #0x24
    str     r1, [r4, r0]
    ldr     r0, [pc, #0xe4]
    ldrsb   r0, [r4, r0]
_L_00bc:
    bl      func_0202bfcc
    add     r1, r0, #0
    add     r0, r4, #0
    add     r0, #0x20
_L_00c6:
    bl      func_0202d968
    mov     r3, #0
    sub     r2, r3, #1
    ldr     r0, [pc, #0x100]
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
    ldr     r1, [pc, #0xe0]
_L_00f4:
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
    ldr     r1, [pc, #0xbc]
_L_011a:
    bl      func_02016f10
    b       _L_0124
_L_0120:
    mov     r0, #0
    mvn     r0, r0
_L_0124:
    ldr     r1, [pc, #0xb4]
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
    ldr     r1, [pc, #0xa0]
_L_013e:
    bl      func_02016f10
    b       _L_0148
_L_0144:
    mov     r0, #0
    mvn     r0, r0
_L_0148:
    ldr     r1, [pc, #0x98]
    str     r0, [r4, r1]
    ldr     r0, [r5, #0xc]
    cmp     r0, #0
    beq     _L_0162
    ldr     r3, [r4, #0]
    mov     r0, #0x20
    ldr     r2, [r4, #4]
    mov     r1, #0
    orr     r0, r3
    orr     r1, r2
    str     r0, [r4, #0]
    str     r1, [r4, #4]
_L_0162:
    ldr     r0, [r5, #0x10]
    cmp     r0, #0
    beq     _L_017a
    mov     r0, #1
    ldr     r3, [r4, #0]
    lsl     r0, r0, #0x10
    ldr     r2, [r4, #4]
    mov     r1, #0
    orr     r0, r3
    orr     r1, r2
    str     r0, [r4, #0]
    str     r1, [r4, #4]
_L_017a:
    ldr     r0, [r5, #0x14]
    cmp     r0, #0
    beq     _L_0190
    ldr     r3, [r4, #0]
    mov     r0, #0
    ldr     r2, [r4, #4]
    mov     r1, #0x10
    orr     r0, r3
    orr     r1, r2
    str     r0, [r4, #0]
    str     r1, [r4, #4]
_L_0190:
    add     r0, r4, #0
_L_0192:
    bl      func_ov022_0209f6e0
    add     sp, #0x18
    pop     {r3, r4, r5, pc}
    mov     r8, r8
    dcd     data_ov073_020ba540
    lsl     r4, r7, #0x12
    lsl     r0, r0, #0
    dcd     data_ov073_020ba4b4
    dcd     data_ov073_020ba4c8
    dcd     func_ov073_020b84ec
    lsl     r4, r4, #0x19
    lsl     r0, r0, #0
    dcd     func_ov073_020b8664
    dcd     func_ov073_020b8b50
    dcd     func_ov073_020b8374
    dcd     func_ov073_020b84c4
    dcd     func_ov073_020b8b88
    dcd     func_ov073_020b8d74
    dcd     func_ov073_020b8e10
    lsl     r4, r2, #0x14
    lsl     r0, r0, #0
    dcd     data_ov073_020ba46c
    dcd     data_ov073_020ba45c
    lsl     r4, r3, #0x14
    lsl     r0, r0, #0
    dcd     data_ov073_020ba47c
    lsl     r4, r4, #0x14
    lsl     r0, r0, #0
}
