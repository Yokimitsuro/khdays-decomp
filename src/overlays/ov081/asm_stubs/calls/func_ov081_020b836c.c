#pragma thumb on

extern void func_ov022_0209fb60(void *p, int a, int b);
extern void func_ov022_0209fb98(void *p, int a, int b);

asm void func_ov081_020b836c(void *r0)
{
    push    {r4, lr}
    add     r4, r0, #0
    mov     r1, #0
    mov     r2, #1
    bl      func_ov022_0209fb60
    add     r0, r4, #0
    mov     r1, #0
    mov     r2, #1
    bl      func_ov022_0209fb98
    ldr     r1, [pc, #0x14]
    ldrsb   r0, [r4, r1]
    cmp     r0, #0
    beq     _L_2a
    sub     r0, r1, #1
    ldrb    r2, [r4, r0]
    mov     r0, #1
    orr     r2, r0
    sub     r0, r1, #1
    strb    r2, [r4, r0]
_L_2a:
    pop     {r4, pc}
    dcd     0x00000da9
}
