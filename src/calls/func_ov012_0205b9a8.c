extern void func_02021980(void);
extern void func_020219b4(void);
extern void func_ov012_0205b258(void);
extern void func_ov024_02084e68(void);

asm void func_ov012_0205b9a8(void)
{
    push    {r3, r4, r5, lr}
    add     r5, r0, #0
    bl      func_02021980
    add     r4, r0, #0
    add     r0, r5, #0
    add     r1, r4, #0
    bl      func_020219b4
    bl      func_ov012_0205b258
    cmp     r0, #0
    bne     L_func_ov012_0205b9a8_001e
    mov     r0, #1
    pop     {r3, r4, r5, pc}
L_func_ov012_0205b9a8_001e:
    cmp     r4, #0
    bne     L_func_ov012_0205b9a8_0026
    mov     r0, #0
    pop     {r3, r4, r5, pc}
L_func_ov012_0205b9a8_0026:
    bl      func_ov024_02084e68
    cmp     r0, r4
    bge     L_func_ov012_0205b9a8_0032
    mov     r0, #0
    pop     {r3, r4, r5, pc}
L_func_ov012_0205b9a8_0032:
    mov     r0, #1
    pop     {r3, r4, r5, pc}
}
