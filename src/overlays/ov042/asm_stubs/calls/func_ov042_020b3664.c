extern void func_ov042_020b4388(void);
extern void func_ov042_020b43fc(void);

asm void func_ov042_020b3664(void)
{
    stmdb   sp!, {r3, r4, r5, lr}
    mov     r5, r0
    add     r1, r5, #0x2a00
    ldrsh   r2, [r1, #0xba]
    add     r4, r5, #0x2c
    add     r1, r4, #0x2c00
    bl      func_ov042_020b4388
    mov     r0, r5
    add     r1, r4, #0x2c00
    bl      func_ov042_020b43fc
    ldmia   sp!, {r3, r4, r5, pc}
}
