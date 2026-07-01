extern void func_ov012_0205b258(void);
extern void func_ov024_02084e68(void);

asm void func_ov012_0205b9e0(void)
{
    push    {r4, lr}
    add     r4, r1, #0
    bl      func_ov012_0205b258
    cmp     r0, #0
    bne     L_func_ov012_0205b9e0_0010
    mov     r0, #1
    pop     {r4, pc}
L_func_ov012_0205b9e0_0010:
    cmp     r4, #0
    bne     L_func_ov012_0205b9e0_0018
    mov     r0, #0
    pop     {r4, pc}
L_func_ov012_0205b9e0_0018:
    bl      func_ov024_02084e68
    cmp     r0, r4
    bge     L_func_ov012_0205b9e0_0024
    mov     r0, #0
    pop     {r4, pc}
L_func_ov012_0205b9e0_0024:
    mov     r0, #1
    pop     {r4, pc}
}
