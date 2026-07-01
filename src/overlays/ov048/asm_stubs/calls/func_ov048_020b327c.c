extern void NNSi_FndGetCurrentRootHeap(void);
extern char data_ov048_020b4a4c[];
extern char data_ov048_020b4a5c[];
extern char data_ov048_020b4a6c[];
extern char data_ov048_020b4a7c[];
extern char data_ov048_020b4ae8[];
extern char data_ov048_020b4b80[];
extern void func_02016f10(void);
extern void func_0202b850(void);
extern void func_0202b914(void);
extern void func_0202bfcc(void);
extern void func_0202d968(void);
extern void func_ov022_0209f6e0(void);
extern void func_ov048_020b3474(void);
extern void func_ov048_020b34ac(void);
extern void func_ov048_020b34cc(void);
extern void func_ov048_020b359c(void);
extern void func_ov048_020b360c(void);
extern void func_ov048_020b3850(void);
extern void func_ov048_020b3888(void);
extern void func_ov048_020b4340(void);

asm void func_ov048_020b327c(void)
{
    push    {r3, r4, r5, lr}
    sub     sp, #0x18
    add     r5, r0, #0
_L_0006:
    bl      NNSi_FndGetCurrentRootHeap
    add     r4, r0, #0
    ldr     r0, [pc, #0x198]
    mov     r3, #0x12
    str     r4, [r0, #0]
    ldr     r0, [r5, #0]
    mov     r2, #0
    strb    r0, [r4, #9]
    ldr     r1, [r5, #4]
    ldr     r0, [pc, #0x190]
    strb    r1, [r4, r0]
    ldrb    r1, [r5, #8]
    strb    r1, [r4, #8]
    str     r3, [r4, #0xc]
    str     r2, [r4, #0]
    str     r2, [r4, #4]
    lsl     r3, r3, #7
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
_L_0044:
    bl      func_0202b850
    ldr     r0, [pc, #0x160]
    ldr     r3, [r5, #0]
    ldrsb   r0, [r4, r0]
    ldr     r1, [pc, #0x160]
    mov     r2, #1
    add     r3, r3, #7
_L_0054:
    bl      func_0202b914
    ldr     r1, [pc, #0x158]
    ldr     r0, [pc, #0x15c]
    ldr     r2, [pc, #0x15c]
    str     r1, [r4, r0]
    add     r1, r0, #4
    str     r2, [r4, r1]
    add     r1, r0, #0
    ldr     r2, [pc, #0x158]
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
    ldr     r1, [pc, #0x138]
    add     r0, #0x24
    str     r1, [r4, r0]
    ldr     r0, [pc, #0x108]
    ldrsb   r0, [r4, r0]
_L_00a4:
    bl      func_0202bfcc
    add     r1, r0, #0
    add     r0, r4, #0
    add     r0, #0x20
_L_00ae:
    bl      func_0202d968
    mov     r3, #0
    sub     r2, r3, #1
    ldr     r0, [pc, #0x120]
    b       _L_00c2
_L_00ba:
    lsl     r1, r3, #2
    add     r1, r4, r1
    str     r2, [r1, r0]
    add     r3, r3, #1
_L_00c2:
    cmp     r3, #5
    blt     _L_00ba
    ldr     r0, [r4, #0x20]
    add     r0, #0x24
    ldr     r0, [r0, #4]
    cmp     r0, #0
    beq     _L_00d4
    add     r0, #0x40
    b       _L_00d6
_L_00d4:
    mov     r0, #0
_L_00d6:
    cmp     r0, #0
    beq     _L_00e2
    ldr     r1, [pc, #0x100]
_L_00dc:
    bl      func_02016f10
    b       _L_00e6
_L_00e2:
    mov     r0, #0
    mvn     r0, r0
_L_00e6:
    mov     r1, #0x52
    lsl     r1, r1, #4
    str     r0, [r4, r1]
    ldr     r0, [r4, #0x20]
    add     r0, #0x24
    ldr     r0, [r0, #4]
    cmp     r0, #0
    beq     _L_00fa
    add     r0, #0x40
    b       _L_00fc
_L_00fa:
    mov     r0, #0
_L_00fc:
    cmp     r0, #0
    beq     _L_0108
    ldr     r1, [pc, #0xdc]
_L_0102:
    bl      func_02016f10
    b       _L_010c
_L_0108:
    mov     r0, #0
    mvn     r0, r0
_L_010c:
    ldr     r1, [pc, #0xd4]
    str     r0, [r4, r1]
    ldr     r0, [r4, #0x20]
    add     r0, #0x24
    ldr     r0, [r0, #4]
    cmp     r0, #0
    beq     _L_011e
    add     r0, #0x40
    b       _L_0120
_L_011e:
    mov     r0, #0
_L_0120:
    cmp     r0, #0
    beq     _L_012c
    ldr     r1, [pc, #0xc0]
_L_0126:
    bl      func_02016f10
    b       _L_0130
_L_012c:
    mov     r0, #0
    mvn     r0, r0
_L_0130:
    ldr     r1, [pc, #0xb8]
    str     r0, [r4, r1]
    ldr     r0, [r4, #0x20]
    add     r0, #0x24
    ldr     r0, [r0, #4]
    cmp     r0, #0
    beq     _L_0142
    add     r0, #0x40
    b       _L_0144
_L_0142:
    mov     r0, #0
_L_0144:
    cmp     r0, #0
    beq     _L_0150
    ldr     r1, [pc, #0xa4]
_L_014a:
    bl      func_02016f10
    b       _L_0154
_L_0150:
    mov     r0, #0
    mvn     r0, r0
_L_0154:
    ldr     r1, [pc, #0x9c]
    str     r0, [r4, r1]
    ldr     r0, [r5, #0xc]
    cmp     r0, #0
    beq     _L_016e
    ldr     r3, [r4, #0]
    mov     r0, #0x20
    ldr     r2, [r4, #4]
    mov     r1, #0
    orr     r0, r3
    orr     r1, r2
    str     r0, [r4, #0]
    str     r1, [r4, #4]
_L_016e:
    ldr     r0, [r5, #0x10]
    cmp     r0, #0
    beq     _L_0186
    mov     r0, #1
    ldr     r3, [r4, #0]
    lsl     r0, r0, #0x10
    ldr     r2, [r4, #4]
    mov     r1, #0
    orr     r0, r3
    orr     r1, r2
    str     r0, [r4, #0]
    str     r1, [r4, #4]
_L_0186:
    ldr     r0, [r5, #0x14]
    cmp     r0, #0
    beq     _L_019c
    ldr     r3, [r4, #0]
    mov     r0, #0
    ldr     r2, [r4, #4]
    mov     r1, #0x10
    orr     r0, r3
    orr     r1, r2
    str     r0, [r4, #0]
    str     r1, [r4, #4]
_L_019c:
    add     r0, r4, #0
_L_019e:
    bl      func_ov022_0209f6e0
    add     sp, #0x18
    pop     {r3, r4, r5, pc}
    mov     r8, r8
    dcd     data_ov048_020b4b80
    lsl     r4, r7, #0x12
    lsl     r0, r0, #0
    dcd     data_ov048_020b4ae8
    dcd     func_ov048_020b34cc
    lsl     r4, r4, #0x19
    lsl     r0, r0, #0
    dcd     func_ov048_020b359c
    dcd     func_ov048_020b3850
    dcd     func_ov048_020b3474
    dcd     func_ov048_020b34ac
    dcd     func_ov048_020b360c
    dcd     func_ov048_020b3888
    dcd     func_ov048_020b4340
    lsl     r4, r2, #0x14
    lsl     r0, r0, #0
    dcd     data_ov048_020b4a7c
    dcd     data_ov048_020b4a6c
    lsl     r0, r3, #0x14
    lsl     r0, r0, #0
    dcd     data_ov048_020b4a5c
    lsl     r4, r3, #0x14
    lsl     r0, r0, #0
    dcd     data_ov048_020b4a4c
    lsl     r4, r4, #0x14
    lsl     r0, r0, #0
}
