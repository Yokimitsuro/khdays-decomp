#pragma thumb on

extern void NNSi_FndGetCurrentRootHeap(void);
extern void OS_SPrintf(void);
extern void func_02016f10(void);
extern void func_02023588(void);
extern void func_0202b850(void);
extern void func_0202b914(void);
extern void func_0202bfcc(void);
extern void func_0202d968(void);
extern void func_ov022_0209f6e0(void);
extern void func_ov030_020b35dc(void);
extern void func_ov030_020b3694(void);
extern void func_ov030_020b36cc(void);
extern void func_ov030_020b375c(void);
extern void func_ov030_020b3990(void);
extern void func_ov030_020b3cd4(void);
extern void func_ov030_020b3d18(void);
extern void func_ov030_020b3e24(void);
extern int data_ov030_020b5860;
extern int data_ov030_020b5870;
extern int data_ov030_020b5880;
extern int data_ov030_020b5890;
extern int data_ov030_020b58a0;
extern int data_ov030_020b591c;
extern int data_ov030_020b5920;
extern int data_ov030_020b5934;
extern int data_ov030_020b5948;
extern int data_ov030_020b5a00;

asm void func_ov030_020b3374(void)
{
    push    {r3, r4, r5, lr}
    sub     sp, #0x98
    add     r5, r0, #0
    bl      NNSi_FndGetCurrentRootHeap
    add     r4, r0, #0
    ldr     r0, [pc, #0x1f4]
    mov     r3, #9
    str     r4, [r0, #0]
    ldr     r0, [r5, #0]
    mov     r2, #0
    strb    r0, [r4, #9]
    ldr     r1, [r5, #4]
    ldr     r0, [pc, #0x1ec]
    lsl     r3, r3, #8
    strb    r1, [r4, r0]
    ldrb    r1, [r5, #8]
    strb    r1, [r4, #8]
    str     r2, [r4, #0xc]
    str     r2, [r4, #0]
    str     r2, [r4, #4]
    str     r3, [sp, #0xc]
    mov     r3, #0xf
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
    ldr     r0, [r5, #0x1c]
    cmp     r0, #0
    beq     _L_0054
    cmp     r0, #1
    beq     _L_0070
    b       _L_007a
_L_0054:
    ldr     r0, [r5, #0x18]
    cmp     r0, #0
    add     r0, sp, #0x18
    bne     _L_0066
    ldr     r1, [pc, #0x1ac]
    ldr     r2, [pc, #0x1b0]
    bl      OS_SPrintf
    b       _L_007a
_L_0066:
    ldr     r1, [pc, #0x1a4]
    ldr     r2, [pc, #0x1a8]
    bl      OS_SPrintf
    b       _L_007a
_L_0070:
    ldr     r1, [pc, #0x198]
    ldr     r2, [pc, #0x1a4]
    add     r0, sp, #0x18
    bl      OS_SPrintf
_L_007a:
    ldr     r0, [pc, #0x18c]
    ldr     r3, [r5, #0]
    ldrsb   r0, [r4, r0]
    add     r1, sp, #0x18
    mov     r2, #1
    add     r3, r3, #7
    bl      func_0202b914
    ldr     r1, [pc, #0x190]
    ldr     r0, [pc, #0x190]
    ldr     r2, [pc, #0x194]
    str     r1, [r4, r0]
    add     r1, r0, #4
    str     r2, [r4, r1]
    add     r1, r0, #0
    ldr     r2, [pc, #0x18c]
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
    ldr     r2, [pc, #0x17c]
    add     r1, #0x14
    str     r2, [r4, r1]
    add     r1, r0, #0
    ldr     r2, [pc, #0x178]
    add     r1, #0x18
    str     r2, [r4, r1]
    add     r1, r0, #0
    ldr     r2, [pc, #0x174]
    add     r1, #0x20
    str     r2, [r4, r1]
    add     r1, r0, #0
    ldr     r2, [pc, #0x170]
    add     r1, #0x28
    str     r2, [r4, r1]
    ldr     r1, [pc, #0x16c]
    add     r0, #0x24
    str     r1, [r4, r0]
    ldr     r0, [pc, #0x134]
    ldrsb   r0, [r4, r0]
    bl      func_0202bfcc
    add     r1, r0, #0
    add     r0, r4, #0
    add     r0, #0x20
    bl      func_0202d968
    ldr     r0, [r4, #0x20]
    add     r0, #0x24
    ldr     r0, [r0, #4]
    cmp     r0, #0
    beq     _L_00f2
    add     r0, #0x40
    b       _L_00f4
_L_00f2:
    mov     r0, #0
_L_00f4:
    cmp     r0, #0
    beq     _L_0100
    ldr     r1, [pc, #0x144]
    bl      func_02016f10
    b       _L_0104
_L_0100:
    mov     r0, #0
    mvn     r0, r0
_L_0104:
    mov     r1, #0x52
    lsl     r1, r1, #4
    str     r0, [r4, r1]
    ldr     r0, [r4, #0x20]
    add     r0, #0x24
    ldr     r0, [r0, #4]
    cmp     r0, #0
    beq     _L_0118
    add     r0, #0x40
    b       _L_011a
_L_0118:
    mov     r0, #0
_L_011a:
    cmp     r0, #0
    beq     _L_0126
    ldr     r1, [pc, #0x124]
    bl      func_02016f10
    b       _L_012a
_L_0126:
    mov     r0, #0
    mvn     r0, r0
_L_012a:
    ldr     r1, [pc, #0x11c]
    str     r0, [r4, r1]
    ldr     r0, [r4, #0x20]
    add     r0, #0x24
    ldr     r0, [r0, #4]
    cmp     r0, #0
    beq     _L_013c
    add     r0, #0x40
    b       _L_013e
_L_013c:
    mov     r0, #0
_L_013e:
    cmp     r0, #0
    beq     _L_014a
    ldr     r1, [pc, #0x108]
    bl      func_02016f10
    b       _L_014e
_L_014a:
    mov     r0, #0
    mvn     r0, r0
_L_014e:
    ldr     r1, [pc, #0x100]
    str     r0, [r4, r1]
    ldr     r0, [r4, #0x20]
    add     r0, #0x24
    ldr     r0, [r0, #4]
    cmp     r0, #0
    beq     _L_0160
    add     r0, #0x40
    b       _L_0162
_L_0160:
    mov     r0, #0
_L_0162:
    cmp     r0, #0
    beq     _L_016e
    ldr     r1, [pc, #0xec]
    bl      func_02016f10
    b       _L_0172
_L_016e:
    mov     r0, #0
    mvn     r0, r0
_L_0172:
    ldr     r1, [pc, #0xe4]
    str     r0, [r4, r1]
    ldr     r0, [r4, #0x20]
    add     r0, #0x24
    ldr     r0, [r0, #4]
    cmp     r0, #0
    beq     _L_0184
    add     r0, #0x40
    b       _L_0186
_L_0184:
    mov     r0, #0
_L_0186:
    cmp     r0, #0
    beq     _L_0192
    ldr     r1, [pc, #0xd0]
    bl      func_02016f10
    b       _L_0196
_L_0192:
    mov     r0, #0
    mvn     r0, r0
_L_0196:
    ldr     r1, [pc, #0xc8]
    str     r0, [r4, r1]
    ldr     r0, [r5, #0xc]
    cmp     r0, #0
    beq     _L_01b0
    ldr     r3, [r4, #0]
    mov     r0, #0x20
    ldr     r2, [r4, #4]
    mov     r1, #0
    orr     r0, r3
    orr     r1, r2
    str     r0, [r4, #0]
    str     r1, [r4, #4]
_L_01b0:
    ldr     r0, [r5, #0x10]
    cmp     r0, #0
    beq     _L_01c8
    mov     r0, #1
    ldr     r3, [r4, #0]
    lsl     r0, r0, #0x10
    ldr     r2, [r4, #4]
    mov     r1, #0
    orr     r0, r3
    orr     r1, r2
    str     r0, [r4, #0]
    str     r1, [r4, #4]
_L_01c8:
    ldr     r0, [r5, #0x14]
    cmp     r0, #0
    beq     _L_01de
    ldr     r3, [r4, #0]
    mov     r0, #0
    ldr     r2, [r4, #4]
    mov     r1, #0x10
    orr     r0, r3
    orr     r1, r2
    str     r0, [r4, #0]
    str     r1, [r4, #4]
_L_01de:
    ldr     r0, [pc, #0x84]
    bl      func_02023588
    cmp     r0, #0
    beq     _L_01f8
    ldr     r3, [r4, #0]
    mov     r0, #0
    ldr     r2, [r4, #4]
    mov     r1, #0x80
    orr     r0, r3
    orr     r1, r2
    str     r0, [r4, #0]
    str     r1, [r4, #4]
_L_01f8:
    add     r0, r4, #0
    bl      func_ov022_0209f6e0
    add     sp, #0x98
    pop     {r3, r4, r5, pc}
    mov     r8, r8
    dcd     data_ov030_020b5a00
    dcd     0x000004bc
    dcd     data_ov030_020b591c
    dcd     data_ov030_020b5920
    dcd     data_ov030_020b5934
    dcd     data_ov030_020b5948
    dcd     func_ov030_020b3990
    dcd     0x00000664
    dcd     func_ov030_020b3cd4
    dcd     func_ov030_020b3d18
    dcd     func_ov030_020b35dc
    dcd     func_ov030_020b3694
    dcd     func_ov030_020b375c
    dcd     func_ov030_020b36cc
    dcd     func_ov030_020b3e24
    dcd     data_ov030_020b5880
    dcd     data_ov030_020b58a0
    dcd     0x00000518
    dcd     data_ov030_020b5860
    dcd     0x00000514
    dcd     data_ov030_020b5870
    dcd     0x0000051c
    dcd     data_ov030_020b5890
    dcd     0x00000524
    dcd     0x0000208a
}
