extern void NNSi_FndGetCurrentRootHeap(void);
extern char data_ov035_020b4b8c[];
extern char data_ov035_020b4b9c[];
extern char data_ov035_020b4bac[];
extern char data_ov035_020b4bbc[];
extern char data_ov035_020b4bcc[];
extern char data_ov035_020b4c1c[];
extern char data_ov035_020b4ca0[];
extern void func_02016f10(void);
extern void func_02020a9c(void);
extern void func_0202b850(void);
extern void func_0202b914(void);
extern void func_0202bfcc(void);
extern void func_0202d968(void);
extern void func_ov022_0209f6e0(void);
extern void func_ov035_020b34d0(void);
extern void func_ov035_020b353c(void);
extern void func_ov035_020b355c(void);
extern void func_ov035_020b36e0(void);
extern void func_ov035_020b37ec(void);
extern void func_ov035_020b3824(void);
extern void func_ov035_020b39a8(void);
extern void func_ov035_020b446c(void);

asm void func_ov035_020b32a0(void)
{
    push    {r3, r4, r5, lr}
    sub     sp, #0x18
    add     r5, r0, #0
    bl      NNSi_FndGetCurrentRootHeap
    add     r4, r0, #0
    ldr     r0, [pc, #0x1c4]
    mov     r3, #9
    str     r4, [r0, #0]
    ldr     r0, [r5, #0]
    mov     r2, #0
    strb    r0, [r4, #9]
    ldr     r1, [r5, #4]
    ldr     r0, [pc, #0x1bc]
    lsl     r3, r3, #8
    strb    r1, [r4, r0]
    ldrb    r1, [r5, #8]
    strb    r1, [r4, #8]
    mov     r1, #5
    str     r1, [r4, #0xc]
    str     r2, [r4, #0]
    str     r2, [r4, #4]
    str     r3, [sp, #0xc]
    mov     r3, #0xf
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
    ldr     r0, [pc, #0x18c]
    ldr     r3, [r5, #0]
    ldrsb   r0, [r4, r0]
    ldr     r1, [pc, #0x188]
    mov     r2, #1
    add     r3, r3, #7
_L_0056:
    bl      func_0202b914
    ldr     r1, [pc, #0x184]
    ldr     r0, [pc, #0x184]
    ldr     r2, [pc, #0x188]
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
    ldr     r2, [pc, #0x170]
    add     r1, #0x14
    str     r2, [r4, r1]
    add     r1, r0, #0
    ldr     r2, [pc, #0x16c]
    add     r1, #0x18
    str     r2, [r4, r1]
    ldr     r1, [pc, #0x168]
    add     r0, #0x20
    str     r1, [r4, r0]
_L_0092:
    bl      func_02020a9c
    cmp     r0, #0x2a
    beq     _L_009e
    ldr     r1, [pc, #0x160]
    b       _L_00a0
_L_009e:
    mov     r1, #0
_L_00a0:
    ldr     r0, [pc, #0x15c]
    str     r1, [r4, r0]
    ldr     r1, [pc, #0x15c]
    ldr     r0, [pc, #0x160]
    str     r1, [r4, r0]
    ldr     r0, [pc, #0x12c]
    ldrsb   r0, [r4, r0]
_L_00ae:
    bl      func_0202bfcc
    add     r1, r0, #0
    add     r0, r4, #0
    add     r0, #0x20
_L_00b8:
    bl      func_0202d968
    mov     r3, #0
    sub     r2, r3, #1
    ldr     r0, [pc, #0x148]
    b       _L_00cc
_L_00c4:
    lsl     r1, r3, #2
    add     r1, r4, r1
    str     r2, [r1, r0]
    add     r3, r3, #1
_L_00cc:
    cmp     r3, #5
    blt     _L_00c4
    ldr     r0, [r4, #0x20]
    add     r0, #0x24
    ldr     r0, [r0, #4]
    cmp     r0, #0
    beq     _L_00de
    add     r0, #0x40
    b       _L_00e0
_L_00de:
    mov     r0, #0
_L_00e0:
    cmp     r0, #0
    beq     _L_00ec
    ldr     r1, [pc, #0x128]
_L_00e6:
    bl      func_02016f10
    b       _L_00f0
_L_00ec:
    mov     r0, #0
    mvn     r0, r0
_L_00f0:
    mov     r1, #0x52
    lsl     r1, r1, #4
    str     r0, [r4, r1]
    ldr     r0, [r4, #0x20]
    add     r0, #0x24
    ldr     r0, [r0, #4]
    cmp     r0, #0
    beq     _L_0104
    add     r0, #0x40
    b       _L_0106
_L_0104:
    mov     r0, #0
_L_0106:
    cmp     r0, #0
    beq     _L_0112
    ldr     r1, [pc, #0x108]
_L_010c:
    bl      func_02016f10
    b       _L_0116
_L_0112:
    mov     r0, #0
    mvn     r0, r0
_L_0116:
    ldr     r1, [pc, #0x100]
    str     r0, [r4, r1]
    ldr     r0, [r4, #0x20]
    add     r0, #0x24
    ldr     r0, [r0, #4]
    cmp     r0, #0
    beq     _L_0128
    add     r0, #0x40
    b       _L_012a
_L_0128:
    mov     r0, #0
_L_012a:
    cmp     r0, #0
    beq     _L_0136
    ldr     r1, [pc, #0xec]
_L_0130:
    bl      func_02016f10
    b       _L_013a
_L_0136:
    mov     r0, #0
    mvn     r0, r0
_L_013a:
    ldr     r1, [pc, #0xd0]
    str     r0, [r4, r1]
    ldr     r0, [r4, #0x20]
    add     r0, #0x24
    ldr     r0, [r0, #4]
    cmp     r0, #0
    beq     _L_014c
    add     r0, #0x40
    b       _L_014e
_L_014c:
    mov     r0, #0
_L_014e:
    cmp     r0, #0
    beq     _L_015a
    ldr     r1, [pc, #0xcc]
_L_0154:
    bl      func_02016f10
    b       _L_015e
_L_015a:
    mov     r0, #0
    mvn     r0, r0
_L_015e:
    ldr     r1, [pc, #0xc4]
    str     r0, [r4, r1]
    ldr     r0, [r4, #0x20]
    add     r0, #0x24
    ldr     r0, [r0, #4]
    cmp     r0, #0
    beq     _L_0170
    add     r0, #0x40
    b       _L_0172
_L_0170:
    mov     r0, #0
_L_0172:
    cmp     r0, #0
    beq     _L_017e
    ldr     r1, [pc, #0xb0]
_L_0178:
    bl      func_02016f10
    b       _L_0182
_L_017e:
    mov     r0, #0
    mvn     r0, r0
_L_0182:
    ldr     r1, [pc, #0xa8]
    str     r0, [r4, r1]
    ldr     r0, [r5, #0xc]
    cmp     r0, #0
    beq     _L_019c
    ldr     r3, [r4, #0]
    mov     r0, #0x20
    ldr     r2, [r4, #4]
    mov     r1, #0
    orr     r0, r3
    orr     r1, r2
    str     r0, [r4, #0]
    str     r1, [r4, #4]
_L_019c:
    ldr     r0, [r5, #0x10]
    cmp     r0, #0
    beq     _L_01b4
    mov     r0, #1
    ldr     r3, [r4, #0]
    lsl     r0, r0, #0x10
    ldr     r2, [r4, #4]
    mov     r1, #0
    orr     r0, r3
    orr     r1, r2
    str     r0, [r4, #0]
    str     r1, [r4, #4]
_L_01b4:
    ldr     r0, [r5, #0x14]
    cmp     r0, #0
    beq     _L_01ca
    ldr     r3, [r4, #0]
    mov     r0, #0
    ldr     r2, [r4, #4]
    mov     r1, #0x10
    orr     r0, r3
    orr     r1, r2
    str     r0, [r4, #0]
    str     r1, [r4, #4]
_L_01ca:
    add     r0, r4, #0
_L_01cc:
    bl      func_ov022_0209f6e0
    add     sp, #0x18
    pop     {r3, r4, r5, pc}
    dcd     data_ov035_020b4ca0
    dcd     0x000004bc
    dcd     data_ov035_020b4c1c
    dcd     func_ov035_020b355c
    dcd     0x00000664
    dcd     func_ov035_020b36e0
    dcd     func_ov035_020b37ec
    dcd     func_ov035_020b34d0
    dcd     func_ov035_020b353c
    dcd     func_ov035_020b3824
    dcd     func_ov035_020b39a8
    dcd     0x0000068c
    dcd     func_ov035_020b446c
    dcd     0x00000688
    dcd     0x00000514
    dcd     data_ov035_020b4bbc
    dcd     data_ov035_020b4bcc
    dcd     0x00000518
    dcd     data_ov035_020b4bac
    dcd     data_ov035_020b4b8c
    dcd     0x0000051c
    dcd     data_ov035_020b4b9c
    dcd     0x00000524
}
