extern void func_ov070_020b8c10(void);
extern void func_ov070_020b8c9c(void);

asm void func_ov070_020b8608(void)
{
    stmdb   sp!, {r4, lr}
    mov     r4, r0
    add     r1, r4, #0x2a00
    ldrsh   r2, [r1, #0xba]
    add     r1, r4, #0x2c
    add     r1, r1, #0x2c00
    bl      func_ov070_020b8c10
    add     r1, r4, #0x2c
    mov     r0, r4
    add     r1, r1, #0x2c00
    bl      func_ov070_020b8c9c
    ldmia   sp!, {r4, pc}
}
