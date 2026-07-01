extern void func_ov042_020b465c(void);

asm void func_ov042_020b43fc(void)
{
    stmdb   sp!, {r3, r4, r5, lr}
    add     r5, r1, #0x14
    mov     r4, #0
_020b43fc_loop:
    mov     r0, r5
    bl      func_ov042_020b465c
    add     r4, r4, #1
    cmp     r4, #7
    add     r5, r5, #0x10c
    blt     _020b43fc_loop
    ldmia   sp!, {r3, r4, r5, pc}
}
