extern int func_ov002_0206d448(void);
extern int func_ov002_0206d424(void);
extern int func_ov002_02057390(int);
extern int func_ov002_0206d3ec(int, int);
extern int func_ov002_020573a4(void);

asm void func_ov019_0207fc88(void)
{
    push    {r3, lr}
    bl      func_ov002_0206d448
    cmp     r0, #0
    beq     _a
    mov     r0, #1
    pop     {r3, pc}
_a:
    mov     r0, #0
    bl      func_ov002_0206d424
    cmp     r0, #0
    beq     _b
    mov     r0, #1
    bl      func_ov002_02057390
    mov     r0, #0
    add     r1, r0, #0
    bl      func_ov002_0206d3ec
_b:
    bl      func_ov002_020573a4
    cmp     r0, #0
    beq     _c
    mov     r0, #1
    pop     {r3, pc}
_c:
    mov     r0, #0
    pop     {r3, pc}
}
