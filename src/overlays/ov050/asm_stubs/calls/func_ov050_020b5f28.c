extern void func_ov050_020b6530(void);
extern void func_ov050_020b65bc(void);

asm void func_ov050_020b5f28(void)
{
    stmdb   sp!, {r4, lr}
    mov     r4, r0
    add     r1, r4, #0x2a00
    ldrsh   r2, [r1, #0xba]
    add     r1, r4, #0x2c
    add     r1, r1, #0x2c00
    bl      func_ov050_020b6530
    add     r1, r4, #0x2c
    mov     r0, r4
    add     r1, r1, #0x2c00
    bl      func_ov050_020b65bc
    ldmia   sp!, {r4, pc}
}
