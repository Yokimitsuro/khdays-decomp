extern void func_ov002_020767ec(void);

asm void func_ov017_020804b4(void)
{
    push    {r3, lr}
    ldr     r1, [r0, #8]
    add     r1, #0x4c
    ldrh    r1, [r1, #0]
    cmp     r1, #8
    beq     _L_0012
    cmp     r1, #0x15
    beq     _L_0018
    pop     {r3, pc}
_L_0012:
    bl      func_ov002_020767ec
    pop     {r3, pc}
_L_0018:
    bl      func_ov002_020767ec
    pop     {r3, pc}
}
