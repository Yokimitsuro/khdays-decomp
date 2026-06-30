extern void func_ov012_0205b8fc(void);

asm void func_ov012_0205ba48(void)
{
    push    {r3, lr}
    bl      func_ov012_0205b8fc
    cmp     r0, #0
    beq     L_func_ov012_0205ba48_000e
    mov     r0, #1
    pop     {r3, pc}
L_func_ov012_0205ba48_000e:
    mov     r0, #0
    pop     {r3, pc}
}
