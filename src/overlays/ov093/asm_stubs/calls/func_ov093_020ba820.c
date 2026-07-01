extern void NNSi_FndGetCurrentRootHeap(void);
extern char data_ov093_020bc2c4[];
extern char data_ov093_020bc2d4[];
extern char data_ov093_020bc2e4[];
extern char data_ov093_020bc2f4[];
extern char data_ov093_020bc304[];
extern char data_ov093_020bc348[];
extern char data_ov093_020bc35c[];
extern char data_ov093_020bc3c0[];
extern void func_02016f10(void);
extern void func_0202b850(void);
extern void func_0202b914(void);
extern void func_0202bfcc(void);
extern void func_0202d968(void);
extern void func_ov022_0209f6e0(void);
extern void func_ov093_020baa68(void);
extern void func_ov093_020baad4(void);
extern void func_ov093_020baafc(void);
extern void func_ov093_020babc8(void);
extern void func_ov093_020bacd0(void);
extern void func_ov093_020bad08(void);
extern void func_ov093_020bad98(void);
extern void func_ov093_020bafdc(void);
extern void func_ov093_020bb210(void);

asm void func_ov093_020ba820(void)
{
    push    {r3, r4, r5, lr}
    sub     sp, #0x18
    add     r5, r0, #0
    bl      NNSi_FndGetCurrentRootHeap
    add     r4, r0, #0
    ldr     r0, [pc, #0x1dc]
    mov     r3, #9
    str     r4, [r0, #0]
    ldr     r0, [r5, #0]
    mov     r2, #0
    strb    r0, [r4, #9]
    ldr     r1, [r5, #4]
    ldr     r0, [pc, #0x1d4]
    lsl     r3, r3, #8
    strb    r1, [r4, r0]
    ldrb    r1, [r5, #8]
    strb    r1, [r4, #8]
    mov     r1, #7
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
_L_0046:
    bl      func_0202b850
    ldr     r0, [r5, #0x18]
    cmp     r0, #0
    ldr     r0, [pc, #0x1a0]
    bne     _L_0062
    ldr     r3, [r5, #0]
    ldrsb   r0, [r4, r0]
    ldr     r1, [pc, #0x19c]
    mov     r2, #1
    add     r3, r3, #7
_L_005c:
    bl      func_0202b914
    b       _L_0070
_L_0062:
    ldr     r3, [r5, #0]
    ldrsb   r0, [r4, r0]
    ldr     r1, [pc, #0x190]
    mov     r2, #1
    add     r3, r3, #7
_L_006c:
    bl      func_0202b914
_L_0070:
    ldr     r1, [pc, #0x188]
    ldr     r0, [pc, #0x18c]
    ldr     r2, [pc, #0x18c]
    str     r1, [r4, r0]
    add     r1, r0, #4
    str     r2, [r4, r1]
    add     r1, r0, #0
    ldr     r2, [pc, #0x188]
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
    ldr     r2, [pc, #0x174]
    add     r1, #0x14
    str     r2, [r4, r1]
    add     r1, r0, #0
    ldr     r2, [pc, #0x170]
    add     r1, #0x18
    str     r2, [r4, r1]
    add     r1, r0, #0
    ldr     r2, [pc, #0x16c]
    add     r1, #0x20
    str     r2, [r4, r1]
    add     r1, r0, #0
    ldr     r2, [pc, #0x168]
    add     r1, #0x1c
    str     r2, [r4, r1]
    add     r1, r0, #0
    ldr     r2, [pc, #0x164]
    add     r1, #0x28
    str     r2, [r4, r1]
    ldr     r1, [pc, #0x164]
    add     r0, #0x24
    str     r1, [r4, r0]
    ldr     r0, [pc, #0x12c]
    ldrsb   r0, [r4, r0]
_L_00c4:
    bl      func_0202bfcc
    add     r1, r0, #0
    add     r0, r4, #0
    add     r0, #0x20
_L_00ce:
    bl      func_0202d968
    mov     r3, #0
    sub     r2, r3, #1
    ldr     r0, [pc, #0x14c]
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
    ldr     r1, [pc, #0x12c]
_L_00fc:
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
    ldr     r1, [pc, #0x108]
_L_0122:
    bl      func_02016f10
    b       _L_012c
_L_0128:
    mov     r0, #0
    mvn     r0, r0
_L_012c:
    ldr     r1, [pc, #0x100]
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
    ldr     r1, [pc, #0xec]
_L_0146:
    bl      func_02016f10
    b       _L_0150
_L_014c:
    mov     r0, #0
    mvn     r0, r0
_L_0150:
    ldr     r1, [pc, #0xd0]
    str     r0, [r4, r1]
    ldr     r0, [r4, #0x20]
    add     r0, #0x24
    ldr     r0, [r0, #4]
    cmp     r0, #0
    beq     _L_0162
    add     r0, #0x40
    b       _L_0164
_L_0162:
    mov     r0, #0
_L_0164:
    cmp     r0, #0
    beq     _L_0170
    ldr     r1, [pc, #0xcc]
_L_016a:
    bl      func_02016f10
    b       _L_0174
_L_0170:
    mov     r0, #0
    mvn     r0, r0
_L_0174:
    ldr     r1, [pc, #0xc4]
    str     r0, [r4, r1]
    ldr     r0, [r4, #0x20]
    add     r0, #0x24
    ldr     r0, [r0, #4]
    cmp     r0, #0
    beq     _L_0186
    add     r0, #0x40
    b       _L_0188
_L_0186:
    mov     r0, #0
_L_0188:
    cmp     r0, #0
    beq     _L_0194
    ldr     r1, [pc, #0xb0]
_L_018e:
    bl      func_02016f10
    b       _L_0198
_L_0194:
    mov     r0, #0
    mvn     r0, r0
_L_0198:
    ldr     r1, [pc, #0xa8]
    str     r0, [r4, r1]
    ldr     r0, [r5, #0xc]
    cmp     r0, #0
    beq     _L_01b2
    ldr     r3, [r4, #0]
    mov     r0, #0x20
    ldr     r2, [r4, #4]
    mov     r1, #0
    orr     r0, r3
    orr     r1, r2
    str     r0, [r4, #0]
    str     r1, [r4, #4]
_L_01b2:
    ldr     r0, [r5, #0x10]
    cmp     r0, #0
    beq     _L_01ca
    mov     r0, #1
    ldr     r3, [r4, #0]
    lsl     r0, r0, #0x10
    ldr     r2, [r4, #4]
    mov     r1, #0
    orr     r0, r3
    orr     r1, r2
    str     r0, [r4, #0]
    str     r1, [r4, #4]
_L_01ca:
    ldr     r0, [r5, #0x14]
    cmp     r0, #0
    beq     _L_01e0
    ldr     r3, [r4, #0]
    mov     r0, #0
    ldr     r2, [r4, #4]
    mov     r1, #0x10
    orr     r0, r3
    orr     r1, r2
    str     r0, [r4, #0]
    str     r1, [r4, #4]
_L_01e0:
    add     r0, r4, #0
_L_01e2:
    bl      func_ov022_0209f6e0
    add     sp, #0x18
    pop     {r3, r4, r5, pc}
    mov     r8, r8
    dcd     data_ov093_020bc3c0
    dcd     0x000004bc
    dcd     data_ov093_020bc348
    dcd     data_ov093_020bc35c
    dcd     func_ov093_020baafc
    dcd     0x00000664
    dcd     func_ov093_020babc8
    dcd     func_ov093_020bacd0
    dcd     func_ov093_020baa68
    dcd     func_ov093_020baad4
    dcd     func_ov093_020bad98
    dcd     func_ov093_020bafdc
    dcd     func_ov093_020bad08
    dcd     func_ov093_020bb210
    dcd     0x00000514
    dcd     data_ov093_020bc2e4
    dcd     data_ov093_020bc2f4
    dcd     0x00000518
    dcd     data_ov093_020bc2c4
    dcd     data_ov093_020bc2d4
    dcd     0x0000051c
    dcd     data_ov093_020bc304
    dcd     0x00000524
}
