extern void NNSi_FndGetCurrentRootHeap(void);
extern void func_0202b850(void);
extern void func_0202b914(void);
extern void func_0202bfcc(void);
extern void func_0202d968(void);
extern void func_02016f10(void);
extern void func_ov022_0209f6e0(void);
extern void data_ov078_020ba4e0(void);
extern void data_ov078_020ba45c(void);
extern void data_ov078_020ba470(void);
extern void func_ov078_020b8450(void);
extern void func_ov078_020b8768(void);
extern void func_ov078_020b89b4(void);
extern void func_ov078_020b8360(void);
extern void func_ov078_020b8428(void);
extern void func_ov078_020b89ec(void);
extern void func_ov078_020b8b88(void);
extern void func_ov078_020b99c8(void);
extern void data_ov078_020ba2f4(void);
extern void data_ov078_020ba2e4(void);
extern void data_ov078_020ba304(void);

asm void func_ov078_020b817c(void)
{
    push    {r3, r4, r5, lr}
    sub     sp, #0x18
    add     r5, r0, #0
    bl      NNSi_FndGetCurrentRootHeap
    add     r4, r0, #0
    ldr     r0, [pc, #0x188]
    mov     r3, #9
    str     r4, [r0, #0]
    ldr     r0, [r5, #0]
    mov     r2, #0
    strb    r0, [r4, #9]
    ldr     r1, [r5, #4]
    ldr     r0, [pc, #0x180]
    strb    r1, [r4, r0]
    ldrb    r1, [r5, #8]
    strb    r1, [r4, #8]
    str     r3, [r4, #0xc]
    str     r2, [r4, #0]
    str     r2, [r4, #4]
    lsl     r3, r3, #8
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
    ldr     r0, [pc, #0x14c]
    bne     _L_0060
    ldr     r3, [r5, #0]
    ldrsb   r0, [r4, r0]
    ldr     r1, [pc, #0x148]
    mov     r2, #1
    add     r3, r3, #7
    bl      func_0202b914
    b       _L_006e
_L_0060:
    ldr     r3, [r5, #0]
    ldrsb   r0, [r4, r0]
    ldr     r1, [pc, #0x13c]
    mov     r2, #1
    add     r3, r3, #7
    bl      func_0202b914
_L_006e:
    ldr     r1, [pc, #0x138]
    ldr     r0, [pc, #0x138]
    ldr     r2, [pc, #0x13c]
    str     r1, [r4, r0]
    add     r1, r0, #4
    str     r2, [r4, r1]
    add     r1, r0, #0
    ldr     r2, [pc, #0x134]
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
    ldr     r1, [pc, #0x114]
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
    ldr     r0, [pc, #0xfc]
    b       _L_00d8
_L_00d0:
    lsl     r1, r3, #2
    add     r1, r4, r1
    str     r2, [r1, r0]
    add     r3, r3, #1
_L_00d8:
    cmp     r3, #5
    blt     _L_00d0
    ldr     r0, [r4, #0x20]
    add     r0, #0x24
    ldr     r0, [r0, #4]
    cmp     r0, #0
    beq     _L_00ea
    add     r0, #0x40
    b       _L_00ec
_L_00ea:
    mov     r0, #0
_L_00ec:
    cmp     r0, #0
    beq     _L_00f8
    ldr     r1, [pc, #0xdc]
    bl      func_02016f10
    b       _L_00fc
_L_00f8:
    mov     r0, #0
    mvn     r0, r0
_L_00fc:
    mov     r1, #0x52
    lsl     r1, r1, #4
    str     r0, [r4, r1]
    ldr     r0, [r4, #0x20]
    add     r0, #0x24
    ldr     r0, [r0, #4]
    cmp     r0, #0
    beq     _L_0110
    add     r0, #0x40
    b       _L_0112
_L_0110:
    mov     r0, #0
_L_0112:
    cmp     r0, #0
    beq     _L_011e
    ldr     r1, [pc, #0xbc]
    bl      func_02016f10
    b       _L_0122
_L_011e:
    mov     r0, #0
    mvn     r0, r0
_L_0122:
    ldr     r1, [pc, #0xb4]
    str     r0, [r4, r1]
    ldr     r0, [r4, #0x20]
    add     r0, #0x24
    ldr     r0, [r0, #4]
    cmp     r0, #0
    beq     _L_0134
    add     r0, #0x40
    b       _L_0136
_L_0134:
    mov     r0, #0
_L_0136:
    cmp     r0, #0
    beq     _L_0142
    ldr     r1, [pc, #0xa0]
    bl      func_02016f10
    b       _L_0146
_L_0142:
    mov     r0, #0
    mvn     r0, r0
_L_0146:
    ldr     r1, [pc, #0x98]
    str     r0, [r4, r1]
    ldr     r0, [r5, #0xc]
    cmp     r0, #0
    beq     _L_0160
    ldr     r3, [r4, #0]
    mov     r0, #0x20
    ldr     r2, [r4, #4]
    mov     r1, #0
    orr     r0, r3
    orr     r1, r2
    str     r0, [r4, #0]
    str     r1, [r4, #4]
_L_0160:
    ldr     r0, [r5, #0x10]
    cmp     r0, #0
    beq     _L_0178
    mov     r0, #1
    ldr     r3, [r4, #0]
    lsl     r0, r0, #0x10
    ldr     r2, [r4, #4]
    mov     r1, #0
    orr     r0, r3
    orr     r1, r2
    str     r0, [r4, #0]
    str     r1, [r4, #4]
_L_0178:
    ldr     r0, [r5, #0x14]
    cmp     r0, #0
    beq     _L_018e
    ldr     r3, [r4, #0]
    mov     r0, #0
    ldr     r2, [r4, #4]
    mov     r1, #0x10
    orr     r0, r3
    orr     r1, r2
    str     r0, [r4, #0]
    str     r1, [r4, #4]
_L_018e:
    add     r0, r4, #0
    bl      func_ov022_0209f6e0
    add     sp, #0x18
    pop     {r3, r4, r5, pc}
    dcd     data_ov078_020ba4e0
    lsl     r4, r7, #0x12
    lsl     r0, r0, #0
    dcd     data_ov078_020ba45c
    dcd     data_ov078_020ba470
    dcd     func_ov078_020b8450
    lsl     r4, r4, #0x19
    lsl     r0, r0, #0
    dcd     func_ov078_020b8768
    dcd     func_ov078_020b89b4
    dcd     func_ov078_020b8360
    dcd     func_ov078_020b8428
    dcd     func_ov078_020b89ec
    dcd     func_ov078_020b8b88
    dcd     func_ov078_020b99c8
    lsl     r4, r2, #0x14
    lsl     r0, r0, #0
    dcd     data_ov078_020ba2f4
    dcd     data_ov078_020ba2e4
    lsl     r4, r3, #0x14
    lsl     r0, r0, #0
    dcd     data_ov078_020ba304
    lsl     r4, r4, #0x14
    lsl     r0, r0, #0
}
