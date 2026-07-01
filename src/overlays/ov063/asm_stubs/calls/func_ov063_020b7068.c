extern void func_0202a7dc(void);
extern void func_ov063_020b6310(void);

asm void func_ov063_020b7068(void)
{
    push    {r4, lr}
    add     r4, r0, #0
    add     r0, #0x18
    bl      func_0202a7dc
    mov     r0, #0x4a
    lsl     r0, r0, #2
    add     r0, r4, r0
_L_0010:
    bl      func_0202a7dc
    add     r0, r4, #0
_L_0016:
    bl      func_ov063_020b6310
    pop     {r4, pc}
}
