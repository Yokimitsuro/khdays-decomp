extern int func_0201e4a8(int, int);
extern char data_ov029_020b3200[];

asm void func_ov029_020b2f40(int x)
{
    push    {r4, lr}
    add     r4, r0, #0
    mov     r0, #0
    add     r1, r4, #0
    bl      func_0201e4a8
    ldr     r2, =data_ov029_020b3200
    mov     r1, #0
_lp:
    ldr     r0, [r2, #0]
    cmp     r4, r0
    bne     _nx
    mov     r2, #0
    ldr     r0, =data_ov029_020b3200
    mvn     r2, r2
    lsl     r1, r1, #2
    str     r2, [r0, r1]
    pop     {r4, pc}
_nx:
    add     r1, r1, #1
    add     r2, r2, #4
    cmp     r1, #4
    blt     _lp
    pop     {r4, pc}
}
