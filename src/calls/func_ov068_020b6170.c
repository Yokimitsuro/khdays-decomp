extern void func_ov068_020b63ac(void);
extern void func_ov068_020b6600(void);
extern void *data_ov068_020b7500;

asm void func_ov068_020b6170(void)
{
    stmfd   sp!, {r3, r4, r5, lr}
    ldr     r2, =data_ov068_020b7500
    mov     r5, r0
    add     r1, r5, #0x2a00
    ldr     r3, [r2]
    ldrsh   r2, [r1, #0xba]
    add     r4, r3, #0xfc
    add     r1, r4, #0x2c00
    bl      func_ov068_020b63ac
    mov     r0, r5
    add     r1, r4, #0x2c00
    bl      func_ov068_020b6600
    ldmfd   sp!, {r3, r4, r5, pc}
}
