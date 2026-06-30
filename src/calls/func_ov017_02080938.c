extern void func_ov002_020769b0(void);
extern void strncpy(void);
extern void func_ov017_020804e8(void);
extern void func_ov017_020805c4(void);
extern void func_ov017_020805cc(void);
extern void func_ov017_020805c0(void);
extern void func_ov017_020805c8(void);
extern void func_ov017_020805d0(void);
extern void func_ov017_020806d0(void);
extern void func_ov017_02080708(void);
extern void func_ov017_02080714(void);
extern void func_ov017_0208071c(void);

asm void func_ov017_02080938(void)
{
    push    {r3, r4, r5, lr}
    add     r5, r1, #0
    mov     r1, #7
    add     r2, r0, #0
    mov     r0, #0x6c
    lsl     r1, r1, #6
    bl      func_ov002_020769b0
    add     r4, r0, #0
    mov     r1, #0
    add     r0, #0x58
    strb    r1, [r0, #0]
    ldr     r1, [r5, #0]
    cmp     r1, #0
    beq     _L_0028
    add     r0, r4, #0
    add     r0, #0x58
    mov     r2, #0x10
    bl      strncpy
_L_0028:
    ldr     r0, [r5, #4]
    ldr     r1, [pc, #0x4c]
    str     r0, [r4, #0x68]
    mov     r0, #0
    str     r0, [r4, #0]
    str     r0, [r4, #4]
    str     r1, [r4, #8]
    ldr     r1, [pc, #0x44]
    str     r1, [r4, #0xc]
    ldr     r1, [pc, #0x44]
    str     r1, [r4, #0x10]
    ldr     r1, [pc, #0x44]
    str     r1, [r4, #0x14]
    ldr     r1, [pc, #0x44]
    str     r1, [r4, #0x18]
    ldr     r1, [pc, #0x44]
    str     r0, [r4, #0x1c]
    str     r1, [r4, #0x20]
    ldr     r1, [pc, #0x40]
    str     r1, [r4, #0x24]
    ldr     r1, [pc, #0x40]
    str     r1, [r4, #0x28]
    ldr     r1, [pc, #0x40]
    str     r1, [r4, #0x2c]
    str     r0, [r4, #0x38]
    str     r0, [r4, #0x44]
    ldr     r0, [pc, #0x3c]
    str     r0, [r4, #0x3c]
    ldrb    r0, [r5, #8]
    cmp     r0, #0
    bne     _L_006a
    mov     r1, #0x1d
    b       _L_006c
_L_006a:
    mov     r1, #0x1e
_L_006c:
    add     r0, r4, #0
    add     r0, #0x4c
    strh    r1, [r0, #0]
    add     r0, r4, #0
    pop     {r3, r4, r5, pc}
    mov     r8, r8
    dcd     func_ov017_020804e8
    dcd     func_ov017_020805c4
    dcd     func_ov017_020805cc
    dcd     func_ov017_020805c0
    dcd     func_ov017_020805c8
    dcd     func_ov017_020805d0
    dcd     func_ov017_020806d0
    dcd     func_ov017_02080708
    dcd     func_ov017_02080714
    dcd     func_ov017_0208071c
}
