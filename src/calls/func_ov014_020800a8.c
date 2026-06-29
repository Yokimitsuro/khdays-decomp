extern char data_0204c240[];
extern void func_02005418(void);
extern void func_02029438(void);
extern void func_0202b450(void);
extern void func_ov002_02076480(void);
extern void func_ov002_02076a38(void);
extern void func_ov002_0207c4c0(void);
extern void func_ov002_0207c53c(void);
extern void func_ov014_0207fd78(void);

asm void func_ov014_020800a8(void)
{
    push    {r4, r5, r6, r7, lr}
    sub     sp, #0x3c
    add     r5, r0, #0
    str     r1, [sp, #0x18]
    add     r6, r2, #0
    add     r7, r3, #0
    bl      func_ov002_02076a38
    mov     r1, #0x6c
    ldrsb   r1, [r5, r1]
    add     r2, sp, #0x40
    add     r4, r0, #0
    str     r1, [sp, #0]
    mov     r1, #0x6e
    ldrsh   r1, [r5, r1]
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
    ldr     r3, [sp, #0x18]
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
    ldr     r0, [pc, #0xa4]
    strb    r6, [r4, #0x10]
    str     r0, [r4, #0xc]
    ldrh    r1, [r4, #0x12]
    mov     r0, #0x48
    orr     r0, r1
    strh    r0, [r4, #0x12]
    strh    r7, [r4, #0x14]
    add     r0, sp, #0x40
    ldrb    r0, [r0, #0x10]
    add     r1, r4, #0
    strb    r0, [r4, #0x16]
    mov     r0, #0
    strb    r0, [r4, #0x17]
    add     r0, r6, #0
    bl      func_ov002_02076480
    ldr     r0, [pc, #0x88]
    mov     r1, #0
    strb    r1, [r4, r0]
    ldr     r0, [pc, #0x84]
    ldrb    r1, [r0, #0]
    mov     r0, #4
    tst     r0, r1
    beq     _L_00a8
    ldr     r0, [sp, #0x5c]
    asr     r0, r0, #0x10
    b       _L_00ae
_L_00a8:
    ldr     r0, [sp, #0x5c]
    lsl     r0, r0, #0x10
    lsr     r0, r0, #0x10
_L_00ae:
    mov     r1, #0x1d
    lsl     r1, r1, #4
    strh    r0, [r4, r1]
    mov     r2, #0
    sub     r0, r1, #4
    str     r2, [r4, r0]
    add     r0, r1, #0
    sub     r0, #0x1d
    strb    r2, [r4, r0]
    add     r0, r1, #0
    ldr     r2, [pc, #0x60]
    sub     r0, #0x1c
    str     r2, [r4, r0]
    sub     r1, #0x1c
    ldr     r0, [r5, #0x74]
    ldr     r1, [r4, r1]
    bl      func_02005418
    mov     r1, #0x6e
    lsl     r1, r1, #2
    str     r0, [r4, r1]
    sub     r1, r1, #4
    ldr     r0, [r5, #0x78]
    ldr     r1, [r4, r1]
    bl      func_02005418
    mov     r1, #0x6f
    lsl     r1, r1, #2
    str     r0, [r4, r1]
    sub     r1, #8
    ldr     r0, [r5, #0x7c]
    ldr     r1, [r4, r1]
    bl      func_02005418
    mov     r1, #7
    lsl     r1, r1, #6
    str     r0, [r4, r1]
    add     r0, r1, #0
    sub     r0, #0xc
    ldr     r2, [r4, r0]
    add     r0, r1, #0
    add     r0, #8
    str     r2, [r4, r0]
    sub     r1, #0x78
    add     r0, r4, r1
    mov     r1, #1
    mov     r2, #3
    bl      func_02029438
    add     r0, r4, #0
    add     sp, #0x3c
    pop     {r4, r5, r6, r7, pc}
    mov     r8, r8
    dcd     func_ov014_0207fd78
    dcd     0x000001b1
    dcd     data_0204c240
    dcd     0x000046bd
}
