extern int func_02021980(void);
extern int func_020235e8(int, int, int);

asm void func_ov019_0207fcc0(void)
{
    push    {r3, lr}
    bl      func_02021980
    add     r2, r0, #0
    mov     r0, #0x82
    lsl     r2, r2, #0x10
    lsl     r0, r0, #6
    mov     r1, #5
    lsr     r2, r2, #0x10
    bl      func_020235e8
    mov     r0, #0
    pop     {r3, pc}
}
