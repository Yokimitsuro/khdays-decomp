extern void strncpy(void);
extern void func_ov002_020769b0(void);
extern void func_ov014_0207fa78(void);
extern void func_ov014_0207fa7c(void);
extern void func_ov014_0207fae4(void);
extern void func_ov014_0207faf4(void);
extern void func_ov014_0207fb04(void);
extern void func_ov014_0207fb88(void);
extern void func_ov014_0207fbf0(void);
extern void func_ov014_0207fcb0(void);
extern void func_ov014_0207fce8(void);
extern void func_ov014_0207fd24(void);
extern void func_ov014_0207fd2c(void);

asm void func_ov014_0207ffdc(void)
{
    push    {r3, r4, r5, lr}
    add     r5, r1, #0
    mov     r1, #0x75
    add     r2, r0, #0
    mov     r0, #0x84
    lsl     r1, r1, #2
    bl      func_ov002_020769b0
    add     r4, r0, #0
    ldr     r1, [r5, #0]
    add     r0, #0x58
    mov     r2, #0x10
    bl      strncpy
    ldr     r0, [r5, #4]
    str     r0, [r4, #0x68]
    mov     r0, #8
    ldrsb   r1, [r5, r0]
    add     r0, r4, #0
    add     r0, #0x6c
    strb    r1, [r0, #0]
    mov     r0, #0xa
    ldrsh   r1, [r5, r0]
    add     r0, r4, #0
    add     r0, #0x6e
    strh    r1, [r0, #0]
    mov     r0, #0xc
    ldrsh   r1, [r5, r0]
    add     r0, r4, #0
    add     r0, #0x70
    strh    r1, [r0, #0]
    mov     r0, #0xe
    ldrsh   r1, [r5, r0]
    add     r0, r4, #0
    add     r0, #0x72
    strh    r1, [r0, #0]
    ldr     r0, [r5, #0x10]
    str     r0, [r4, #0x74]
    ldr     r0, [r5, #0x14]
    str     r0, [r4, #0x78]
    ldr     r0, [r5, #0x18]
    str     r0, [r4, #0x7c]
    add     r0, r4, #0
    ldrb    r1, [r5, #0x1c]
    add     r0, #0x80
    strb    r1, [r0, #0]
    mov     r0, #0
    ldr     r1, [pc, #0x40]
    str     r0, [r4, #0]
    str     r1, [r4, #4]
    ldr     r1, [pc, #0x3c]
    str     r1, [r4, #8]
    ldr     r1, [pc, #0x3c]
    str     r1, [r4, #0xc]
    ldr     r1, [pc, #0x3c]
    str     r1, [r4, #0x10]
    ldr     r1, [pc, #0x3c]
    str     r1, [r4, #0x14]
    ldr     r1, [pc, #0x3c]
    str     r1, [r4, #0x18]
    ldr     r1, [pc, #0x3c]
    str     r1, [r4, #0x1c]
    ldr     r1, [pc, #0x3c]
    str     r0, [r4, #0x20]
    str     r1, [r4, #0x24]
    ldr     r1, [pc, #0x3c]
    str     r1, [r4, #0x28]
    ldr     r1, [pc, #0x3c]
    str     r1, [r4, #0x2c]
    str     r0, [r4, #0x38]
    str     r0, [r4, #0x44]
    ldr     r0, [pc, #0x38]
    mov     r1, #7
    str     r0, [r4, #0x3c]
    add     r0, r4, #0
    add     r0, #0x4c
    strh    r1, [r0, #0]
    add     r0, r4, #0
    pop     {r3, r4, r5, pc}
    mov     r8, r8
    dcd     func_ov014_0207fa78
    dcd     func_ov014_0207fa7c
    dcd     func_ov014_0207faf4
    dcd     func_ov014_0207fb88
    dcd     func_ov014_0207fae4
    dcd     func_ov014_0207fb04
    dcd     func_ov014_0207fbf0
    dcd     func_ov014_0207fcb0
    dcd     func_ov014_0207fce8
    dcd     func_ov014_0207fd24
    dcd     func_ov014_0207fd2c
}
