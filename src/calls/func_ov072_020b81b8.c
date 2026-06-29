extern void NNSi_FndGetCurrentRootHeap(void);
extern char data_ov072_020ba628[];
extern char data_ov072_020ba668[];
extern char data_ov072_020ba678[];
extern char data_ov072_020ba688[];
extern char data_ov072_020ba698[];
extern char data_ov072_020ba6fc[];
extern char data_ov072_020ba710[];
extern char data_ov072_020ba7a0[];
extern void func_02016f10(void);
extern void func_0202b850(void);
extern void func_0202b914(void);
extern void func_0202bfcc(void);
extern void func_0202d968(void);
extern void func_ov022_0209f6e0(void);
extern void func_ov072_020b8404(void);
extern void func_ov072_020b8534(void);
extern void func_ov072_020b855c(void);
extern void func_ov072_020b8578(void);
extern void func_ov072_020b8874(void);
extern void func_ov072_020b8a88(void);
extern void func_ov072_020b8d08(void);
extern void func_ov072_020b8e18(void);
extern void func_ov072_020b8f14(void);
extern void func_ov072_020b97c0(void);
extern void func_ov072_020b9d9c(void);

asm void func_ov072_020b81b8(void)
{
    push    {r4, r5, r6, lr}
    sub     sp, #0x18
    add     r5, r0, #0
_L_0006:
    bl      NNSi_FndGetCurrentRootHeap
    add     r4, r0, #0
    ldr     r0, [pc, #0x1d4]
    ldr     r3, [pc, #0x1d8]
    str     r4, [r0, #0]
    ldr     r0, [r5, #0]
    mov     r2, #0
    strb    r0, [r4, #9]
    ldr     r0, [r5, #4]
    ldr     r1, [pc, #0x1d0]
    strb    r0, [r4, r3]
    ldrb    r0, [r5, #8]
    strb    r0, [r4, #8]
    mov     r0, #2
    str     r0, [r4, #0xc]
    str     r2, [r4, #0]
    str     r2, [r4, #4]
    ldrb    r6, [r4, r1]
    mov     r0, #2
    bic     r6, r0
    mov     r0, #9
    strb    r6, [r4, r1]
    lsl     r0, r0, #8
    str     r0, [sp, #0xc]
    mov     r0, #0x17
    mov     r1, #1
    lsl     r0, r0, #8
    str     r1, [sp, #4]
    str     r0, [sp, #8]
    str     r2, [sp, #0]
    ldrsb   r0, [r4, r3]
    ldrb    r3, [r4, #8]
    lsl     r1, r3
    lsl     r1, r1, #0x10
    lsr     r1, r1, #0x10
    add     r3, sp, #4
_L_0050:
    bl      func_0202b850
    ldr     r0, [r5, #0x18]
    cmp     r0, #0
    ldr     r0, [pc, #0x18c]
    bne     _L_006c
    ldr     r3, [r5, #0]
    ldrsb   r0, [r4, r0]
    ldr     r1, [pc, #0x18c]
    mov     r2, #1
    add     r3, r3, #7
_L_0066:
    bl      func_0202b914
    b       _L_007a
_L_006c:
    ldr     r3, [r5, #0]
    ldrsb   r0, [r4, r0]
    ldr     r1, [pc, #0x180]
    mov     r2, #1
    add     r3, r3, #7
_L_0076:
    bl      func_0202b914
_L_007a:
    ldr     r1, [pc, #0x17c]
    ldr     r0, [pc, #0x17c]
    ldr     r2, [pc, #0x180]
    str     r1, [r4, r0]
    add     r1, r0, #4
    str     r2, [r4, r1]
    add     r1, r0, #0
    ldr     r2, [pc, #0x178]
    add     r1, #8
    str     r2, [r4, r1]
    add     r1, r0, #0
    ldr     r2, [pc, #0x174]
    add     r1, #0xc
    str     r2, [r4, r1]
    add     r1, r0, #0
    ldr     r2, [pc, #0x170]
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
    add     r1, #0x1c
    str     r2, [r4, r1]
    add     r1, r0, #0
    ldr     r2, [pc, #0x15c]
    add     r1, #0x28
    str     r2, [r4, r1]
    ldr     r1, [pc, #0x15c]
    add     r0, #0x24
    str     r1, [r4, r0]
    ldr     r0, [pc, #0x118]
    ldrsb   r0, [r4, r0]
_L_00d0:
    bl      func_0202bfcc
    add     r1, r0, #0
    add     r0, r4, #0
    add     r0, #0x20
_L_00da:
    bl      func_0202d968
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
    ldr     r1, [pc, #0x134]
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
    ldr     r1, [pc, #0x110]
_L_011a:
    bl      func_02016f10
    b       _L_0124
_L_0120:
    mov     r0, #0
    mvn     r0, r0
_L_0124:
    ldr     r1, [pc, #0x108]
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
    ldr     r1, [pc, #0xf4]
_L_013e:
    bl      func_02016f10
    b       _L_0148
_L_0144:
    mov     r0, #0
    mvn     r0, r0
_L_0148:
    ldr     r1, [pc, #0xec]
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
    ldr     r1, [pc, #0xd8]
_L_0162:
    bl      func_02016f10
    b       _L_016c
_L_0168:
    mov     r0, #0
    mvn     r0, r0
_L_016c:
    ldr     r1, [pc, #0xd0]
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
    ldr     r1, [pc, #0xbc]
_L_0186:
    bl      func_02016f10
    b       _L_0190
_L_018c:
    mov     r0, #0
    mvn     r0, r0
_L_0190:
    ldr     r1, [pc, #0xb4]
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
    str     r0, [r4, #0]
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
    str     r0, [r4, #0]
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
    str     r0, [r4, #0]
    str     r1, [r4, #4]
_L_01d8:
    add     r0, r4, #0
_L_01da:
    bl      func_ov022_0209f6e0
    add     sp, #0x18
    pop     {r4, r5, r6, pc}
    mov     r8, r8
    dcd     data_ov072_020ba7a0
    lsl     r4, r7, #0x12
    lsl     r0, r0, #0
    cmp     r4, #0x30
    lsl     r0, r0, #0
    dcd     data_ov072_020ba6fc
    dcd     data_ov072_020ba710
    dcd     func_ov072_020b8a88
    lsl     r4, r4, #0x19
    lsl     r0, r0, #0
    dcd     func_ov072_020b8d08
    dcd     func_ov072_020b8e18
    dcd     func_ov072_020b855c
    dcd     func_ov072_020b8f14
    dcd     func_ov072_020b8404
    dcd     func_ov072_020b8534
    dcd     func_ov072_020b8578
    dcd     func_ov072_020b8874
    dcd     func_ov072_020b97c0
    dcd     func_ov072_020b9d9c
    dcd     data_ov072_020ba668
    dcd     data_ov072_020ba678
    lsl     r0, r3, #0x14
    lsl     r0, r0, #0
    dcd     data_ov072_020ba698
    lsl     r4, r2, #0x14
    lsl     r0, r0, #0
    dcd     data_ov072_020ba688
    lsl     r4, r3, #0x14
    lsl     r0, r0, #0
    dcd     data_ov072_020ba628
    lsl     r4, r4, #0x14
    lsl     r0, r0, #0
}
