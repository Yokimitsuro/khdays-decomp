extern void func_02021948(void);
extern void func_02021980(void);
extern void func_ov002_0206aeb8(void);

asm void func_ov069_020b84dc(void)
{
    push    {r4, r5, r6, lr}
    add     r4, r1, #0
    add     r5, r0, #0
    bl      func_02021948
    add     r4, #8
    add     r6, r0, #0
    add     r0, r5, #0
    add     r1, r4, #0
    bl      func_02021980
    add     r1, r0, #0
    add     r0, r6, #0
    mov     r2, #0
    mov     r3, #9
    bl      func_ov002_0206aeb8
    ldr     r1, [pc, #0x14]
    mov     r0, #3
    ldrh    r2, [r1, #0]
    bic     r2, r0
    strh    r2, [r1, #0]
    sub     r1, r1, #4
    ldrh    r2, [r1, #0]
    bic     r2, r0
    strh    r2, [r1, #0]
    mov     r0, #1
    pop     {r4, r5, r6, pc}
    dcd     0x0400000e
}
