extern void NNSi_FndGetCurrentRootHeap(void);
extern void func_0202b850(void);
extern void func_0202b914(void);
extern void func_0202bfcc(void);
extern void func_0202d968(void);
extern void func_02016f10(void);
extern void func_ov022_0209f6e0(void);
extern void data_ov092_020bc4e0(void);
extern void data_ov092_020bc408(void);
extern void data_ov092_020bc41c(void);
extern void func_ov092_020baacc(void);
extern void func_ov092_020bab98(void);
extern void func_ov092_020bac24(void);
extern void func_ov092_020baa38(void);
extern void func_ov092_020baaa4(void);
extern void func_ov092_020bace4(void);
extern void func_ov092_020bc264(void);
extern void func_ov092_020bad8c(void);
extern void func_ov092_020bb7fc(void);
extern void data_ov092_020bc3a8(void);
extern void data_ov092_020bc3b8(void);
extern void data_ov092_020bc3c8(void);

asm void func_ov092_020ba844(void)
{
    push    {r3, r4, r5, lr}
    sub     sp, #0x18
    add     r5, r0, #0
    bl      NNSi_FndGetCurrentRootHeap
    add     r4, r0, #0
    ldr     r0, [pc, #0x194]
    mov     r3, #9
    str     r4, [r0, #0]
    ldr     r0, [r5, #0]
    mov     r2, #0
    strb    r0, [r4, #9]
    ldr     r1, [r5, #4]
    ldr     r0, [pc, #0x18c]
    lsl     r3, r3, #8
    strb    r1, [r4, r0]
    ldrb    r1, [r5, #8]
    strb    r1, [r4, #8]
    mov     r1, #6
    str     r1, [r4, #0xc]
    str     r2, [r4, #0]
    str     r2, [r4, #4]
    str     r3, [sp, #0xc]
    mov     r3, #0x17
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
    bl      func_0202b850
    ldr     r0, [r5, #0x18]
    cmp     r0, #0
    ldr     r0, [pc, #0x158]
    bne     _L_0062
    ldr     r3, [r5, #0]
    ldrsb   r0, [r4, r0]
    ldr     r1, [pc, #0x154]
    mov     r2, #1
    add     r3, r3, #7
    bl      func_0202b914
    b       _L_0070
_L_0062:
    ldr     r3, [r5, #0]
    ldrsb   r0, [r4, r0]
    ldr     r1, [pc, #0x148]
    mov     r2, #1
    add     r3, r3, #7
    bl      func_0202b914
_L_0070:
    ldr     r1, [pc, #0x140]
    ldr     r0, [pc, #0x144]
    ldr     r2, [pc, #0x144]
    str     r1, [r4, r0]
    add     r1, r0, #4
    str     r2, [r4, r1]
    add     r1, r0, #0
    ldr     r2, [pc, #0x140]
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
    ldr     r2, [pc, #0x12c]
    add     r1, #0x14
    str     r2, [r4, r1]
    add     r1, r0, #0
    ldr     r2, [pc, #0x128]
    add     r1, #0x18
    str     r2, [r4, r1]
    add     r1, r0, #0
    ldr     r2, [pc, #0x124]
    add     r1, #0x20
    str     r2, [r4, r1]
    add     r1, r0, #0
    ldr     r2, [pc, #0x120]
    add     r1, #0x1c
    str     r2, [r4, r1]
    add     r1, r0, #0
    ldr     r2, [pc, #0x11c]
    add     r1, #0x28
    str     r2, [r4, r1]
    ldr     r1, [pc, #0x11c]
    add     r0, #0x24
    str     r1, [r4, r0]
    ldr     r0, [pc, #0xe4]
    ldrsb   r0, [r4, r0]
    bl      func_0202bfcc
    add     r1, r0, #0
    add     r0, r4, #0
    add     r0, #0x20
    bl      func_0202d968
    mov     r3, #0
    sub     r2, r3, #1
    ldr     r0, [pc, #0x104]
    b       _L_00e2
_L_00da:
    lsl     r1, r3, #2
    add     r1, r4, r1
    str     r2, [r1, r0]
    add     r3, r3, #1
_L_00e2:
    cmp     r3, #5
    blt     _L_00da
    ldr     r0, [r4, #0x20]
    add     r0, #0x24
    ldr     r0, [r0, #4]
    cmp     r0, #0
    beq     _L_00f4
    add     r0, #0x40
    b       _L_00f6
_L_00f4:
    mov     r0, #0
_L_00f6:
    cmp     r0, #0
    beq     _L_0102
    ldr     r1, [pc, #0xe4]
    bl      func_02016f10
    b       _L_0106
_L_0102:
    mov     r0, #0
    mvn     r0, r0
_L_0106:
    mov     r1, #0x52
    lsl     r1, r1, #4
    str     r0, [r4, r1]
    ldr     r0, [r4, #0x20]
    add     r0, #0x24
    ldr     r0, [r0, #4]
    cmp     r0, #0
    beq     _L_011a
    add     r0, #0x40
    b       _L_011c
_L_011a:
    mov     r0, #0
_L_011c:
    cmp     r0, #0
    beq     _L_0128
    ldr     r1, [pc, #0xc0]
    bl      func_02016f10
    b       _L_012c
_L_0128:
    mov     r0, #0
    mvn     r0, r0
_L_012c:
    ldr     r1, [pc, #0xb8]
    str     r0, [r4, r1]
    ldr     r0, [r4, #0x20]
    add     r0, #0x24
    ldr     r0, [r0, #4]
    cmp     r0, #0
    beq     _L_013e
    add     r0, #0x40
    b       _L_0140
_L_013e:
    mov     r0, #0
_L_0140:
    cmp     r0, #0
    beq     _L_014c
    ldr     r1, [pc, #0xa4]
    bl      func_02016f10
    b       _L_0150
_L_014c:
    mov     r0, #0
    mvn     r0, r0
_L_0150:
    ldr     r1, [pc, #0x9c]
    str     r0, [r4, r1]
    ldr     r0, [r5, #0xc]
    cmp     r0, #0
    beq     _L_016a
    ldr     r3, [r4, #0]
    mov     r0, #0x20
    ldr     r2, [r4, #4]
    mov     r1, #0
    orr     r0, r3
    orr     r1, r2
    str     r0, [r4, #0]
    str     r1, [r4, #4]
_L_016a:
    ldr     r0, [r5, #0x10]
    cmp     r0, #0
    beq     _L_0182
    mov     r0, #1
    ldr     r3, [r4, #0]
    lsl     r0, r0, #0x10
    ldr     r2, [r4, #4]
    mov     r1, #0
    orr     r0, r3
    orr     r1, r2
    str     r0, [r4, #0]
    str     r1, [r4, #4]
_L_0182:
    ldr     r0, [r5, #0x14]
    cmp     r0, #0
    beq     _L_0198
    ldr     r3, [r4, #0]
    mov     r0, #0
    ldr     r2, [r4, #4]
    mov     r1, #0x10
    orr     r0, r3
    orr     r1, r2
    str     r0, [r4, #0]
    str     r1, [r4, #4]
_L_0198:
    add     r0, r4, #0
    bl      func_ov022_0209f6e0
    add     sp, #0x18
    pop     {r3, r4, r5, pc}
    mov     r8, r8
    dcd     data_ov092_020bc4e0
    lsl     r4, r7, #0x12
    lsl     r0, r0, #0
    dcd     data_ov092_020bc408
    dcd     data_ov092_020bc41c
    dcd     func_ov092_020baacc
    lsl     r4, r4, #0x19
    lsl     r0, r0, #0
    dcd     func_ov092_020bab98
    dcd     func_ov092_020bac24
    dcd     func_ov092_020baa38
    dcd     func_ov092_020baaa4
    dcd     func_ov092_020bace4
    dcd     func_ov092_020bc264
    dcd     func_ov092_020bad8c
    dcd     func_ov092_020bb7fc
    lsl     r4, r2, #0x14
    lsl     r0, r0, #0
    dcd     data_ov092_020bc3a8
    dcd     data_ov092_020bc3b8
    lsl     r4, r3, #0x14
    lsl     r0, r0, #0
    dcd     data_ov092_020bc3c8
    lsl     r4, r4, #0x14
    lsl     r0, r0, #0
}
