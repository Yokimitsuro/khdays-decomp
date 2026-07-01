extern void func_0202b450(void);

asm void func_ov017_020804a4(void)
{
    push    {r3, r4, r5, lr}
    add     r5, r0, #0
    add     r0, #0x28
    add     r4, r2, #0
    bl      func_0202b450
    strh    r4, [r5, #0x18]
    pop     {r3, r4, r5, pc}
}
