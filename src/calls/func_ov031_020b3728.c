extern void func_ov031_020b3d30(void);
extern void func_ov031_020b3dbc(void);

asm void func_ov031_020b3728(void)
{
    stmdb   sp!, {r4, lr}
    mov     r4, r0
    add     r1, r4, #0x2a00
    ldrsh   r2, [r1, #0xba]
    add     r1, r4, #0x2c
    add     r1, r1, #0x2c00
    bl      func_ov031_020b3d30
    add     r1, r4, #0x2c
    mov     r0, r4
    add     r1, r1, #0x2c00
    bl      func_ov031_020b3dbc
    ldmia   sp!, {r4, pc}
}
