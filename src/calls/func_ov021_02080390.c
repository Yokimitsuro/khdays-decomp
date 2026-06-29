extern char data_ov021_02080f18[];
extern void func_0202b450(void);
extern void func_02030788(void);
extern void func_ov002_0206b84c(void);
extern void func_ov002_0206cf4c(void);
extern void func_ov002_02076480(void);
extern void func_ov002_02076968(void);
extern void func_ov002_02076a38(void);
extern void func_ov002_02077b30(void);
extern void func_ov002_0207c4c0(void);
extern void func_ov002_0207c53c(void);
extern void func_ov021_0207feec(void);

asm void func_ov021_02080390(void)
{
    push    {r4, r5, r6, r7, lr}
    sub     sp, #0x3c
    add     r5, r0, #0
    add     r7, r1, #0
    add     r6, r2, #0
    str     r3, [sp, #0x18]
    bl      func_ov002_02076a38
    mov     r1, #0x6c
    ldrsb   r1, [r5, r1]
    add     r2, sp, #0x40
    add     r4, r0, #0
    str     r1, [sp, #0]
    mov     r1, #0x6e
    ldrsh   r1, [r5, r1]
    add     r3, r7, #0
    str     r1, [sp, #4]
    mov     r1, #0x70
    ldrsh   r1, [r5, r1]
    str     r1, [sp, #8]
    mov     r1, #0x72
    ldrsh   r1, [r5, r1]
    str     r1, [sp, #0xc]
    mov     r1, #0x18
    ldrsh   r1, [r2, r1]
    add     r2, sp, #0x1c
    str     r1, [sp, #0x10]
    mov     r1, #1
    str     r1, [sp, #0x14]
    add     r1, r4, #0
    add     r1, #0x2c
    bl      func_ov002_0207c4c0
    ldr     r1, [sp, #0x54]
    add     r0, sp, #0x30
    add     r2, sp, #0x1c
    bl      func_ov002_0207c53c
    add     r0, r4, #0
    ldr     r1, [sp, #0x54]
    add     r0, #0x38
    bl      func_0202b450
    add     r2, r4, #0
    mov     r1, #0x18
    add     r0, sp, #0x40
    ldrsh   r0, [r0, r1]
    add     r3, sp, #0x30
    add     r2, #0x1c
    strh    r0, [r4, #0x18]
    ldmia   r3!, {r0, r1}
    stmia   r2!, {r0, r1}
    ldr     r0, [r3, #0]
    str     r0, [r2, #0]
    ldr     r0, [sp, #0x24]
    str     r0, [r4, #0x28]
    ldr     r0, [pc, #0xb4]
    strb    r6, [r4, #0x10]
    str     r0, [r4, #0xc]
    ldrh    r1, [r4, #0x12]
    mov     r0, #0x48
    orr     r0, r1
    strh    r0, [r4, #0x12]
    mov     r0, #0
    strb    r0, [r4, #0x17]
    ldr     r1, [sp, #0x18]
    strh    r1, [r4, #0x14]
    add     r1, sp, #0x40
    ldrb    r1, [r1, #0x10]
    strb    r1, [r4, #0x16]
    mov     r1, #0x6e
    lsl     r1, r1, #2
    strb    r0, [r4, r1]
    add     r2, r1, #1
    strb    r0, [r4, r2]
    add     r2, r1, #4
    strb    r0, [r4, r2]
    ldrsb   r3, [r4, r2]
    ldr     r2, [pc, #0x8c]
    ldrsb   r2, [r2, r3]
    lsl     r3, r2, #0xc
    sub     r2, r1, #4
    str     r3, [r4, r2]
    add     r2, r1, #0
    sub     r2, #8
    str     r0, [r4, r2]
    add     r2, r1, #2
    strb    r7, [r4, r2]
    add     r2, r1, #5
    strb    r0, [r4, r2]
    sub     r2, r0, #1
    add     r0, r1, #3
    strb    r2, [r4, r0]
    bl      func_02030788
    cmp     r0, #0
    bne     _L_0100
    ldr     r0, [pc, #0x6c]
    ldrsb   r1, [r4, r0]
    add     r2, r5, r1
    add     r1, r0, #0
    sub     r1, #0x82
    ldrsb   r2, [r2, r1]
    add     r1, r0, #4
    add     r0, r0, #4
    strb    r2, [r4, r1]
    ldrsb   r1, [r4, r0]
    mov     r0, #6
    mul     r0, r1
    add     r1, r5, r0
    mov     r0, #0x78
    ldrsb   r0, [r1, r0]
    cmp     r0, #0
    bne     _L_0108
    bl      func_ov002_02077b30
    ldr     r1, [pc, #0x48]
    strb    r0, [r4, r1]
    add     r0, r1, #3
    ldrsb   r1, [r4, r0]
    mov     r0, #6
    mul     r0, r1
    add     r1, r5, r0
    mov     r0, #0x7a
    ldrsh   r0, [r1, r0]
    bl      func_ov002_0206cf4c
    b       _L_0108
_L_0100:
    mov     r1, #0
    ldr     r0, [pc, #0x34]
    mvn     r1, r1
    strb    r1, [r4, r0]
_L_0108:
    add     r0, r6, #0
    add     r1, r4, #0
    bl      func_ov002_02076480
    bl      func_ov002_0206b84c
    ldr     r1, [pc, #0x24]
    cmp     r0, r1
    bne     _L_0122
    add     r0, r6, #0
    mov     r1, #1
    bl      func_ov002_02076968
_L_0122:
    add     r0, r4, #0
    add     sp, #0x3c
    pop     {r4, r5, r6, r7, pc}
    dcd     func_ov021_0207feec
    dcd     data_ov021_02080f18
    dcd     0x000001ba
    dcd     0x000001bb
    dcd     0x000001be
    dcd     0x0000041d
}
