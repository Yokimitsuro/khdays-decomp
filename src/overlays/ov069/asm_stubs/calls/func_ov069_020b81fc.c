extern void func_020235d0(void);

asm void func_ov069_020b81fc(void)
{
    push    {r3, lr}
    lsl     r1, r0, #1
    add     r1, r0, r1
    ldr     r0, [pc, #0x14]
    add     r0, r1, r0
    mov     r1, #3
    bl      func_020235d0
    cmp     r0, #0
    beq     _L_0018
    mov     r0, #1
    pop     {r3, pc}
_L_0018:
    mov     r0, #0
    pop     {r3, pc}
    cmp     r2, #0x4c
    lsl     r0, r0, #0
}
