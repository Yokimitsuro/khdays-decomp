extern void MI_CpuCopy8(void);
extern void func_02023e80(void);
extern void func_02030788(void);
extern void func_ov002_020769b0(void);
extern void func_ov021_0207faf8(void);
extern void func_ov021_0207fb80(void);
extern void func_ov021_0207fbb8(void);
extern void func_ov021_0207fbc8(void);
extern void func_ov021_0207fca0(void);
extern void func_ov021_0207fd98(void);
extern void func_ov021_0207fec0(void);
extern void func_ov021_0207fed4(void);
extern void func_ov021_0207fee0(void);
extern void func_ov021_0207fee8(void);
extern void strncpy(void);

asm void func_ov021_0208024c(void)
{
    push    {r3, r4, r5, r6, r7, lr}
    sub     sp, #8
    add     r6, r0, #0
    mov     r0, #0x56
    lsl     r0, r0, #2
    add     r7, r1, #0
    add     r1, r0, #0
    add     r1, #0x68
    add     r2, r6, #0
    bl      func_ov002_020769b0
    add     r5, r0, #0
    mov     r1, #0
    add     r0, #0x58
    strb    r1, [r0, #0]
    ldr     r1, [r7, #0]
    cmp     r1, #0
    beq     _L_002e
    add     r0, r5, #0
    add     r0, #0x58
    mov     r2, #0x10
    bl      strncpy
_L_002e:
    ldr     r0, [r7, #4]
    str     r0, [r5, #0x68]
    mov     r0, #8
    ldrsb   r1, [r7, r0]
    add     r0, r5, #0
    add     r0, #0x6c
    strb    r1, [r0, #0]
    mov     r0, #0xa
    ldrsh   r1, [r7, r0]
    add     r0, r5, #0
    add     r0, #0x6e
    strh    r1, [r0, #0]
    mov     r0, #0xc
    ldrsh   r1, [r7, r0]
    add     r0, r5, #0
    add     r0, #0x70
    strh    r1, [r0, #0]
    mov     r0, #0xe
    ldrsh   r1, [r7, r0]
    add     r0, r5, #0
    add     r0, #0x72
    strh    r1, [r0, #0]
    add     r0, r5, #0
    ldrh    r1, [r7, #0x10]
    add     r0, #0x74
    strh    r1, [r0, #0]
    add     r0, r5, #0
    ldrb    r1, [r7, #0x12]
    add     r0, #0x76
    strb    r1, [r0, #0]
    bl      func_02030788
    cmp     r0, #0
    bne     _L_00b4
    mov     r2, #0
    cmp     r6, #0
    ble     _L_0086
    mov     r0, #0x4e
    lsl     r0, r0, #2
_L_007c:
    add     r1, r5, r2
    strb    r2, [r1, r0]
    add     r2, r2, #1
    cmp     r2, r6
    blt     _L_007c
_L_0086:
    mov     r0, #0
    str     r0, [sp, #0]
_L_008a:
    add     r0, r6, #0
    bl      func_02023e80
    add     r4, r0, #0
    add     r0, r6, #0
    bl      func_02023e80
    mov     r2, #0x4e
    lsl     r2, r2, #2
    add     r1, r5, r4
    add     r3, r5, r0
    add     r0, r2, #0
    ldrsb   r4, [r1, r2]
    ldrsb   r2, [r3, r0]
    strb    r2, [r1, r0]
    strb    r4, [r3, r0]
    ldr     r0, [sp, #0]
    add     r0, r0, #1
    str     r0, [sp, #0]
    cmp     r0, #0x20
    blt     _L_008a
_L_00b4:
    mov     r0, #0
    str     r0, [sp, #4]
    cmp     r6, #0
    ble     _L_00da
    add     r4, r5, #0
    add     r4, #0x78
    add     r7, #0x14
_L_00c2:
    add     r0, r7, #0
    add     r1, r4, #0
    mov     r2, #6
    bl      MI_CpuCopy8
    ldr     r0, [sp, #4]
    add     r4, r4, #6
    add     r0, r0, #1
    add     r7, r7, #6
    str     r0, [sp, #4]
    cmp     r0, r6
    blt     _L_00c2
_L_00da:
    mov     r0, #0
    str     r0, [r5, #0]
    ldr     r1, [pc, #0x3c]
    str     r0, [r5, #4]
    str     r1, [r5, #8]
    ldr     r1, [pc, #0x38]
    str     r1, [r5, #0xc]
    ldr     r1, [pc, #0x38]
    str     r1, [r5, #0x10]
    ldr     r1, [pc, #0x38]
    str     r1, [r5, #0x14]
    ldr     r1, [pc, #0x38]
    str     r1, [r5, #0x18]
    ldr     r1, [pc, #0x38]
    str     r1, [r5, #0x1c]
    ldr     r1, [pc, #0x38]
    str     r0, [r5, #0x20]
    str     r1, [r5, #0x24]
    ldr     r1, [pc, #0x38]
    str     r1, [r5, #0x28]
    ldr     r1, [pc, #0x38]
    str     r1, [r5, #0x2c]
    str     r0, [r5, #0x38]
    str     r0, [r5, #0x44]
    ldr     r0, [pc, #0x34]
    mov     r1, #0x11
    str     r0, [r5, #0x3c]
    add     r0, r5, #0
    add     r0, #0x4c
    strh    r1, [r0, #0]
    add     r0, r5, #0
    add     sp, #8
    pop     {r3, r4, r5, r6, r7, pc}
    dcd     func_ov021_0207faf8
    dcd     func_ov021_0207fbb8
    dcd     func_ov021_0207fca0
    dcd     func_ov021_0207fb80
    dcd     func_ov021_0207fbc8
    dcd     func_ov021_0207fd98
    dcd     func_ov021_0207fec0
    dcd     func_ov021_0207fed4
    dcd     func_ov021_0207fee0
    dcd     func_ov021_0207fee8
}
