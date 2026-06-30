extern void func_01fffde0(void);

asm void func_ov017_02080c88(void)
{
    push    {r4, r5, r6, lr}
    mov     r5, #0
    mov     r4, #1
    lsl     r4, r4, #0x1e
    add     r6, r5, #0
_L_000a:
    add     r0, r5, #0
    bl      func_01fffde0
    cmp     r0, #0
    beq     _L_0020
    ldr     r2, [r0, #0]
    ldr     r1, [r0, #4]
    orr     r2, r6
    orr     r1, r4
    str     r2, [r0, #0]
    str     r1, [r0, #4]
_L_0020:
    add     r5, r5, #1
    cmp     r5, #4
    blt     _L_000a
    mov     r0, #1
    pop     {r4, r5, r6, pc}
}
