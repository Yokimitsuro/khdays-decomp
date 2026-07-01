extern void func_02021948(void);
extern void func_02021980(void);
extern void func_02021994(void);
extern void func_ov002_0207643c(void);
extern void func_ov021_0208024c(void);

asm void func_ov021_02080c98(void)
{
    push    {r4, r5, r6, r7, lr}
    sub     sp, #0xdc
    add     r4, r1, #0
    add     r6, r0, #0
    bl      func_02021980
    add     r1, r4, #0
    str     r0, [sp, #4]
    add     r0, r6, #0
    add     r1, #8
    bl      func_02021980
    add     r1, r4, #0
    str     r0, [sp, #0]
    add     r0, r6, #0
    add     r1, #0x10
    bl      func_02021948
    add     r1, r4, #0
    str     r0, [sp, #8]
    add     r0, r6, #0
    add     r1, #0x18
    bl      func_02021994
    add     r1, r4, #0
    str     r0, [sp, #0xc]
    add     r0, r6, #0
    add     r1, #0x20
    bl      func_02021980
    add     r1, sp, #8
    strb    r0, [r1, #8]
    add     r1, r4, #0
    add     r0, r6, #0
    add     r1, #0x28
    bl      func_02021994
    add     r1, sp, #8
    strh    r0, [r1, #0xa]
    add     r1, r4, #0
    add     r0, r6, #0
    add     r1, #0x30
    bl      func_02021994
    add     r1, sp, #8
    strh    r0, [r1, #0xc]
    add     r1, r4, #0
    add     r0, r6, #0
    add     r1, #0x38
    bl      func_02021994
    add     r1, sp, #8
    strh    r0, [r1, #0xe]
    ldr     r0, [r4, #0x44]
    mov     r7, #0
    strh    r0, [r1, #0x10]
    ldr     r0, [r4, #0x44]
    add     r4, #0x48
    lsr     r0, r0, #0x10
    strb    r0, [r1, #0x12]
    ldr     r0, [sp, #0]
    cmp     r0, #0
    ble     _L_00e2
    add     r5, sp, #8
_L_0080:
    add     r0, r6, #0
    add     r1, r4, #0
    bl      func_02021980
    strb    r0, [r5, #0x14]
    mov     r0, #0x14
    ldrsb   r0, [r5, r0]
    add     r4, #8
    cmp     r0, #3
    bhi     _L_00d4
    add     r0, r0, r0
    add     r0, pc
    ldrh    r0, [r0, #6]
    lsl     r0, r0, #0x10
    asr     r0, r0, #0x10
    add     pc, r0
    lsl     r6, r0, #0
    lsl     r4, r2, #0
    lsl     r2, r4, #0
    lsl     r0, r6, #0
    add     r0, r6, #0
    add     r1, r4, #0
    bl      func_02021980
    add     r4, #8
    strh    r0, [r5, #0x16]
    b       _L_00d4
    add     r0, r6, #0
    add     r1, r4, #0
    bl      func_02021994
    add     r4, #8
    strh    r0, [r5, #0x16]
    b       _L_00d4
    add     r0, r6, #0
    add     r1, r4, #0
    bl      func_02021980
    add     r4, #8
    strh    r0, [r5, #0x16]
    b       _L_00d4
    add     r4, #8
_L_00d4:
    mov     r0, #0
    strb    r0, [r5, #0x18]
    ldr     r0, [sp, #0]
    add     r7, r7, #1
    add     r5, r5, #6
    cmp     r7, r0
    blt     _L_0080
_L_00e2:
    ldr     r0, [sp, #0]
    add     r1, sp, #8
    lsl     r0, r0, #0x10
    lsr     r0, r0, #0x10
    bl      func_ov021_0208024c
    add     r1, r0, #0
    ldr     r0, [sp, #4]
    bl      func_ov002_0207643c
    mov     r0, #1
    add     sp, #0xdc
    pop     {r4, r5, r6, r7, pc}
}
