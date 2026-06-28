extern void NNSi_FndGetCurrentRootHeap(void);
extern void func_0202b850(void);
extern void func_0202b914(void);
extern void func_0202bfcc(void);
extern void func_0202d968(void);
extern void func_02016f10(void);
extern void func_ov022_0209f6e0(void);
extern char data_ov047_020b4380[];
extern char data_ov047_020b4308[];
extern void func_ov047_020b34cc(void);
extern void func_ov047_020b3630(void);
extern void func_ov047_020b37a4(void);
extern void func_ov047_020b3474(void);
extern void func_ov047_020b34ac(void);
extern void func_ov047_020b36c8(void);
extern void func_ov047_020b37dc(void);
extern void func_ov047_020b3e34(void);
extern char data_ov047_020b423c[];
extern char data_ov047_020b422c[];
extern char data_ov047_020b421c[];
extern char data_ov047_020b420c[];

asm void func_ov047_020b327c(void)
{
    push    {r3, r4, r5, lr}
    sub     sp, #0x18
    add     r5, r0, #0
    bl      NNSi_FndGetCurrentRootHeap
    add     r4, r0, #0
    ldr     r0, [pc, #0x198]
    mov     r3, #9
    str     r4, [r0]
    ldr     r0, [r5, #0]
    mov     r2, #0
    strb    r0, [r4, #9]
    ldr     r1, [r5, #4]
    ldr     r0, [pc, #0x190]
    lsl     r3, r3, #8
    strb    r1, [r4, r0]
    ldrb    r1, [r5, #8]
    strb    r1, [r4, #8]
    mov     r1, #0x11
    str     r1, [r4, #0xc]
    str     r2, [r4]
    str     r2, [r4, #4]
    str     r3, [sp, #0xc]
    mov     r3, #7
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
    ldr     r0, [pc, #0x160]
    ldr     r3, [r5, #0]
    ldrsb   r0, [r4, r0]
    ldr     r1, [pc, #0x15c]
    mov     r2, #1
    add     r3, r3, #7
    bl      func_0202b914
    ldr     r1, [pc, #0x158]
    ldr     r0, [pc, #0x158]
    ldr     r2, [pc, #0x15c]
    str     r1, [r4, r0]
    add     r1, r0, #4
    str     r2, [r4, r1]
    add     r1, r0, #0
    ldr     r2, [pc, #0x154]
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
    ldr     r2, [pc, #0x144]
    add     r1, #0x14
    str     r2, [r4, r1]
    add     r1, r0, #0
    ldr     r2, [pc, #0x140]
    add     r1, #0x18
    str     r2, [r4, r1]
    add     r1, r0, #0
    ldr     r2, [pc, #0x13c]
    add     r1, #0x20
    str     r2, [r4, r1]
    add     r1, r0, #0
    ldr     r2, [pc, #0x138]
    add     r1, #0x28
    str     r2, [r4, r1]
    ldr     r1, [pc, #0x134]
    add     r0, #0x24
    str     r1, [r4, r0]
    ldr     r0, [pc, #0x108]
    ldrsb   r0, [r4, r0]
    bl      func_0202bfcc
    add     r1, r0, #0
    add     r0, r4, #0
    add     r0, #0x20
    bl      func_0202d968
    mov     r3, #0
    sub     r2, r3, #1
    ldr     r0, [pc, #0x11c]
    b       _L_00c4
_L_00bc:
    lsl     r1, r3, #2
    add     r1, r4, r1
    str     r2, [r1, r0]
    add     r3, r3, #1
_L_00c4:
    cmp     r3, #5
    blt     _L_00bc
    ldr     r0, [r4, #0x20]
    add     r0, #0x24
    ldr     r0, [r0, #4]
    cmp     r0, #0
    beq     _L_00d6
    add     r0, #0x40
    b       _L_00d8
_L_00d6:
    mov     r0, #0
_L_00d8:
    cmp     r0, #0
    beq     _L_00e4
    ldr     r1, [pc, #0xfc]
    bl      func_02016f10
    b       _L_00e8
_L_00e4:
    mov     r0, #0
    mvn     r0, r0
_L_00e8:
    mov     r1, #0x52
    lsl     r1, r1, #4
    str     r0, [r4, r1]
    ldr     r0, [r4, #0x20]
    add     r0, #0x24
    ldr     r0, [r0, #4]
    cmp     r0, #0
    beq     _L_00fc
    add     r0, #0x40
    b       _L_00fe
_L_00fc:
    mov     r0, #0
_L_00fe:
    cmp     r0, #0
    beq     _L_010a
    ldr     r1, [pc, #0xdc]
    bl      func_02016f10
    b       _L_010e
_L_010a:
    mov     r0, #0
    mvn     r0, r0
_L_010e:
    ldr     r1, [pc, #0xd4]
    str     r0, [r4, r1]
    ldr     r0, [r4, #0x20]
    add     r0, #0x24
    ldr     r0, [r0, #4]
    cmp     r0, #0
    beq     _L_0120
    add     r0, #0x40
    b       _L_0122
_L_0120:
    mov     r0, #0
_L_0122:
    cmp     r0, #0
    beq     _L_012e
    ldr     r1, [pc, #0xc0]
    bl      func_02016f10
    b       _L_0132
_L_012e:
    mov     r0, #0
    mvn     r0, r0
_L_0132:
    ldr     r1, [pc, #0xb8]
    str     r0, [r4, r1]
    ldr     r0, [r4, #0x20]
    add     r0, #0x24
    ldr     r0, [r0, #4]
    cmp     r0, #0
    beq     _L_0144
    add     r0, #0x40
    b       _L_0146
_L_0144:
    mov     r0, #0
_L_0146:
    cmp     r0, #0
    beq     _L_0152
    ldr     r1, [pc, #0xa4]
    bl      func_02016f10
    b       _L_0156
_L_0152:
    mov     r0, #0
    mvn     r0, r0
_L_0156:
    ldr     r1, [pc, #0x9c]
    str     r0, [r4, r1]
    ldr     r0, [r5, #0xc]
    cmp     r0, #0
    beq     _L_0170
    ldr     r3, [r4, #0]
    mov     r0, #0x20
    ldr     r2, [r4, #4]
    mov     r1, #0
    orr     r0, r3
    orr     r1, r2
    str     r0, [r4]
    str     r1, [r4, #4]
_L_0170:
    ldr     r0, [r5, #0x10]
    cmp     r0, #0
    beq     _L_0188
    mov     r0, #1
    ldr     r3, [r4, #0]
    lsl     r0, r0, #0x10
    ldr     r2, [r4, #4]
    mov     r1, #0
    orr     r0, r3
    orr     r1, r2
    str     r0, [r4]
    str     r1, [r4, #4]
_L_0188:
    ldr     r0, [r5, #0x14]
    cmp     r0, #0
    beq     _L_019e
    ldr     r3, [r4, #0]
    mov     r0, #0
    ldr     r2, [r4, #4]
    mov     r1, #0x10
    orr     r0, r3
    orr     r1, r2
    str     r0, [r4]
    str     r1, [r4, #4]
_L_019e:
    add     r0, r4, #0
    bl      func_ov022_0209f6e0
    add     sp, #0x18
    pop     {r3, r4, r5, pc}
    dcd     data_ov047_020b4380
    dcd     0x000004bc
    dcd     data_ov047_020b4308
    dcd     func_ov047_020b34cc
    dcd     0x00000664
    dcd     func_ov047_020b3630
    dcd     func_ov047_020b37a4
    dcd     func_ov047_020b3474
    dcd     func_ov047_020b34ac
    dcd     func_ov047_020b36c8
    dcd     func_ov047_020b37dc
    dcd     func_ov047_020b3e34
    dcd     0x00000514
    dcd     data_ov047_020b423c
    dcd     data_ov047_020b422c
    dcd     0x00000518
    dcd     data_ov047_020b421c
    dcd     0x0000051c
    dcd     data_ov047_020b420c
    dcd     0x00000524
}
