extern void func_0202ba9c(void);
extern void func_ov002_0207285c(void);

asm void func_ov021_02080738(void)
{
    push    {r4, lr}
    add     r4, r0, #0
    ldrb    r0, [r4, #0x10]
    bl      func_ov002_0207285c
    add     r1, r0, #0
    mov     r0, #0x49
    lsl     r0, r0, #2
    lsl     r1, r1, #0x10
    mov     r2, #0
    add     r0, r4, r0
    lsr     r1, r1, #0x10
    add     r3, r2, #0
    bl      func_0202ba9c
    pop     {r4, pc}
}
