extern char data_ov068_020b7500[];
extern void func_ov002_02051d6c(void);
extern void func_ov002_02051eec(void);
extern void func_ov022_0209fb60(void);

asm void func_ov068_020b5d38(void)
{
    push    {r3, r4, r5, lr}
    add     r5, r0, #0
    ldr     r0, [pc, #0x90]
    mov     r1, #0
    ldr     r4, [r0, #0]
    mov     r2, #1
    add     r0, r4, #0
    bl      func_ov022_0209fb60
    ldr     r1, [pc, #0x88]
    ldrsb   r0, [r4, r1]
    cmp     r0, #0
    beq     _L_0026
    sub     r0, r1, #1
    ldrb    r2, [r4, r0]
    mov     r0, #1
    orr     r2, r0
    sub     r0, r1, #1
    strb    r2, [r4, r0]
_L_0026:
    ldr     r0, [pc, #0x78]
    ldr     r1, [pc, #0x78]
    mov     r2, #0x91
    lsl     r2, r2, #4
    add     r0, r4, r0
    add     r1, r4, r1
    add     r2, r5, r2
    bl      func_ov002_02051d6c
    mov     r0, #0x78
    str     r0, [sp, #0]
    ldr     r2, [pc, #0x64]
    ldr     r0, [pc, #0x60]
    add     r1, r4, r2
    sub     r2, #0x84
    ldrb    r3, [r5, #9]
    ldr     r2, [r5, r2]
    add     r0, r5, r0
    bl      func_ov002_02051eec
    add     r0, r4, #0
    mov     r1, #1
    mov     r2, #2
    bl      func_ov022_0209fb60
    ldr     r1, [pc, #0x4c]
    ldrsb   r0, [r4, r1]
    cmp     r0, #0
    beq     _L_006c
    sub     r0, r1, #1
    ldrb    r2, [r4, r0]
    mov     r0, #1
    orr     r2, r0
    sub     r0, r1, #1
    strb    r2, [r4, r0]
_L_006c:
    ldr     r0, [pc, #0x3c]
    ldr     r1, [pc, #0x40]
    mov     r2, #0x91
    lsl     r2, r2, #4
    add     r0, r4, r0
    add     r1, r4, r1
    add     r2, r5, r2
    bl      func_ov002_02051d6c
    mov     r0, #0xbe
    str     r0, [sp, #0]
    ldr     r2, [pc, #0x2c]
    ldr     r0, [pc, #0x24]
    add     r1, r4, r2
    sub     r2, #0xd8
    ldrb    r3, [r5, #9]
    ldr     r2, [r5, r2]
    add     r0, r5, r0
    bl      func_ov002_02051eec
    pop     {r3, r4, r5, pc}
    mov     r8, r8
    dcd     data_ov068_020b7500
    dcd     0x00000da9
    dcd     0x00000da8
    dcd     0x00002c54
    dcd     0x00000f0d
    dcd     0x00000f0c
    dcd     0x00002ca8
}
