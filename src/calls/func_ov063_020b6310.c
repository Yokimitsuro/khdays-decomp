extern void func_0202a7dc(void);

asm void func_ov063_020b6310(void)
{
    push    {r4, r5, r6, lr}
    mov     r1, #0x8d
    lsl     r1, r1, #2
    add     r6, r1, #0
    mov     r4, #0
    add     r5, r0, r1
    sub     r6, #0xc4
_L_000e:
    add     r0, r5, #0
_L_0010:
    bl      func_0202a7dc
    add     r4, r4, #1
    add     r5, r5, r6
    cmp     r4, #8
    blt     _L_000e
    pop     {r4, r5, r6, pc}
}
