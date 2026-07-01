extern void func_0202bc30(void);

asm void func_ov021_02080650(void)
{
    mov     r1, #0x49
    lsl     r1, r1, #2
    ldr     r3, [pc, #4]
    add     r0, r0, r1
    bx      r3
    mov     r8, r8
    dcd     func_0202bc30
}
