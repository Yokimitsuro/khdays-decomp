extern void func_02021980(void);
extern void func_ov012_0205b214(void);

asm void func_ov012_0205b984(void)
{
    push    {r4, r5, r6, lr}
    add     r4, r1, #0
    add     r5, r0, #0
    bl      func_02021980
    add     r4, #8
    add     r6, r0, #0
    add     r0, r5, #0
    add     r1, r4, #0
    bl      func_02021980
    add     r1, r0, #0
    add     r0, r6, #0
    bl      func_ov012_0205b214
    mov     r0, #6
    pop     {r4, r5, r6, pc}
}
