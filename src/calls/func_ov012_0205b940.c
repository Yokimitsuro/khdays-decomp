extern void func_02021948(void);
extern void func_ov012_0205b0cc(void);

asm void func_ov012_0205b940(void)
{
    push    {r4, r5, r6, lr}
    add     r4, r1, #0
    mov     r6, #0
    ldrsh   r2, [r4, r6]
    add     r5, r0, #0
    cmp     r2, #2
    bne     L_func_ov012_0205b940_0014
    bl      func_02021948
    add     r6, r0, #0
L_func_ov012_0205b940_0014:
    mov     r0, #8
    ldrsh   r0, [r4, r0]
    cmp     r0, #2
    bne     L_func_ov012_0205b940_0026
    add     r1, r4, #0
    add     r0, r5, #0
    add     r1, #8
    bl      func_02021948
L_func_ov012_0205b940_0026:
    mov     r0, #0x10
    ldrsh   r0, [r4, r0]
    cmp     r0, #2
    bne     L_func_ov012_0205b940_0038
    add     r4, #0x10
    add     r0, r5, #0
    add     r1, r4, #0
    bl      func_02021948
L_func_ov012_0205b940_0038:
    add     r0, r6, #0
    bl      func_ov012_0205b0cc
    mov     r0, #1
    pop     {r4, r5, r6, pc}
}
