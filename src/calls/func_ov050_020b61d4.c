extern void func_ov050_020b688c(void);

asm void func_ov050_020b61d4(void)
{
    stmdb   sp!, {r4, lr}
    mov     r4, r1
    bl      func_ov050_020b688c
    mov     r1, #0
    mov     r0, r1
_loop:
    add     r1, r1, #1
    str     r0, [r4, #0x10]
    cmp     r1, #2
    add     r4, r4, #0x118
    blt     _loop
    ldmia   sp!, {r4, pc}
}
