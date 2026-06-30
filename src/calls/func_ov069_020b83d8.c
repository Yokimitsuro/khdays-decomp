extern void NNS_FndInitList(void);
extern void func_ov069_020ba1c4(void);
extern void func_ov069_020ba4cc(void);
extern void func_ov069_020ba250(void);
extern void NNS_FndGetNextListObject(void);
extern void func_ov069_020ba71c(void);
extern void WM_EndKeySharing_0x020ba244(void);
extern void data_0204be18(void);

asm void func_ov069_020b83d8(void)
{
    push    {r3, r4, r5, r6, r7, lr}
    sub     sp, #0x1fc
    sub     sp, #0xf4
    add     r4, r0, #0
    mov     r0, #0
    str     r0, [sp, #0]
    add     r0, sp, #4
    mov     r1, #0x28
    bl      NNS_FndInitList
    add     r0, sp, #0x10
    mov     r1, #0
    bl      func_ov069_020ba1c4
    ldr     r3, [pc, #0x80]
    add     r0, sp, #0x10
    ldr     r5, [r3, #0]
    mov     r3, #0xee
    lsl     r3, r3, #4
    add     r1, sp, #0x110
    add     r2, sp, #4
    add     r3, r5, r3
    bl      func_ov069_020ba4cc
    add     r0, sp, #0x10
    add     r1, sp, #0x110
    add     r2, sp, #4
    bl      func_ov069_020ba250
    add     r0, sp, #4
    mov     r1, #0
    bl      NNS_FndGetNextListObject
    add     r1, r0, #0
    beq     _L_0086
    add     r5, sp, #0x110
    mov     r7, #0xa0
_L_004a:
    ldrh    r0, [r1, #0xa]
    ldrh    r2, [r1, #0x12]
    ldrh    r3, [r1, #0x10]
    add     r6, r0, #0
    lsl     r0, r2, #2
    add     r0, r2, r0
    add     r0, r3, r0
    mul     r6, r7
    lsl     r2, r0, #2
    add     r0, r5, r6
    ldr     r0, [r2, r0]
    ldr     r0, [r0, #0x18]
    cmp     r0, #4
    bne     _L_007c
    cmp     r4, #0
    beq     _L_0076
    ldr     r0, [r1, #4]
    cmp     r0, #0
    beq     _L_007c
    ldrh    r0, [r1, #8]
    cmp     r0, r4
    blo     _L_007c
_L_0076:
    mov     r0, #1
    str     r0, [sp, #0]
    b       _L_0086
_L_007c:
    add     r0, sp, #4
    bl      NNS_FndGetNextListObject
    add     r1, r0, #0
    bne     _L_004a
_L_0086:
    add     r0, sp, #0x10
    add     r1, sp, #0x110
    add     r2, sp, #4
    bl      func_ov069_020ba71c
    add     r0, sp, #0x10
    bl      WM_EndKeySharing_0x020ba244
    ldr     r0, [sp, #0]
    add     sp, #0x1fc
    add     sp, #0xf4
    pop     {r3, r4, r5, r6, r7, pc}
    mov     r8, r8
    dcd     data_0204be18
}
