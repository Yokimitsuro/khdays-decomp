extern void func_020235d0(void);

asm void func_ov069_020b8304(void)
{
    push    {r4, lr}
    add     r4, r0, #0
    mov     r0, #5
    lsl     r0, r0, #0xa
    mov     r1, #0xa
    bl      func_020235d0
    cmp     r0, r4
    blo     _L_0016
    mov     r0, #1
    pop     {r4, pc}
_L_0016:
    mov     r0, #0
    pop     {r4, pc}
}
