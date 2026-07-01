extern void func_020235d0(void);

asm void func_ov069_020b826c(void)
{
    push    {r4, lr}
    add     r4, r0, #0
    ldr     r0, [pc, #0x10]
    mov     r1, #0xa
    bl      func_020235d0
    cmp     r0, r4
    blo     _L_0014
    mov     r0, #1
    pop     {r4, pc}
_L_0014:
    mov     r0, #0
    pop     {r4, pc}
    asr     r5, r2, #0x10
    lsl     r0, r0, #0
}
