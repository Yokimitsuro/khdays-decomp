extern void NNSi_FndGetCurrentRootHeap(void);
extern void OS_SPrintf(void);
extern char data_ov082_020ba374[];
extern char data_ov082_020ba384[];
extern char data_ov082_020ba394[];
extern char data_ov082_020ba3a4[];
extern char data_ov082_020ba408[];
extern char data_ov082_020ba40c[];
extern char data_ov082_020ba420[];
extern char data_ov082_020ba434[];
extern char data_ov082_020ba448[];
extern char data_ov082_020ba500[];
extern void func_02016f10(void);
extern void func_0202b850(void);
extern void func_0202b914(void);
extern void func_0202bfcc(void);
extern void func_0202d968(void);
extern void func_ov022_0209f6e0(void);
extern void func_ov082_020b843c(void);
extern void func_ov082_020b84dc(void);
extern void func_ov082_020b8514(void);
extern void func_ov082_020b882c(void);
extern void func_ov082_020b8870(void);
extern void func_ov082_020b888c(void);
extern void func_ov082_020b890c(void);
extern void func_ov082_020b895c(void);

asm void func_ov082_020b81f4(void)
{
    push    {r3, r4, r5, lr}
    sub     sp, #0x98
    add     r5, r0, #0
    bl      NNSi_FndGetCurrentRootHeap
    add     r4, r0, #0
    ldr     r0, [pc, #0x1d8]
    mov     r3, #9
    str     r4, [r0, #0]
    ldr     r0, [r5, #0]
    mov     r2, #0
    strb    r0, [r4, #9]
    ldr     r1, [r5, #4]
    ldr     r0, [pc, #0x1d0]
    lsl     r3, r3, #8
    strb    r1, [r4, r0]
    ldrb    r1, [r5, #8]
    strb    r1, [r4, #8]
    mov     r1, #0xe
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
    ldr     r0, [r5, #0x1c]
    ldr     r1, [r5, #0x18]
    cmp     r0, #0
    beq     _L_0058
    cmp     r0, #1
    beq     _L_0072
    b       _L_008a
_L_0058:
    cmp     r1, #0
    add     r0, sp, #0x18
    beq     _L_0068
    ldr     r1, [pc, #0x190]
    ldr     r2, [pc, #0x190]
_L_0062:
    bl      OS_SPrintf
    b       _L_008a
_L_0068:
    ldr     r1, [pc, #0x184]
    ldr     r2, [pc, #0x18c]
_L_006c:
    bl      OS_SPrintf
    b       _L_008a
_L_0072:
    cmp     r1, #0
    add     r0, sp, #0x18
    beq     _L_0082
    ldr     r1, [pc, #0x174]
    ldr     r2, [pc, #0x180]
_L_007c:
    bl      OS_SPrintf
    b       _L_008a
_L_0082:
    ldr     r1, [pc, #0x16c]
    ldr     r2, [pc, #0x178]
_L_0086:
    bl      OS_SPrintf
_L_008a:
    ldr     r0, [pc, #0x160]
    ldr     r3, [r5, #0]
    ldrsb   r0, [r4, r0]
    add     r1, sp, #0x18
    mov     r2, #1
    add     r3, r3, #7
_L_0096:
    bl      func_0202b914
    ldr     r1, [pc, #0x168]
    ldr     r0, [pc, #0x168]
    ldr     r2, [pc, #0x16c]
    str     r1, [r4, r0]
    add     r1, r0, #4
    str     r2, [r4, r1]
    add     r1, r0, #0
    ldr     r2, [pc, #0x164]
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
    ldr     r2, [pc, #0x154]
    add     r1, #0x14
    str     r2, [r4, r1]
    add     r1, r0, #0
    ldr     r2, [pc, #0x150]
    add     r1, #0x18
    str     r2, [r4, r1]
    add     r1, r0, #0
    ldr     r2, [pc, #0x14c]
    add     r1, #0x20
    str     r2, [r4, r1]
    add     r1, r0, #0
    ldr     r2, [pc, #0x148]
    add     r1, #0x28
    str     r2, [r4, r1]
    ldr     r1, [pc, #0x144]
    add     r0, #0x24
    str     r1, [r4, r0]
    ldr     r0, [pc, #0x108]
    ldrsb   r0, [r4, r0]
_L_00e6:
    bl      func_0202bfcc
    add     r1, r0, #0
    add     r0, r4, #0
    add     r0, #0x20
_L_00f0:
    bl      func_0202d968
    mov     r3, #0
    sub     r2, r3, #1
    ldr     r0, [pc, #0x12c]
    b       _L_0104
_L_00fc:
    lsl     r1, r3, #2
    add     r1, r4, r1
    str     r2, [r1, r0]
    add     r3, r3, #1
_L_0104:
    cmp     r3, #5
    blt     _L_00fc
    ldr     r0, [r4, #0x20]
    add     r0, #0x24
    ldr     r0, [r0, #4]
    cmp     r0, #0
    beq     _L_0116
    add     r0, #0x40
    b       _L_0118
_L_0116:
    mov     r0, #0
_L_0118:
    cmp     r0, #0
    beq     _L_0124
    ldr     r1, [pc, #0x10c]
_L_011e:
    bl      func_02016f10
    b       _L_0128
_L_0124:
    mov     r0, #0
    mvn     r0, r0
_L_0128:
    mov     r1, #0x52
    lsl     r1, r1, #4
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
    ldr     r1, [pc, #0xec]
_L_0144:
    bl      func_02016f10
    b       _L_014e
_L_014a:
    mov     r0, #0
    mvn     r0, r0
_L_014e:
    ldr     r1, [pc, #0xe4]
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
    ldr     r1, [pc, #0xd0]
_L_0168:
    bl      func_02016f10
    b       _L_0172
_L_016e:
    mov     r0, #0
    mvn     r0, r0
_L_0172:
    ldr     r1, [pc, #0xc8]
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
    ldr     r1, [pc, #0xb4]
_L_018c:
    bl      func_02016f10
    b       _L_0196
_L_0192:
    mov     r0, #0
    mvn     r0, r0
_L_0196:
    ldr     r1, [pc, #0xac]
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
    add     r0, r4, #0
_L_01e0:
    bl      func_ov022_0209f6e0
    add     sp, #0x98
    pop     {r3, r4, r5, pc}
    dcd     data_ov082_020ba500
    dcd     0x000004bc
    dcd     data_ov082_020ba408
    dcd     data_ov082_020ba40c
    dcd     data_ov082_020ba420
    dcd     data_ov082_020ba434
    dcd     data_ov082_020ba448
    dcd     func_ov082_020b8514
    dcd     0x00000664
    dcd     func_ov082_020b882c
    dcd     func_ov082_020b8870
    dcd     func_ov082_020b843c
    dcd     func_ov082_020b84dc
    dcd     func_ov082_020b890c
    dcd     func_ov082_020b888c
    dcd     func_ov082_020b895c
    dcd     0x00000514
    dcd     data_ov082_020ba384
    dcd     data_ov082_020ba3a4
    dcd     0x00000518
    dcd     data_ov082_020ba394
    dcd     0x0000051c
    dcd     data_ov082_020ba374
    dcd     0x00000524
}
