extern void func_ov022_0209fb60(void);
extern void func_ov022_0209fb98(void);
extern void func_ov002_02051d6c(void);
extern void func_ov002_02051eec(void);
extern void func_0202a634(void);
extern void func_02016cd0(void);
extern void func_0202afc4(void);
extern char data_ov064_020b7420[];

asm void func_ov064_020b5c80(void)
{
    push    {r3, r4, r5, r6, r7, lr}
    sub     sp, #8
    add     r5, r0, #0
    ldr     r0, [pc, #0x154]
    mov     r1, #0
    ldr     r4, [r0, #0]
    ldr     r0, [pc, #0x150]
    mov     r2, #3
    str     r1, [r4, r0]
    add     r0, r4, #0
    bl      func_ov022_0209fb60
    add     r0, r4, #0
    mov     r1, #0
    mov     r2, #1
    bl      func_ov022_0209fb98
    ldr     r1, [pc, #0x140]
    ldrsb   r0, [r4, r1]
    cmp     r0, #0
    beq     _L_0036
    sub     r0, r1, #1
    ldrb    r2, [r4, r0]
    mov     r0, #1
    orr     r2, r0
    sub     r0, r1, #1
    strb    r2, [r4, r0]
_L_0036:
    ldr     r0, [pc, #0x130]
    ldr     r1, [pc, #0x130]
    mov     r2, #0x91
    lsl     r2, r2, #4
    add     r0, r4, r0
    add     r1, r4, r1
    add     r2, r5, r2
    bl      func_ov002_02051d6c
    mov     r0, #0x78
    str     r0, [sp]
    ldr     r2, [pc, #0x120]
    ldr     r0, [pc, #0x118]
    ldr     r1, [pc, #0x118]
    ldrb    r3, [r5, #9]
    ldr     r2, [r5, r2]
    add     r0, r5, r0
    add     r1, r4, r1
    bl      func_ov002_02051eec
    add     r0, r4, #0
    mov     r1, #1
    mov     r2, #4
    bl      func_ov022_0209fb60
    mov     r1, #1
    add     r0, r4, #0
    add     r2, r1, #0
    bl      func_ov022_0209fb98
    ldr     r1, [pc, #0x100]
    ldrsb   r0, [r4, r1]
    cmp     r0, #0
    beq     _L_0086
    sub     r0, r1, #1
    ldrb    r2, [r4, r0]
    mov     r0, #1
    orr     r2, r0
    sub     r0, r1, #1
    strb    r2, [r4, r0]
_L_0086:
    ldr     r1, [pc, #0xf0]
    mov     r0, #8
    ldrb    r2, [r5, r1]
    bic    r2, r0
    strb    r2, [r5, r1]
    add     r0, r4, r1
    ldr     r1, [pc, #0xe8]
    mov     r2, #0x91
    lsl     r2, r2, #4
    add     r1, r4, r1
    add     r2, r5, r2
    bl      func_ov002_02051d6c
    mov     r3, #0
    ldr     r0, [pc, #0xdc]
    sub     r2, r3, #1
_L_00a6:
    add     r1, r4, r3
    add     r3, r3, #1
    strb    r2, [r1, r0]
    cmp     r3, #0xd
    blt     _L_00a6
    mov     r6, #0
    add     r7, r6, #0
_L_00b4:
    mov     r0, #0xb5
    add     r1, r4, r6
    lsl     r0, r0, #6
    ldrsb   r0, [r1, r0]
    str     r1, [sp, #4]
    cmp     r0, #0
    blt     _L_0156
    cmp     r0, #0xc
    bhi     _L_0150
    add     r0, r0, r0
    add     r0, pc
    ldrh    r0, [r0, #6]
    lsl     r0, r0, #0x10
    asr    r0, r0, #0x10
    add     pc, r0
    lsl     r4, r7, #1
    lsl     r4, r7, #1
    lsl     r4, r7, #1
    lsl     r4, r7, #1
    lsl     r4, r7, #1
    lsl     r4, r7, #1
    lsl     r4, r7, #1
    dcd     0x00180018
    dcd     0x00180018
    dcd     0x00180018
    ldr     r0, [pc, #0x70]
    ldr     r0, [r4, r0]
    cmp     r0, #0
    bne     _L_0140
    ldr     r1, [pc, #0x78]
    ldr     r0, [pc, #0x8c]
    ldr     r2, [r5, r1]
    mov     r1, #2
    lsl     r1, r1, #0xe
    add     r2, r2, r1
    ldr     r1, [pc, #0x84]
    add     r0, r4, r0
    and    r1, r2
    lsl     r2, r1, #7
    mov     r1, #2
    lsl     r1, r1, #0x1e
    add     r3, r2, #0
    orr     r3, r1
    ldr     r1, [pc, #0x78]
    ldrb    r2, [r5, r1]
    ldr     r1, [pc, #0x78]
    add     r2, #0xbe
    and    r1, r2
    orr     r1, r3
    ldrb    r3, [r5, #9]
    mov     r2, #1
    add     r3, r3, #7
    bl      func_0202a634
    ldr     r0, [pc, #0x6c]
    mov     r1, #0x3f
    ldr     r0, [r4, r0]
    bl      func_02016cd0
    ldr     r0, [pc, #0x50]
    mov     r1, #1
    add     r0, r4, r0
    bl      func_0202afc4
    ldr     r0, [pc, #0x24]
    mov     r1, #1
    str     r1, [r4, r0]
_L_0140:
    mov     r0, #0xb5
    ldr     r1, [sp, #4]
    lsl     r0, r0, #6
    ldrsb   r0, [r1, r0]
    add     r1, r4, r0
    ldr     r0, [pc, #0x34]
    strb    r7, [r1, r0]
    add     r7, r7, #1
_L_0150:
    add     r6, r6, #1
    cmp     r6, #0xd
    blt     _L_00b4
_L_0156:
    add     sp, #8
    pop     {r3, r4, r5, r6, r7, pc}
    mov     r8, r8
    dcd     data_ov064_020b7420
    dcd     0x00002c2c
    dcd     0x00000da9
    dcd     0x00000da8
    dcd     0x00002d38
    dcd     0x00002bd0
    dcd     0x00000f0d
    dcd     0x00000f0c
    dcd     0x00002d8c
    dcd     0x00002de0
    dcd     0x00002c30
    dcd     0x00fffffc
    dcd     0x00000918
    dcd     0x000001ff
    dcd     0x00002ca8
}
