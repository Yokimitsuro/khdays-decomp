extern char data_ov022_020b2930[];
extern char data_ov052_020b7f10[];
extern char data_ov052_020b80c0[];
extern void func_02023930(void);
extern void func_0202a634(void);
extern void func_0202accc(void);
extern void func_ov022_0209fb60(void);
extern void func_ov022_0209fb98(void);
extern void func_ov052_020b6bdc(void);

asm void func_ov052_020b5d24(void)
{
    push    {r4, r5, r6, r7, lr}
    sub     sp, #0x14
    add     r4, r0, #0
    ldr     r0, [pc, #0x100]
    mov     r1, #0
    ldr     r5, [r0, #0]
    ldr     r0, [pc, #0xfc]
    mov     r2, #1
    add     r6, r4, r0
    add     r0, r5, #0
_L_0014:
    bl      func_ov022_0209fb60
    add     r0, r5, #0
    mov     r1, #0
    mov     r2, #1
_L_001e:
    bl      func_ov022_0209fb98
    ldr     r1, [pc, #0xec]
    ldrsb   r0, [r5, r1]
    cmp     r0, #0
    beq     _L_0036
    sub     r0, r1, #1
    ldrb    r2, [r5, r0]
    mov     r0, #1
    orr     r2, r0
    sub     r0, r1, #1
    strb    r2, [r5, r0]
_L_0036:
    add     r0, r5, #0
    mov     r1, #1
    mov     r2, #2
_L_003c:
    bl      func_ov022_0209fb60
    mov     r1, #1
    add     r0, r5, #0
    add     r2, r1, #0
_L_0046:
    bl      func_ov022_0209fb98
    ldr     r1, [pc, #0xc8]
    ldrsb   r0, [r5, r1]
    cmp     r0, #0
    beq     _L_005e
    sub     r0, r1, #1
    ldrb    r2, [r5, r0]
    mov     r0, #1
    orr     r2, r0
    sub     r0, r1, #1
    strb    r2, [r5, r0]
_L_005e:
    add     r0, r5, #0
    ldrb    r7, [r6, #0x13]
_L_0062:
    bl      func_ov052_020b6bdc
    ldr     r3, [pc, #0xb0]
    add     r2, sp, #0
    ldmia   r3!, {r0, r1}
    mov     ip, r2
    stmia   r2!, {r0, r1}
    ldmia   r3!, {r0, r1}
    stmia   r2!, {r0, r1}
    ldr     r0, [r3, #0]
    mov     r3, #2
    str     r0, [r2, #0]
    ldr     r0, [pc, #0xa0]
    lsl     r3, r3, #0xe
    ldr     r0, [r4, r0]
    ldr     r2, [pc, #0x9c]
    add     r0, r0, r3
    and     r0, r2
    lsl     r1, r0, #7
    lsl     r0, r3, #0x10
    orr     r0, r1
    ldrb    r1, [r6, #0]
    lsr     r2, r2, #0xf
    add     r1, #0x28
    and     r1, r2
    orr     r0, r1
    str     r0, [sp, #0]
    ldrb    r0, [r4, #9]
    ldr     r1, [sp, #0x10]
    add     r0, r1, r0
    str     r0, [sp, #0x10]
    ldr     r0, [pc, #0x80]
    mov     r1, ip
_L_00a4:
    bl      func_02023930
    ldr     r1, [pc, #0x7c]
    add     r7, #0x78
    str     r0, [r5, r1]
    ldr     r0, [pc, #0x7c]
    add     r1, #8
    mov     r6, #0
    add     r5, r5, r1
    and     r7, r0
_L_00b8:
    ldr     r1, [pc, #0x60]
    ldrb    r3, [r4, #9]
    ldr     r2, [r4, r1]
    mov     r1, #2
    lsl     r1, r1, #0xe
    add     r2, r2, r1
    ldr     r1, [pc, #0x58]
    add     r0, r5, #0
    and     r1, r2
    lsl     r2, r1, #7
    mov     r1, #2
    lsl     r1, r1, #0x1e
    orr     r1, r2
    orr     r1, r7
    mov     r2, #1
    add     r3, r3, #7
_L_00d8:
    bl      func_0202a634
    mov     r1, #0
    add     r2, r5, #0
    add     r0, r5, #0
    add     r2, #0xe0
    add     r3, r1, #0
_L_00e6:
    bl      func_0202accc
    add     r2, r5, #0
    add     r0, r5, #0
    mov     r1, #2
    add     r2, #0xe0
    mov     r3, #0
_L_00f4:
    bl      func_0202accc
    mov     r0, #0x42
    lsl     r0, r0, #2
    add     r6, r6, #1
    add     r5, r5, r0
    cmp     r6, #2
    blt     _L_00b8
    add     sp, #0x14
    pop     {r4, r5, r6, r7, pc}
    dcd     data_ov052_020b80c0
    lsr     r0, r3, #4
    lsl     r0, r0, #0
    lsr     r1, r5, #0x16
    lsl     r0, r0, #0
    lsr     r5, r1, #0x1c
    lsl     r0, r0, #0
    dcd     data_ov052_020b7f10
    cmp     r3, #0xd0
    lsl     r0, r0, #0
    dcd     0x00fffffc
    dcd     data_ov022_020b2930
    dcd     0x00002c2c
    dcd     0x000001ff
}
