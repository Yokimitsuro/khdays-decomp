extern void func_02021980(void);
extern void func_020235a8(void);
extern void func_020235bc(void);
extern void data_0204be18(void);

asm void func_ov069_020b8698(void)
{
    push    {r3, r4, r5, r6, r7, lr}
    bl      func_02021980
    add     r2, r0, #0
    ldr     r0, [pc, #0x38]
    mov     r3, #0
    ldr     r5, [r0, #0]
    mov     r0, #0xee
    add     r7, r3, #0
    lsl     r0, r0, #4
_L_0014:
    add     r4, r7, #0
    add     r6, r5, #0
_L_0018:
    ldrh    r1, [r6, r0]
    cmp     r2, r1
    bne     _L_0028
    ldr     r0, [pc, #0x28]
    bl      func_020235a8
    mov     r0, #1
    pop     {r3, r4, r5, r6, r7, pc}
_L_0028:
    add     r4, r4, #1
    add     r6, r6, #2
    cmp     r4, #0x28
    blt     _L_0018
    add     r3, r3, #1
    add     r5, #0x50
    cmp     r3, #3
    blt     _L_0014
    ldr     r0, [pc, #0xc]
    bl      func_020235bc
    mov     r0, #1
    pop     {r3, r4, r5, r6, r7, pc}
    mov     r8, r8
    dcd     data_0204be18
    mov     r0, #0xe1
    lsl     r0, r0, #0
}
