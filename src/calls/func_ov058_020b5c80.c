extern void func_ov022_0209fb60(void);
extern void func_ov022_0209fb98(void);
extern void func_ov002_02051d6c(void);
extern void func_ov002_02051eec(void);
extern void data_ov058_020b7e00(void);

asm void func_ov058_020b5c80(void)
{
    push    {r3, r4, r5, lr}
    add     r5, r0, #0
    ldr     r0, [pc, #0xa8]
    mov     r1, #0
    ldr     r4, [r0, #0]
    mov     r2, #3
    add     r0, r4, #0
    bl      func_ov022_0209fb60
    add     r0, r4, #0
    mov     r1, #0
    mov     r2, #1
    bl      func_ov022_0209fb98
    ldr     r1, [pc, #0x94]
    ldrsb   r0, [r4, r1]
    cmp     r0, #0
    beq     _L_0030
    sub     r0, r1, #1
    ldrb    r2, [r4, r0]
    mov     r0, #1
    orr     r2, r0
    sub     r0, r1, #1
    strb    r2, [r4, r0]
_L_0030:
    ldr     r0, [pc, #0x84]
    ldr     r1, [pc, #0x88]
    mov     r2, #0x91
    lsl     r2, r2, #4
    add     r0, r4, r0
    add     r1, r4, r1
    add     r2, r5, r2
    bl      func_ov002_02051d6c
    mov     r0, #0x78
    str     r0, [sp, #0]
    ldr     r2, [pc, #0x74]
    ldr     r0, [pc, #0x6c]
    add     r1, r4, r2
    sub     r2, #0x5c
    ldrb    r3, [r5, #9]
    ldr     r2, [r5, r2]
    add     r0, r5, r0
    bl      func_ov002_02051eec
    add     r0, r4, #0
    mov     r1, #1
    mov     r2, #4
    bl      func_ov022_0209fb60
    mov     r1, #1
    add     r0, r4, #0
    add     r2, r1, #0
    bl      func_ov022_0209fb98
    ldr     r1, [pc, #0x50]
    ldrsb   r0, [r4, r1]
    cmp     r0, #0
    beq     _L_0080
    sub     r0, r1, #1
    ldrb    r2, [r4, r0]
    mov     r0, #1
    orr     r2, r0
    sub     r0, r1, #1
    strb    r2, [r4, r0]
_L_0080:
    ldr     r0, [pc, #0x40]
    mov     r1, #0xb2
    mov     r2, #0x91
    lsl     r1, r1, #6
    lsl     r2, r2, #4
    add     r0, r4, r0
    add     r1, r4, r1
    add     r2, r5, r2
    bl      func_ov002_02051d6c
    mov     r0, #0xbe
    str     r0, [sp, #0]
    mov     r2, #0xb2
    lsl     r2, r2, #6
    ldr     r0, [pc, #0x24]
    add     r1, r4, r2
    sub     r2, #0xb0
    ldrb    r3, [r5, #9]
    ldr     r2, [r5, r2]
    add     r0, r5, r0
    bl      func_ov002_02051eec
    pop     {r3, r4, r5, pc}
    mov     r8, r8
    dcd     data_ov058_020b7e00
    lsr     r1, r5, #0x16
    lsl     r0, r0, #0
    lsr     r0, r5, #0x16
    lsl     r0, r0, #0
    cmp     r4, #0x2c
    lsl     r0, r0, #0
    lsr     r5, r1, #0x1c
    lsl     r0, r0, #0
    lsr     r4, r1, #0x1c
    lsl     r0, r0, #0
}
