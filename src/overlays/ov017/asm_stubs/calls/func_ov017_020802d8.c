extern void func_ov002_020769b0(void);
extern void strncpy(void);
extern void func_ov017_0207fb94(void);
extern void func_ov017_0207fc08(void);
extern void func_ov017_0207fd88(void);
extern void func_ov017_0207fba8(void);
extern void func_ov017_0207fc18(void);
extern void func_ov017_0207fdb4(void);
extern void func_ov017_0207fe10(void);
extern void func_ov017_0207fe18(void);
extern void func_ov017_0207fe24(void);

asm void func_ov017_020802d8(void)
{
    push    {r3, r4, r5, lr}
    add     r5, r1, #0
    add     r2, r0, #0
    ldr     r1, [pc, #0xbc]
    mov     r0, #0x94
    bl      func_ov002_020769b0
    add     r4, r0, #0
    mov     r1, #0
    add     r0, #0x58
    strb    r1, [r0, #0]
    ldr     r1, [r5, #0]
    cmp     r1, #0
    beq     _L_0026
    add     r0, r4, #0
    add     r0, #0x58
    mov     r2, #0x10
    bl      strncpy
_L_0026:
    add     r0, r4, #0
    mov     r1, #0
    add     r0, #0x68
    strb    r1, [r0, #0]
    ldr     r1, [r5, #4]
    cmp     r1, #0
    beq     _L_003e
    add     r0, r4, #0
    add     r0, #0x68
    mov     r2, #0x10
    bl      strncpy
_L_003e:
    add     r0, r4, #0
    mov     r1, #0
    add     r0, #0x78
    strb    r1, [r0, #0]
    ldr     r1, [r5, #8]
    cmp     r1, #0
    beq     _L_0056
    add     r0, r4, #0
    add     r0, #0x78
    mov     r2, #0x10
    bl      strncpy
_L_0056:
    add     r0, r4, #0
    ldr     r1, [r5, #0xc]
    add     r0, #0x88
    str     r1, [r0, #0]
    mov     r0, #0x10
    ldrsb   r1, [r5, r0]
    add     r0, r4, #0
    add     r0, #0x8c
    strb    r1, [r0, #0]
    mov     r0, #0x12
    ldrsh   r1, [r5, r0]
    add     r0, r4, #0
    add     r0, #0x8e
    strh    r1, [r0, #0]
    mov     r0, #0x14
    ldrsh   r1, [r5, r0]
    add     r0, r4, #0
    add     r0, #0x90
    strh    r1, [r0, #0]
    mov     r0, #0x16
    ldrsh   r1, [r5, r0]
    add     r0, r4, #0
    add     r0, #0x92
    strh    r1, [r0, #0]
    mov     r0, #0
    str     r0, [r4, #0]
    ldr     r1, [pc, #0x3c]
    str     r0, [r4, #4]
    str     r1, [r4, #8]
    ldr     r1, [pc, #0x38]
    str     r1, [r4, #0xc]
    ldr     r1, [pc, #0x38]
    str     r1, [r4, #0x10]
    ldr     r1, [pc, #0x38]
    str     r1, [r4, #0x14]
    ldr     r1, [pc, #0x38]
    str     r1, [r4, #0x18]
    ldr     r1, [pc, #0x38]
    str     r1, [r4, #0x1c]
    ldr     r1, [pc, #0x38]
    str     r0, [r4, #0x20]
    str     r1, [r4, #0x24]
    ldr     r1, [pc, #0x38]
    str     r1, [r4, #0x28]
    ldr     r1, [pc, #0x38]
    str     r1, [r4, #0x2c]
    str     r0, [r4, #0x38]
    str     r0, [r4, #0x44]
    str     r0, [r4, #0x3c]
    add     r0, r4, #0
    mov     r1, #0x15
    add     r0, #0x4c
    strh    r1, [r0, #0]
    add     r0, r4, #0
    pop     {r3, r4, r5, pc}
    lsl     r4, r4, #0x13
    lsl     r0, r0, #0
    dcd     func_ov017_0207fb94
    dcd     func_ov017_0207fc08
    dcd     func_ov017_0207fd88
    dcd     func_ov017_0207fba8
    dcd     func_ov017_0207fc18
    dcd     func_ov017_0207fdb4
    dcd     func_ov017_0207fe10
    dcd     func_ov017_0207fe18
    dcd     func_ov017_0207fe24
}
